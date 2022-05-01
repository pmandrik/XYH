

void make_interface_back( string input_file, string tree_path ){
  TFile * file = TFile::Open( input_file.c_str() );
  TTree * t1 = (TTree*) gDirectory->Get(tree_path.c_str());
  t1->MakeClass();
}

