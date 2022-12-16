set +x

scaner_exe=/home/pmandrik/work/projects/SCANER/ScannerS/build/TRSMBroken

npoints=100000

# for index in 0 1 2 3 4 5 6 7; do
for index in 6 7; do
  mx=`python3 get_mass_point.py $index 0`
  my=`python3 get_mass_point.py $index 1`


  cp TRSMBroken.ini TRSMBroken_MX$mx"_"MY$my.ini
  sed -i 's/%MX%/'$mx'/g'       TRSMBroken_MX$mx"_"MY$my.ini
  sed -i 's/%MY%/'$my'/g'       TRSMBroken_MX$mx"_"MY$my.ini

  $scaner_exe output_file_MX$mx"_"MY$my.tsv --config TRSMBroken_MX$mx"_"MY$my.ini scan -n $npoints

done;

