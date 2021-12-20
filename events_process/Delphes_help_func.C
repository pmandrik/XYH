
TLorentzVector make_met(Delphes * reader, int index){
  TLorentzVector vec;
  if(index >=0) vec.SetPtEtaPhiM(reader->MissingET_MET[index], reader->MissingET_Eta[index], reader->MissingET_Phi[index], 0 );
  return vec;
}

TLorentzVector make_jet(Delphes * reader, int index){
  TLorentzVector vec;
  if(index >=0) vec.SetPtEtaPhiM(reader->Jet_PT[index], reader->Jet_Eta[index], reader->Jet_Phi[index], reader->Jet_Mass[index] );
  return vec;
}

TLorentzVector make_muon(Delphes * reader, int index){
  TLorentzVector vec;
  if(index >=0) vec.SetPtEtaPhiM(reader->Muon_PT[index], reader->Muon_Eta[index], reader->Muon_Phi[index], 0.105 );
  return vec;
}

TLorentzVector make_electron(Delphes * reader, int index){
  TLorentzVector vec;
  vec.SetPtEtaPhiM(reader->Electron_PT[index], reader->Electron_Eta[index], reader->Electron_Phi[index], 0.005 );
  return vec;
}

/*
TLorentzVector make_photon(Delphes * reader, int & index){
  TLorentzVector vec;
  vec.SetPtEtaPhiM(reader->Photon_PT[index], reader->Photon_Eta[index], reader->Photon_Phi[index], 0 );
  return vec;
}
*/

TLorentzVector make_genjet(Delphes * reader, int index){
  TLorentzVector vec;
  vec.SetPtEtaPhiM(reader->GenJet_PT[index], reader->GenJet_Eta[index], reader->GenJet_Phi[index], reader->GenJet_Mass[index] );
  return vec;
}

void get_tlvs_jets(Delphes * reader, vector<int> & indexes, vector<TLorentzVector> & answer){
  for(auto index : indexes){
    TLorentzVector vec = make_genjet( reader, index );  
    answer.push_back( vec );
  }
}

void get_tlvs_candidates( vector<TLorentzVector> & inputs, vector<TLorentzVector> & answer ){
  for( int i = 0; i < inputs.size(); i++){
    for( int j = i+1; j < inputs.size(); j++){
      answer.push_back( inputs[i] + inputs[j] );
    }
  }
}

void get_tlvs_candidates( vector<TLorentzVector> & inputs_a, vector<TLorentzVector> & inputs_b, vector<TLorentzVector> & answer ){
  for( int i = 0; i < inputs_a.size(); i++){
    for( int j = 0; j < inputs_b.size(); j++){
      answer.push_back( inputs_a[i] + inputs_b[j] );
    }
  }
}

TLorentzVector get_nearest_vec(const TLorentzVector & dir, const vector<TLorentzVector> & vecs){
  double dR = dir.DeltaR( vecs.at(0) );
  int best_index = 0;

  for(int i = 1; i < vecs.size(); i++){
    double alt_dR = dir.DeltaR( vecs.at(i) );
    if( alt_dR < dR ){
      best_index = i;
      dR = alt_dR;
    }
  }
  
  return vecs.at( best_index );
}

// create unic samples from with 'total' size with 'selected' size
void create_unic_samples( int total, int selected, vector< vector<int> > & answer, bool print=false ){
  vector<int> sample;
  for(int i = 0; i < selected; i++) sample.push_back( i );
  if( selected > total ){
    for(int i = total; i < selected; i++) sample[ i ] = -1;
    selected = total;
  }

  int i = selected-1;
  while( i >= 0){
    if(sample[i] + 1 < total - (selected-i-1) ) { 
      answer.push_back( sample );
      sample[i] += 1;
      for(int k = i + 1; k < selected; k++) sample[k] = sample[k-1] + 1;
      i = selected-1;
      continue; 
    }
    i--;
  }
  answer.push_back( sample );

  if( print ){
    cout << "samples: " << answer.size() << " " <<  TMath::Binomial(total, selected) << endl;
    for( auto s : answer){
      for(int val : s) cout << val << " ";
      cout << "\n";
    }
  }
}

void create_unic_samples( vector<int> indexes, int selected, vector< vector<int> > & answer, bool print=false ){
  vector< vector<int> > sample_indexes;
  create_unic_samples( indexes.size(), selected, sample_indexes, false);

  for( int i = 0; i < sample_indexes.size(); i ++){
    answer.push_back( vector<int>() );
    for( int j = 0; j < sample_indexes[i].size(); j ++){
      int val = sample_indexes[i][j];
      if( val == -1 ) answer[i].push_back( -1 );
      else            answer[i].push_back( indexes[ sample_indexes[i][j] ] );
    }
  }

  if( print ){
    for( auto s : answer){
      for(int val : s) cout << val << " ";
      cout << "\n";
    }
  }
}

