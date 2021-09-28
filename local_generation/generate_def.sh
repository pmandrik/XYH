
set +x

SEED=1
NEVENTS=100
process="def"

mg_dir=/home/pmandrik/soft/MG5_aMC_v2_6_1/
mg_dir=/home/pmandrik/soft/MG5_aMC_v2_6_5/

sdir=`pwd`
tag="_fix"
wdir=$sdir/$process$tag
mkdir -p $wdir; cd $wdir

run_mg () {
  card_folder=$1
  process=`basename $card_folder`
  echo "PREPARATION ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++" $card_folder $process

  mkdir $process; cd $process
  
  #cp $sdir/customizecards_$card_index.dat customizecards.dat
  #cp "../$card_folder/*_proc_card.dat" proc_card.dat
  find $card_folder -name "*_proc_card.dat" -exec cp '{}' proc_card.dat \;

  echo "WORKDIR GENERATION ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++"
  $mg_dir/bin/mg5_aMC proc_card.dat

  echo "EVENTS GENERATION ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++"
  #cp ../$card_folder/"NMSSM_XYH_bbbb_MX_470_MY_345_run_card.dat"  "HH_"$process/Cards/run_card.dat
  find $card_folder -name "*_run_card.dat" -exec cp '{}' $process/Cards/run_card.dat \;

  sed -i 's/%SEED%/'$SEED'/g'       $process/Cards/run_card.dat
  sed -i 's/%NEVENTS%/'$NEVENTS'/g' $process/Cards/run_card.dat
  #cp $sdir/$process"_pythia_card.dat"  "HH_"$process/Cards/pythia8_card.dat
  #cp $sdir/$process"_delphes_card.dat" "HH_"$process/Cards/delphes_card.dat

  echo "run_mode = 2" >> $process/Cards/me5_configuration.txt
  echo "nb_core = 2"  >> $process/Cards/me5_configuration.txt
  echo "automatic_html_opening = False"  >> $process/Cards/me5_configuration.txt
  ls -lat $process/Cards/*

  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/pmandrik/soft/MG5_aMC_v2_6_3_2/HEPTools/lhapdf6/lib/
  LHAPDFCONFIG="/home/pmandrik/soft/MG5_aMC_v2_6_3_2/HEPTools/lhapdf6/bin/lhapdf-config"
  #echo "pythia8_path = /home/pmandrik/soft/pythia8235 #  "  >> "HH_"$process/Cards/me5_configuration.txt
  #echo "mg5amc_py8_interface_path = /home/pmandrik/soft/MG5_aMC_v2_6_3_2/HEPTools/MG5aMC_PY8_interface #  "  >> "HH_"$process/Cards/me5_configuration.txt
  #echo "hepmc_path = /home/pmandrik/soft/MG5_aMC_v2_6_3_2/HEPTools/hepmc #  "  >> "HH_"$process/Cards/me5_configuration.txt
  #echo "delphes_path = /home/pmandrik/soft/MG5_aMC_v2_6_3_2/Delphes #  "  >> "HH_"$process/Cards/me5_configuration.txt
  echo "lhapdf = $LHAPDFCONFIG #  "  >> $process/Cards/me5_configuration.txt
  #echo "cluster_local_path = `${LHAPDFCONFIG} --datadir`"  >> $PROCESS/Cards/me5_configuration.txt
  
  ls -lat $process/Cards/*
  echo "done" > customizecards.dat
  find $card_folder -name "*_customizecards.dat" -exec cat '{}' >> customizecards.dat \;
  echo "done" >> customizecards.dat
  cat customizecards.dat
  cat customizecards.dat | ./$process/bin/generate_events $run_tag
  ls -lat $process/Cards/*

  echo `pwd`

  echo "MADSPIN GENERATION ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++"
  echo "import $process/Events/run_01/unweighted_events.lhe.gz" > madspin_card.dat
  find $card_folder -name "*_t_l_madspin_card.dat" -exec cat '{}' >> madspin_card.dat \;
  cat madspin_card.dat | $mg_dir/MadSpin/madspin
}

for folder in $sdir/NMSSM_XYH_*; do
  echo $folder
  run_mg $folder
  cd $wdir
  break
done





