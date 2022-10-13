
import numpy as np
import pandas as pd

def get_dataset( X, Y, max_rows ):
  path = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/"
  path = "./"
  file = "csvOUT_NMSSM_XYH_ttbb_MX_" + str(X) + "_MY_" + str(Y) + ".csv"

  df1 = pd.read_csv( path + file , sep=",", nrows=max_rows)
  return df1


def get_dataset2( X, Y, max_rows ):
  path = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/"
  path = "./"
  file = "csvOUT2_NMSSM_XYH_ttbb_MX_" + str(X) + "_MY_" + str(Y) + ".csv"

  df1 = pd.read_csv( path + file , sep=",", nrows=max_rows)
  return df1

def get_dataset_back( X, Y, max_rows ):
  path = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/"
  path = "./"
  file = "csvOUT2_ttbar_MX_" + str(X) + "_MY_" + str(Y) + ".csv"

  df1 = pd.read_csv( path + file , sep=",", nrows=max_rows)
  return df1

def get_dataset_back_ttH( X, Y, max_rows ):
  path = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/"
  path = "./"
  file = "csvOUT2_ttH_MX_" + str(X) + "_MY_" + str(Y) + ".csv"

  df1 = pd.read_csv( path + file , sep=",", nrows=max_rows)
  return df1

