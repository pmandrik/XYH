file=/home/pmandrik/work/projects/XYH/SAMPLES/ttbar.root
file_ttbar=/home/pmandrik/work/projects/XYH/process_ttbar2/ttbar.root
file_higgs=/home/pmandrik/work/projects/XYH/process_ttbar2/higgs.root
path_train=/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_train

for cut in "hf"; do
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1700_MY_475_"$cut".root\", \"\", \"csv_tbarx.csv\" ,\"$path_train/eval2_ttbar_MX_1700_MY_475.txt\", \""$cut"\", 475)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1700_MY_1225_"$cut".root\", \"\", \"csv_tbarx.csv\" ,\"$path_train/eval2_ttbar_MX_1700_MY_1225.txt\", \""$cut"\", 1225)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1900_MY_475_"$cut".root\", \"\", \"csv_tbaxr.csv\" ,\"$path_train/eval2_ttbar_MX_1900_MY_475.txt\", \""$cut"\", 475)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1900_MY_1600_"$cut".root\", \"\", \"csv_tbaxr.csv\" ,\"$path_train/eval2_ttbar_MX_1900_MY_1600.txt\", \""$cut"\", 1600)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_650_MY_375_"$cut".root\", \"\", \"csv_tbarx.csv\" ,\"$path_train/eval2_ttbar_MX_650_MY_375.txt\", \""$cut"\", 375)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_900_MY_600_"$cut".root\", \"\", \"csv_tbarx.csv\" ,\"$path_train/eval2_ttbar_MX_900_MY_600.txt\", \""$cut"\", 600)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1300_MY_475_"$cut".root\", \"\", \"csv_tbarx.csv\" ,\"$path_train/eval2_ttbar_MX_1300_MY_475.txt\", \""$cut"\", 475)"
  root -l -b -q "process_delphes.cpp(\""$file_ttbar"\",\"pd_file_1300_MY_975_"$cut".root\", \"\", \"csv_tbarx.csv\" ,\"$path_train/eval2_ttbar_MX_1300_MY_975.txt\", \""$cut"\", 975)"
done;
exit
