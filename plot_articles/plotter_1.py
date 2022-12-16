import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
from matplotlib.pyplot import figure
from matplotlib.lines import Line2D

path_out = "./article_plots/";

points = [(650, 375), (900, 600), (1300, 475), (1300, 975), (1700, 475), (1700, 1225), (1900, 475), (1900, 1600)]
path = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/"
files = [ path + "pd_NMSSM_XYH_ttbb_MX_" + str(point[0]) + "_MY_" + str(point[1]) + ".root" for point in points ] # pd_NMSSM_XYH_ttbb_MX_650_MY_375.root

if True:
  points += [ r"$t\bar{t}$+lf" ]
  files  += [ "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_900_MY_600_lf.root" ]

  points += [ r"$t\bar{t}$+hf" ]
  files  += [ "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_900_MY_600_hf.root" ]

  points += [ r"ttH" ]
  files  += [ "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_900_MY_600_ttH.root" ]
else:
  points += [ r"$t\bar{t}$+lf" ]
  files  += [ "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_1900_MY_1600_lf.root" ]

  points += [ r"$t\bar{t}$+hf" ]
  files  += [ "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_1900_MY_1600_hf.root" ]

  points += [ r"ttH" ]
  files  += [ "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_1900_MY_1600_ttH.root" ]


L = 137 * 1000
hf_frac = 939250 / (1.395 * 1000000 + 1.609 * 1000000 + 939250)
xsecs = {}
xsecs[ r"ttH" ] = 5.071E-01 * L
xsecs[ r"$t\bar{t}$+lf" ] = 833.9 * L * ( 1. - hf_frac)
xsecs[ r"$t\bar{t}$+hf" ] = 833.9 * L * hf_frac # Cross Section (pb)

# https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt13TeV#ttH_Process


if False:
  point_ttbar = []
  files_ttbar = []
  for point in points[:] :
    point_ttbar += [ r"$t\bar{t}$ DNN " + str( point ) ]
    files_ttbar += [ "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_" + str(point[0]) + "_MY_" + str(point[1]) + ".root" ]

  points = point_ttbar
  files  = files_ttbar

  print( point_ttbar, files )

points_X = list(set( [ point[0] for point in points ] ))
colors = []
for point in points:
  xx = list( mcolors.TABLEAU_COLORS )
  colors += [ xx[ points_X.index( point[ 0 ]) ] ]
colors_t2 = list( mcolors.TABLEAU_COLORS )
colors_t2 += [ "blue" ]

print( len(points), len(colors_t2) )

### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### 
answer = {}
selection_effs = {}
import ROOT
for point, file in zip(points, files):
  print( file )
  f = ROOT.TFile.Open( file, "READ" )
  
  if True:
    hist = f.Get( "selections" )
    total_events = hist.GetBinContent(1)

    hist = f.Get( "selections_nice2" )
    selected_events = hist.GetBinContent(3)
    selection_effs[ str(point) ] = selected_events / total_events

    if selected_events < 1 : 
      selection_effs[ str(point) ] = selected_events
      
    print(point , total_events, selected_events, selection_effs[ str(point) ] )

  for hist_name in ["selections_nice", "N_bjets", "N_ljets", "N_l"] + ["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"] + ["bb_al_BMl", "qq_all_BM", "bqq_all_BM", "nul_all_BM", "blnu_all_BM", "tt_all_BM", "HY_all_BM", "tt_eval", "HY_eval", "bb_eval",   "bqq_eval", "blnu_eval", "HY_eval_fnal"]:
    # print(str(point) + "_" + hist_name, hist_name)
    hist = f.Get( hist_name )

    array = []
    for n in range(1, hist.GetNbinsX()+1 ):
      array += [ [hist.GetXaxis().GetBinCenter(n), hist.GetBinContent(n)] ]
      # print ( hist_name, [hist.GetXaxis().GetBinCenter(n), hist.GetBinContent(n)] )
    #print( array )
    # y = hist.GetArray()
    # y.SetSize(hist.GetNbinsX())
    # print( root_numpy.hist2array( hist ) )
    #y = np.linspace(hist.GetXaxis().GetXmin(), hist.GetXaxis().GetXmax()-hist.GetXaxis().GetBinWidth(1), num=hist.GetNbinsX())
    answer[ str(point) + "_" + hist_name ] = array

