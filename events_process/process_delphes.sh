
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
