

TLorentzVector make_met(Events_mymets * reader, int index){
  TLorentzVector vec;
  if(index >=0) vec.SetPtEtaPhiM(reader->met_pt, 0, reader->met_phi, 0 );
  return vec;
}

TLorentzVector make_jet(Events_myjets * reader, int index){
  TLorentzVector vec;
  if(index >=0) vec.SetPtEtaPhiM(reader->jet_pt->at(index), reader->jet_eta->at(index), reader->jet_phi->at(index), reader->jet_mass->at(index) );
  return vec;
}

TLorentzVector make_muon(Events_mymuons * reader, int index){
  TLorentzVector vec;
  if(index >=0) vec.SetPtEtaPhiM(reader->muon_pt->at(index), reader->muon_eta->at(index), reader->muon_phi->at(index), 0.105 );
  return vec;
}

TLorentzVector make_electron(Events_myelectrons * reader, int index){
  TLorentzVector vec;
  vec.SetPtEtaPhiM(reader->electron_pt->at(index), reader->electron_eta->at(index), reader->electron_phi->at(index), 0.005 );
  return vec;
}

void get_tlvs_jets(Events_myjets * reader, vector<int> & indexes, vector<TLorentzVector> & answer){
  for(auto index : indexes){
    TLorentzVector vec = make_jet( reader, index );  
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
  answer.push_back( sample );

  int i = n_groups-1;
  while( i >= 0){    
    if(sample[i] + 1 < group_sizes[i] ) { 
      sample[i] += 1;
      for(int k = i + 1; k < n_groups; k++) sample[k] = 0;
      i = n_groups-1;
      answer.push_back( sample );
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

  // reconstruct decay x -> y nu
  // know m_x, P_y, and p_nu_x, p_nu_y, dont know p_nu_z
  bool reconstruct_decay(double m_x, const TLorentzVector & P_y, const TLorentzVector & P_n, TLorentzVector & P_n_answer, TLorentzVector & P_x_answer) {
		double C = (m_x - P_y.M()) * (m_x + P_y.M()) * 0.5 + P_y.Px() * P_n.Px() + P_y.Py() * P_n.Py();
		double a = P_y.E() * P_y.E() - P_y.Pz() * P_y.Pz();
		double b = -2 * C * P_y.Pz();
		double c = P_y.E() * P_y.E() * P_n.Pt() * P_n.Pt() - C * C;

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

      TLorentzVector P_H1 = p1 + P_y;
      TLorentzVector P_H2 = p2 + P_y;

      // if( P_H1.M() < P_H2.M() ) P_n_answer = p1;
      // else                      P_n_answer = p2;

      if( TMath::Abs( p1.Pz() ) < TMath::Abs( p2.Pz() ) ) P_n_answer = p1;
      else                                                P_n_answer = p2;
		}
		else{
      P_n_answer.SetXYZM(P_n.Px(), P_n.Py(), x, P_n.M());
    }

    P_x_answer = P_n_answer + P_y;
    return true;
  }





// ================================================================== ================================================================== ==================================================================
// write/read TLorentzVectors in tree
struct ftlv;
vector<ftlv*> ftlvs;
map<string, ftlv*> ftlvs_map;
bool ftlv_write = true;

struct ftlv {
  ftlv(string name_, TTree * tree, bool write = ftlv_write){
    if(not tree) return;
    name = name_;

    vector<float*> brunches = {&pt, &pz, &eta, &phi, &m};
    vector<string> names = {"_pt", "_pz", "_eta", "_phi", "_m"};
    
    if( write ){
      for(int i = 0; i < brunches.size(); i ++){
        tree->Branch( (name + names.at(i)).c_str(), brunches.at(i));
      }
    } else {
      for(int i = 0; i < brunches.size(); i ++){
        tree->SetBranchAddress( (name + names.at(i)).c_str(), brunches.at(i) );
      }
    }

    ftlvs.push_back( this );
    ftlvs_map[ name ] = this;
  };

  void load_tlv(){
    tlv.SetPtEtaPhiM( pt, eta, phi, m );
  }

  void set(float x, float y, float z, float z4){
    tlv.SetPxPyPzE( x, y, z, z4 );
    set( tlv );
  }

  void set(TLorentzVector v){
    tlv = v;
    pt  = v.Pt();
    pz  = v.Pz();
    eta = v.Eta();
    phi = v.Phi();
    m   = v.M();
  }

  void reset(){ 
    tlv = TLorentzVector();
    pt = 0, pz = 0, eta = 0, phi = 0, m = 0;
  }
  
  TLorentzVector tlv;
  float pt = 0, pz = 0, eta = 0, phi = 0, m = 0;
  string name;
};

void load_tlv(){
  for(ftlv * f : ftlvs) f->load_tlv();
}

void ftlv_clear(){
  for(auto item : ftlvs){
    // delete item;
  }
  ftlvs.clear();
  ftlvs_map.clear();
}

// ================================================================== ================================================================== ==================================================================

vector< pair<int,int> > get_XY_mass(string type){
  vector< pair<int,int> > XY_mass = {}; 
  int start_X = 500;
  int start_Y = 475;
  XY_mass.push_back( make_pair(650, 375) );
  for(int X = start_X; X < 2000; X += 200){
    for(int Y = start_Y; Y < 2000; Y += 125){
      if(X - Y <= 200) continue;
      if( X == 1700 and Y == 1350 ) continue;

      if( type == "min" and Y == start_Y ){
        XY_mass.push_back( make_pair(650, 375) );
        continue;
      }
      if( type == "max" and (Y + 125 >= 2000 or X - Y - 125 <= 200) ){
        XY_mass.push_back( make_pair(650, 375) );
        continue;
      }

      XY_mass.push_back( make_pair(X, Y) );    
    }
  }
  return XY_mass;
}

// ================================================================== ================================================================== ==================================================================

TLorentzVector make_particle(Events_mygenparticles * reader, int index){
  TLorentzVector vec;
  vec.SetPtEtaPhiM( reader->GenPart_pt->at(index), reader->GenPart_eta->at(index), reader->GenPart_phi->at(index), reader->GenPart_mass->at(index) );
  return vec;
}

struct particle{
  int id = -1;
  int from_tt = 0;
  TLorentzVector tlv;
};

string get_cat( Events_mygenparticles * reader5 ){
      //cout << "======================" << endl;
      map<string, int> parts;
      parts["b"] = 0; 
      parts["c"] = 0;
      parts["l"] = 0; 

      particle wgen1, wgen2;
      vector<particle> gens;

        for(int i = 0; i < reader5->numGenPart; i++){
          //if( reader5->GenPart_pdgId->at(i) == -5 or reader5->GenPart_pdgId->at(i) == 5 ){
          //  cout << i << " " << reader5->GenPart_pdgId->at(i) << " " << reader5->GenPart_status->at(i) << " " << reader5->GenPart_pt->at(i) << endl;
          //}

          // if( reader5->GenPart_pt->at(i) < 25 ) continue;
          if( reader5->GenPart_pt->at(i) < 30 ) continue;
          if( TMath::Abs(reader5->GenPart_eta->at(i)) > 2.4 ) continue;

          if( abs(reader5->GenPart_pdgId->at(i)) == 10000+5 ) continue;
          if( abs(reader5->GenPart_pdgId->at(i)) == 10000-5 ) continue;

          if( abs( reader5->GenPart_pdgId->at(i)) == 6   ) continue;
          if( abs( reader5->GenPart_pdgId->at(i)) == 24  ){
            if( wgen1.id == -1 ){
              wgen1.id = i;
              wgen1.tlv = make_particle(reader5, i);
            } else {
              wgen2.id = i;
              wgen2.tlv = make_particle(reader5, i);
            }
          } else {
            particle p;
            p.id = i;
            p.tlv = make_particle(reader5, i);
            gens.push_back( p );
          }
        }

        float dm_best = 9999990;
        pair<int, int> best_indexes;

        for(int i = 0; i < gens.size(); ++i){
          for(int j = i+1; j < gens.size(); ++j){
            float dm = abs( wgen1.tlv.M() - (gens[i].tlv + gens[j].tlv).M() );
            if( dm_best < dm ) continue;
            dm_best = dm;
            best_indexes = make_pair(i, j);
          }
        }

        if( dm_best < 0.1 ){
          gens[best_indexes.first].from_tt = 1;
          gens[best_indexes.second].from_tt = 1;
          /// cout << dm_best << " " << gens[best_indexes.first].id << " " << gens[best_indexes.second].id << " " << wgen1.tlv.M()  << endl;
        }

        dm_best = 9999990;
        for(int i = 0; i < gens.size(); ++i){
          for(int j = i+1; j < gens.size(); ++j){
            if( gens[i].from_tt ) continue;
            if( gens[j].from_tt ) continue;

            float dm = abs( wgen2.tlv.M() - (gens[i].tlv + gens[j].tlv).M() );
            if( dm_best < dm ) continue;
            dm_best = dm;
            best_indexes = make_pair(i, j);
          }
        }

        if( dm_best < 0.1 ){
          gens[best_indexes.first].from_tt = 1;
          gens[best_indexes.second].from_tt = 1;
          /// cout << dm_best << " " << gens[best_indexes.first].id << " " << gens[best_indexes.second].id << " " << wgen2.tlv.M()  << endl;
        }

        for(int i = 0; i < gens.size(); ++i){
            if( gens[i].from_tt ) continue;

            int id = gens[i].id;
            if( abs( reader5->GenPart_pdgId->at(id)) == 5   ) parts["b"] += 1;
            if( abs( reader5->GenPart_pdgId->at(id)) == 4   ) parts["c"] += 1;
            if( abs( reader5->GenPart_pdgId->at(id)) < 4   )  parts["l"] += 1;
        }

     // for(auto it : parts){
      //  cout << it.first << " " << it.second << endl;
     // }

      string cat = "lf";
      // if( parts["l"] > 0 ) cat = "lf";
      if( parts["c"] > 0 ) cat = "hf";
      if( parts["b"] > 0 ) cat = "hf";
      if( parts["b"] > 1 ) cat = "hf";
      // cout << cat << endl;
      return cat;
}



















