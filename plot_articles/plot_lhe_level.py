import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
from matplotlib.pyplot import figure
from matplotlib.lines import Line2D

dfs = {}
max_rows = 100000000

points = [ (650, 375) ]
start_X = 500
start_Y = 475

for X in range(start_X, 2000, 200):
  for Y in range(start_Y, 2000, 125):
    if X - Y <= 200 : continue
    if X == 1700 and Y == 1350 : continue
    if X == 1700 and Y == 1475 : continue
    print( X, Y, X-Y, 125, "...")
    points += [ (X, Y) ]

points = [(650, 375), (700, 475), (900, 475), (900, 600), 
          (1100, 475), (1100, 600), (1100, 725), (1100, 850), 
          (1300, 475), (1300, 600), (1300, 725), (1300, 850), (1300, 975), 
          (1500, 475), (1500, 600), (1500, 725), (1500, 850), (1500, 975), (1500, 1100), (1500, 1225), 
          (1700, 475), (1700, 600), (1700, 725), (1700, 850), (1700, 975), (1700, 1100), (1700, 1225), 
          (1900, 475), (1900, 600), (1900, 725), (1900, 850), (1900, 975), (1900, 1100), (1900, 1225), (1900, 1350), (1900, 1475), (1900, 1600)]
points = [(650, 375), (700, 475), (900, 475), (900, 600), 
          (1100, 475), (1100, 850), 
          (1300, 475), (1300, 725), (1300, 975), 
          (1500, 475), (1500, 850), (1500, 1225), 
          (1700, 475), (1700, 850), (1700, 1225), 
          (1900, 475), (1900, 850), (1900, 1225),(1900, 1600)]
points = [(650, 375), (900, 600), 
          (1300, 475), (1300, 975), 
          (1700, 475), (1700, 1225), 
          (1900, 475), (1900, 1600)]

points_X = list(set( [ point[0] for point in points ] ))
import matplotlib.colors as mcolors
path_inp = "/home/pmandrik/work/projects/XYZ/XYH/events_process/after_lhe_hlv/";
path_out = "/home/pmandrik/work/projects/XYZ/XYH/events_process/after_lhe_plot/";
path_inp = "/home/pmandrik/work/projects/XYH/events_process/after_lhe_hlv/";
path_out = "/home/pmandrik/work/projects/XYH/events_process/after_lhe_plot/";
for point in points:
  Xm, Ym = point
  if Xm == 1700 and Ym == 1350 : continue
  if Xm == 1700 and Ym == 1475 : continue
  inp1 = path_inp+ "NMSSM_XYH_ttbb_MX_" + str(Xm) + "_MY_" + str(Ym) + "_t_l.csv";
  inp2 = path_inp+ "NMSSM_XYH_ttbb_MX_" + str(Xm) + "_MY_" + str(Ym) + "_tbar_l.csv";
  df1 = pd.read_csv( inp1, sep=" ", nrows=max_rows)
  df2 = pd.read_csv( inp2, sep=" ", nrows=max_rows)
  df = pd.concat( [df1, df2] )
  # df = df1
  dfs[ point ] = df

colors = []
for point in points:
  xx = list( mcolors.TABLEAU_COLORS )
  colors += [ xx[ points_X.index( point[ 0 ]) ] ]

colors_t2 = list( mcolors.TABLEAU_COLORS )

### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### 
def make_box_plot( h_pt_data, label, outname, limit_x=False):
  fig, ax = plt.subplots()
  fig.set_figheight(7)
  ax.set_title('')
  ax.set_yticklabels( [ str(point) for point in points ], fontsize=8 )
  medianprops = dict(color="black",linewidth=1.0)
  bplot = ax.boxplot( h_pt_data, 0, '', vert=False, showfliers=True, patch_artist=True,medianprops=medianprops)
  ax.set( xlabel=label, ylabel=r'$(M_X, M_Y)$, [GeV]')
  ax.xaxis.set_major_locator(plt.MaxNLocator(15))
  ax.grid(True, linestyle='dashed')
  plt.grid(axis='y', linestyle='dashed')
  if limit_x :
    limits = ax.get_xlim()
    plt.xlim([0, limits[1]])

  for patch, color in zip(bplot['boxes'], colors):
    patch.set_facecolor( mcolors.TABLEAU_COLORS[color] )

  #ax.violinplot( h_pt_data, vert=False,  )
  #plt.show()

  plt.savefig( path_out + "/" + outname + '.png', bbox_inches='tight')
  plt.savefig( path_out + "/" + outname + '.pdf', bbox_inches='tight')

### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### 
def make_hists_plot( h_pt_data, label, outname, bins = np.linspace(-5, 5, 30), markers=None, cols=None):
  fig, ax = plt.subplots()
  fig.set_figheight(7)
  ax.set_title('')
  # ax.set_yticklabels( [ str(point) for point in points ], fontsize=8 )
  medianprops = dict(color="black",linewidth=1.0)
  if not markers : markers = [ "" for point in points ] 
  if not cols : cols = [None for point in points]
  for point, point_data, mark, col in zip(points, h_pt_data, markers, cols) :
    if col:
      n,bins,patches=plt.hist( point_data, bins, alpha=1.0, label=str(point), color=col, histtype='step', linewidth=2)
      plt.scatter(bins[:-1]+ 0.5*(bins[1:] - bins[:-1]), n, marker=mark, c=col, s=40, alpha=1)
    else :
      n,bins,patches=plt.hist( point_data, bins, alpha=1.0, label=str(point), histtype='step', linewidth=2)
  ax.set( xlabel=label, ylabel=r'N events')
  ax.xaxis.set_major_locator(plt.MaxNLocator(15))
  ax.grid(True, linestyle='dashed')
  plt.grid(axis='both', color='0.95', linestyle='dashed')
  plt.legend(title=r'$(M_X, M_Y)$, [GeV]')
  plt.savefig( path_out + "/" + outname + '.png', bbox_inches='tight')
  plt.savefig( path_out + "/" + outname + '.pdf', bbox_inches='tight')

### b ratio
if True:
  h_pt_data1 = []
  h_pt_data2 = []

  def f1(b1, b2, a1, a2):
    return max(b1, b2) / max(a1, a2)

  def f2(b1, b2, a1, a2):
    return min(b1, b2) / min(a1, a2)

  for point in points:
    df = dfs[ point ]

    data1 = df.apply(lambda x: f1(x.b_H_Pt, x.bbar_H_Pt, x.b_t_Pt, x.bbar_t_Pt), axis=1)
    data2 = df.apply(lambda x: f2(x.b_H_Pt, x.bbar_H_Pt, x.b_t_Pt, x.bbar_t_Pt), axis=1)

    h_pt_data1 += [ data1 ]
    h_pt_data2 += [ data2 ]

  make_box_plot( h_pt_data1, "$p_T(b_H^{leading})/p_T(b_t^{leading})$", "Pt_b_ratio1" )
  make_box_plot( h_pt_data2, "$p_T(b_H^{second})/p_T(b_t^{second})$", "Pt_b_ratio2" )

### Pts
if True:
  pt_vars = [ [r'$p_T(H)$, [GeV]', "Pt_H", ["H_Pt"]],  
              [r'$p_T(l)$, [GeV]', "Pt_l", ["l_Pt"]],
              [r'$p_T(q)$, [GeV]', "Pt_q", ["q_Pt", "qbar_Pt"]],
              [r'$p_T(t)$, [GeV]', "Pt_t", ["t_Pt", "tbar_Pt"]],
              [r'$p_T(W)$, [GeV]', "Pt_W", ["W_Pt", "Wbar_Pt"]],
              [r'$p_T(b_H)$, [GeV]', "Pt_b_H", ["b_H_Pt", "bbar_H_Pt"]],
              [r'$p_T(b_t)$, [GeV]', "Pt_b_t", ["b_t_Pt", "bbar_t_Pt"]],
              [r'$E_T(\nu)$, [GeV]', "Et_nu",  ["v_Pt"]],
  ]
  for label, outname, var_list in pt_vars:
    h_pt_data = []

    for point in points:
      df = dfs[ point ]
      data_point = pd.Series([])
      for var in var_list : 
        data_point = data_point.append( df[ var ], ignore_index=True )
      h_pt_data += [ data_point ]

    make_box_plot( h_pt_data, label, outname )

### Eta
if True:
  pt_vars = [ [r'$\eta(H)$', "Eta_H", ["H_Eta"]],  
              [r'$\eta(l)$', "Eta_l", ["l_Eta"]],
              [r'$\eta(q)$', "Eta_q", ["q_Eta", "qbar_Eta"]],
              [r'$\eta(t)$', "Eta_t", ["t_Eta", "tbar_Eta"]],
              [r'$\eta(W)$', "Eta_W", ["W_Eta", "Wbar_Eta"]],
              [r'$\eta(b_H)$', "Eta_b_H", ["b_H_Eta", "bbar_H_Eta"]],
              [r'$\eta(b_t)$', "Eta_b_t", ["b_t_Eta", "bbar_t_Eta"]],
              [r'$\eta(\nu)$', "Et_nu",   ["v_Eta"]],
  ]
  for label, outname, var_list in pt_vars:
    h_pt_data = []

    for point in points:
      df = dfs[ point ]
      data_point = pd.Series([])
      for var in var_list : 
        data_point = data_point.append( df[ var ], ignore_index=True )
      h_pt_data += [ data_point ]

    make_hists_plot( h_pt_data, label, outname, cols=colors_t2 )

