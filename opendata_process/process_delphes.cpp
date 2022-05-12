//#include "LHEF.h"

#include "Events_myelectrons.C"
#include "Events_myjets.C"
#include "Events_mymets.C"
#include "Events_mymuons.C"

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
      float val = 3;
      if( j != -1 ) match_metric( v1.at( i_0 ), v2.at(j) );
      total_metric += val;
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

void process_delphes( string file, string ofile_name, string file_from_lhe = "", string scv_file_name = "", string input_train_name = "" ) {
  vector<string> delphes_files = { file };

  // for csv ==========================================================
    std::ifstream infile;
    if( input_train_name.size() ){
      infile = std::ifstream( input_train_name );
    }

    std::ofstream myfile;
    myfile.open ( scv_file_name );
    vector<string> header;

        for(int j = 0; j < 8; j++){
            header.push_back( "JetMatch" + to_string(j) + "_H" );
            header.push_back( "JetMatch" + to_string(j) + "_tq" );
            header.push_back( "JetMatch" + to_string(j) + "_tl" );
        }
        for(int i = 0; i < 8; i++){
          header.push_back( "JetPt" + to_string(i) );
          header.push_back( "JetEta" + to_string(i) );
          header.push_back( "JetPhi" + to_string(i) );
          header.push_back( "JetM" + to_string(i) );
          header.push_back( "JetBtag" + to_string(i) );
        }
        for(int j = 0; j < 8; j++){
          for(int k = j; k < 8; k++){
            header.push_back( "Jet" + to_string(j) + "N" + to_string(k) + "_M" );
            header.push_back( "Jet" + to_string(j) + "N" + to_string(k) + "_dR" );
          }
        }
    vector<string> header2 = { "nuPt", "nuPhi", "lPt", "lEta", "lPhi", "Nmu", "Ne", "wlPt", "WlEta", "WlPhi", "WlM" };


    for(auto item : header){
      myfile << item << " ";
    }
    for(auto item : header2){
      myfile << item << " ";
    }
    myfile << "\n";
  // end csv ==========================================================

  TFile * ofile = TFile::Open( ofile_name.c_str(), "RECREATE" );
  TH1D * selections = new TH1D("selections", "selections", 100, 0, 100);
  TH1D * selections_nice = new TH1D("selections_nice", "selections_nice", 100, 0, 100);
  selections->Fill("Total", 0);
  selections->Fill("Total_X_Weight", 0);
  selections->Fill("Selected", 0);
  selections->Fill("Selected_X_Weight", 0);

  TH1D * hist_N_bjets = new TH1D("N_bjets", "N_bjets", 20, 0, 10);
  TH1D * hist_N_ljets = new TH1D("N_ljets", "N_ljets", 20, 0, 10);
  TH1D * hist_N_l     = new TH1D("N_l", "N_l", 20, 0, 4);

  TH1D * hist_qq_all  = new TH1D("qq_all",  "qq_all", 100, 0, 800);
  TH1D * hist_bqq_all = new TH1D("bqq_all", "bqq_all", 100, 0, 1000);
  TH1D * hist_bb_all  = new TH1D("bb_all",  "bb_all", 100, 0, 800);

  TH1D * hist_bb_all0  = new TH1D("bb_all0", "bb_all0", 100, 0, 800);
  TH1D * hist_qq_all0  = new TH1D("qq_all0", "qq_all0", 100, 0, 800);
  TH1D * hist_qqb_all0 = new TH1D("qqb_all0", "qqb_all0", 100, 0, 1000);

  TH1D * hist_nul_all   = new TH1D("nul_all", "nul_all", 100, 0, 500);
  TH1D * hist_blnu_all  = new TH1D("blnu_all", "blnu_all", 100, 0, 1000);
  TH1D * hist_tt_all    = new TH1D("tt_all", "tt_all", 200, 0, 3000);
  TH1D * hist_HY_all    = new TH1D("HY_all", "HY_all", 200, 0, 3000);

  // lhe vs reco
  TH1D * hist_Hb_dR     = new TH1D("lhe_Hb_dR_all", "lhe_Hb_dR_all", 100, 0, 10);
  TH1D * hist_Hbbar_dR  = new TH1D("lhe_Hbar_dR_all", "lhe_Hbar_dR_all", 100, 0, 10);

  TH1D * hist_Hb_dPt    = new TH1D("lhe_Hb_dPt", "lhe_Hb_dPt", 100, -3, 3);
  TH1D * hist_Hbbar_dPt = new TH1D("lhe_Hbbar_dPt", "lhe_Hbbar_dPt", 100, -3, 3);

  TH1D * hist_H_dPt     = new TH1D("lhe_H_dPt_all", "lheH_dPt_all", 100, -3, 3);
  TH1D * hist_H_dR      = new TH1D("lhe_H_dR_all", "lhe_H_dR_all", 100,  0, 10);

  TH2D * hist_H_dPt_x_m = new TH2D("lhe_H_dPt_x_dm_all", "lheH_dPt_x_dm_all", 100, -3, 3, 100, 0, 250);
  TH2D * hist_H_dR_x_m  = new TH2D("lhe_H_dR_x_dm_all", "lhe_H_dR_x_dm_all", 100,  0, 10, 100, 0, 250);

  TH1D * hist_q_dR       = new TH1D("hist_q_dR", "hist_q_dR", 100, 0, 10);
  TH1D * hist_q_dPt      = new TH1D("hist_q_dPt", "hist_q_dPt", 100, -3, 3);
  TH1D * hist_qbar_dR    = new TH1D("hist_qbar_dR", "hist_qbar_dR", 100, 0, 10);
  TH1D * hist_qbar_dPt   = new TH1D("hist_qbar_dPt", "hist_qbar_dPt", 100, -3, 3);
  TH1D * hist_qq_dPt     = new TH1D("hist_qq_dPt", "hist_qq_dPt", 100, -3, 3);
  TH1D * hist_qq_dR      = new TH1D("hist_qq_dR", "hist_qq_dR", 100, 0, 10);
  TH2D * hist_qq_dPt_x_m = new TH2D("lhe_qq_dPt_x_m_all", "lhe_qq_dPt_x_m_all", 100, -3, 3, 100, 0, 250);
  TH2D * hist_qq_dR_x_m  = new TH2D("lhe_qq_dR_x_m_all", "lhe_qq_dR_x_m_all", 100,  0, 10, 100, 0, 250);

  TH1D * hist_qqb_dR      = new TH1D("hist_qqb_dR", "hist_qqb_dR", 100, 0, 10);
  TH1D * hist_qqb_dPt     = new TH1D("hist_qqb_dPt", "hist_qqb_dPt", 100, -3, 3);
  TH2D * hist_bqq_dPt_x_m = new TH2D("hist_bqq_dPt_x_m", "hist_bqq_dPt_x_m", 100,  0, 10, 100, 0, 250);
  TH2D * hist_bqq_dR_x_m  = new TH2D("hist_bqq_dR_x_m", "hist_bqq_dR_x_m", 100,  0, 10, 100, 0, 250);

  TH1D * hist_bb_match = new TH1D("hist_bb_match", "hist_bb_match", 100, 0, 200);
  TH1D * hist_qqb_match = new TH1D("hist_qbb_match", "hist_qbb_match", 100, 0, 300);
  TH1D * hist_qqbar_match = new TH1D("hist_qbbar_match", "hist_qbbar_match", 100, 0, 300);
  TH1D * hist_qq_match    = new TH1D("hist_qq_match", "hist_qq_match", 100, 0, 200);

  TH1D * hist_wl_match = new TH1D("hist_wl_match", "hist_wl_match", 100, 0, 200);
  TH1D * hist_tl_match = new TH1D("hist_tl_match", "hist_tl_match", 100, 0, 300);
  TH1D * hist_Y_match = new TH1D("hist_Y_match", "hist_Y_match", 200, 300, 2000);
  TH1D * hist_X_match = new TH1D("hist_X_match", "hist_X_match", 200, 300, 2000);

  TH1D * hist_nul_BM       = new TH1D("nul_all_BM", "nul_all_BM", 100, 0, 500);
  TH1D * hist_blnu_BM      = new TH1D("blnu_all_BM", "blnu_all_BM", 100, 0, 1000);
  TH1D * hist_tt_BM        = new TH1D("tt_all_BM", "tt_all_BM", 200, 0, 3000);
  TH1D * hist_HY_BM        = new TH1D("HY_all_BM", "HY_all_BM", 200, 0, 3000);
  TH1D * hist_bb_BMl       = new TH1D("bb_al_BMl", "bb_all_BM", 100, 0, 800);
  TH1D * hist_bqq_BM       = new TH1D("bqq_all_BM", "bqq_all_BM", 100, 0, 1000);
  TH1D * hist_qq_BM        = new TH1D("qq_all_BM", "qq_all_BM", 100, 0, 800);

  TH1D * hist_blnu_eval = new TH1D("blnu_eval", "blnu_eval", 100, 0, 1000);
  TH1D * hist_tt_eval   = new TH1D("tt_eval", "tt_eval", 200, 0, 3000);
  TH1D * hist_HY_eval   = new TH1D("HY_eval", "HY_eval", 200, 0, 3000);
  TH1D * hist_bb_eval   = new TH1D("bb_eval", "bb_eval", 100, 0, 800);
  TH1D * hist_bqq_eval  = new TH1D("bqq_eval", "bqq_eval", 100, 0, 1000);

  TH2D * hist_score_vs_hmass  = new TH2D("hist_score_vs_hmass", "hist_score_vs_hmass", 100,  0, 1, 100, 0, 250);

  Long64_t total_entrys = 0;
  float weight = 1;
  float total_weight_sum = 1;

  TFile * file1 = TFile::Open( delphes_files.at(0).c_str() );
  TTree * tree1 = (TTree*) file1->Get("myelectrons/Events");
  int n1 = tree1->GetEntries();
  file1->Close();
  float weight_1 = 1. / n1;

  vector< vector< vector<int> > > b_groups;
  create_groups_from_unic_sample( {2, 1, 1}, b_groups, true );
  // create_groups_from_unic_sample( {2, 0, 0}, b_groups, true );

  for(int i = 0; i < delphes_files.size(); i++){
    float weight = weight_1;

    TFile * file = TFile::Open( delphes_files.at(i).c_str() );
    TTree * tree1 = (TTree*) file->Get("myelectrons/Events");
    TTree * tree2 = (TTree*) file->Get("mymuons/Events");
    TTree * tree3 = (TTree*) file->Get("mymets/Events");
    TTree * tree4 = (TTree*) file->Get("myjets/Events");
    Events_myelectrons * reader1 = new Events_myelectrons( tree1 );
    Events_mymuons     * reader2 = new Events_mymuons( tree2 );
    Events_mymets      * reader3 = new Events_mymets( tree3 );
    Events_myjets      * reader4 = new Events_myjets( tree4 );

    Long64_t entrys = tree1->GetEntries();
    Long64_t entry = 0;
    for(;entry < entrys;entry++){
      if( not (entry % 10000) )
        cout << entry << "/" << entrys << endl;

      // if( entry > 10000 ) break;

      file->cd();
      reader1->GetEntry(entry);
      reader2->GetEntry(entry);
      reader3->GetEntry(entry);
      reader4->GetEntry(entry);

      selections->Fill("Total", 1);

      // OBJECT SELECTIONS ==============================================
      selections->Fill("Total_X_Weight", weight);

      // lepton veto candidates --- --- --- --- --- --- --- 
      vector<int> lepton_veto_candidates;
      for(int i = 0; i < reader2->numbermuon; i++){
        if( reader2->muon_pt->at(i) < 15 ) continue;
        if( TMath::Abs(reader2->muon_eta->at(i)) > 2.1 ) continue;
        if( reader2->muon_pfreliso04all->at(i) > 0.15 ) continue; 
        lepton_veto_candidates.push_back(i);
      }

      for(int i = 0; i < reader1->numberelectron; i++){
        if( reader1->electron_pt->at(i) < 15 ) continue;
        if( TMath::Abs(reader1->electron_eta->at(i)) > 2.1 ) continue; 
        if( TMath::Abs(reader1->electron_eta->at(i)) > 1.4442 and TMath::Abs(reader1->electron_eta->at(i)) < 1.5560 ) continue; 
        if( reader1->electron_iso->at(i) > 0.06 ) continue; 
        lepton_veto_candidates.push_back(i);
      }

      // muon candidates --- --- --- --- --- --- --- 
      vector<int> muon_candidates;
      for(int i = 0; i < reader2->numbermuon; i++){
        if( reader2->muon_pt->at(i) < 26 ) continue;
        if( TMath::Abs(reader2->muon_eta->at(i)) > 2.1 ) continue;
        if( reader2->muon_pfreliso04all->at(i) > 0.15 ) continue; 
        muon_candidates.push_back(i);
      }

      // electron candidates --- --- --- --- --- --- --- 
      vector<int> electron_candidates;
      for(int i = 0; i < reader1->numberelectron; i++){
        if( reader1->electron_pt->at(i) < 30 ) continue;
        if( TMath::Abs(reader1->electron_eta->at(i)) > 2.1 ) continue; 
        if( TMath::Abs(reader1->electron_eta->at(i)) > 1.4442 and TMath::Abs(reader1->electron_eta->at(i)) < 1.5560 ) continue; 
        if( reader1->electron_iso->at(i) > 0.06 ) continue; 
        electron_candidates.push_back(i);
      }
      // cout << electron_candidates.size() << " " << muon_candidates.size() << " " << lepton_particle_candidates.size() << endl;

      // jet candidates --- --- --- --- --- --- --- 
      vector<int> jet_candidates;
      for(int i = 0; i < reader4->numberjet; i++){
        if( reader4->jet_pt->at(i) < 30 ) continue;
        if( TMath::Abs(reader4->jet_eta->at(i)) > 2.4 ) continue;
        jet_candidates.push_back(i);
      }

        TLorentzVector nu0 = make_met(reader3, 0);

      vector<int> ljet_candidates;
      vector<int> bjet_candidates;
      for(auto i : jet_candidates){
        // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation74X50ns
        if( reader4->jet_btag->at(i) <  0.605 ) ljet_candidates.push_back(i);
        else bjet_candidates.push_back(i);
      }

      // BASIC EVENT SELECTIONS ==============================================
      hist_N_bjets->Fill( bjet_candidates.size(), weight );
      hist_N_ljets->Fill( ljet_candidates.size(), weight );
      hist_N_l->Fill( muon_candidates.size() + electron_candidates.size(), weight );
      selections_nice->Fill("Total", weight);

      // at least 2 b-jets:
      if( bjet_candidates.size() < 2 ) continue;
      selections->Fill("b-jets >= 2", weight);
      selections_nice->Fill("b-jets >= 2", weight);

      // at least 2 b-jets:
      if( nu0.Pt() < 20 ) continue;
      selections->Fill("p_{T}^{#nu} > 20 GeV", weight);
      selections_nice->Fill("p_T^{#nu} > 20 GeV", weight);

      // only one lepton
      if( muon_candidates.size() + electron_candidates.size() != 1 ) continue;
      selections->Fill("leptons number = 1", weight);
      selections_nice->Fill("leptons number = 1", weight);

      // lepton veto
      if( lepton_veto_candidates.size() != 1 ) continue;
      selections->Fill("leptons veto", weight);
      selections_nice->Fill("Extra leptons veto", weight);

      // RECONSTRUCTIONS ==============================================
      vector<TLorentzVector> bjets_tlvs, ljets_tlvs, jets_tlvs;

      get_tlvs_jets( reader4, ljet_candidates, ljets_tlvs );
      get_tlvs_jets( reader4, bjet_candidates, bjets_tlvs );
      get_tlvs_jets( reader4, jet_candidates,  jets_tlvs  );

      // for csv ==========================================================
      string cluster;
      double score_h_1, score_h_1t, score_h_2, score_h_2t, score_tq_1, score_tq_1t, score_tq_2, score_tq_2t, score_tq_3, score_tq_3t, score_tl_1, score_tl_1t;
      int index_h_1, index_h_2, index_tq_1, index_tq_2, index_tq_3, index_tl_1;
      if( input_train_name.size() ){
        /*
        0.33973044 0 H 2
        0.32396072 0 H 1
        0.6927199 1 tq 0
        0.20426865 0 tq 3
        0.16255765 0 tq 4
        0.051923893 0 tl 5
        */
        infile >> score_h_1 >> score_h_1t >> cluster >> index_h_1;
        infile >> score_h_2 >> score_h_2t >> cluster >> index_h_2;
        infile >> score_tq_1 >> score_tq_1t >> cluster >> index_tq_1;
        infile >> score_tq_2 >> score_tq_2t >> cluster >> index_tq_2;
        infile >> score_tq_3 >> score_tq_3t >> cluster >> index_tq_3;
        infile >> score_tl_1 >> score_tl_1t >> cluster >> index_tl_1;

        // cout << score_h_1 << " " << score_h_1t << " " << cluster << " " << index_h_1 << " " << endl;
        TLorentzVector jet_h1 = jets_tlvs[ index_h_1 ];
        TLorentzVector jet_h2 = jets_tlvs[ index_h_2 ];
        TLorentzVector jet_tq1 = jets_tlvs[ index_tq_1 ];
        TLorentzVector jet_tq2 = jets_tlvs[ index_tq_2 ];
        TLorentzVector jet_tq3 = jets_tlvs[ index_tq_3 ];
        TLorentzVector jet_tl1 = jets_tlvs[ index_tl_1 ];

        hist_score_vs_hmass->Fill( score_h_1 + score_h_2, (jet_h1+jet_h2).M() );

        TLorentzVector l, nu, Wl;
        if( muon_candidates.size() ) l = make_muon(reader2, muon_candidates.at(0));
        else                         l = make_electron(reader1, electron_candidates.at(0));
        reconstruct_decay(80, l, nu0, nu, Wl);

        TLorentzVector H_eval = jet_h1 + jet_h2;
        TLorentzVector tq_eval = jet_tq1 + jet_tq2 + jet_tq3;
        TLorentzVector tl_eval = jet_tl1 + Wl;
        TLorentzVector Y_eval = tq_eval + tl_eval;
        TLorentzVector X_eval = H_eval + tq_eval + tl_eval;

        hist_blnu_eval->Fill( tl_eval.M() , weight  );
        hist_tt_eval->Fill( Y_eval.M() , weight  );
        hist_HY_eval->Fill( X_eval.M() , weight  );
        hist_bb_eval->Fill( H_eval.M() , weight  );
        hist_bqq_eval->Fill( tq_eval.M() , weight  );
      }

      for(int j = 0; j < 8; j++){
            myfile << 0 << " ";
            myfile << 0 << " ";
            myfile << 0 << " ";
      }
      for(int j = 0; j < 8; j++){
        TLorentzVector jet;
        if( j < jet_candidates.size() ){
          int jet_index = jet_candidates[ j ];
          TLorentzVector jet = jets_tlvs[ j ] ;
          
          myfile << TMath::Log( jet.Pt() + 1) << " " << jet.Eta()/2.5 << " " << jet.Phi()/3.15 << " " << TMath::Log(jet.M() + 1) << " " ;
          myfile << (reader4->jet_btag->at(jet_index) <  0.605) << " ";
        } else {
          myfile << 0 << " " << 0 << " " << 0 << " " << 0 << " " ;
          myfile << -1  << " " ;
        }
      }
      for(int j = 0; j < 8; j++){
        for(int k = j; k < 8; k++){
          if( j < jet_candidates.size() and k < jet_candidates.size() ){
            TLorentzVector jet1 = jets_tlvs[ j ] ;
            TLorentzVector jet2 = jets_tlvs[ k ] ;
            myfile << TMath::Log( (jet1+jet2).M() + 1 ) << " " << jet1.DeltaR( jet2 ) << " " ;
          } else myfile << 0 << " " << 0 << " ";
        }
      }

      TLorentzVector lll;
      if( muon_candidates.size() ) lll = make_muon(reader2, muon_candidates.at(0));
      else                         lll = make_electron(reader1, electron_candidates.at(0));
      TLorentzVector tl, nu, Wl;
      if( muon_candidates.size() + electron_candidates.size() )
        reconstruct_decay(80, lll, nu0, nu, Wl);

      myfile << TMath::Log(nu0.Pt() + 1) << " " << nu0.Phi()/3.15 << " " << TMath::Log(lll.Pt() + 1) << " " << lll.Eta()/2.5 << " " << lll.Phi()/3.15 << " " << muon_candidates.size() << " " << electron_candidates.size() << " " << TMath::Log(Wl.Pt() + 1) << " " << Wl.Eta()/2.5 << " " << Wl.Phi()/3.15 << " " << TMath::Log(Wl.M() + 1) << " ";
      myfile << endl;
      // for csv ==========================================================

      vector<TLorentzVector> bb_combo;
      get_tlvs_candidates(bjets_tlvs, bb_combo);

      //cout << bjets_tlvs.size() << endl;
      //cout << bb_combo.size() << "  " << weight << endl;


      vector<TLorentzVector> qq_combo;
      get_tlvs_candidates(ljets_tlvs, qq_combo);

      // cout << "combo size = " << bb_combo.size() << endl;
      TLorentzVector b_H_match, bbar_H_match, b_t_match, bbar_t_match, q_match, qbar_match, qq_match;

      for(auto bb : bb_combo){
        //bb.Print();
        //cout << bb.Pt() << " " << bb.Eta() << " " << bb.Phi() << " " << bb.M() << " - ";
        //cout << bb.DeltaR( H.tlv ) << " " << H.tlv.Pt() - bb.Pt() << endl;
        hist_bb_all0->Fill( bb.M() , weight  );
      }

      for(auto qq : qq_combo){
        // cout << qq.M() << endl;
        hist_qq_all0->Fill( qq.M() , weight  );
      }

        for( auto bc : bjets_tlvs ){
          for(auto qq : qq_combo){
            auto qqb = bc + qq;
            hist_qqb_all0->Fill( qqb.M() , weight  );
          }
        }

      // bjets
      // select all unic unordered samples of N=4 bjets from bjet_candidates into bjets_samples
      // N=4 bjects must be in agreement with total number of elements in groups b_groups
      vector< vector<int> > bjets_samples;
      // cout << "bjet_candidates " << bjet_candidates.size() << endl;
      create_unic_samples( bjet_candidates, 4, bjets_samples, false );

      // split every sample into groups defined by b_groups
      vector< vector< vector<int> > > b_groups_all;
      for(int i = 0; i < bjets_samples.size(); i++){
        for(int j = 0; j < b_groups.size(); j++){
          vector< vector<int> > b_groups_one;
          map_groups_to_samples( bjets_samples[i], b_groups[j], b_groups_one );
          b_groups_all.push_back( b_groups_one );
        }
      }

      if( false ){
        for(auto item : b_groups_all){
          cout << endl;
          for(auto gp : item){
            cout << "{";
            for(auto g : gp) cout << g << ",";
            cout << "}";
          }
        }
      }

      // ljets
      vector< vector<int> > ljets_samples;
      create_unic_samples( ljet_candidates, 2, ljets_samples, false ); 

      // muon
      vector< vector<int> > muon_samples;
      create_unic_samples( muon_candidates, 1, muon_samples, false ); 

      // electron
      vector< vector<int> > electron_samples;
      create_unic_samples( electron_candidates, 1, electron_samples, false );

      // cout << "TADA " << muon_candidates.size() << " " << electron_candidates.size() << " " << muon_samples.size() << " " << electron_samples.size()<< endl;

      // info groups
      //cout << b_groups_all.size() << " " << ljets_samples.size() << " " << muon_samples.size() << " " << endl;
      //cout << b_groups_all.size()* ljets_samples.size() * muon_samples.size() << endl;
      // vector< vector<int> > combinations = get_group_combinations( {(int)ljets_samples.size(), (int)( muon_samples.size() + electron_samples.size() ), (int)b_groups_all.size()}, false );

      // get possible indexes combination of groups: ljets, leptons, bjets
      // cout << "groups sizes " << 1 << " " << (int)( muon_samples.size() + electron_samples.size() ) << " " << b_groups_all.size() << endl;
      //vector< vector<int> > combinations = get_group_combinations( {1, (int)( muon_samples.size() + electron_samples.size() ), (int)b_groups_all.size()}, false );
      vector< vector<int> > combinations = get_group_combinations( {(int)ljets_samples.size(), 1, (int)b_groups_all.size()}, false );
      // cout << "=== " << endl;

      // iterate over event reconstruction candidates
      full_reco_events best_event;
      best_event.metric = 999999999999999;

      for( int i = 0; i < combinations.size(); i++ ){
        // cout << "combinations " << i << endl;
        // cout << combinations[i].size() << endl;
        
        int ljets_samples_index = combinations[i][0];
        int lepton_samples_index  = combinations[i][1];
        int b_groups_all_index  = combinations[i][2];
        
        //cout << ljets_samples_index << " " << endl;
        //cout << "lepton_samples_index " << lepton_samples_index << " " << b_groups_all_index << endl;

        vector<int> ljets_sample = ljets_samples[ ljets_samples_index ];
        vector< vector<int> > b_groups = b_groups_all[ b_groups_all_index ];
        
        //cout << "b_groups " << b_groups.size() << endl;
        
        vector<int> b_hs  = b_groups[0];
        vector<int> b_tls  = b_groups[1];
        vector<int> b_tqs  = b_groups[2];
        int b1_h_index = b_hs[0];
        int b2_h_index = b_hs[1];
        int b_tl_index = b_tls[0];
        int b_tq_index = b_tqs[0];
        
        bool type_h_reco  = b1_h_index != -1 and b2_h_index != -1;
        bool type_tl_reco = b_tl_index != -1;
        bool type_tq_reco = b_tq_index != -1;
        
        // cout << type_h_reco << endl;
        TLorentzVector b1_h = make_jet(reader4, b_hs[0]);
        TLorentzVector b2_h = make_jet(reader4, b_hs[1]);
        // cout << b1_h_index << " " << b2_h_index << endl;

        TLorentzVector b_tl = make_jet(reader4, b_tls[0]);
        TLorentzVector b_tq = make_jet(reader4, b_tqs[0]);

        TLorentzVector q1   = make_jet(reader4, ljets_sample[0]);
        TLorentzVector q2   = make_jet(reader4, ljets_sample[1]);
        // cout << ljets_sample[0] << " " << ljets_sample[1] << " " << b_tq_index << " " << (q1 + q2).M() << " " << (q1 + q2 + b_tq).M() << endl;
        if( q1.Pt() < q2.Pt() ) swap(q1, q2);

        // light jets into W boson, top
        TLorentzVector Wq = q1 + q2;
        TLorentzVector tq = b_tq + Wq;

        // bquarks into H
        TLorentzVector H = b1_h + b2_h;

        // t -> b_tl l nu
        TLorentzVector l;

        // cout << muon_samples.size() << "!!!" << " " << reader2->numbermuon << endl;

        if( muon_candidates.size() ) l = make_muon(reader2, muon_candidates.at(0));
        else                         l = make_electron(reader1, electron_candidates.at(0));

        TLorentzVector bl = b_tl + l;
        TLorentzVector nu0 = make_met(reader3, 0);
        TLorentzVector tl, nu, Wl;
        // reconstruct_t_from_bW(bl, nu0, nu, tl);
        reconstruct_decay(80, l, nu0, nu, Wl);

        tl = nu + l + b_tl;

        // Y -> tt
        TLorentzVector Y = tl + tq;

        // X -> HY
        TLorentzVector X = Y + H;

        // mb cuts
        // if( abs( H.M() - 125 ) > 30 ) continue;
        // if( b1_h.Pt() < b2_h.Pt() ) swap(b1_h, b2_h);
        // if( b1_h.Pt() < 15 or b2_h.Pt() < 15 ) continue;

        // hists
        hist_nul_all->Fill( Wl.M() , weight );
        hist_blnu_all->Fill( tl.M() , weight  );
        hist_tt_all->Fill( Y.M() , weight  );
        hist_HY_all->Fill( X.M() , weight  );
        hist_bb_all->Fill( H.M() , weight  );
        hist_bqq_all->Fill( tq.M() , weight  );
        hist_qq_all->Fill( Wq.M() , weight  );

        double metric = calc_metric(Wl, tl, Wq, tq, H);
        if( best_event.metric > metric )
          best_event.set( metric, Wl, tl, Wq, tq, H, Y, X );
      }

        hist_nul_BM->Fill( best_event.Wl.M() , weight );
        hist_blnu_BM->Fill( best_event.tl.M() , weight  );
        hist_tt_BM->Fill( best_event.Y.M() , weight  );
        hist_HY_BM->Fill( best_event.X.M() , weight  );
        hist_bb_BMl->Fill( best_event.H.M() , weight  );
        hist_bqq_BM->Fill( best_event.tq.M() , weight  );
        hist_qq_BM->Fill( best_event.Wq.M() , weight  );

      // DONE !!! 
      selections->Fill("Selected", 1);
      selections->Fill("Selected_X_Weight", weight);
      total_weight_sum += weight;
    }

    file->Close();
  }

	for(int i = 1; i < 100; ++i) {
		double passed = selections->GetBinContent(i);
		string label = selections->GetXaxis()->GetBinLabel(i);

		if(label.size() < 1) break;
		cout << "dic[\"" + label + "\"]" << "=[" << passed << ", " << passed  / total_entrys << ", " << passed / total_weight_sum << "]" << endl;
	}

  ofile->Write();
  myfile.close();
}




