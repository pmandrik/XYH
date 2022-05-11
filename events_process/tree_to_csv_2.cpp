#include "LHEF.h"
#include "Delphes.C"
#include "Delphes_help_func.C"

// TODO
// read tree with matching and tree with event content
// write matching result and jets and leptons variables
// output = matching result per 8 first jets (pt eta phi m) btag integer
//                                    lepton (pt eta phi m) e/mu tag
//                                        nu (pt eta phi)
//                                   wl reco (pt eta phi M)
// resonanses energy Y, X
// 

void tree_to_csv( string file_t, string file_tbar, string file_matcher = "", string ofile_name = "" ) {
  vector<string> delphes_files = { file_t,            file_tbar          } ;

  std::ofstream myfile;
  myfile.open ( ofile_name );
  vector<string> header;

      for(int j = 0; j < 10; j++){
          header.push_back( "JetMatch" + to_string(j) + "_H" );
          header.push_back( "JetMatch" + to_string(j) + "_tq" );
          header.push_back( "JetMatch" + to_string(j) + "_tl" );
      }
      for(int i = 0; i < 10; i++){
        header.push_back( "JetPt" + to_string(i) );
        header.push_back( "JetEta" + to_string(i) );
        header.push_back( "JetPhi" + to_string(i) );
        header.push_back( "JetM" + to_string(i) );
        header.push_back( "JetBtag" + to_string(i) );
      }
  vector<string> header2 = { "nuPt", "nuPhi", "lPt", "lEta", "lPhi", "Nmu", "Ne", "wlPt", "WlEta", "WlPhi", "WlM" };


  for(auto item : header){
    myfile << item << " ";
  }
  for(auto item : header2){
    myfile << item << " ";
  }
  myfile << "\n";

  TFile * fmatcher = TFile::Open( file_matcher.c_str(), "READ" );
  TTree * tmatcher = (TTree*)fmatcher->Get("out_tree");
  UInt_t Jet_matches[ 30 ];
  tmatcher->SetBranchAddress("JetMatches",&Jet_matches);

  for(int i = 0; i < delphes_files.size(); i++){
    bool t_lepton = (i == 0);

    TFile * file = TFile::Open( delphes_files.at(i).c_str() );
    TTree * tree = (TTree*) file->Get("Delphes");
    Delphes * reader = new Delphes( tree );

    Long64_t entrys = tree->GetEntries();
    cout << "entrys = " << entrys << endl;

    Long64_t entry_total = 0;
    Long64_t entry = 0;
    for(;entry < entrys;entry++){
      if( not (entry % 10000) )
        cout << entry << "/" << entrys << endl;

      // if( entry > 1000 ) break;

      fmatcher->cd();
      tmatcher->GetEntry(entry_total);
      entry_total++;

      file->cd();
      reader->GetEntry(entry);

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

      // BASIC EVENT SELECTIONS ==============================================
      // RECONSTRUCTIONS ==============================================
      vector<TLorentzVector> ljets_tlvs, bjets_tlvs, jets_tlvs; 

      get_tlvs_jets( reader, ljet_candidates, ljets_tlvs );
      get_tlvs_jets( reader, bjet_candidates, bjets_tlvs );
      get_tlvs_jets( reader,  jet_candidates,  jets_tlvs );

      for(int j = 0; j < 10; j++){
          myfile << ((Jet_matches[j] == 1) || (Jet_matches[j] == 2)) << " ";
          myfile << ((Jet_matches[j] == 5) || (Jet_matches[j] == 6) || ((Jet_matches[j] == 4) && t_lepton) || ((Jet_matches[j] == 3) && not t_lepton)) << " ";
          myfile << (((Jet_matches[j] == 3) && t_lepton) || ((Jet_matches[j] == 4) && not t_lepton)) << " ";

          // header.push_back( "JetMatch" + to_string(j) + "_H" );
          // header.push_back( "JetMatch" + to_string(j) + "_tq" );
          // header.push_back( "JetMatch" + to_string(j) + "_tl" );
      }

      for(int j = 0; j < 10; j++){
        TLorentzVector jet;
        if( j < jet_candidates.size() ){
          int jet_index = jet_candidates[ j ];
          TLorentzVector jet = jets_tlvs[ j ] ;
          
          myfile << TMath::Log( jet.Pt() + 1) << " " << jet.Eta()/2.5 << " " << jet.Phi()/3.15 << " " << TMath::Log(jet.M() + 1) << " " ;
          myfile << reader->Jet_BTag[ jet_index ] << " ";
        } else {
          myfile << 0 << " " << 0 << " " << 0 << " " << 0 << " " ;
          myfile << -1  << " " ;
        }
      }

      TLorentzVector l;
      if( muon_candidates.size() )  l = make_muon(reader, muon_candidates.at(0));
      else if( electron_candidates.size() ) l = make_electron(reader, electron_candidates.at(0));
      // else continue;
      TLorentzVector nu0 = make_met(reader, 0);
      TLorentzVector tl, nu, Wl;

      if( muon_candidates.size() + electron_candidates.size() )
        reconstruct_decay(80, l, nu0, nu, Wl);

      myfile << TMath::Log(nu0.Pt()) << " " << nu0.Phi()/3.15 << " " << TMath::Log(l.Pt() + 1) << " " << l.Eta()/2.5 << " " << l.Phi()/3.15 << " " << muon_candidates.size() << " " << electron_candidates.size() << " " << TMath::Log(Wl.Pt() + 1) << " " << Wl.Eta()/2.5 << " " << Wl.Phi()/3.15 << " " << TMath::Log(Wl.M() + 1) << " ";
      myfile << endl;
    }
    file->Close();
  }
  fmatcher->Close();
  myfile.close();
}