def get_data_from_file(file_name, hist_name):
  f = ROOT.TFile.Open( file_name, "READ" )
  hist = f.Get( hist_name )
  array = []
  for n in range(1, hist.GetNbinsX()+1 ):
    array += [ [hist.GetXaxis().GetBinCenter(n), hist.GetBinContent(n)] ]
  return array

print( selection_effs )

### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### 
import collections
if False:
  data = collections.defaultdict( list )
  data2 = collections.defaultdict( list )

  hist_name = "selections_nice"
  outname   = "selections_nice"
  data_points = []
  for point in points:
    data_point = answer[ str(point) + "_" + hist_name ][0:5]
    s = data_point[0][1];

    for i in range(len(data_point)):
      data_point[i][1] /= s

    print( data_point )

    data[""] += [ point ]
    if point in xsecs : 
      data2[""] += [ point ]

    labels = [ r'Total', r'N b-jets >= 2', r'$p_{T}^{MET} > 20$ GeV', r'N leptons = 1', r'Low $p_{T}$ leptons veto' ]
    for i in range(1, len(data_point)):
      data[ labels[i] ] += [ data_point[i][1] ] 
      if not point in xsecs : continue
      data2[ labels[i] ] += [ data_point[i][1] * xsecs[ point ] ]
  
  print( data )
  import pandas as pd
  df = pd.DataFrame.from_dict(data)
  print(df.to_latex(index=False, float_format="{:0.3f}".format, escape=False))

  df = pd.DataFrame.from_dict(data2)
  print(df.to_latex(index=False, float_format="{:0.0f}".format, escape=False))
  print( xsecs )

if False:
  point_ttbar_lf = []
  files_ttbar_lf = []
  point_ttbar_hf = []
  files_ttbar_hf = []
  for point in points[:] :
    point_ttbar_lf += [ r"$t\bar{t}-lf$  " + str( point ) ]
    files_ttbar_lf += [ "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_" + str(point[0]) + "_MY_" + str(point[1]) + "_lf.root" ]

    point_ttbar_hf += [ r"$t\bar{t}-hf$  " + str( point ) ]
    files_ttbar_hf += [ "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_" + str(point[0]) + "_MY_" + str(point[1]) + "_hf.root" ]
  
  data = collections.defaultdict( list )
  data2 = collections.defaultdict( list )

  get_data_from_file

  hist_name = "selections_nice2"
  outname   = "selections_nice2"
  points = [(650, 375), (900, 600), (1300, 475), (1300, 975), (1700, 475), (1700, 1225), (1900, 475), (1900, 1600)]
  for point in points:
    data[ r"DNN (m_X, m_Y)" ] += [ str(point) ]
    data2[ r"DNN (m_X, m_Y)" ] += [ str(point) ]

    fname = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_" + str(point[0]) + "_MY_" + str(point[1]) + "_lf.root"
    f = ROOT.TFile.Open( fname, "READ" )

    hist = f.Get( "selections" )
    total_events = hist.GetBinContent(1)

    hist = f.Get( "selections_nice2" )
    selected_events = hist.GetBinContent(3)
    selection_effs[ str(point) ] = selected_events / total_events
      
    print("lf", point , total_events, selected_events, selection_effs[ str(point) ], selection_effs[ str(point) ] * xsecs[ r"$t\bar{t}$+lf" ] )

    data[ r"$t\bar{t}$+lf" ] += [ selection_effs[ str(point) ] * xsecs[ r"$t\bar{t}$+lf" ] ]
    data2[ r"$t\bar{t}$+lf" ] += [ selection_effs[ str(point) ] ]
    #############
    fname = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_" + str(point[0]) + "_MY_" + str(point[1]) + "_hf.root"
    f = ROOT.TFile.Open( fname, "READ" )

    hist = f.Get( "selections" )
    total_events = hist.GetBinContent(1)

    hist = f.Get( "selections_nice2" )
    selected_events = hist.GetBinContent(3)
    selection_effs[ str(point) ] = selected_events / total_events
      
    print("hf", point , total_events, selected_events, selection_effs[ str(point) ], selection_effs[ str(point) ] * xsecs[ r"$t\bar{t}$+hf" ] )

    data[ r"$t\bar{t}$+hf" ] += [ selection_effs[ str(point) ] * xsecs[ r"$t\bar{t}$+hf" ] ]
    data2[ r"$t\bar{t}$+hf" ] += [ selection_effs[ str(point) ] ]
    #############
    #/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_650_MY_375_ttH.root
    fname = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file_" + str(point[0]) + "_MY_" + str(point[1]) + "_ttH.root"
    f = ROOT.TFile.Open( fname, "READ" )

    hist = f.Get( "selections" )
    total_events = hist.GetBinContent(1)

    hist = f.Get( "selections_nice2" )
    selected_events = hist.GetBinContent(3)
    selection_effs[ str(point) ] = selected_events / total_events
      
    print("ttH", point , total_events, selected_events, selection_effs[ str(point) ], selection_effs[ str(point) ] * xsecs[ "ttH" ] )

    data[ r"$t\bar{t}H" ] += [ selection_effs[ str(point) ] * xsecs[ "ttH" ] ]
    data2[ r"$t\bar{t}H" ] += [ selection_effs[ str(point) ] ]

    #############
    fname = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/pd_NMSSM_XYH_ttbb_MX_" + str(point[0]) + "_MY_" + str(point[1]) + ".root"
    f = ROOT.TFile.Open( fname, "READ" )

    hist = f.Get( "selections_nice2" )
    selected_events = hist.GetBinContent(3)
    selection_effs[ str(point) ] = selected_events

    data2[ r"Signal" ] += [ selection_effs[ str(point) ] ]
  
  print( data )
  import pandas as pd
  df = pd.DataFrame.from_dict(data)
  print(df.to_latex(index=False, float_format="{:0.0f}".format, escape=False))

  print( data2 )
  import pandas as pd
  df = pd.DataFrame.from_dict(data2)
  print(df.to_latex(index=False, float_format="{:0.3f}".format, escape=False))

### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### 
def make_hists_plot( h_pt_data, label, outname, bins = np.linspace(-5, 5, 30), markers=None, cols=None, labelsx=None, labely=None, range_y=None, limitx0 = 0, limitx=None, dense = False, poitns_=False, title_=False):
  fig, ax = plt.subplots()
  fig.set_figheight(7)
  ax.set_title('')
  # ax.set_yticklabels( [ str(point) for point in points ], fontsize=8 )
  medianprops = dict(color="black",linewidth=1.0)
  points__ = points
  if poitns_ : points__ = poitns_;
  if not markers : markers = [ "" for point in points__ ] 
  if not cols : cols = [None for point in points__]

  line_style = [':', '-', '-.', '-', '-']

  for point, point_data, mark, col, lstyle in zip(points__, h_pt_data, markers, cols, line_style) :
    weights = [ data[1] for data in point_data ]
    xdata   = [ data[0] for data in point_data ]
    max_weight = max(weights)
    if not dense : weights = [ w / max_weight for w in weights ]
    # print(xdata, weights, bins)
    if col:
      n,bins,patches=plt.hist( xdata, bins, weights=weights, alpha=1.0, label=str(point), color=col, histtype='step', linewidth=4, density=dense)

      if lstyle:
        patches[0].set_linestyle( lstyle )

      # plt.scatter(bins[:-1]+ 0.5*(bins[1:] - bins[:-1]), n, marker=mark, c=col, s=40, alpha=1)
    else :
      n,bins,patches=plt.hist( xdata, bins, weights=weights, alpha=1.0, label=str(point), histtype='step', linewidth=2)

  if not dense : ax.set( xlabel=label, ylabel=r'Events yield')
  else         : ax.set( xlabel=label, ylabel=r'Fraction of selected events')
  ax.xaxis.set_major_locator(plt.MaxNLocator(10))

  if labelsx:
    xdata   = [ data[0] for data in h_pt_data[0] ]
    # print( xdata )
    ax.set_xticks( xdata )
    ax.set_xticklabels(labelsx)
    plt.xticks(rotation=45)

  if range_y:
    plt.yticks(np.arange(0, 1.05, step=0.05))

  #ax.grid(True, linestyle='dashed')
  plt.xlim([bins[0], bins[-1]])
  if limitx : plt.xlim([limitx0, limitx])
  plt.grid(axis='y', color='0.90', linestyle='dashed')
  if not title_ : plt.legend(title=r'$(m_X, m_Y)$, [GeV]')
  else : plt.legend(title=title_, loc='upper right')
  plt.savefig( path_out + "/" + outname + '.png', bbox_inches='tight')
  plt.savefig( path_out + "/" + outname + '.pdf', bbox_inches='tight')

