#include "LHEF.h"

#include "Delphes.C"
#include "Delphes_help_func.C"

float match_metric(TLorentzVector t1, TLorentzVector t2){
  return t1.DeltaR( t2 );
};

int get_best_match(TLorentzVector t, vector<TLorentzVector> v2, set<int> & used_indexes, float threshold = 0.2){
  float v_min = 99999;
  int index = -1;
  for( int i = 0; i < v2.size(); ++i ){
    if( used_indexes.count(i) ) continue;
    float val = match_metric(t, v2.at(i));
    if( val > v_min ) continue; 
    v_min = val;
    index = i;
  }
  
  if(threshold < v_min) index = -1;
  return index;
};

map<int,int> match_multiple( vector<TLorentzVector> v1, vector<TLorentzVector> v2, float threshold = 0.3){
  map<int,int> match;
  float best_total_metric = 9999;

  //vector< vector<int> > permutatiuons;

  //for( auto permutation : permutatiuons ){
    map<int,int> match_temp;

    float total_metric = 0;
    set<int> used_indexes;
    for( int i = 0; i < v1.size(); ++i ){
      int i_0 = i; // permutation[ i ];

      int j     = get_best_match( v1.at( i_0 ), v2, used_indexes, threshold );
      //float val = 3;
      if( j != -1 ) match_metric( v1.at( i_0 ), v2.at(j) );
      //total_metric += val;
      used_indexes.insert( j );

      match_temp[ i_0 ] = j;
    }

  return match_temp;
    ////if( best_total_metric < total_metric ) continue;
    //match = match_temp;
    //total_metric = best_total_metric;
  //}

  //return match;
};

double calc_metric(TLorentzVector Wl, TLorentzVector tl, TLorentzVector Wq, TLorentzVector tq, TLorentzVector H){
  double val  = TMath::Power((Wl.M() - 80)/80, 2) + TMath::Power((Wq.M() - 80)/80, 2);
         val += TMath::Power((tl.M() - 174)/174, 2) + TMath::Power((tl.M() - 174)/174, 2);
         val += TMath::Power((H.M() - 125)/125, 2);
  return val; 
};

struct full_reco_events{
  double metric;
  TLorentzVector Wl, tl, Wq, tq, H, Y, X;

  void set(double metric_, TLorentzVector Wl_, TLorentzVector tl_, TLorentzVector Wq_, TLorentzVector tq_, TLorentzVector H_, TLorentzVector Y_, TLorentzVector X_){
    metric = metric_;
    Wl = Wl_;
    tl = tl_;
    Wq = Wq_;
    tq = tq_;
    H  = H_ ;
    Y = Y_;
    X = X_;
  }
};