void create_csv( string file_from_lhe, string file_out_name ){
  TFile * file_lhe = TFile::Open( file_from_lhe.c_str() );
  TTree * tree = (TTree*) file_lhe->Get("ttree");
  cout << tree << endl;

  ftlv_write = false;
  ftlv_clear();
  ftlv H("H", tree), Y("Y", tree), X("X", tree), Y_reco("Y_reco", tree), X_reco("X_reco", tree);
  ftlv t("t", tree), tbar("tbar", tree),  t_l_reco("t_l_reco", tree), t_q_reco("t_q_reco", tree), b_H("b_H", tree), bbar_H("bbar_H", tree), v("v", tree), l("l", tree), q("q", tree), qbar("qbar", tree);
  ftlv W("W", tree), Wbar("Wbar", tree), W_l_reco("W_l_reco", tree), b_t("b_t", tree), bbar_t("bbar_t", tree);

  vector<string> header = {};
  vector<string> vnames = {};
  for(auto item : ftlvs_map){
    string name = item.first;
    vnames.push_back( name );
    header.push_back( name + "_Pt"  );
    header.push_back( name + "_Et"  );
    header.push_back( name + "_Mt"  );
    header.push_back( name + "_Eta" );
  }

  for(int i = 0; i < ftlvs.size(); i++){
    string name_1 = ftlvs.at(i)->name;
    for(int j = i+1; j < ftlvs.size(); j++){
      string name_2 = ftlvs.at(j)->name;
      if( name_1 == name_2 ) continue;
      header.push_back( "dR_" + name_1 + "_" + name_2 );
      header.push_back( "dEta_" + name_1 + "_" + name_2 );
      header.push_back( "dPhi_" + name_1 + "_" + name_2 );
    }
  }
  header.push_back( "nu_reco_dPz" );
  header.push_back( "nu_reco_dR" );
  header.push_back( "nu_reco_dEta" );
  header.push_back( "W_reco_dR" );
  header.push_back( "W_reco_dEta" );

  std::ofstream myfile;
  myfile.open ( file_out_name );
  for(auto item : header){
    myfile << item << " ";
  }
  myfile << "\n";

  file_lhe->cd();
  file_lhe->ls();
  Long64_t entrys = tree->GetEntries();
  Long64_t entry = 0;
  for(;entry < entrys;entry++){
    tree->GetEntry(entry);
    load_tlv();

    // Pt
    for( string name : vnames ){
      auto tlv = ftlvs_map.find( name )->second->tlv;
      myfile << tlv.Pt() << " ";
      myfile << tlv.Mt() << " ";
      myfile << tlv.Mt() << " ";
      myfile << tlv.Eta() << " ";
    }

    for(int i = 0; i < ftlvs.size(); i++){
      string name_1 = ftlvs.at(i)->name;
      auto tlv1 = ftlvs_map.find( name_1 )->second->tlv;
      for(int j = i+1; j < ftlvs.size(); j++){
        string name_2 = ftlvs.at(j)->name;
        if( name_1 == name_2 ) continue;
        auto tlv2 = ftlvs_map.find( name_2 )->second->tlv;
        myfile << tlv1.DeltaR( tlv2 ) << " ";
        myfile << tlv1.Eta() - tlv2.Eta() << " ";
        myfile << tlv1.DeltaPhi( tlv2 ) << " ";
      }
    }

    auto v_tlv = ftlvs_map.find( "v" )->second->tlv;
    auto l_tlv = ftlvs_map.find( "l" )->second->tlv;
    auto W_tlv = v_tlv + l_tlv;
    TLorentzVector v_0;
    v_0.SetPxPyPzE(v_tlv.Px(),v_tlv.Py(),0, TMath::Sqrt( v_tlv.Px()*v_tlv.Px() + v_tlv.Py()*v_tlv.Py() ) );
    TLorentzVector v_tlv_answer, W_tlv_answer;
    reconstruct_decay(80.379, l_tlv, v_tlv, v_tlv_answer, W_tlv_answer);

    myfile << (v_tlv_answer.Pz() - v_tlv.Pz())/v_tlv.Pz() << " ";
    myfile << v_tlv_answer.DeltaR( v_tlv ) << " ";
    myfile << v_tlv_answer.Eta() - v_tlv.Eta() << " ";
    myfile << W_tlv_answer.DeltaR( W_tlv ) << " ";
    myfile << W_tlv_answer.Eta() - W_tlv.Eta() << " ";

    myfile << "\n";
  }

  file_lhe->Close();
  myfile.close();
}

