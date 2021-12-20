

void make_interface( string input_file ){
  TFile * file = TFile::Open( input_file.c_str() );
  TTree * t = (TTree*) gDirectory->Get("Delphes");
  t->MakeClass();
}

