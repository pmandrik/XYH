#!/bin/bash

fitter_path=/afs/cern.ch/work/p/pmandrik/fcc_100TeV/7_limits/
workdir=/afs/cern.ch/work/p/pmandrik/fcc_100TeV/7_limits/H

#mkdir -p $workdir
#cd $workdir

# cd /afs/cern.ch/work/p/pmandrik/dihiggs/0_stat/CMSSW_10_2_13/src; eval `scramv1 runtime -sh`; cd -;           

do_hists(){
  bdt_name=$1"_"$2"_"$3
  root -l -b -q "../make_hists.C(\"$1\", \".\", $2, $3, true)"
}

do_fit(){
  cp card.txt card$bdt_name.txt
  echo $bdt_name 
  
  sed -i -e "s/%POSTFIX%/$2"_"$3/g" card$bdt_name.txt
  sed -i -e "s/%SIGNAL_NAME%/$1/g" card$bdt_name.txt

  bdt_name=$1"_"$2"_"$3
  combine card$bdt_name.txt -M AsymptoticLimits --run blind
  mv higgsCombineTest.AsymptoticLimits.mH120.root "results"$bdt_name".root"
}

# 25.6% 24.8%
#do_fit "H_m_xfactor" 5 1
#do_fit "H_m_xfactor_1" 5 1
#do_fit "H_m_xfactor_2" 5 1

do_hists "" 35 1

#do_fit "pd_NMSSM_XYH_ttbb_MX_900_MY_600" 25 1
