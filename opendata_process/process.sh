
file=/home/pmandrik/work/projects/XYH/SAMPLES/ttbar.root

root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_file.root\")"

exit

root -l -b -q "make_interface_back.cpp(\""$file"\", \"myelectrons/Events\")"
mv Events.C Events_myelectrons.C
mv Events.h Events_myelectrons.h
sed 's/Events/Events_myelectrons/' -i Events_myelectrons.C
sed 's/Events/Events_myelectrons/' -i Events_myelectrons.h

root -l -b -q "make_interface_back.cpp(\""$file"\", \"mymuons/Events\")"
mv Events.C Events_mymuons.C
mv Events.h Events_mymuons.h
sed 's/Events/Events_mymuons/' -i Events_mymuons.C
sed 's/Events/Events_mymuons/' -i Events_mymuons.h

root -l -b -q "make_interface_back.cpp(\""$file"\", \"mymets/Events\")"
mv Events.C Events_mymets.C
mv Events.h Events_mymets.h
sed 's/Events/Events_mymets/' -i Events_mymets.C
sed 's/Events/Events_mymets/' -i Events_mymets.h

root -l -b -q "make_interface_back.cpp(\""$file"\", \"myjets/Events\")"
mv Events.C Events_myjets.C
mv Events.h Events_myjets.h
sed 's/Events/Events_myjets/' -i Events_myjets.C
sed 's/Events/Events_myjets/' -i Events_myjets.h
