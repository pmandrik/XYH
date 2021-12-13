
set +x

SEED=1
NEVENTS=2000
process="def"

mg_dir=/home/pmandrik/soft/MG5_aMC_v2_6_1/
mg_dir=/home/pmandrik/soft/MG5_aMC_v2_6_5/
mg_dir=/home/pmandrik/work/soft/MG5_aMC_v2.6.0/MG5_aMC_v2_6_0/
mg_dir=/home/pmandrik/work/soft/MG5_aMC_v2.8.3.2/MG5_aMC_v2_8_3_2/
mg_dir=/home/pmandrik/work/soft/MG5_aMC_v2.7.3/MG5_aMC_v2_7_3/

sdir=`pwd`
tag="_fix"
wdir=$sdir/$process$tag
mkdir -p $wdir; cd $wdir

run_mg () {
  card_folder=$1
  mode=$2
  process=`basename $card_folder`
  process_path=$process"_"$mode
  echo "PREPARATION ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++" $card_folder" x "$process

  mkdir $process_path; cd $process_path
  find $card_folder -name "*_proc_card.dat" -exec cp '{}' proc_card.dat \;

  echo "WORKDIR GENERATION ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++"
  wget --no-check-certificate https://cms-project-generators.web.cern.ch/cms-project-generators/
  $mg_dir/bin/mg5_aMC proc_card.dat

  echo "EVENTS GENERATION ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++ ++++++++++++++++++++++++++++++++"
  find $card_folder -name "*_run_card.dat"     -exec cp '{}' $process/Cards/run_card.dat \;
  find $card_folder -name "*_pythia8_card.dat" -exec cp '{}' $process/Cards/pythia8_card.dat \;
  find $card_folder -name "*_delphes_card.dat" -exec cp '{}' $process/Cards/delphes_card.dat \;

  sed -i 's/%SEED%/'$SEED'/g'       $process/Cards/run_card.dat
  sed -i 's/%NEVENTS%/'$NEVENTS'/g' $process/Cards/run_card.dat
  echo "run_mode = 2" >> $process/Cards/me5_configuration.txt
  echo "nb_core = 2"  >> $process/Cards/me5_configuration.txt
  echo "automatic_html_opening = False"  >> $process/Cards/me5_configuration.txt
  ls -lat $process/Cards/*

  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$mg_dir/HEPTools/lhapdf6/lib/
  LHAPDFCONFIG=$mg_dir/HEPTools/lhapdf6/bin/lhapdf-config
  #echo "pythia8_path = /home/pmandrik/work/soft/MG5_aMC_v2.7.3/MG5_aMC_v2_7_3/HEPTools/pythia8 #  "  >> $process/Cards/me5_configuration.txt
  #echo "mg5amc_py8_interface_path = /home/pmandrik/soft/MG5_aMC_v2_6_3_2/HEPTools/MG5aMC_PY8_interface #  "  >> "HH_"$process/Cards/me5_configuration.txt
  #echo "hepmc_path = /home/pmandrik/soft/MG5_aMC_v2_6_3_2/HEPTools/hepmc #  "  >> "HH_"$process/Cards/me5_configuration.txt
  #echo "delphes_path = /home/pmandrik/work/soft/MG5_aMC_v2.7.3/MG5_aMC_v2_7_3/Delphes #  "  >> $process/Cards/me5_configuration.txt
  echo "pythia8_path = /home/pmandrik/work/soft/MG5_aMC_v2.7.3/MG5_aMC_v2_7_3/HEPTools/pythia8 #  "  >> $process/Cards/me5_configuration.txt
  echo "delphes_path = /home/pmandrik/work/soft/MG5_aMC_v2.7.3/MG5_aMC_v2_7_3/Delphes #  "  >> $process/Cards/me5_configuration.txt
  echo "lhapdf = $LHAPDFCONFIG #  "  >> $process/Cards/me5_configuration.txt
  echo "import $process/Events/run_01/unweighted_events.lhe.gz" > $process/Cards/madspin_card.dat
  find $card_folder -name "*_"$mode"_madspin_card.dat" -exec cat '{}' >> $process/Cards/madspin_card.dat \;
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
  #cat madspin_card.dat | $mg_dir/MadSpin/madspin
}

for folder in $sdir/NMSSM_XYH_*; do
  echo $folder
  time run_mg $folder "t_l"
  cd $wdir
  time run_mg $folder "tbar_l"
  cd $wdir
  break
done





