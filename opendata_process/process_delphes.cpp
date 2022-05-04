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

void process_delphes( string file, string ofile_name, string file_from_lhe = "" ) {
  vector<string> delphes_files = { file };

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

  TH1D * hist_qq_all  = new TH1D("qq_all",  "qq_all", 100, 0, 500);
  TH1D * hist_bqq_all = new TH1D("bqq_all", "bqq_all", 100, 0, 500);
  TH1D * hist_bb_all  = new TH1D("bb_all",  "bb_all", 100, 0, 500);

  TH1D * hist_bb_all0  = new TH1D("bb_all0", "bb_all0", 100, 0, 500);
  TH1D * hist_qq_all0  = new TH1D("qq_all0", "qq_all0", 100, 0, 500);
  TH1D * hist_qqb_all0 = new TH1D("qqb_all0", "qqb_all0", 100, 0, 500);

  TH1D * hist_nul_all   = new TH1D("nul_all", "nul_all", 100, 0, 500);
  TH1D * hist_blnu_all  = new TH1D("blnu_all", "blnu_all", 100, 0, 1000);
  TH1D * hist_tt_all    = new TH1D("tt_all", "tt_all", 200, 0, 2000);
  TH1D * hist_HY_all    = new TH1D("HY_all", "HY_all", 200, 0, 2000);

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

  Long64_t total_entrys = 0;
  float weight = 1;
  float total_weight_sum = 1;

  TFile * file1 = TFile::Open( delphes_files.at(0).c_str() );
  TTree * tree1 = (TTree*) file1->Get("Delphes");
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
        if( reader2->muon_pt->at(i) < 30 ) continue;
        if( TMath::Abs(reader2->muon_eta->at(i)) > 2.1 ) continue;
        if( reader2->muon_pfreliso04all->at(i) > 0.15 ) continue; 
        muon_candidates.push_back(i);
      }

      // electron candidates --- --- --- --- --- --- --- 
      vector<int> electron_candidates;
      for(int i = 0; i < reader1->numberelectron; i++){
        if( reader1->electron_pt->at(i) < 26 ) continue;
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
        if( reader4->jet_btag->at(i) < 0. ) ljet_candidates.push_back(i);
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
      vector<TLorentzVector> ljets_tlvs;
      vector<TLorentzVector> bjets_tlvs; 

      get_tlvs_jets( reader, ljet_candidates, ljets_tlvs );
      get_tlvs_jets( reader, bjet_candidates, bjets_tlvs );

      vector<TLorentzVector> bb_combo;
      get_tlvs_candidates(bjets_tlvs, bb_combo);

      vector<TLorentzVector> qq_combo;
      get_tlvs_candidates(ljets_tlvs, qq_combo);

      // cout << "combo size = " << bb_combo.size() << endl;
      TLorentzVector b_H_match, bbar_H_match, b_t_match, bbar_t_match, q_match, qbar_match, qq_match;
      if( true and file_lhe ){
        /*
        cout << "b input data ... in " << endl;
        for(auto item : {b_H.tlv, bbar_H.tlv, b_t.tlv, bbar_t.tlv} ){ 
          cout << item.Pt() << endl;
        }
        for(auto item : bjets_tlvs ){ 
          cout << item.Pt() << endl;
        }
        cout << "b input data ... out " << endl;
        */

        map<int,int> b_matchs = match_multiple( {b_H.tlv, bbar_H.tlv, b_t.tlv, bbar_t.tlv}, bjets_tlvs, 0.4 );
        map<int,int> q_matchs = match_multiple( {q.tlv, qbar.tlv}, ljets_tlvs, 0.4 );

        /*
        cout << "b match:" << endl;
        for( auto item : b_matchs ){
          cout << item.first << " " << item.second << endl;
        }

        cout << "q match:" << endl;
        for( auto item : q_matchs ){
          cout << item.first << " " << item.second << endl;
        }
        */

        if( b_matchs[0] != -1 ) b_H_match = bjets_tlvs[ b_matchs[0] ]; 
        if( b_matchs[1] != -1 ) bbar_H_match = bjets_tlvs[ b_matchs[1] ]; 
        if( b_matchs[2] != -1 ) b_t_match = bjets_tlvs[ b_matchs[2] ]; 
        if( b_matchs[3] != -1 ) bbar_t_match = bjets_tlvs[ b_matchs[3] ];

        if( q_matchs[0] != -1 ) q_match = ljets_tlvs[ q_matchs[0] ]; 
        if( q_matchs[1] != -1 ) qbar_match = ljets_tlvs[ q_matchs[1] ];
        qq_match = q_match + qbar_match;
        if( q_matchs[0] != -1 and q_matchs[1] != -1 ) hist_qq_match->Fill( qq_match.M() , weight  );

        if( b_matchs[0] != -1 and b_matchs[1] != -1 ) hist_bb_match->Fill( (b_H_match + bbar_H_match).M() , weight  );
        if( b_matchs[2] != -1 and q_matchs[0] != -1 and q_matchs[1] != -1 ) hist_qqb_match->Fill( (qq_match + b_t_match).M() , weight  );
        if( b_matchs[3] != -1 and q_matchs[0] != -1 and q_matchs[1] != -1 ) hist_qqbar_match->Fill( (qq_match + bbar_t_match).M() , weight  );

        TLorentzVector l;
        TLorentzVector tq, tl, nu, b_tl, bl;
        if( muon_candidates.size() ) l = make_muon(reader, 0);
        else if( electron_candidates.size() ) l = make_electron(reader, 0);
        bool has_lepton = muon_candidates.size() + electron_candidates.size();
        bool has_t_hadronic = ( b_matchs[2] != -1 and q_matchs[0] != -1 and q_matchs[1] != -1 );
        bool has_H          = ( b_matchs[0] != -1 and b_matchs[1] != -1 );

        b_tl = bbar_t_match;
        bl   = b_tl + l;
        tq   = qq_match + b_t_match;
        
        //if( has_lepton and b_matchs[2] != -1 ) hist_b_match->Fill();
        if( has_lepton and b_matchs[3] != -1 ){
          // reconstruct_t_from_bW(bl, nu0, nu, tl);

          TLorentzVector Wl;
          reconstruct_decay(80, l, nu0, nu, Wl);

                        Wl = nu + l;
          TLorentzVector Y = tl + tq;
          TLorentzVector X = Y + (b_H_match + bbar_H_match);

          hist_wl_match->Fill( Wl.M() , weight  );
          hist_tl_match->Fill( tl.M() , weight  );

          if( has_t_hadronic ) hist_Y_match->Fill( Y.M()  , weight );
          if( has_t_hadronic and has_H ) hist_X_match->Fill( X.M()  , weight );
        }

      }

      if( true and file_lhe ){
        //b_H.tlv.Print();
        //bbar_H.tlv.Print();

        // match  bquarks
        for( auto bc : bjets_tlvs ){
          hist_Hb_dR->Fill( bc.DeltaR( b_H.tlv )  , weight );
          hist_Hb_dPt->Fill( (bc.Pt() - b_H.tlv.Pt())/bc.Pt()  , weight );

          hist_Hbbar_dR->Fill( bc.DeltaR( bbar_H.tlv ) , weight  );
          hist_Hbbar_dPt->Fill( (bc.Pt() - bbar_H.tlv.Pt())/bc.Pt()  , weight );
        }

        // match  bb / H
        for(auto bb : bb_combo){
          hist_H_dPt->Fill( (bb.Pt() - H.tlv.Pt())/bb.Pt()  , weight  );
          hist_H_dR ->Fill( bb.DeltaR( H.tlv ) , weight  );

          hist_H_dPt_x_m->Fill( (bb.Pt() - H.tlv.Pt())/bb.Pt(), bb.M() , weight  );
          hist_H_dR_x_m->Fill( bb.DeltaR( H.tlv ), bb.M() , weight  );
        }

        // match  lquarks
        for( auto qc : ljets_tlvs ){
          hist_q_dR->Fill( qc.DeltaR( q.tlv ) );
          hist_q_dPt->Fill( (qc.Pt() - q.tlv.Pt())/qc.Pt()  , weight );

          hist_qbar_dR->Fill( qc.DeltaR( qbar.tlv ) , weight  );
          hist_qbar_dPt->Fill( (qc.Pt() - qbar.tlv.Pt())/qc.Pt()  , weight );
        }

        // match  qq / W
        TLorentzVector W_qq_tlv = W.tlv;
        if(true) W_qq_tlv = Wbar.tlv;
        for(auto qq : qq_combo){
          hist_qq_dPt->Fill( (qq.Pt() - W_qq_tlv.Pt())/qq.Pt() , weight  );
          hist_qq_dR ->Fill( qq.DeltaR( W_qq_tlv ) , weight  );

          hist_qq_dPt_x_m->Fill( (qq.Pt() - W_qq_tlv.Pt())/qq.Pt(), qq.M() , weight  );
          hist_qq_dR_x_m->Fill( qq.DeltaR( W_qq_tlv ), qq.M() , weight  );
        }

        // match top
        TLorentzVector t_bqq_tlv = t.tlv;
        if(true) t_bqq_tlv = tbar.tlv;

        for( auto bc : bjets_tlvs ){
          for(auto qq : qq_combo){
            auto qqb = bc + qq;
            hist_qqb_dPt->Fill( (qqb.Pt() - t_bqq_tlv.Pt())/qqb.Pt()  , weight  );
            hist_qqb_dR ->Fill( qqb.DeltaR( t_bqq_tlv ) , weight  );

            hist_bqq_dPt_x_m->Fill( (qqb.Pt() - t_bqq_tlv.Pt())/qqb.Pt(), qqb.M() , weight  );
            hist_bqq_dR_x_m->Fill( qqb.DeltaR( t_bqq_tlv ), qqb.M() , weight  );

            hist_qqb_all0->Fill( qqb.M() , weight  );
          }
        }
      }

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
        TLorentzVector b1_h = make_jet(reader, b_hs[0]);
        TLorentzVector b2_h = make_jet(reader, b_hs[1]);
        // cout << b1_h_index << " " << b2_h_index << endl;

        TLorentzVector b_tl = make_jet(reader, b_tls[0]);
        TLorentzVector b_tq = make_jet(reader, b_tqs[0]);

        TLorentzVector q1   = make_jet(reader, ljets_sample[0]);
        TLorentzVector q2   = make_jet(reader, ljets_sample[1]);
        // cout << ljets_sample[0] << " " << ljets_sample[1] << " " << b_tq_index << " " << (q1 + q2).M() << " " << (q1 + q2 + b_tq).M() << endl;
        if( q1.Pt() < q2.Pt() ) swap(q1, q2);

        // light jets into W boson, top
        TLorentzVector Wq = q1 + q2;
        TLorentzVector tq = b_tq + Wq;

        // bquarks into H
        TLorentzVector H = b1_h + b2_h;

        // t -> b_tl l nu
        TLorentzVector l;
        if( muon_samples.size() ) l = make_muon(reader, 0);
        else                      l = make_electron(reader, 0);

        TLorentzVector bl = b_tl + l;
        TLorentzVector nu0 = make_met(reader, 0);
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
      }

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
}




