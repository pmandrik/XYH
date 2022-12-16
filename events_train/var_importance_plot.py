

f = open("log.txt", "r")
data = f.read()

lines = data.split("\n") 

from collections import defaultdict

point_dic = defaultdict(lambda: defaultdict(list) )
point_dic_sum = defaultdict(lambda: defaultdict(float) )

for i in range( len(lines) ) :
  if "MODEL" in lines[i] : continue
  if not "(" in lines[i] : continue
  point_raw = lines[i]
  result    = lines[i+1]
  if "MODEL" in lines[i+1] : continue
  if not result : continue

  print( point_raw, result )
  name = result.split()[0]
  val = float(result.split()[1])

  var_names = {  }
  var_names[ "JetPt" ] = "$\overline{p_T(j)}$"
  var_names[ "JetEta" ] = "$\overline{\eta(j)}$"
  var_names[ "JetPhi" ] = "$\overline{\\varphi(j)}$"
  var_names[ "JetM" ] = "$\overline{m(j)}$"
  var_names[ "JetBtag" ] = "$\overline{ \textrm{b-tag score} }$"
  var_names[ "jj_M" ] = "$\overline{ m(j_i,j_j) }$"
  var_names[ "jj_dR" ] = "$\overline{ \Delta R(j_i,j_j) }$"
  var_names[ "nuPt" ] = "$p_T(\nu)$"
  var_names[ "nuPhi" ] = "$\\varphi(\nu)$"
  var_names[ "lPt" ] = "$p_T(\ell)$"
  var_names[ "lEta" ] = "$\eta(\ell)$"
  var_names[ "lPhi" ] = "$\\varphi(\ell)$"
  var_names[ "Nmu" ] = "$N_{\mu}$"
  var_names[ "Ne" ] = "$N_{e}$"
  var_names[ "wlPt" ] = "$p_T(W_{\ell})$"
  var_names[ "WlEta" ] = "$\eta(W_{\ell})$"
  var_names[ "WlPhi" ] = "$\\varphi(W_{\ell})$"
  var_names[ "WlM" ] = "$m(W_{\ell})$"

  if "JetPt" in result :
    point_dic[ point_raw ][ var_names["JetPt"] ] += [ val ]
    point_dic_sum[ point_raw ][ var_names["JetPt"] ] += val
  elif "JetEta" in result :
    point_dic[ point_raw ][ var_names["JetEta"] ] += [ val ]
    point_dic_sum[ point_raw ][ var_names["JetEta"] ] += val
  elif "JetPhi" in result :
    point_dic[ point_raw ][ var_names["JetPhi"] ] += [ val ]
    point_dic_sum[ point_raw ][ var_names["JetPhi"] ] += val
  elif "JetM" in result :
    point_dic[ point_raw ][ var_names["JetM"] ] += [ val ]
    point_dic_sum[ point_raw ][ var_names["JetM"] ] += val
  elif "JetBtag" in result :
    point_dic[ point_raw ][ var_names["JetBtag"] ] += [ val ]
    point_dic_sum[ point_raw ][ var_names["JetBtag"] ] += val
  elif "_dR" in result :
    point_dic[ point_raw ][ var_names["jj_dR"] ] += [ val ]
    point_dic_sum[ point_raw ][ var_names["jj_dR"] ] += val
  elif "_M" in result :
    point_dic[ point_raw ][ var_names["jj_M"] ] += [ val ]
    point_dic_sum[ point_raw ][ var_names["jj_M"] ] += val
  else :
    point_dic[ point_raw ][ var_names[name] ] += [ val ]
    point_dic_sum[ point_raw ][ var_names[name] ] += val

point_sum = defaultdict(float)

for point in point_dic.keys() :
  for var_key in point_dic_sum[ point ].keys() :
    point_sum[ point ] += point_dic_sum[ point ][ var_key ]
    point_dic_sum[ point ][ var_key ] = point_dic_sum[ point ][ var_key ] / len( point_dic[ point ][ var_key ] )

for point in point_dic.keys() :
  for var_key in point_dic_sum[ point ].keys() :
    point_dic_sum[ point ][ var_key ] = point_dic_sum[ point ][ var_key ] / point_sum[ point ] * 100

import pandas as pd

df = pd.DataFrame.from_dict(point_dic_sum)
print(df.to_latex(index=True, float_format="{:0.1f}".format, escape=False))