void rrr(){

  vector< pair<int,int> > XY_mass = get_XY_mass("");

  string path     = "/home/pmandrik/work/projects/XYZ/XYH/events_process/after_lhe/";
  string path_out = "/home/pmandrik/work/projects/XYZ/XYH/events_process/after_lhe_hlv/";
  int files = 0;
  for( pair<int,int> XYm : XY_mass ){
    int Xm = XYm.first;
    int Ym = XYm.second;

    string file_from_lhe = path + "NMSSM_XYH_ttbb_MX_" + to_string(Xm) + "_MY_" + to_string(Ym) + "_t_l.root";
    string file_out      = path_out + "NMSSM_XYH_ttbb_MX_" + to_string(Xm) + "_MY_" + to_string(Ym) + "_t_l.csv";
    cout << "process " << Xm << " " << Ym << " " << file_from_lhe << endl;
    create_csv( file_from_lhe, file_out );

    file_from_lhe = path + "NMSSM_XYH_ttbb_MX_" + to_string(Xm) + "_MY_" + to_string(Ym) + "_tbar_l.root";
    file_out      = path_out + "NMSSM_XYH_ttbb_MX_" + to_string(Xm) + "_MY_" + to_string(Ym) + "_tbar_l.csv";
    cout << "process " << Xm << " " << Ym << " " << file_from_lhe << endl;
    create_csv( file_from_lhe, file_out );

    files++;
  }
}

