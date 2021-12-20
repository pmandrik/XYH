#include "LHEF.h"

#include "Delphes.C"
#include "Delphes_help_func.C"

void process_delphes( string file, string ofile_name ) {
  vector<string> delphes_files = { file };

  TFile * ofile = TFile::Open( ofile_name.c_str(), "RECREATE" );
  TH1D * selections = new TH1D("selections", "selections", 100, 0, 100);
  selections->Fill("Total", 0);
  selections->Fill("Total_X_Weight", 0);
  selections->Fill("Selected", 0);
  selections->Fill("Selected_X_Weight", 0);

  TH1D * hist_N_bjets = new TH1D("N_bjets", "N_bjets", 20, 0, 20);
  TH1D * hist_N_ljets = new TH1D("N_ljets", "N_ljets", 20, 0, 20);
  TH1D * hist_N_l = new TH1D("N_l", "N_l", 20, 0, 20);

  TH1D * hist_qq_all  = new TH1D("qq_all", "qq_all", 100, 0, 300);
  TH1D * hist_bqq_all = new TH1D("bqq_all", "bqq_all", 100, 0, 300);
  TH1D * hist_bb_all  = new TH1D("bb_all", "bb_all", 100, 0, 300);

  TH1D * hist_bb_all0  = new TH1D("bb_all0", "bb_all0", 100, 0, 300);

  TH1D * hist_nul_all   = new TH1D("nul_all", "nul_all", 100, 0, 300);
  TH1D * hist_blnu_all  = new TH1D("blnu_all", "blnu_all", 100, 0, 300);
  TH1D * hist_tt_all    = new TH1D("tt_all", "tt_all", 100, 0, 500);
  TH1D * hist_HY_all    = new TH1D("HY_all", "HY_all", 100, 0, 2000);

  Long64_t total_entrys = 0;
  float weight = 1;
  float total_weight_sum = 1;

  vector< vector< vector<int> > > b_groups;
  // create_groups_from_unic_sample( {2, 1, 1}, b_groups, true );
  create_groups_from_unic_sample( {2, 0, 0}, b_groups, true );

  for(int i = 0; i < delphes_files.size(); i++){

    TFile * file = TFile::Open( delphes_files.at(i).c_str() );
    TTree * tree = (TTree*) file->Get("Delphes");
    Delphes * reader = new Delphes( tree );

    Long64_t entrys = tree->GetEntries();
    Long64_t entry = 0;
    for(;entry < entrys;entry++){
      reader->GetEntry(entry);
      selections->Fill("Total", 1);

      // OBJECT SELECTIONS ==============================================
      selections->Fill("Total_X_Weight", weight);
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

      // photon candidates --- --- --- --- --- --- --- 
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
      hist_N_bjets->Fill( bjet_candidates.size() );
      hist_N_ljets->Fill( ljet_candidates.size() );
      hist_N_l->Fill( muon_candidates.size() + electron_candidates.size() );


      // No b-jets:
      if( bjet_candidates.size() < 3 ) continue;
      selections->Fill("b-jets > 2", 1);

      // At least two light jets
      if( ljet_candidates.size() < 2) continue;
      selections->Fill("l-jets > 2", 1);

      // At least one lepton
      if( electron_candidates.size() + muon_candidates.size() < 1) continue;
      selections->Fill("At least one lepton", 1);


      // RECONSTRUCTIONS ==============================================
      vector<TLorentzVector> ljets_tlvs;
      vector<TLorentzVector> bjets_tlvs; 

      get_tlvs_jets( reader, ljet_candidates, ljets_tlvs );
      get_tlvs_jets( reader, bjet_candidates, bjets_tlvs );

      vector<TLorentzVector> bb_combo;
      get_tlvs_candidates(bjets_tlvs, bb_combo);
      for(auto bb : bb_combo){
        hist_bb_all0->Fill( bb.M() );
      }

      // bjets
      // cout << "===" << endl;
      vector< vector<int> > bjets_samples;
      create_unic_samples( bjet_candidates, 4, bjets_samples, false );

      vector< vector< vector<int> > > b_groups_all;
      for(int i = 0; i < bjets_samples.size(); i++){
        for(int j = 0; j < b_groups.size(); j++){
          vector< vector<int> > b_groups_one;
          map_groups_to_samples( bjets_samples[i], b_groups[j], b_groups_one );
          b_groups_all.push_back( b_groups_one );
        }
      }

      if( true ){
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
      // cout << b_groups_all.size() << " " << ljets_samples.size() << " " << muon_samples.size() << " " << endl;
      // cout << b_groups_all.size()* ljets_samples.size() * muon_samples.size() << endl;
      // vector< vector<int> > combinations = get_group_combinations( {(int)ljets_samples.size(), (int)( muon_samples.size() + electron_samples.size() ), (int)b_groups_all.size()}, false );

      vector< vector<int> > combinations = get_group_combinations( {1, (int)( muon_samples.size() + electron_samples.size() ), (int)b_groups_all.size()}, false );

      // iterate over event reconstruction candidates
      for( int i = 0; i < combinations.size(); i++ ){
        int ljets_samples_index = combinations[i][0];
        int lepton_samples_index  = combinations[i][1];
        int b_groups_all_index  = combinations[i][2];

        vector<int> ljets_sample = ljets_samples[ ljets_samples_index ];
        vector< vector<int> > b_groups = b_groups_all[ b_groups_all_index ];
        vector<int> b_hs  = b_groups[0];
        vector<int> b_tls  = b_groups[1];
        vector<int> b_tqs  = b_groups[2];

        TLorentzVector b1_h = make_jet(reader, b_hs[0]);
        TLorentzVector b2_h = make_jet(reader, b_hs[1]);
        if( b1_h.Pt() < b2_h.Pt() ) swap(b1_h, b2_h);
        if( b1_h.Pt() < 15 or b2_h.Pt() < 15 ) continue;

        TLorentzVector b_tl = make_jet(reader, b_tls[0]);
        TLorentzVector b_tq = make_jet(reader, b_tqs[0]);

        TLorentzVector q1   = make_jet(reader, ljets_sample[0]);
        TLorentzVector q2   = make_jet(reader, ljets_sample[1]);
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
        TLorentzVector tl, nu;
        reconstruct_t_from_bW(bl, nu0, nu, tl);
        // nu = nu0;
        // tl = nu0 + l + b_tl;

        TLorentzVector Wl = nu + l;

        // Y -> tt
        TLorentzVector Y = tl + tq;

        // X -> HY
        TLorentzVector X = Y + H;

        // mb cuts
        // if( abs( H.M() - 125 ) > 30 ) continue;

        // hists
        hist_nul_all->Fill( Wl.M() );
        hist_blnu_all->Fill( tl.M() );
        hist_tt_all->Fill( Y.M() );
        hist_HY_all->Fill( X.M() );
        hist_bb_all->Fill( H.M() );
        hist_bqq_all->Fill( tq.M() );
        hist_qq_all->Fill( Wq.M() );
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




