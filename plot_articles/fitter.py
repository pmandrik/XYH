import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
from matplotlib.pyplot import figure
from matplotlib.lines import Line2D

path_out = "./article_plots/";

points = [(650, 375), (900, 600), (1300, 475), (1300, 975), (1700, 475), (1700, 1225), (1900, 475), (1900, 1600)]
#points = [(1900, 475)]
path = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/"
files = [ path + "pd_NMSSM_XYH_ttbb_MX_" + str(point[0]) + "_MY_" + str(point[1]) + ".root" for point in points ] # pd_NMSSM_XYH_ttbb_MX_650_MY_375.root

answer = {}
import ROOT

results = ""

import pandas as pd
import collections
data = collections.defaultdict( list )

def get_dm_index( m, pars ):
  best_dm = 999999
  best_dn_index = 0
  for i in range(3):
    if best_dm < abs(m - pars[1+3*i]): continue
    best_dm = min(abs(m - pars[1+3*i]), best_dm)
    best_dn_index = i*3
  return best_dn_index

for point, file in zip(points, files):
  print( file )

  data[r"(m_{X}, m_{Y})"] += [ point ]
  canvs = []

  ls1 = ["$\\frac{\\overline{m_{Y}^{\\chi^2}} - m_{Y}}{m_{Y}}$", "$\\frac{\\overline{m_{Y}^{DNN}} - m_{Y}}{m_{Y}}$", "$\\frac{\\overline{m_{X}^{\\chi^2}} - m_{X}}{m_{X}}$", "$\\frac{\\overline{m_{X}^{DNN}} - m_{X}}{m_{X}}$"]
  ls2 = ["$\\frac{\mu_{Y}^{\\chi^2} - m_{Y}}{m_{Y}}$", "$\\frac{\mu_{Y}^{DNN} - m_{Y}}{m_{Y}}$", "$\\frac{\mu_{X}^{\\chi^2} - m_{X}}{m_{X}}$", "$\\frac{\mu_{X}^{DNN} - m_{X}}{m_{X}}$"]

  f = ROOT.TFile.Open( file, "READ" )
  for hist_name, label, label_alt in zip( ["tt_all_BM", "tt_eval", "HY_all_BM", "HY_eval"] , ls1, ls2 ):
    hist = f.Get( hist_name )
    canv = ROOT.TCanvas(hist_name, hist_name, 640, 480)
    canvs += [ canv ]

    g1 = ROOT.TF1("m" + str(point),"gaus(0)+gaus(3)+gaus(6)",point[0]*0.0,point[0]*1.5);
    g2 = ROOT.TF1("m" + str(point),"gaus(0)+gaus(3)+gaus(6)",point[1]*0.0,hist.GetMean()+hist.GetRMS()*2.0);

    dm_aver = 0;
    dm_aver_rms = 0
    mass = 0;
    if hist_name in ["tt_all_BM", "tt_eval"]: mass = point[1]
    else : mass = point[0]
    
    print( hist.Integral() )
    for n in range(1, hist.GetNbinsX()+1 ):
      if hist.GetXaxis().GetBinCenter(n) < mass*0.0 : continue
      if hist.GetXaxis().GetBinCenter(n) > mass*2.0 : continue
      print(point, hist.GetXaxis().GetBinCenter(n))
      dm_aver += hist.GetBinContent(n) * hist.GetXaxis().GetBinCenter(n) / hist.Integral()
      dm_aver_rms += hist.GetBinContent(n) * pow(hist.GetXaxis().GetBinCenter(n) - mass, 2) / hist.Integral()
      #print( pow(dm_aver, 0.5), hist.GetBinContent(n) * pow(hist.GetXaxis().GetBinCenter(n) - mass, 2), abs(mass - hist.GetXaxis().GetBinCenter(n)), hist.GetBinContent(n) )
    dm_aver_rms = pow(dm_aver_rms, 0.5)
    #data[ label ] += [ abs(mass - hist.GetMean()) ]

    hist.Draw()

    if False: continue
    if hist_name in ["tt_all_BM", "tt_eval"]:
      g2.SetParameters( 0.001, hist.GetMean()*0.5, hist.GetRMS(), 0.001, hist.GetMean(), hist.GetRMS(), 0.001, point[1], hist.GetRMS() );
      hist.Fit( g2, "R" );
      a = g2.GetParameters();
      print(a[0], a[1], a[2])
      index = get_dm_index(point[1], a);
      dm_rel = (a[index+1] - point[1])/point[1]
      #data[ label ] += [ ("%.2f \\pm %.2f" % ((dm_aver-point[1])/point[1]*100, dm_aver_rms/point[1]*100)) ]
      #data[ label_alt ] += [ ("%.2f \\pm %.2f" % (dm_rel*100, a[index+2]/point[1]*100)) ]
      #data[ label ] += [ str(dm_aver) ]
    else :
      g1.SetParameters( 0.001, hist.GetMean()*0.5, hist.GetRMS(), 0.001, hist.GetMean(), hist.GetRMS(), 0.001, point[0], hist.GetRMS() );
      hist.Fit( g1, "R" );
      a = g1.GetParameters();
      print(a[0], a[1], a[2])
      index = get_dm_index(point[0], a);
      dm_rel = (a[index+1] - point[0])/point[0]
      data[ label ] += [ ("$%.2f \\pm %.2f$" % ((dm_aver-point[0])/point[1]*100, dm_aver_rms/point[0]*100)) ]
      data[ label_alt ] += [ ("$%.0f \\pm %.0f$" % (dm_rel*100, a[index+2]/point[0]*100)) ]
      #data[ label ] += [ str(dm_aver) ]
  input()

df = pd.DataFrame.from_dict(data)
print(df.to_latex(index=False, float_format="{:0.3f}".format, escape=False))


