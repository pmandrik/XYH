
double get_br( double value ){
  float L = 137; // 137 fb − 1
  int n_existed = 20000;
  float xsec_Br = value * n_existed / L; // 20000 / (138 * 1000) = 0.14492753623188406

  float BR_H_bb    = 5.824E-01; // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBR
  float BR_H_ttbar = 4./9.;

  // 225.816 * 4./9. * 5.824E-01

  return xsec_Br / BR_H_bb / BR_H_ttbar;
}

vector<double> get_trex_limit(string path){
  vector<double> answer;
  //path = "TRExFitter/OUTPUT/fcnc_apr_03_tune_2_BDT_0_000/tua/Limits/tua.root";
  //path = "TRExFitter/OUTPUT/fcnc_apr_03_tune_2_BDT_1_000/tua/Limits/tua.root";
  //path = "TRExFitter/OUTPUT/fcnc_apr_03_tune_2_BDT_2_000/tua/Limits/tua.root";
  //path = "OUTPUT/fcnc_may_05_tune_3_BDT_2_000/tua/Limits/tua.root";

  TFile * file = TFile::Open( path.c_str() );

    TTree * tree = (TTree * ) file->Get("limit");

    double sigma_2_down, sigma_1_down, central, sigma_1_up, sigma_2_up;
    double lim;
    tree->SetBranchAddress("limit", &lim);
    tree->GetEntry(0); sigma_2_down = lim ; 
    tree->GetEntry(1); sigma_1_down= lim; 

    tree->GetEntry(2); 
    central=     ( lim );

    tree->GetEntry(3); sigma_1_up=  ( lim ); 
    tree->GetEntry(4); sigma_2_up=  ( lim ); 

  cout << " ===== " << path << endl;
  cout << "Raw limits " << sigma_2_down << " " << sigma_1_down << " ";
  cout << central << " " << sigma_1_up << " " << sigma_2_up << endl;

  cout << "Br limits (fb)" << get_br(sigma_2_down) << " " << get_br(sigma_1_down) << " ";
  cout << get_br(central) << " " << get_br(sigma_1_up) << " " << get_br(sigma_2_up) << endl;

  answer.push_back( get_br(sigma_2_down) );
  answer.push_back( get_br(sigma_1_down) );
  answer.push_back( get_br(central) );
  answer.push_back( get_br(sigma_1_up) );
  answer.push_back( get_br(sigma_2_up) );
  return answer;
}

#include "/home/pmandrik/work/PMANDRIK_LIBRARY/pmlib_root_hist_drawer.hh"
using namespace pm;

void plot_results(){
  if( true ){
    string path_signal = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/" ;

    vector< pair<int, int> > mass_points = { 
      pair<int, int>(650,375), 
      pair<int, int>( 900, 600),
      pair<int, int>(1300, 475),
      pair<int, int>(1300, 975),
      pair<int, int>(1700, 475),
      pair<int, int>(1700, 1225),
      pair<int, int>(1900, 475),
      pair<int, int>(1900, 1600),
    };

    map<pair<int, int>, vector<double> > points;
    for(auto point : mass_points){
      //points[ point ] = get_trex_limit("results_cuts/resultspd_NMSSM_XYH_ttbb_MX_" + to_string(point.first) + "_MY_" + to_string(point.second) + "_15_1.root");
    }

    for(auto point : mass_points){
      cout << endl;
      get_trex_limit("results_cuts/resultspd_NMSSM_XYH_ttbb_MX_" + to_string(point.first) + "_MY_" + to_string(point.second) + "_15_1.root");
      points[ point ] = get_trex_limit("results_eval/resultspd_NMSSM_XYH_ttbb_MX_" + to_string(point.first) + "_MY_" + to_string(point.second) + "eval_35_1.root");
    }

    BrasilDrawer bd0;
    bd0.style = new CanvasStyle();
    bd0.label_y = "#sigma#times Br(X#rightarrow Y H)#times Br(Y #rightarrow tt), [fb]";
    bd0.label_x = "(M_{X}, M_{Y}) [GeV]";
    bd0.left_text_src = "LHC CMS Run II Projection (137 fb^{-1}, 13 TeV)";
    bd0.right_text_src = "Semi-leptonic t#bar{t} decay";

    for(auto point : mass_points){
      vector<double> vals = points.find( point )->second;
      bd0.AddPoint( "(" + to_string(point.first) + ", " + to_string(point.second) + ")" , vals[0] , vals[1] , vals[2] , vals[3] , vals[4] , 0 );
    }

    TCanvas * canv = bd0.Draw( false );

    //vector<float> no_sys = { 3.48763, 5.90739, 4.45327, 3.48763, 6.15732, 3.83981, 5.77107, 5.86195, 5.90739, 3.37403, 6.11188, 5.06673, 5.97556 };
    //TH1D * extra_hist = bd0.GetHist( "no sys", no_sys );
    //extra_hist->SetLineColor(2);
    // extra_hist->Draw("same hist");
    canv->Print("limits_plot_eval.pdf");
  }

}


