
void make_hists(string var="HY_all_BM", string out_path=".", int nbins = 25, int lumi_factor = 1, bool cut = false){
  string path_signal = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/";
  string path_background = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/";

  vector<string> signal_files = {"pd_NMSSM_XYH_ttbb_MX_650_MY_375", 
    "pd_NMSSM_XYH_ttbb_MX_900_MY_600",
    "pd_NMSSM_XYH_ttbb_MX_1300_MY_475",
    "pd_NMSSM_XYH_ttbb_MX_1300_MY_975",
    "pd_NMSSM_XYH_ttbb_MX_1700_MY_475",
    "pd_NMSSM_XYH_ttbb_MX_1700_MY_1225",
    "pd_NMSSM_XYH_ttbb_MX_1900_MY_475",
    "pd_NMSSM_XYH_ttbb_MX_1900_MY_1600",  
  };

  vector<string> back_files = {
    "pd_file_650_MY_375_hf",
    "pd_file_900_MY_600_hf",
    "pd_file_1300_MY_475_hf",
    "pd_file_1300_MY_975_hf",
    "pd_file_1700_MY_475_hf",
    "pd_file_1700_MY_1225_hf",
    "pd_file_1900_MY_475_hf",
    "pd_file_1900_MY_1600_hf", // pd_file_1300_MY_975_hf.root

    "pd_file_650_MY_375_lf",
    "pd_file_900_MY_600_lf",
    "pd_file_1300_MY_475_lf",
    "pd_file_1300_MY_975_lf",
    "pd_file_1700_MY_475_lf",
    "pd_file_1700_MY_1225_lf",
    "pd_file_1900_MY_475_lf",
    "pd_file_1900_MY_1600_lf", // pd_file_1300_MY_975_hf.root

    "pd_file_650_MY_375_ttH",
    "pd_file_900_MY_600_ttH",
    "pd_file_1300_MY_475_ttH",
    "pd_file_1300_MY_975_ttH",
    "pd_file_1700_MY_475_ttH",
    "pd_file_1700_MY_1225_ttH",
    "pd_file_1900_MY_475_ttH",
    "pd_file_1900_MY_1600_ttH", // pd_file_1300_MY_975_hf.root
  };

  //TFile * file_b = TFile::Open((path_background + "pd_file.root").c_str());
  //TH1D* histb = (TH1D*) file_b->Get("HY_all_BM");
  //histb->SetName("ttbar");
  //vector<TH1D*> hists = { histb };

  vector<TH1D*> hists = { };
  for(auto fname : signal_files){
    TFile * file_s = TFile::Open((path_signal + fname + ".root").c_str());

    TH1D* hista = (TH1D*) file_s->Get("HY_all_BM");
    cout << fname << " " << hista << endl;
    hista->SetName( fname.c_str() );
    hists.push_back( hista );

    TH1D* hista2 = (TH1D*) file_s->Get("HY_eval_fnal");
    cout << fname << " " << hista2 << endl;
    hista2->SetName( (fname + "eval").c_str() );
    hists.push_back( hista2 );
  }

  map<string, float> effs;
  for(auto fname : back_files){
    // cout << (path_background + fname + ".root") << endl;
    TFile * file_s = TFile::Open((path_background + fname + ".root").c_str());

    TH1D* hista2 = (TH1D*) file_s->Get("HY_eval_fnal");
    // cout << fname << " " << hista2 << endl;
    hista2->SetName( (fname + "eval").c_str() );
    hists.push_back( hista2 );

    // efficienties ... 
    TH1D* h1 = (TH1D*) file_s->Get("selections");
    float total_events = h1->GetBinContent(1);

    TH1D* h2 = (TH1D*) file_s->Get("selections_nice2");
    float selected_events = h2->GetBinContent(3);

    effs[ (fname + "eval") ] = selected_events / total_events;
    // cout << total_events << " " << selected_events << endl;
    cout << fname << " " << selected_events / total_events << endl;
  }

  TFile * file_out = new TFile((out_path + "/" + "hists_limits_" + to_string(nbins) + "_" + to_string(lumi_factor) + ".root").c_str(), "RECREATE");

  double left_entry  = 3000;
  double right_entry = 0;

  for(auto hist : hists){
    string name = hist->GetName();

    left_entry  = TMath::Min(left_entry,  hist->GetBinCenter(hist->FindFirstBinAbove(0)) );
    right_entry = TMath::Max(right_entry, hist->GetBinCenter(hist->FindLastBinAbove(0))  );
  }

  left_entry  = 0;
  right_entry = 3000;

  float Lumi = 137 * 1000 ; // 138 fb-1
  float ttbar_xsec = 831.76 ; // pb https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
  float N_expected_ttbar = Lumi * ttbar_xsec ; // 114782880 6652000./114782880 = 0.05795289332346427
  float N_generated = 3943779;

  float hf_frac = 939250. / (1.395 * 1000000 + 1.609 * 1000000 + 939250);

  float N_expected_ttbar_hf = N_expected_ttbar *  hf_frac ;
  float N_expected_ttbar_lf = N_expected_ttbar *  (1. - hf_frac) ;
  float N_expected_ttH      = Lumi * 5.071E-01;

  float N_expected_signal = 20000;
  // GetBinContent return efficiency
  // N_observed = efficiency * N_expected;

  // SM ttH L = 35.9 fb
  // ttbar selected = 580000
  // ttbar selected eff = 580000 / (831.76 * 37 * 1000) = 0.018846392800418
  // 

  bool TEV_14 = true;
  if( TEV_14 ){
    double sigma_ttH_14_TEV = 6.137E-01;
    double sigma_ggH_14_TEV = 5.467E+01;

    double sigma_ggH_13_TEV = 4.858E+01;
    double sigma_ttH_13_TEV = 5.071E-01;

    float ttbar_xsec_14TEV = 985.7; // pb https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO 

    double Lumi_HLLHC_factor = 3000. * 1000 / Lumi;

    N_expected_ttbar_hf = N_expected_ttbar_hf * Lumi_HLLHC_factor * ttbar_xsec_14TEV / ttbar_xsec ;
    N_expected_ttbar_lf = N_expected_ttbar_lf * Lumi_HLLHC_factor * ttbar_xsec_14TEV / ttbar_xsec ;
    N_expected_ttH      = N_expected_ttH * Lumi_HLLHC_factor * sigma_ttH_14_TEV / sigma_ttH_13_TEV;
    cout << Lumi_HLLHC_factor * ttbar_xsec_14TEV / ttbar_xsec << " " << Lumi_HLLHC_factor * ttbar_xsec_14TEV / ttbar_xsec << " " << Lumi_HLLHC_factor * sigma_ttH_14_TEV / sigma_ttH_13_TEV << endl;
  }

  for(auto hist : hists){
    string name = hist->GetName();
    // if(name.find(var) == std::string::npos) continue;
    // cout << hist->GetName() << " " << left_entry << " " << right_entry << endl;

    float eff = effs[ name ];
    float total = 0;
    for(int i = 1; i <= hist->GetXaxis()->GetNbins(); i++) total += hist->GetBinContent(i);

    TH1D * new_hist = new TH1D((string(hist->GetName()) + "_" + to_string(nbins) + "_" + to_string(lumi_factor)).c_str(), hist->GetTitle(), nbins, left_entry, right_entry);        
    for(int i = 1; i <= hist->GetXaxis()->GetNbins(); i++){
      float pos = hist->GetBinCenter(i);
      if( pos >= right_entry ) pos = right_entry - 0.1;

      if( name.find("hf") != std::string::npos ){
        new_hist->Fill(pos, eff * N_expected_ttbar_hf*hist->GetBinContent(i) / float(lumi_factor) / float(total) );
      } else if( name.find("lf") != std::string::npos ){
        new_hist->Fill(pos, eff * N_expected_ttbar_lf*hist->GetBinContent(i) / float(lumi_factor) / float(total) );
      } else if( name.find("ttH") != std::string::npos ){
        new_hist->Fill(pos, eff * N_expected_ttH*hist->GetBinContent(i) / float(lumi_factor) / float(total) );
      }
      else // signal normalisation
        new_hist->Fill(pos, N_expected_signal*hist->GetBinContent(i) / float(lumi_factor) );
    }

      int lbin = hist->GetXaxis()->GetNbins();
      if( name.find("hf") != std::string::npos ){
        new_hist->Fill(hist->GetBinCenter(lbin), eff * N_expected_ttbar_hf*hist->GetBinContent(lbin+1) / float(lumi_factor) / float(total) );
      } else if( name.find("lf") != std::string::npos ){
        new_hist->Fill(hist->GetBinCenter(lbin), eff * N_expected_ttbar_lf*hist->GetBinContent(lbin+1) / float(lumi_factor) / float(total) );
      } else if( name.find("ttH") != std::string::npos ){
        new_hist->Fill(hist->GetBinCenter(lbin), eff * N_expected_ttH*hist->GetBinContent(lbin+1) / float(lumi_factor) / float(total) );
      }
      else // signal normalisation
        new_hist->Fill(hist->GetBinCenter(lbin), N_expected_signal*hist->GetBinContent(lbin+1) / float(lumi_factor) );

  }

  // file_out->ls();
  file_out->Write();
  file_out->Close();
}


