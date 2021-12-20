
expect -c ' spawn -noecho root -l
            send "gInterpreter->AddIncludePath(\"/home/pmandrik/work/soft/HepMC-2.06.11\");\r"
            send "gSystem->Load(\"/home/pmandrik/work/soft/HepMC-2.06.11-build/lib/libHepMC.so.4.0.0\");\r"
            send ".x process_hepmc.cpp\r"
            send ".q\r"
            interact '

# send "gSystem->Load(\"/home/pmandrik/soft/hepmc2.07-beta00/lib/libHepMC.so.4.0.0\");\r"