def make_bar_plot( h_pt_data, label, outname, bins = np.linspace(-5, 5, 30), markers=None, cols=None, labelsx=None, labely=None, range_y=None, bar_width=0.1):
  fig, ax = plt.subplots()
  fig.set_figheight(7)
  ax.set_title('')
  # ax.set_yticklabels( [ str(point) for point in points ], fontsize=8 )
  medianprops = dict(color="black",linewidth=1.0)
  if not markers : markers = [ "" for point in points ] 
  if not cols : cols = [None for point in points]
  bar_width_local = -len(points) * bar_width/2
  for point, point_data, mark, col in zip(points, h_pt_data, markers, cols) :
    weights = [ data[1] for data in point_data ]
    xdata   = [ data[0] + bar_width_local for data in point_data ]
    bar_width_local += bar_width
    # print(xdata, weights, bins)
    if col:
      ax.bar(xdata, weights, color = col, width = bar_width, alpha=0.9, label=str(point))
      #n,bins,patches=plt.hist( xdata, bins, weights=weights, alpha=1.0, label=str(point), color=col, histtype='bar', linewidth=2, rwidth=0.1)
      #plt.scatter(bins[:-1]+ 0.5*(bins[1:] - bins[:-1]), n, marker=mark, c=col, s=40, alpha=1)
  ax.set( xlabel=label, ylabel=r'Fraction of events')
  ax.xaxis.set_major_locator(plt.MaxNLocator(15))

  if labelsx:
    xdata   = [ data[0] for data in h_pt_data[0] ]
    # print( xdata )
    ax.set_xticks( xdata )
    ax.set_xticklabels(labelsx)
    plt.xticks(rotation=45)

  if range_y:
    plt.yticks(np.arange(0, 1.05, step=0.05))

  #ax.grid(True, linestyle='dashed')
  plt.grid(axis='y', color='0.90', linestyle='dashed')
  plt.legend(title=r'$(m_X, m_Y)$, [GeV]')
  plt.savefig( path_out + "/" + outname + '.png', bbox_inches='tight')
  plt.savefig( path_out + "/" + outname + '.pdf', bbox_inches='tight')

### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### 

# selections_nice
if False :
    hist_name = "selections_nice"
    outname   = "selections_nice"
    data_points = []
    for point in points:
      data_point = answer[ str(point) + "_" + hist_name ][0:5]
        
      data_points += [ data_point ]
      # print( point, data_point )

    labels = [ r'Total', r'N b-jets >= 2', r'$p_{T}^{MET} > 20$ GeV', r'N leptons = 1', r'Low $p_{T}$ leptons veto' ]
    unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
    make_hists_plot( data_points, "", outname, bins = np.linspace(0, len(labels), len(labels)+1), cols=colors_t2, labelsx=labels )

