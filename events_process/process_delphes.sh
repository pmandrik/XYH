path=/home/me/work/projects/XYZ/back/
path=/home/pmandrik/work/projects/XYZ/back/

path=/home/pmandrik/work/projects/XYH/SAMPLES/signal/
for folder in $path/NMSSM_*; do
#for folder in $path/NMSSM_XYH_ttbb_MX_650_MY_375; do
  pname=`basename $folder` # run_01_decayed_1
  file=$folder/$pname"_t_l"/run_01_decayed_1/tag_1_delphes_events.root
  file_lhe=$folder/$pname"_t_l"/run_01_decayed_1/unweighted_events.lhe
  file2=$folder/$pname"_tbar_l"/run_01_decayed_1/tag_1_delphes_events.root
  file_lhe2=$folder/$pname"_tbar_l"/run_01_decayed_1/unweighted_events.lhe
  echo $file

  oname0="lhe_"$pname"_t_l.root"
  oname1="lhe_"$pname"_tbar_l.root"

  if [ ! -f "$oname0" ]; then
    root -l -b -q 'lhe_to_root.cpp("'$file_lhe'","'$pname'","t_l", "'$oname0'")'
  fi

  if [ ! -f "$oname1" ]; then
    root -l -b -q 'lhe_to_root.cpp("'$file_lhe2'","'$pname'","tbar_l", "'$oname1'")'
  fi

  root -l -b -q "make_interface.cpp(\""$file"\")"
  #root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_"$pname".root\", \"$file_lhe\")"
  #root -l -b -q "matcher.cpp(\""$file"\",\""$file2"\",\"match_"$pname".root\", \"$oname0\", \"$oname1\")"
  root -l -b -q "process_delphes.cpp(\""$file"\",\""$file2"\",\"pd_"$pname".root\", \"$oname0\", \"$oname1\",\"csv2_"$pname".csv\")"
  #root -l -b -q "tree_to_csv.cpp(\""$file"\",\""$file2"\",\"match_"$pname".root\", \"csv_"$pname".csv\")"
done
exit

path=/home/pmandrik/work/projects/XYH/XYH/local_generation/def_fix_2/
for file in $path*; do

  pname=`basename $file`

  if [[ "$pname" == *"tbar_l"* ]]; then
    sname="tbar_l"
    pname=${pname::-7}
    file=$path$pname"_"$sname"/"$pname"/Events/run_01_decayed_1/tag_1_delphes_events.root"
    echo $file
    root -l -b -q "make_interface.cpp(\""$file"\")"
    root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_"$pname".root\")"
    break
  elif [[ "$pname" == *"t_l"* ]]; then
    sname="t_l"
    pname=${pname::-4}
    file=$path$pname"_"$sname"/"$pname"/Events/run_01_decayed_1/tag_1_delphes_events.root"
    echo $file
    root -l -b -q "make_interface.cpp(\""$file"\")"
    root -l -b -q "process_delphes.cpp(\""$file"\",\"pd_"$pname".root\")"
    break
  fi

done
