#include "LHEF.h"
#include "Delphes.C"
#include "Delphes_help_func.C"

// TODO
// read tree with matching and tree with event content
// write matching result and jets and leptons prope

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

void tree_to_csv(){

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