void create_groups_from_unic_sample( const vector<int> & group_sizes, vector< vector< vector<int> > > & answer, bool print=false ){
  int N_groups = group_sizes.size();
  int N_elements = std::accumulate(group_sizes.begin(), group_sizes.end(), 0);
  
  vector<int> sample = vector<int>(N_elements, 0);
  vector<int> group_content = vector<int>(N_groups, 0);
  group_content[0] = N_elements;

  int i = N_elements-1;
  while( i >= 0){
    if(sample[i] + 1 < N_groups ) { 

      bool good_group = true;
      for(int k = 0; k < N_groups; k++){
        good_group = good_group and (group_content[k] == group_sizes[k]);
        if(not good_group) break;
      }
      if(good_group){
        vector< vector<int> > group_set = vector< vector<int> >(N_groups);
        for(int k = 0; k < N_elements; k++){
          group_set[ sample[k] ].push_back( k );
        }
        answer.push_back( group_set );
      }

      sample[i] += 1;

      group_content[ sample[i]-1 ] -= 1;
      group_content[ sample[i]   ] += 1;

      for(int k = i + 1; k < N_elements; k++){
        group_content[ sample[k] ] -= 1;
        group_content[ 0 ] += 1;
        sample[k] = 0;
      }      

      i = N_elements-1;
      continue; 
    }
    i--;
  }

  if( print ){
    for(auto item : answer){
      cout << endl;
      for(auto gp : item){
        cout << "{";
        for(auto g : gp) cout << g << ",";
        cout << "}";
      }
    }
  }
}

void map_groups_to_samples( vector<int> & samples, vector< vector<int> > & groups, vector< vector<int> > & answer ){
  for(int i = 0; i < groups.size(); ++i){
    vector<int> sanswer;
    for(int j = 0; j < groups[i].size(); ++j){
      sanswer.push_back( samples[ groups[i][j] ] );
    }
    answer.push_back( sanswer );
  }
}

vector< vector<int> > get_group_combinations( vector<int> group_sizes, bool print = false ){
  vector< vector<int> > answer;
  int n_groups = group_sizes.size();
  vector<int> sample = vector<int>(n_groups, 0);

  int i = n_groups-1;
  while( i >= 0){
    answer.push_back( sample );
    if(sample[i] + 1 < group_sizes[i] ) { 
      sample[i] += 1;
      for(int k = i + 1; k < n_groups; k++) sample[k] = 0;
      i = n_groups-1;
      continue; 
    }
    i--;
  }

  if( print ){
    for( auto s : answer){
      for(int val : s) cout << val << " ";
      cout << "\n";
    }
  }

  return answer;
};

  // reconstruct Higgs from t->bW->b nu l decay
  bool reconstruct_t_from_bW(const TLorentzVector & P_bl, const TLorentzVector & P_n, TLorentzVector & P_n_answer, TLorentzVector & P_t_answer) {
    double m_h = 172.76;
		double C = (m_h - P_bl.M()) * (m_h + P_bl.M()) * 0.5 + P_bl.Px() * P_n.Px() + P_bl.Py() * P_n.Py();
		double a = P_bl.E() * P_bl.E() - P_bl.Pz() * P_bl.Pz();
		double b = -2 * C * P_bl.Pz();
		double c = P_bl.E() * P_bl.E() * P_n.Pt() * P_n.Pt() - C * C;

		if(a < 0.00000001) return false;
		b /= a;
		c /= a;
		double D = b * b - 4 * c;
		double x = -b / 2;

		if(D > 0) {
			double k = sqrt(D) / 2;
			
			TLorentzVector p1, p2;
			p1.SetXYZM(P_n.Px(), P_n.Py(), x - k, P_n.M());
			p2.SetXYZM(P_n.Px(), P_n.Py(), x + k, P_n.M());

      TLorentzVector P_H1 = p1 + P_bl;
      TLorentzVector P_H2 = p2 + P_bl;

      // if( P_H1.M() < P_H2.M() ) P_n_answer = p1;
      // else                      P_n_answer = p2;

      if( TMath::Abs( p1.Pz() ) < TMath::Abs( p2.Pz() ) ) P_n_answer = p1;
      else                                                P_n_answer = p2;
		}
		else{
      P_n_answer.SetXYZM(P_n.Px(), P_n.Py(), x, P_n.M());
    }

    P_t_answer = P_n_answer + P_bl;
    return true;
  }


TLorentzVector make_tlv(Delphes * reader, int & index, string & type){
  TLorentzVector vec;
  if(type == "jet")      return make_jet(reader, index);
//if(type == "photon")   return make_photon(reader, index);
  if(type == "muon")     return make_muon(reader, index);
  if(type == "electron") return make_electron(reader, index);
  cout << "Unknow type " << type << endl;
  return vec;
} 



