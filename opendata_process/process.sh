
file=/home/pmandrik/work/projects/XYH/SAMPLES/ttbar.root
file_ttbar=/home/pmandrik/work/projects/XYH/process_ttbar2/ttbar.root
file_higgs=/home/pmandrik/work/projects/XYH/process_ttbar2/higgs.root
path_train=/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_train

cut=""
#root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_650_MY_375_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_650_MY_375.txt\", \""$cut"\", 375)"
#root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_900_MY_600_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_900_MY_600.txt\", \""$cut"\", 600)"
#root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1300_MY_475_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1300_MY_475.txt\", \""$cut"\", 475)"
#root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1300_MY_975_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1300_MY_975.txt\", \""$cut"\", 975)"
#root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1700_MY_475_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1700_MY_475.txt\", \""$cut"\", 475)"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1700_MY_1225_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1700_MY_1225.txt\", \""$cut"\", 1225)"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1900_MY_475_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1900_MY_475.txt\", \""$cut"\", 475)"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1900_MY_1600_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1900_MY_1600.txt\", \""$cut"\", 1600)"

exit

for cut in "lf" "hf"; do
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_650_MY_375_"$cut".root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_650_MY_375.txt\", \""$cut"\", 375)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_900_MY_600_"$cut".root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_900_MY_600.txt\", \""$cut"\", 600)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1300_MY_475_"$cut".root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1300_MY_475.txt\", \""$cut"\", 475)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1300_MY_975_"$cut".root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1300_MY_975.txt\", \""$cut"\", 975)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1700_MY_475_"$cut".root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1700_MY_475.txt\", \""$cut"\", 475)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1700_MY_1225_"$cut".root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1700_MY_1225.txt\", \""$cut"\", 1225)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1900_MY_475_"$cut".root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1900_MY_475.txt\", \""$cut"\", 475)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1900_MY_1600_"$cut".root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1900_MY_1600.txt\", \""$cut"\", 1600)"
done;
exit

root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_650_MY_375_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_900_MY_600.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_900_MY_600_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_900_MY_600.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1300_MY_475_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1300_MY_475.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1300_MY_975_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1300_MY_975.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1700_MY_475_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1700_MY_475.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1700_MY_1225_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1700_MY_1225.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1900_MY_475_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1900_MY_475.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1900_MY_1600_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1900_MY_1600.txt\")"

exit

root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_650_MY_375_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_650_MY_375.txt\")"
exit

root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_900_MY_600_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_900_MY_600.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1300_MY_475_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1300_MY_475.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1300_MY_975_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1300_MY_975.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1700_MY_475_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1700_MY_475.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1700_MY_1225_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1700_MY_1225.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1900_MY_475_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1900_MY_475.txt\")"
root -l -b -q "process_delphes.cpp(\""$file_higgs"\",\"pd_file_1900_MY_1600_ttH.root\", \"\", \"csv_higg.csv\" ,\"$path_train/eval2_ttH_MX_1900_MY_1600.txt\")"
exit

root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_file_650_MY_375.root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_650_MY_375.txt\")"
root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_file_900_MY_600.root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_900_MY_600.txt\")"
root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_file_1300_MY_475.root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1300_MY_475.txt\")"
root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_file_1300_MY_975.root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1300_MY_975.txt\")"
root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_file_1700_MY_475.root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1700_MY_475.txt\")"
root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_file_1700_MY_1225.root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1700_MY_1225.txt\")"
root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_file_1900_MY_475.root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1900_MY_475.txt\")"
root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_file_1900_MY_1600.root\", \"\", \"csv_tbar.csv\" ,\"$path_train/eval2_ttbar_MX_1900_MY_1600.txt\")"
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

root -l -b -q "make_interface_back.cpp(\""$file_ttbar"\", \"mygenparticle/Events\")"
mv Events.C Events_mygenparticles.C
mv Events.h Events_mygenparticles.h
sed 's/Events/Events_mygenparticles/g' -i Events_mygenparticles.C
sed 's/Events/Events_mygenparticles/g' -i Events_mygenparticles.h