def pm_train():
  do_print = False
  if True:
    points = [(650, 375), (900, 600), (1300, 475), (1300, 975), (1700, 475), (1700, 1225), (1900, 475), (1900, 1600)]
    for point in points:
      rate_array = []
      all_jets_event = 0
      # f = open("eval2_ttbar_MX_" + str(point[0]) + "_MY_" + str(point[1]) + ".txt", "w")
      f = open("eval2_ttH_MX_" + str(point[0]) + "_MY_" + str(point[1]) + ".txt", "w")
      df = get_dataset_back_ttH( point[0], point[1], 9999999999 )
      vars_y1 = []
      vars_y2 = []

      for j in range(0, 8) :
        vars_y1 += [ "JetMatch" + str(j) + "_H"  ]
        vars_y1 += [ "JetMatch" + str(j) + "_tq" ] # 51
        vars_y1 += [ "JetMatch" + str(j) + "_tl" ] # 16

        vars_y2 += [ "JetPred" + str(j) + "_H"  ]
        vars_y2 += [ "JetPred" + str(j) + "_tq" ] # 51
        vars_y2 += [ "JetPred" + str(j) + "_tl" ] # 16

      y_features1 = df[ vars_y1 ]
      y_features2 = df[ vars_y2 ]

      size = len(df.index)
      for i in range( size ):
        yy1 = y_features1.iloc[ i ]
        yy2 = y_features2.iloc[ i ]
        # print( yy1 )
        if do_print :
          for var, y1, y2 in zip( vars_y1, yy1, yy2 ):
            print( int(y1+0.1), y2, var )

        clusters = []
        sum_score = 0
        founds_score = 0;
        for var, y1, y2 in zip( vars_y1, yy1, yy2 ):
          clusters += [ (y2, int(y1+0.1), var.split("_")[-1], int(var.split("_")[0][-1:]) ) ]
          sum_score += int(y1+0.1);
        clusters = sorted( clusters, key=lambda x: x[0], reverse = True )

        out_h = []
        out_tq = []
        out_tl = []
        used_jets = {}
        for inp in clusters:
          if inp[3] in used_jets : continue

          if inp[2] == 'H' and len(out_h) < 2:
            out_h += [ inp ]
            used_jets[inp[3]] = True
            founds_score += inp[1]
          elif inp[2] == 'tq' and len(out_tq) < 3:
            out_tq += [ inp ]
            used_jets[inp[3]] = True
            founds_score += inp[1]
          elif inp[2] == 'tl' and len(out_tl) < 1:
            out_tl += [ inp ]
            used_jets[inp[3]] = True
            founds_score += inp[1]

        if do_print :
          print( clusters )

          print(out_h)
          print(out_tq)
          print(out_tl)

          print("Score", founds_score, "/", sum_score)
          print("\n--- --- --- --- --- --- --- --- ---\n")

        output_write = ""
        output_write += " ".join([ str(x) for x in out_h[0] ]) + "\n"
        output_write += " ".join([ str(x) for x in out_h[1] ]) + "\n"
        output_write += " ".join([ str(x) for x in out_tq[0] ]) + "\n"
        output_write += " ".join([ str(x) for x in out_tq[1] ]) + "\n"
        output_write += " ".join([ str(x) for x in out_tq[2] ]) + "\n"
        output_write += " ".join([ str(x) for x in out_tl[0] ]) + "\n"
        f.write( output_write )

        if sum_score :
          all_jets_event += int(founds_score/sum_score)
          rate_array += [ founds_score/sum_score ]
        else : 
          rate_array += [ 1 ]

      print( point, sum(rate_array)/len(rate_array), all_jets_event / size   )
    return

  points = [(650, 375), (900, 600), (1300, 475), (1300, 975), (1700, 475), (1700, 1225), (1900, 475), (1900, 1600)]
  # points = [ (1900, 1600) ]
  n_points = 99990000

  for point in points:
    f = open("eval2_NMSSM_XYH_ttbb_MX_" + str(point[0]) + "_MY_" + str(point[1]) + ".txt", "w")
    datasets = []
    all_jets_event = 0
    #for X, Y in points:
    #dt = get_dataset( point[0], point[1], 125000 )
    dt = get_dataset2( point[0], point[1], n_points )
    datasets += [ dt ]

    vars_y1 = []
    vars_y2 = []

    for j in range(0, 8) :
      vars_y1 += [ "JetMatch" + str(j) + "_H"  ]
      vars_y1 += [ "JetMatch" + str(j) + "_tq" ] # 51
      vars_y1 += [ "JetMatch" + str(j) + "_tl" ] # 16

      vars_y2 += [ "JetPred" + str(j) + "_H"  ]
      vars_y2 += [ "JetPred" + str(j) + "_tq" ] # 51
      vars_y2 += [ "JetPred" + str(j) + "_tl" ] # 16

    df = datasets [ 0 ]
    size = len(df.index)
    # print( df )

    y_features1 = df[ vars_y1 ]
    y_features2 = df[ vars_y2 ]
    rate_array = []

    for i in range( min( n_points, size ) ):
      yy1 = y_features1.iloc[ i ]
      yy2 = y_features2.iloc[ i ]
      # print( yy1 )
      if do_print :
        for var, y1, y2 in zip( vars_y1, yy1, yy2 ):
          print( int(y1+0.1), y2, var )

      clusters = []
      sum_score = 0
      founds_score = 0;
      for var, y1, y2 in zip( vars_y1, yy1, yy2 ):
        clusters += [ (y2, int(y1+0.1), var.split("_")[-1], int(var.split("_")[0][-1:]) ) ]
        sum_score += int(y1+0.1);
      clusters = sorted( clusters, key=lambda x: x[0], reverse = True )

      out_h = []
      out_tq = []
      out_tl = []
      used_jets = {}
      for inp in clusters:
        if inp[3] in used_jets : continue

        if inp[2] == 'H' and len(out_h) < 2:
          out_h += [ inp ]
          used_jets[inp[3]] = True
          founds_score += inp[1]
        elif inp[2] == 'tq' and len(out_tq) < 3:
          out_tq += [ inp ]
          used_jets[inp[3]] = True
          founds_score += inp[1]
        elif inp[2] == 'tl' and len(out_tl) < 1:
          out_tl += [ inp ]
          used_jets[inp[3]] = True
          founds_score += inp[1]

      if do_print :
        print( clusters )

        print(out_h)
        print(out_tq)
        print(out_tl)

        print("Score", founds_score, "/", sum_score)
        print("\n--- --- --- --- --- --- --- --- ---\n")

      output_write = ""
      output_write += " ".join([ str(x) for x in out_h[0] ]) + "\n"
      output_write += " ".join([ str(x) for x in out_h[1] ]) + "\n"
      output_write += " ".join([ str(x) for x in out_tq[0] ]) + "\n"
      output_write += " ".join([ str(x) for x in out_tq[1] ]) + "\n"
      output_write += " ".join([ str(x) for x in out_tq[2] ]) + "\n"
      output_write += " ".join([ str(x) for x in out_tl[0] ]) + "\n"
      f.write( output_write )

      if sum_score :
        all_jets_event += int(founds_score/sum_score)
        rate_array += [ founds_score/sum_score ]
      else : 
        rate_array += [ 1 ]

    print( point, sum(rate_array)/len(rate_array), all_jets_event / min( n_points, size )  )

if __name__ == "__main__" : 
  pm_train() 





