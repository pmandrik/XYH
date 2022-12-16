
points = [(650, 375), (900, 600), (1300, 475), (1300, 975), (1700, 475), (1700, 1225), (1900, 475), (1900, 1600)]
#points = [(650, 375), (900, 600), (1300, 475), (1300, 975), (1700, 475), (1700, 1225)]


def get_df( point ):
  import pandas as pd
  df = pd.read_csv("output_file_MX" + str(point[0]) + "_MY" + str(point[1]) + ".tsv", sep='\t')
  # print(df.values)
  return df

def get_xsec_limits( point ):
  df = get_df( point )

  if False:
    print( df.columns.values )
    print( df['b_H2_tt'] )   # Br(H2->tt)
    print( df['b_H3_H1H2'] ) # Br(H->H1H2)
    print( df['hb_result'] ) # excluded or not
    print( df['x_H3_gg'] ) # ggF X crossection

  sxec_max = 0
  sxec_max_1 = 0

  br_max = 0
  for index, row in df.iterrows():
    xsec = row['x_H3_gg']
    br1  = row['b_H2_tt']
    br1_alt  = row['b_H2_bb']
    br2  = row['b_H3_H1H2']

    br1_1  = row['b_H2_WW']
    br1_2  = row['b_H2_gg']
    br1_3  = row['b_H2_ZZ']
    br1_4  = row['b_H2_bb']

    br_min = min( [ br1/br1_1, br1/br1_2, br1/br1_3, br1/br1_4 ] )
    if br_max < br_min and False:
      print( br_max )
      print( [ br1/br1_1, br1/br1_2, br1/br1_3, br1/br1_4 ] )
      print( [ br1, br1_1, br1_2, br1_3, br1_4 ] )

    br_max = max( br_max, br1 / br1_4 );

    veto = row['hb_result']
    veto1 = row['hs_deltaChisq']

    xsec_sm = row['x_H1_gg']

    k_factor = 50.35 / xsec_sm

    xsec_tot = xsec * br1 * br2
    xsec_tot_1 = xsec * br1_alt * br2

    sxec_max = max(xsec_tot * k_factor * 1000, sxec_max)
    sxec_max_1 = max(xsec_tot_1 * k_factor * 1000, sxec_max_1)
    # print( veto, veto1, veto2, xsec_tot, xsec_sm, k_factor, xsec_tot * k_factor * 1000 ) #fb

    if veto1 > 6.18 :
      print( veto, veto1, veto1 < 6.18 )

  print( point, sxec_max, sxec_max_1, br_min, br_max )

for point in points:
  get_xsec_limits( point )

"""
  //! `1` = allowed, `0` = excluded, `-1` = invalid
  std::array<int, nHzero + nHplus + 1> result;
  //! id of the most sensitive channel (use with `Key.dat`)
  std::array<int, nHzero + nHplus + 1> chan;
  //! predicted rate over observed limit
  std::array<double, nHzero + nHplus + 1> obsratio;
  //! number of combined Higgses contributing
  std::array<int, nHzero + nHplus + 1> ncombined;

"""
