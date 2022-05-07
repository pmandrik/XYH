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

points += [ r"$t\bar{t}$ background" ]
files  += [ "/home/pmandrik/work/projects/XYH/gitrepo/XYH/opendata_process/pd_file.root" ]

points_X = list(set( [ point[0] for point in points ] ))
colors = []
for point in points:
  xx = list( mcolors.TABLEAU_COLORS )
  colors += [ xx[ points_X.index( point[ 0 ]) ] ]
colors_t2 = list( mcolors.TABLEAU_COLORS )

### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### 
answer = {}
import ROOT
for point, file in zip(points, files):
  print( file )
  f = ROOT.TFile.Open( file, "READ" )
  for hist_name in ["selections_nice", "N_bjets", "N_ljets", "N_l"] + ["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"]:
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

### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### 
def make_hists_plot( h_pt_data, label, outname, bins = np.linspace(-5, 5, 30), markers=None, cols=None, labelsx=None, labely=None, range_y=None, limitx0 = 0, limitx=None, dense = False):
  fig, ax = plt.subplots()
  fig.set_figheight(7)
  ax.set_title('')
  # ax.set_yticklabels( [ str(point) for point in points ], fontsize=8 )
  medianprops = dict(color="black",linewidth=1.0)
  if not markers : markers = [ "" for point in points ] 
  if not cols : cols = [None for point in points]
  for point, point_data, mark, col in zip(points, h_pt_data, markers, cols) :
    weights = [ data[1] for data in point_data ]
    xdata   = [ data[0] for data in point_data ]
    max_weight = max(weights)
    if not dense : weights = [ w / max_weight for w in weights ]
    # print(xdata, weights, bins)
    if col:
      n,bins,patches=plt.hist( xdata, bins, weights=weights, alpha=1.0, label=str(point), color=col, histtype='step', linewidth=2, density=dense)
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
  plt.legend(title=r'$(M_X, M_Y)$, [GeV]')
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
  plt.legend(title=r'$(M_X, M_Y)$, [GeV]')
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
      #print( data_point )

    labels = [ r'Total', r'N b-jets >= 2', r'$p_{T}^{MET} > 20$ GeV', r'N leptons = 1', r'Low $p_{T}$ leptons veto' ]
    unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
    make_hists_plot( data_points, "", outname, bins = np.linspace(0, len(labels), len(labels)+1), cols=colors_t2, labelsx=labels )

# selections_nice
if False :
    points = [(650, 375), (900, 600), (1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$ background"]
    data_plot = [ ["N_bjets", "N_ljets", "N_l"], ["N selected b-tagged jets", "N selected non b-tagged jets", "N selected leptons"] ]
    for hist_name, axis_label in zip(["N_bjets", "N_ljets", "N_l"], ["N selected b-tagged jets", "N selected non b-tagged jets", "N selected leptons"]):
      outname   = hist_name
      data_points = []
      for point in points:
        data_point = answer[ str(point) + "_" + hist_name ]
        data_points += [ data_point ]
        #print( data_point )
      
      width   = data_points[0][1][0] - data_points[0][0][0]
      start_x = data_points[0][0][0] - width/2
      end_x   = data_points[0][-1][0] + width/2

      labels = []
      for x in range(0, 20 ):
        if width*x - int(width*x) < width : labels += [ str(int(width*x)) ]
        else : labels += [ "" ]
      bar_width = (end_x - start_x) / 20. / len(data_points) * 3.5

      unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
      make_bar_plot( data_points, axis_label, outname, bins = np.linspace(start_x, int(end_x), len(labels)+1), cols=colors_t2, labelsx=labels, bar_width=bar_width )


if True :
    # points = [(650, 375), (900, 600), (1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$ background"]
    #for hist_name, axis_label in zip(["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"], ["bb_all0", "qq_all0", "qqb_all0", "nul_all", "blnu_all", "tt_all", "HY_all"]):
    reqs = [ 
      ["tt_all",   r"$M(t\bar{t})$ GeV", 2000],
      ["HY_all",   r"$M(HY)$ GeV", 2500],
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

    points = [(650, 375),(1300, 975), (1700, 475), (1900, 1600), r"$t\bar{t}$ background"]
    reqs = [ 
      ["qq_all0",  r"$M(q\bar{q})$ GeV", 0,600],
      ["qqb_all0", r"$M(q\bar{q}b)$ GeV", 0,1000],
      ["nul_all",  r"$M(\nu l)$ GeV", 60,200],
      ["blnu_all", r"$M(\nu l b)$ GeV", 60,600],
      ["bb_all0",  r"$M(b\bar{b})$ GeV", 0,600],
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








