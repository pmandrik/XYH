
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

  vector<string> back_files = {"pd_file_650_MY_375",
    "pd_file_900_MY_600",
    "pd_file_1300_MY_475",
    "pd_file_1300_MY_975",
    "pd_file_1700_MY_475",
    "pd_file_1700_MY_1225",
    "pd_file_1900_MY_475",
    "pd_file_1900_MY_1600",
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

    TH1D* hista2 = (TH1D*) file_s->Get("HY_eval");
    cout << fname << " " << hista2 << endl;
    hista2->SetName( (fname + "eval").c_str() );
    hists.push_back( hista2 );
  }

  for(auto fname : back_files){
    TFile * file_s = TFile::Open((path_background + fname + ".root").c_str());

    TH1D* hista = (TH1D*) file_s->Get("HY_all_BM");
    cout << fname << " " << hista << endl;
    hista->SetName( fname.c_str() );
    hists.push_back( hista );

    TH1D* hista2 = (TH1D*) file_s->Get("HY_eval");
    cout << fname << " " << hista2 << endl;
    hista2->SetName( (fname + "eval").c_str() );
    hists.push_back( hista2 );
  }

  TFile * file_out = new TFile((out_path + "/" + "hists_limits_" + to_string(nbins) + "_" + to_string(lumi_factor) + ".root").c_str(), "RECREATE");

  double left_entry  = 3000;
  double right_entry = -1;

  for(auto hist : hists){
    string name = hist->GetName();

    left_entry  = TMath::Min(left_entry,  hist->GetBinCenter(hist->FindFirstBinAbove(0)) );
    right_entry = TMath::Max(right_entry, hist->GetBinCenter(hist->FindLastBinAbove(0))  );
  }

  float Lumi = 137 * 1000 ; // 138 fb-1
  float ttbar_xsec = 831.76 ; // pb https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
  float N_expected_ttbar = Lumi * ttbar_xsec ; // 114782880 6652000./114782880 = 0.05795289332346427
  float N_generated = 3943779;

  float N_expected_signal = 20000;
  // GetBinContent return efficiency
  // N_observed = efficiency * N_expected;

  // SM ttH L = 35.9 fb
  // ttbar selected = 580000
  // ttbar selected eff = 580000 / (831.76 * 37 * 1000) = 0.018846392800418
  // 

  for(auto hist : hists){
    string name = hist->GetName();
    // if(name.find(var) == std::string::npos) continue;
    // cout << hist->GetName() << " " << left_entry << " " << right_entry << endl;

    TH1D * new_hist = new TH1D((string(hist->GetName()) + "_" + to_string(nbins) + "_" + to_string(lumi_factor)).c_str(), hist->GetTitle(), nbins, left_entry, right_entry);        
    for(int i = 1; i <= hist->GetXaxis()->GetNbins(); i++){
      if( name.find("ttbar") != std::string::npos or name.find("pd_file_") != std::string::npos ) // ttbar normalisation // 
        new_hist->Fill(hist->GetBinCenter(i), N_expected_ttbar*hist->GetBinContent(i) / float(lumi_factor) );
      else // signal normalisation
        new_hist->Fill(hist->GetBinCenter(i), N_expected_signal*hist->GetBinContent(i) / float(lumi_factor) );
    }


    if( name.find("ttbar") != std::string::npos or name.find("pd_file_") != std::string::npos ) {// ttbar normalisation // 
      new_hist->Fill(hist->GetBinCenter(hist->GetXaxis()->GetNbins()-1), N_expected_ttbar*hist->GetBinContent(hist->GetXaxis()->GetNbins()+1) / float(lumi_factor) );
      // cout << N_expected_ttbar*hist->GetBinContent(hist->GetXaxis()->GetNbins()+1) << endl;
    }
    else { // signal normalisation
      new_hist->Fill(hist->GetBinCenter(hist->GetXaxis()->GetNbins()-1) , N_expected_signal*hist->GetBinContent(hist->GetXaxis()->GetNbins()+1) / float(lumi_factor) );
      cout << N_expected_signal*hist->GetBinContent(hist->GetXaxis()->GetNbins()+1) << endl;
    }
  }

  // file_out->ls();
  file_out->Write();
  file_out->Close();
}


