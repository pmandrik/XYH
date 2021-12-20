
path=/home/pmandrik/work/projects/XYH/XYH/local_generation/def_fix_2/
for file in $path*; do

  pname=`basename $file`

  if [[ "$pname" == *"tbar_l"* ]]; then
    sname="tbar_l"
    pname=${pname::-7}
    echo $path $pname $sname
    root -l -b -q 'lhe_to_root.cpp("'$path'","'$pname'","'$sname'")'
  elif [[ "$pname" == *"t_l"* ]]; then
    sname="t_l"
    pname=${pname::-4}
    echo $path $pname $sname
    root -l -b -q 'lhe_to_root.cpp("'$path'","'$pname'","'$sname'")'
  fi
  break
done