### dR
if True:
  pt_vars = [ [r'$\Delta R(q,\bar{q})$', "dR_q_qbar", ["dR_q_qbar"]],
              [r'$\Delta R(t,\bar{t})$', "dR_t_tbar", ["dR_t_tbar"]],
              [r'$\Delta R(W,\bar{W})$', "dR_W_Wbar", ["dR_W_Wbar"]],
              [r'$\Delta R(b_H,\bar{b}_H)$', "dR_b_H_bbar_H", ["dR_b_H_bbar_H"]],
              [r'$\Delta R(b_t,\bar{b}_t)$', "dR_b_t_bbar_t", ["dR_b_t_bbar_t"]],
              [r'$\Delta R(b_H,b_t)$', "dR_b_H_b_t", ["dR_b_H_b_t", "dR_b_H_bbar_t", "dR_bbar_H_b_t", "dR_bbar_H_bbar_t"]],
 ]
  for label, outname, var_list in pt_vars:
    h_pt_data = []

    for point in points:
      df = dfs[ point ]
      data_point = pd.Series([])
      for var in var_list : 
        data_point = data_point.append( df[ var ], ignore_index=True)
      h_pt_data += [ data_point ]

    # make_hists_plot( h_pt_data, label, outname, bins = np.linspace(0, 5, 20) )
    make_box_plot( h_pt_data, label, outname )

### dEta
if True:
  pt_vars = [ [r'$\Delta\eta(q,\bar{q})$', "dEta_q_qbar", ["dEta_q_qbar"]],
              [r'$\Delta\eta(t,\bar{t})$', "dEta_t_tbar", ["dEta_t_tbar"]],
              [r'$\Delta\eta(W,\bar{W})$', "dEta_W_Wbar", ["dEta_W_Wbar"]],
              [r'$\Delta\eta(b_H,\bar{b}_H)$', "dEta_b_H_bbar_H", ["dEta_b_H_bbar_H"]],
              [r'$\Delta\eta(b_t,\bar{b}_t)$', "dEta_b_t_bbar_t", ["dEta_b_t_bbar_t"]],
              [r'$\Delta\eta(b_H,b_t)$', "dEta_b_H_b_t", ["dEta_b_H_b_t", "dEta_b_H_bbar_t", "dEta_bbar_H_b_t", "dEta_bbar_H_bbar_t"]],
 ]
  for label, outname, var_list in pt_vars:
    h_pt_data = []

    for point in points:
      df = dfs[ point ]
      data_point = pd.Series([])
      for var in var_list : 
        data_point = data_point.append( df[ var ], ignore_index=True)
      h_pt_data += [ data_point ]

    # make_hists_plot( h_pt_data, label, outname, bins = np.linspace(0, 5, 20) )
    unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
    make_hists_plot( h_pt_data, label, outname, markers=unfilled_markers[:len(points)], cols=colors_t2 )

### dPhi
if True:
  pt_vars = [ [r'$\Delta\varphi(q,\bar{q})$', "dPhi_q_qbar", ["dPhi_q_qbar"]],
              [r'$\Delta\varphi(t,\bar{t})$', "dPhi_t_tbar", ["dPhi_t_tbar"]],
              [r'$\Delta\varphi(W,\bar{W})$', "dPhi_W_Wbar", ["dPhi_W_Wbar"]],
              [r'$\Delta\varphi(b_H,\bar{b}_H)$', "dPhi_b_H_bbar_H", ["dPhi_b_H_bbar_H"]],
              [r'$\Delta\varphi(b_t,\bar{b}_t)$', "dPhi_b_t_bbar_t", ["dPhi_b_t_bbar_t"]],
              [r'$\Delta\varphi(b_H,b_t)$', "dPhi_b_H_b_t", ["dPhi_b_H_b_t", "dPhi_b_H_bbar_t", "dPhi_bbar_H_b_t", "dPhi_bbar_H_bbar_t"]],
 ]
  for label, outname, var_list in pt_vars:
    h_pt_data = []

    for point in points:
      df = dfs[ point ]
      data_point = pd.Series([])
      for var in var_list : 
        data_point = data_point.append( df[ var ], ignore_index=True)
      h_pt_data += [ data_point ]

    # make_hists_plot( h_pt_data, label, outname, bins = np.linspace(0, 5, 20) )
    unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
    print(colors)
    make_hists_plot( h_pt_data, label, outname, bins = np.linspace(-3.14, 3.14, 30), markers=unfilled_markers[:len(points)], cols=colors_t2 )

### nu_reco_dPz
if True:
  pt_vars = [ [r'$\frac{p_{z}(\nu)-p_{z}(\nu_{reco})}{p_{z}(\nu)}$', "nu_reco_dPz_delta", ["nu_reco_dPz"]],
              [r'$\Delta R(\nu, \nu_{reco})$', "nu_reco_dR", ["nu_reco_dR"]],
              [r'$\Delta \eta(\nu,|\nu_{reco})|$', "nu_reco_dEta", ["nu_reco_dEta"]]
  ]
  for label, outname, var_list in pt_vars:
    h_pt_data = []

    for point in points:
      df = dfs[ point ]
      data_point = pd.Series([])
      for var in var_list : 
        data_point = data_point.append( df[ var ], ignore_index=True)
      h_pt_data += [ data_point ]

    # make_hists_plot( h_pt_data, label, outname, bins = np.linspace(0, 5, 20) )
    unfilled_markers = [m for m, func in Line2D.markers.items() if func != 'nothing' and m not in Line2D.filled_markers]
    print(colors)
    make_hists_plot( h_pt_data, label, outname, bins = np.linspace(-3.14, 3.14, 30), markers=unfilled_markers[:len(points)], cols=colors_t2 )