# selections_nice
if False :
    points = [(650, 375), (900, 600), (1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$+hf", r"$t\bar{t}$+lf", r"ttH"]
    data_plot = [ ["N_bjets", "N_ljets", "N_l"], ["N selected b-tagged jets", "N selected non b-tagged jets", "N selected leptons"] ]
    for hist_name, axis_label in zip(["N_bjets", "N_ljets", "N_l"], ["N selected b-tagged jets", "N selected non b-tagged jets", "N selected leptons"]):
      outname   = hist_name
      data_points = []
      for point in points:
        data_point = answer[ str(point) + "_" + hist_name ]
        s = 0;
        for d in data_point: s += d[1]
        for i in range(len(data_point)):
          data_point[i][1] /= s

        data_points += [ data_point ]
        print( point, data_point )
      
      width   = data_points[0][1][0] - data_points[0][0][0]
      start_x = data_points[0][0][0] - width/2
      end_x   = data_points[0][-1][0] + width/2

      labels = []
      for x in range(0, 20 ):
        if width*x - int(width*x) < width : labels += [ str(int(width*x)) ]
        else : labels += [ "" ]
      bar_width = (end_x - start_x) / 20. / len(data_points) * 1.8

      unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
      make_bar_plot( data_points, axis_label, outname, bins = np.linspace(start_x, int(end_x), len(labels)+1), cols=colors_t2, labelsx=labels, bar_width=bar_width )


if False :
    # points = [(650, 375), (900, 600), (1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$ background"]
    #for hist_name, axis_label in zip(["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"], ["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"]):
    reqs = [ 
      ["tt_all",   r"$m(t\bar{t})$ GeV", 2000],
      ["HY_all",   r"$m(HY)$ GeV", 2500],
    ]
    for hist_name, axis_label, limitx in reqs:
      outname   = hist_name
      data_points = []
      for point in points:
        data_point = answer[ str(point) + "_" + hist_name ]
        data_points += [ data_point ]
        width   = data_points[0][1][0] - data_points[0][0][0]
      
      width   = data_points[0][1][0] - data_points[0][0][0]
      start_x = data_points[0][0][0] - width/2
      end_x   = data_points[0][-1][0] + width/2
      bins = [ 2 *width * i for i in range( int((end_x-start_x) / width) + 1 ) ]

      # print(start_x, end_x, len(data_points[0]),width,(end_x-start_x)/width)
      # print( bins )
      # print( data_point )

      unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
      make_hists_plot( data_points, axis_label, outname, bins = bins, cols=colors_t2, limitx=limitx, dense=True )

    points = [(650, 375),(1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$+lf", r"$t\bar{t}$+hf", r"ttH"]
    reqs = [ 
      ["qq_all0",  r"$m(q\bar{q})$ GeV", 0,600],
      ["qqb_all0", r"$m(q\bar{q}b)$ GeV", 0,1000],
      ["nul_all",  r"$m(\nu l)$ GeV", 60,200],
      ["blnu_all", r"$m(\nu l b)$ GeV", 60,600],
      ["bb_all0",  r"$m(b\bar{b})$ GeV", 0,600],
    ]
    for hist_name, axis_label, limitx0, limitx in reqs:
      outname   = hist_name
      data_points = []
      for point in points:
        data_point = answer[ str(point) + "_" + hist_name ]
        data_points += [ data_point ]

        width   = data_points[0][1][0] - data_points[0][0][0]
      
      width   = data_points[0][1][0] - data_points[0][0][0]
      start_x = data_points[0][0][0] - width/2
      end_x   = data_points[0][-1][0] + width/2
      bins = [ width * i for i in range( int((end_x-start_x) / width) + 1 ) ]

      # print(start_x, end_x, len(data_points[0]),width,(end_x-start_x)/width)
      # print( bins )
      # print( data_point )

      unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
      make_hists_plot( data_points, axis_label, outname, bins = bins, cols=colors_t2, limitx0=limitx0, limitx=limitx )

if False :
    # points = [(650, 375), (900, 600), (1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$ background"]
    #for hist_name, axis_label in zip(["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"], ["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"]):
    reqs = [ 
      [ "tt_all_BM",   r"$m(t\bar{t})$ GeV", 2000 ],
      [ "HY_all_BM",   r"$m(HY)$ GeV", 2500 ],
    ]
    for hist_name, axis_label, limitx in reqs:
      outname   = hist_name
      data_points = []
      for point in points:
        data_point = answer[ str(point) + "_" + hist_name ]
        data_points += [ data_point ]
        width   = data_points[0][1][0] - data_points[0][0][0]
      
      width   = data_points[0][1][0] - data_points[0][0][0]
      start_x = data_points[0][0][0] - width/2
      end_x   = data_points[0][-1][0] + width/2
      bins = [ 2 *width * i for i in range( int((end_x-start_x) / width) + 1 ) ]

      # print(start_x, end_x, len(data_points[0]),width,(end_x-start_x)/width)
      # print( bins )
      # print( data_point )

      unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
      make_hists_plot( data_points, axis_label, outname, bins = bins, cols=colors_t2, limitx=limitx, dense=True )

    points = [ (650, 375), (1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$+lf", r"$t\bar{t}$+hf", r"ttH" ]
    reqs = [ 
      ["qq_all_BM",  r"$m(q\bar{q})$ GeV", 0,600],
      ["bqq_all_BM", r"$m(q\bar{q}b)$ GeV", 0,1000],
      ["nul_all_BM",  r"$m(\nu l)$ GeV", 60,200],
      ["blnu_all_BM", r"$m(\nu l b)$ GeV", 60,600],
      ["bb_al_BMl",  r"$m(b\bar{b})$ GeV", 0,600],
    ]
    for hist_name, axis_label, limitx0, limitx in reqs:
      outname   = hist_name
      data_points = []
      for point in points:
        data_point = answer[ str(point) + "_" + hist_name ]
        data_points += [ data_point ]

        width   = data_points[0][1][0] - data_points[0][0][0]
      
      width   = data_points[0][1][0] - data_points[0][0][0]
      start_x = data_points[0][0][0] - width/2
      end_x   = data_points[0][-1][0] + width/2
      bins = [ width * i for i in range( int((end_x-start_x) / width) + 1 ) ]

      # print(start_x, end_x, len(data_points[0]),width,(end_x-start_x)/width)
      # print( bins )
      # print( data_point )

      unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
      make_hists_plot( data_points, axis_label, outname, bins = bins, cols=colors_t2, limitx0=limitx0, limitx=limitx )

if False :
    # points = [(650, 375), (900, 600), (1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$ background"]
    #for hist_name, axis_label in zip(["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"], ["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"]):
    reqs = [ 
      ["tt_eval",   r"$m(t\bar{t})$ GeV", 2000],
      ["HY_eval",   r"$m(HY)$ GeV", 2500],
      ["HY_eval_fnal",   r"$m(HY)$ GeV", 2500],

      #["bb_eval",   r"$m(bb)$ GeV", 500],
      #["bqq_eval",   r"$m(bqbq)$ GeV", 500],
      #["blnu_eval",   r"$m(blnu)$ GeV", 500],
    ]
    for hist_name, axis_label, limitx in reqs:
      outname   = hist_name
      data_points = []
      for point in points:
        data_point = answer[ str(point) + "_" + hist_name ]
        data_points += [ data_point ]
        width   = data_points[0][1][0] - data_points[0][0][0]
      
      width   = data_points[0][1][0] - data_points[0][0][0]
      start_x = data_points[0][0][0] - width/2
      end_x   = data_points[0][-1][0] + width/2
      bins = [ 2 *width * i for i in range( int((end_x-start_x) / width) + 1 ) ]

      # print(start_x, end_x, len(data_points[0]),width,(end_x-start_x)/width)
      # print( bins )
      # print( data_point )

      unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
      make_hists_plot( data_points, axis_label, outname, bins = bins, cols=colors_t2, limitx=limitx, dense=True )

def make_stack_plot( h_pt_data, label, outname, bins = np.linspace(-5, 5, 30), markers=None, cols=None, labelsx=None, labely=None, range_y=None, limitx0 = 0, limitx=None, dense = False, poitns_=False, title_=False, hatch_cycle_=False):
  fig, ax = plt.subplots()
  fig.set_figheight(7)
  ax.set_title('')
  # ax.set_yticklabels( [ str(point) for point in points ], fontsize=8 )
  medianprops = dict(color="black",linewidth=1.0)
  points__ = points
  if poitns_ : points__ = poitns_;
  if not markers : markers = [ "" for point in points__ ] 
  if not cols : cols = [None for point in points__]
  xdatas = []
  xweights = []
  xlabels = []
  for point, point_data, mark, col in zip(points__, h_pt_data, markers, cols) :
    weights = [ data[1] for data in point_data ]
    xdata   = [ data[0] for data in point_data ]
    max_weight = max(weights)
    # print(xdata, weights, bins)

    xdatas += [ xdata ]
    xweights += [ weights ]
    xlabels += [ str(point) ] 
  
  #print( hatch_cycle_ )
  #hatch_cycle_ = ("/", "|")

  n,bins,patches=plt.hist( xdatas, bins, weights=xweights, alpha=1.0, label=xlabels, histtype='step', linewidth=0, stacked=True, fill=True, hatch=hatch_cycle_, edgecolor='k')

  for hatch, patch in zip(hatch_cycle_, patches):
    print( patch )
    patch[0].set_hatch(hatch);

  ax.set( xlabel=label, ylabel=r'Expected number of events')
  ax.xaxis.set_major_locator(plt.MaxNLocator(10))

  if labelsx:
    xdata   = [ data[0] for data in h_pt_data[0] ]
    # print( xdata )
    ax.set_xticks( xdata )
    ax.set_xticklabels(labelsx)
    plt.xticks(rotation=45)

  if range_y:
    plt.yticks(np.arange(0, 1.05, step=0.05))

  #ax.grid(True, linestyle='dashed')
  plt.xlim([bins[0], bins[-1]])
  if limitx : plt.xlim([limitx0, limitx])
  plt.grid(axis='y', color='0.90', linestyle='dashed')
  if not title_ : plt.legend(title=r'$(m_X, m_Y)$, [GeV]', prop={'size': 13})
  else : plt.legend(title=title_, loc='upper left', prop={'size': 16})
  plt.savefig( path_out + "/" + outname + '.png', bbox_inches='tight')
  plt.savefig( path_out + "/" + outname + '.pdf', bbox_inches='tight')

if False :
    points = [(650, 375), (900, 600), (1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$ background"]


    #for hist_name, axis_label in zip(["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"], ["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"]):
    reqs = [ 
      [ "900_600", "HY_eval_fnal",   r"$m(HY)$ GeV", 3000, [ r"$t\bar{t}$+lf", r"$t\bar{t}$+hf", r"ttH", (900, 600) ]],
      ["1900_1600", "HY_eval_fnal",   r"$m(HY)$ GeV", 3000, [ r"$t\bar{t}$+lf", r"$t\bar{t}$+hf", r"ttH", (1900, 1600) ]],

      #["bb_eval",   r"$m(bb)$ GeV", 500],
      #["bqq_eval",   r"$m(bqbq)$ GeV", 500],
      #["blnu_eval",   r"$m(blnu)$ GeV", 500],
    ]
    for oname, hist_name, axis_label, limitx, points in reqs:
      outname   = hist_name + "_X" + oname
      data_points = []

      for point in points:
        data_point = answer[ str(point) + "_" + hist_name ]

        s = 0;
        for d in data_point: s += d[1]
        
        selection_eff = selection_effs[ str(point) ]

        xsec = (xsecs[ r"$t\bar{t}$+lf" ] + xsecs[ r"$t\bar{t}$+hf" ]) * 0.025
        if point in xsecs:
          xsec = xsecs[point];

        integral = 0
        for i in range(len(data_point)):
          data_point[i][1] /= s
          data_point[i][1] *= selection_eff
          data_point[i][1] *= xsec
          integral += data_point[i][1]
        print( point, integral, integral * 36 / 137 )

        data_points += [ data_point ]
        width   = data_points[0][1][0] - data_points[0][0][0]
      
      width   = data_points[0][1][0] - data_points[0][0][0]
      start_x = data_points[0][0][0] - width/2
      end_x   = data_points[0][-1][0] + width/2
      bins = [ 8 * width * i for i in range( int((end_x-start_x) / width) + 1 ) ]

      # print(start_x, end_x, len(data_points[0]),width,(end_x-start_x)/width)
      # print( bins )
      #print( data_points )

      unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
      make_stack_plot( data_points, axis_label, outname, bins = bins, cols=colors_t2, limitx=limitx, dense=False , hatch_cycle_ = ('+', '*', '/', 'o') )


if True :
    # points = [(650, 375), (900, 600), (1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$ background"]
    #for hist_name, axis_label in zip(["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"], ["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"]):
    reqs = [ 
      [(1900, 1600), "tt", ["tt_eval", "tt_all_BM", "tt_all"], ["DNN", r"$\chi^2$", "Combinatorics"], r"$m(t\bar{t})$ GeV", 2500],
      [(1900, 1600), "HY", ["HY_eval", "HY_all_BM", "HY_all"], ["DNN", r"$\chi^2$", "Combinatorics"],  r"$m(HY)$ GeV", 3000],
      [(900, 600), "tt", ["tt_eval", "tt_all_BM", "tt_all"], ["DNN", r"$\chi^2$", "Combinatorics"], r"$m(t\bar{t})$ GeV", 2000],
      [(900, 600), "HY", ["HY_eval", "HY_all_BM", "HY_all"], ["DNN", r"$\chi^2$", "Combinatorics"],  r"$m(HY)$ GeV", 2500],
    ]

    print( answer.keys() )

    for point, outname, hist_names, labels, axis_label, limitx in reqs:
      data_points = []
      for hist_name in hist_names :
        data_point = answer[ str(point) + "_" + hist_name ]
        data_points += [ data_point ]
        width   = data_points[0][1][0] - data_points[0][0][0]
      
      width   = data_points[0][1][0] - data_points[0][0][0]
      start_x = data_points[0][0][0] - width/2
      end_x   = data_points[0][-1][0] + width/2
      bins = [ 4 *width * i for i in range( int((end_x-start_x) / width) + 1 ) ]

      # print(start_x, end_x, len(data_points[0]),width,(end_x-start_x)/width)
      # print( bins )
      # print( data_point )

      unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
      make_hists_plot( data_points, axis_label, outname + "_" + str(point[0]) + "_" + str(point[1]), bins = bins, cols=colors_t2, limitx=limitx, dense=True, poitns_=labels, title_ = r'$(m_X, m_Y) = ' + str(point) + '$ [GeV]' )