void matcher( string file, string file_tbar, string ofile_name, string file_from_lhe_t = "", string file_from_lhe_tbar = "" ) {
  vector<string> delphes_files = { file,            file_tbar          } ;
  vector<string> lhe_files     = { file_from_lhe_t, file_from_lhe_tbar } ;

  TFile * ofile = TFile::Open( ofile_name.c_str(), "RECREATE" );
  TTree * tree_out = new TTree("out_tree", "out_tree");
  UInt_t Jet_matches[ 30 ];
  TBranch* my_new_branch = tree_out->Branch( "JetMatches", Jet_matches, "Jet_matches[30]/i" );

  TH1D * matching_size = new TH1D("matching_size", "matching_size", 20, 0, 20);
  TH1D * matching_distr = new TH1D("matching_distr", "matching_distr", 20, 0, 20);
  TH1D * matching_prob = new TH1D("matching_prob", "matching_prob", 10, 0, 10);

  TFile * file1 = TFile::Open( delphes_files.at(0).c_str() );
  TTree * tree1 = (TTree*) file1->Get("Delphes");
  int n1 = tree1->GetEntries();
  file1->Close();

  TFile * file2 = TFile::Open( delphes_files.at(1).c_str() );
  TTree * tree2 = (TTree*) file2->Get("Delphes");
  int n2 = tree2->GetEntries();
  file2->Close();
  
  float weight_1 = 0.5 / n1;
  float weight_2 = 0.5 / n2;
  vector<float> weights = { weight_1, weight_2 };
  cout << n1 << " " << n2 << " " << weight_1 << " " << weight_2 << endl;

  for(int i = 0; i < delphes_files.size(); i++){
    float weight = weights.at( i );
    bool t_lepton = (i == 0);

    TFile * file = TFile::Open( delphes_files.at(i).c_str() );
    TTree * tree = (TTree*) file->Get("Delphes");
    Delphes * reader = new Delphes( tree );

    ftlv_write = false;
    TFile * file_lhe = 0;
    TTree * tree_lhe = 0;
    string file_from_lhe = lhe_files.at(i);
    if( file_from_lhe.size() and true){
      file_lhe = TFile::Open( file_from_lhe.c_str() );
      tree_lhe = (TTree*) file_lhe->Get("ttree");
    }
    cout << file_lhe << " " << tree_lhe << " " << tree_lhe->GetEntries() << endl;

    ftlv H("H", tree_lhe), Y("Y", tree_lhe), X("X", tree_lhe), Y_reco("Y_reco", tree_lhe), X_reco("X_reco", tree_lhe);
    ftlv t("t", tree_lhe), tbar("tbar", tree_lhe),  t_l_reco("t_l_reco", tree_lhe), b_H("b_H", tree_lhe), bbar_H("bbar_H", tree_lhe), v("v", tree_lhe), l("l", tree_lhe), q("q", tree_lhe), qbar("qbar", tree_lhe);
    ftlv W("W", tree_lhe), Wbar("Wbar", tree_lhe), W_l_reco("W_l_reco", tree_lhe), b_t("b_t", tree_lhe), bbar_t("bbar_t", tree_lhe);

    Long64_t entrys = tree->GetEntries();
    cout << "entrys = " << entrys << endl;

    Long64_t entry = 0;
    for(;entry < entrys;entry++){
      if( not (entry % 10000) )
        cout << entry << "/" << entrys << endl;

      file->cd();
      reader->GetEntry(entry);

      if( file_lhe ){
        file_lhe->cd();
        tree_lhe->GetEntry(entry);
        for(ftlv * f : ftlvs){
          f->load_tlv();
          // cout << f->tlv.Pt() << endl;
        }
      }
      
      // OBJECT SELECTIONS ==============================================
      /*
      vector<int> lepton_particle_candidates;
      for(int i = 0; i < reader->Particle_; i++){
        if( reader->Particle_Status[i] != 1 ) continue;
        if( abs(reader->Particle_PID[i]) < 11 or abs(reader->Particle_PID[i]) > 15 ) continue;
        if( abs(reader->Particle_PID[i]) % 2 != 1 ) continue;
        if( TMath::Abs(reader->Particle_Eta[i]) > 2.4 ) continue;
        if( TMath::Abs(reader->Particle_PT[i]) < 10 ) continue; 
        lepton_particle_candidates.push_back(i);
      }
      */

      vector<int> lepton_veto_candidates;
      // muon candidates --- --- --- --- --- --- --- 
      for(int i = 0; i < reader->Muon_; i++){
        if( reader->Muon_PT[i] < 15 ) continue;
        if( TMath::Abs(reader->Muon_Eta[i]) > 2.1 ) continue;
        if( reader->Muon_IsolationVar[i] > 0.15 ) continue; 
        lepton_veto_candidates.push_back(i);
      }

      // electron candidates --- --- --- --- --- --- --- 
      for(int i = 0; i < reader->Electron_; i++){
        if( reader->Electron_PT[i] < 15 ) continue;
        if( TMath::Abs(reader->Electron_Eta[i]) > 2.1 ) continue; 
        if( TMath::Abs(reader->Electron_Eta[i]) > 1.4442 and TMath::Abs(reader->Electron_Eta[i]) < 1.5560 ) continue; 
        if( reader->Electron_IsolationVar[i] > 0.06 ) continue; 
        lepton_veto_candidates.push_back(i);
      }

      // muon candidates --- --- --- --- --- --- --- 
      vector<int> muon_candidates;
      for(int i = 0; i < reader->Muon_; i++){
        if( reader->Muon_PT[i] < 30 ) continue;
        if( TMath::Abs(reader->Muon_Eta[i]) > 2.1 ) continue;
        if( reader->Muon_IsolationVar[i] > 0.15 ) continue; 
        muon_candidates.push_back(i);
      }

      // electron candidates --- --- --- --- --- --- --- 
      vector<int> electron_candidates;
      for(int i = 0; i < reader->Electron_; i++){
        if( reader->Electron_PT[i] < 26 ) continue;
        if( TMath::Abs(reader->Electron_Eta[i]) > 2.1 ) continue; 
        if( TMath::Abs(reader->Electron_Eta[i]) > 1.4442 and TMath::Abs(reader->Electron_Eta[i]) < 1.5560 ) continue; 
        if( reader->Electron_IsolationVar[i] > 0.06 ) continue; 
        electron_candidates.push_back(i);
      }
      // cout << electron_candidates.size() << " " << muon_candidates.size() << " " << lepton_particle_candidates.size() << endl;

      // jet candidates --- --- --- --- --- --- --- 
      vector<int> jet_candidates;
      for(int i = 0; i < reader->Jet_; i++){
        if( reader->Jet_PT[i] < 30 ) continue;
        if( TMath::Abs(reader->Jet_Eta[i]) > 2.4 ) continue;
        jet_candidates.push_back(i);
      }

      vector<int> ljet_candidates;
      vector<int> bjet_candidates;
      for(auto i : jet_candidates){
        if( not reader->Jet_BTag[i] ) ljet_candidates.push_back(i);
        else bjet_candidates.push_back(i);
      }

      TLorentzVector nu0 = make_met(reader, 0);

      // BASIC EVENT SELECTIONS ==============================================
      // RECONSTRUCTIONS ==============================================
      vector<TLorentzVector> ljets_tlvs, bjets_tlvs, jets_tlvs; 

      get_tlvs_jets( reader, ljet_candidates, ljets_tlvs );
      get_tlvs_jets( reader, bjet_candidates, bjets_tlvs );
      get_tlvs_jets( reader,  jet_candidates,  jets_tlvs );

      TLorentzVector b_H_match, bbar_H_match, b_t_match, bbar_t_match, q_match, qbar_match, qq_match;
      if( true and file_lhe ){
        map<int,int> b_matchs = match_multiple( {b_H.tlv, bbar_H.tlv, b_t.tlv, bbar_t.tlv, q.tlv, qbar.tlv}, jets_tlvs, 0.4 );
        for(int j = 0; j < 30; j++){
          Jet_matches[j] = 0;
        }
      
        int msize = 0;
        if( b_matchs[0] != -1 ) { Jet_matches[ jet_candidates[b_matchs[0]] ] = 1; msize++; matching_distr->Fill(jet_candidates[b_matchs[0]], weight); matching_prob->Fill(1, weight); }
        if( b_matchs[1] != -1 ) { Jet_matches[ jet_candidates[b_matchs[1]] ] = 2; msize++; matching_distr->Fill(jet_candidates[b_matchs[1]], weight); matching_prob->Fill(2, weight); }
        if( b_matchs[2] != -1 ) { Jet_matches[ jet_candidates[b_matchs[2]] ] = 3; msize++; matching_distr->Fill(jet_candidates[b_matchs[2]], weight); matching_prob->Fill(3, weight); }
        if( b_matchs[3] != -1 ) { Jet_matches[ jet_candidates[b_matchs[3]] ] = 4; msize++; matching_distr->Fill(jet_candidates[b_matchs[3]], weight); matching_prob->Fill(4, weight); }
        if( b_matchs[4] != -1 ) { Jet_matches[ jet_candidates[b_matchs[4]] ] = 5; msize++; matching_distr->Fill(jet_candidates[b_matchs[4]], weight); matching_prob->Fill(5, weight); }
        if( b_matchs[5] != -1 ) { Jet_matches[ jet_candidates[b_matchs[5]] ] = 6; msize++; matching_distr->Fill(jet_candidates[b_matchs[5]], weight); matching_prob->Fill(6, weight); }

        matching_size->Fill( msize, weight );

        if(entry < 10){
          for(int j = 0; j < 30; j++){
            cout << Jet_matches[j] << " ";
          }
          cout << endl;
        }

        ofile->cd();
        tree_out->Fill();

      }
    }
    file->Close();
  }
  tree_out->Write();
  ofile->Write();
}




