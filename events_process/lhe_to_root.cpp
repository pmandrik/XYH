#include "LHEF.h"
#include "Delphes.C"
#include "Delphes_help_func.C"

float min_ftlv_dR_v(ftlv & p, vector<ftlv> others){
  double dr = 999999 ;
  for(auto other : others){
    dr = min(dr, p.tlv.DeltaR( other.tlv) );
  }
  return dr ;
}

void lhe_to_root(string path = "/home/pmandrik/work/projects/XYH/XYH/local_generation/def_fix/", string process = "NMSSM_XYH_ttbb_MX_1700_MY_475", string subprocess = "tbar_l", string oname = "") {
  string postfix = "/Events/run_01_decayed_1/";
  string lhe_name = "unweighted_events.lhe";

  string gz_file = path + process + "_" + subprocess + "/" + process + postfix + lhe_name + ".gz";
  string olhe_name = process + "_" +  subprocess + ".lhe";
  olhe_name = path;
  string oroot_name = oname;

  /*
  if(path.size()){
    // gzip -d file.gz
    system( ("cp " + gz_file + " " + olhe_name + ".gz").c_str() );
    system( ("gzip -df " + olhe_name + ".gz").c_str() );
  } else {
    olhe_name = process;
    std::string base_filename = process.substr(process.find_last_of("/") + 1);
    std::string::size_type const p(base_filename.find_last_of('.'));
    std::string file_without_extension = base_filename.substr(0, p);
    oroot_name = file_without_extension + ".root";
  }
  */

  std::ifstream lhe_file ( olhe_name );

  LHEF::Reader * reader = new LHEF::Reader( lhe_file );

  TFile * ofile = new TFile(oroot_name.c_str(), "RECREATE");
  TTree * tree = new TTree("ttree", "ttree");

  ftlv_write = true;
  ftlv H("H", tree), Y("Y", tree), X("X", tree), Y_reco("Y_reco", tree), X_reco("X_reco", tree);
  ftlv t("t", tree), tbar("tbar", tree),  t_l_reco("t_l_reco", tree), t_q_reco("t_q_reco", tree), b_H("b_H", tree), bbar_H("bbar_H", tree), v("v", tree), l("l", tree), q("q", tree), qbar("qbar", tree);
  ftlv W("W", tree), Wbar("Wbar", tree), W_l_reco("W_l_reco", tree), b_t("b_t", tree), bbar_t("bbar_t", tree);

  /*
  bool do_check = false;
  if(do_check){
    ftlv W_reco("W_reco", tree), Wbar_reco("Wbar_reco", tree), H_reco("H_reco", tree), t_reco("t_reco", tree), tbar_reco("tbar_reco", tree), Y_reco("Y_reco", tree);
  }
  */

  float dR_bb_h, dR_qq_W, dR_WW, dR_bb_t, dR_l_nearest;
  int qbar_id, q_id, l_id;
  tree->Branch( "dR_bb_h", &dR_bb_h);
  tree->Branch( "dR_qq_W", &dR_qq_W);
  tree->Branch( "dR_WW",   &dR_WW);
  tree->Branch( "dR_bb_t",   &dR_bb_t);
  tree->Branch( "l_id",   &l_id);
  tree->Branch( "q_id",   &q_id);
  tree->Branch( "qbar_id",   &qbar_id);
  tree->Branch( "dR_l_nearest",   &dR_l_nearest);

  int veto = 0;
  tree->Branch( "veto", &veto );

  int channel = 0;
  tree->Branch( "channel", &channel );

  int n_events = 0;
  while( reader->readEvent() ){
    veto = 0;
    if( reader->hepeup.NUP != 17){
      veto = 1;
      tree->Fill();
      n_events++;
      continue; 
    }

    qbar_id = -1;
    q_id    = -1;
    l_id    = -1;
    for(ftlv * f : ftlvs){
      f->reset();
    }
    
    // run information
    reader->heprup;

    // event information
    reader->hepeup;

    string channel = "";
    map<int,int> kinds;
    for(int i = 0, NUP = reader->hepeup.NUP; i < NUP; i++){
      int IDUP = reader->hepeup.IDUP.at(i);
      int ISTUP = reader->hepeup.ISTUP.at(i);
      std::pair<int,int> MOTHUP = reader->hepeup.MOTHUP.at(i);
      std::vector<double> PUP   = reader->hepeup.PUP.at(i);  // (Px, Py, Pz, E and M in GeV)

      kinds[i+1] = IDUP;

      // cout << i << " " << PUP[0] << " " << PUP[1]  << " " << PUP[2]  << " " << PUP[3] << " " << IDUP << endl;

      if( IDUP == 45  ) X.set( PUP[0], PUP[1], PUP[2], PUP[3] );
      if( IDUP == 35  ) Y.set( PUP[0], PUP[1], PUP[2], PUP[3] );
      if( IDUP == 25  ) H.set( PUP[0], PUP[1], PUP[2], PUP[3] );
      if( IDUP == 24  ) W.set( PUP[0], PUP[1], PUP[2], PUP[3] );
      if( IDUP == -24 ) Wbar.set( PUP[0], PUP[1], PUP[2], PUP[3] );

      if( IDUP == 6  ) t.set( PUP[0], PUP[1], PUP[2], PUP[3] );
      if( IDUP == -6 ) tbar.set( PUP[0], PUP[1], PUP[2], PUP[3] );

      if( abs(IDUP) == 11 or abs(IDUP) == 13 or abs(IDUP) == 15 ) {l.set( PUP[0], PUP[1], PUP[2], PUP[3] ); l_id = IDUP;};
      if( abs(IDUP) == 12 or abs(IDUP) == 14 or abs(IDUP) == 16 ) v.set( PUP[0], PUP[1], PUP[2], PUP[3] );

      if( abs(IDUP) < 6 ){
        int mother_kind = kinds[ MOTHUP.first ];
        if( abs(mother_kind) == 6 ) {
          if( IDUP < 0 ) bbar_t.set( PUP[0], PUP[1], PUP[2], PUP[3] );
          else           b_t.set( PUP[0], PUP[1], PUP[2], PUP[3] );
        } else if( abs(mother_kind) == 25 ) {
          if( IDUP < 0 ) bbar_H.set( PUP[0], PUP[1], PUP[2], PUP[3] );
          else           b_H.set( PUP[0], PUP[1], PUP[2], PUP[3] );
        } else {
          if( IDUP < 0) {qbar.set( PUP[0], PUP[1], PUP[2], PUP[3] ); qbar_id = IDUP; }
          else          {q.set( PUP[0], PUP[1], PUP[2], PUP[3] );    q_id    = IDUP; }
        }
      }
    }

    if( X.tlv.M() < 1 ) cout << n_events << endl;

  /*
    if(do_check){
      if(subprocess == "tbar_l"){
        W_reco.set(qbar.tlv + q.tlv);
        Wbar_reco.set(v.tlv + l.tlv);
      } else {
        Wbar_reco.set(qbar.tlv + q.tlv);
        W_reco.set(v.tlv + l.tlv);
      }

      H_reco.set(b_H.tlv  + bbar_H.tlv);
      t_reco.set(W_reco.tlv + b_t.tlv);
      tbar_reco.set(Wbar_reco.tlv    + bbar_t.tlv);
      Y_reco.set(t_reco.tlv + tbar_reco.tlv);
    }
  */

    dR_bb_h = b_H.tlv.DeltaR( bbar_H.tlv );
    dR_qq_W = q.tlv.DeltaR( qbar.tlv );
    dR_WW   = W.tlv.DeltaR( Wbar.tlv );
    dR_bb_t = b_t.tlv.DeltaR( bbar_t.tlv );

    dR_l_nearest = min_ftlv_dR_v( l, { b_t, bbar_t, b_H, bbar_H, q, qbar } );

    TLorentzVector t_reco_tlv, t_q_reco_tlv,  v_reco_tlv, W_reco_tlv;
    if(subprocess == "tbar_l") reconstruct_t_from_bW( l.tlv + bbar_t.tlv, v.tlv, v_reco_tlv, t_reco_tlv );
    else                       reconstruct_t_from_bW( l.tlv + b_t.tlv,    v.tlv, v_reco_tlv, t_reco_tlv );
    W_reco_tlv = v_reco_tlv + l.tlv;

    if(subprocess == "tbar_l") t_q_reco_tlv = q.tlv + qbar.tlv + b_t.tlv;
    else                       t_q_reco_tlv = q.tlv + qbar.tlv + bbar_t.tlv;

    channel = ( subprocess == "tbar_l" );

    W_l_reco.set( W_reco_tlv );
    t_l_reco.set( t_reco_tlv );
    t_q_reco.set( t_q_reco_tlv );
    if(subprocess == "tbar_l") Y_reco.set( t_reco_tlv + t.tlv );
    else                       Y_reco.set( t_reco_tlv + tbar.tlv );
    X_reco.set( Y_reco.tlv + H.tlv );

    /*
    cout << " === " << endl;
    v_reco_tlv.Print();
    v.tlv.Print();

    t_reco_tlv.Print();
    tbar.tlv.Print();

    cout << W_reco_tlv.M() << endl;
    cout << t_reco_tlv.M() << endl;
    cout << tbar.tlv.M() << endl;
    */

    tree->Fill();
    
    n_events++;
    if( n_events > 100000 ) break;
  }

  tree->Write();
  ofile->Write();
  ofile->Close();
}

