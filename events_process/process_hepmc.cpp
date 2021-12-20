// Include files

#include "HepMC/IO_GenEvent.h"
#include "HepMC/GenEvent.h"

void process_hepmc(){
  gSystem->Load("/home/pmandrik/work/soft/HepMC-2.06.11-build/lib/libHepMC.so.4.0.0");

  string path = "/home/pmandrik/work/projects/XYH/XYH/local_generation/def_fix/NMSSM_XYH_ttbb_MX_675_MY_375_t_l/NMSSM_XYH_ttbb_MX_675_MY_375/Events/run_01_decayed_1/1.hepmc";
  HepMC::IO_GenEvent ascii_in( path.c_str(), std::ios::in );
  HepMC::GenEvent* evt = ascii_in.read_next_event();

  int event_counter = 0;
  while( evt ) {
    bool ok = false;

    HepMC::GenParticle * higgs;
    for( HepMC::GenEvent::particle_iterator it = evt->particles_begin(); it != evt->particles_end(); it++ ){
      HepMC::GenParticle * particle  = *it;

      if( particle->status() != 1 ) continue;
      if( abs(particle->pdg_id()) == 11 or abs(particle->pdg_id()) == 13 or abs(particle->pdg_id()) == 15 ){
        // cout << particle->pdg_id() << " " << particle->status() << " " << particle->momentum().perp() << " " << particle->momentum().eta() << endl;
        if( particle->momentum().perp() < 10 ) continue;
        if( abs(particle->momentum().eta()) > 2.5 ) continue;
        ok = true;
      }
    }

    cout << event_counter << " " << ok << endl;

    delete evt;
    ascii_in >> evt;

    event_counter++;
    if(event_counter > 100) break;
  }
}
