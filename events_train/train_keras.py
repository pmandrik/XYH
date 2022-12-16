import tensorflow as tf
from tensorflow import keras

import numpy as np
import pandas as pd

def get_dataset( X, Y, max_rows ):
  path = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/"
  # path = "./"
  file = "csv_NMSSM_XYH_ttbb_MX_" + str(X) + "_MY_" + str(Y) + ".csv"

  df1 = pd.read_csv( path + file , sep=" ", nrows=max_rows)
  return df1

def pm_train():
  points = [(650, 375), (900, 600), (1300, 475), (1300, 975), (1700, 475), (1700, 1225), (1900, 475), (1900, 1600)]
  points = [(1900, 1600)]
  for point in points:
    datasets = []
    #for X, Y in points:
    #dt = get_dataset( point[0], point[1], 125000 )
    dt = get_dataset( point[0], point[1], 125000 )
    datasets += [ dt ]

    vars_y = []
    vars_x = []

    for j in range(0, 8) :
      vars_y += [ "JetMatch" + str(j) + "_H"  ]
      vars_y += [ "JetMatch" + str(j) + "_tq" ] # 51
      vars_y += [ "JetMatch" + str(j) + "_tl" ] # 16

      vars_x += [ "JetPt" + str(j) ]
      vars_x += [ "JetEta" + str(j) ]
      vars_x += [ "JetPhi" + str(j) ]
      vars_x += [ "JetM" + str(j) ]
      vars_x += [ "JetBtag" + str(j) ]

      for k in range(j, 8) :
        vars_x += [ "Jet" + str(j) + "N" + str(k) + "_M"  ];
        vars_x += [ "Jet" + str(j) + "N" + str(k) + "_dR" ];

    vars_x += [ "nuPt", "nuPhi", "lPt", "lEta", "lPhi", "Nmu", "Ne", "wlPt", "WlEta", "WlPhi", "WlM" ];


    df = datasets [ 0 ]
    print( df )
    df=(df-df.min())/(df.max()-df.min()+0.000000001)
    x_features = df[ vars_x ]
    y_features = df[ vars_y ]

    data_x = x_features.to_numpy()
    data_y = y_features.to_numpy()

    # xft = tf.convert_to_tensor( x_features )
    # yft = tf.convert_to_tensor( y_features )

    #normalizer = tf.keras.layers.experimental.preprocessing.Normalization( axis=-1 ); # keras.layers.Normalization(axis=-1)
    #normalizer.adapt( x_features )

    model = keras.Sequential([
      # tf.keras.layers.InputLayer(input_shape=(len(vars_x),)),
      keras.layers.Dense(units=2*len(vars_x), activation='linear', input_shape=(len(vars_x),) ),
      keras.layers.Dense(units=5*len(vars_x), activation='relu'),
      keras.layers.Dense(units=len(vars_x), activation='relu'),
      keras.layers.Dense(units=3*len(vars_y), activation='relu'),
      keras.layers.Dense(units=3*len(vars_y), activation='relu'),
      keras.layers.Dense(units=2*len(vars_y), activation='relu'),
      keras.layers.Dense(units=1*len(vars_y), activation='sigmoid'),
    ])
    model.compile(optimizer='adam', loss="binary_crossentropy", metrics=["binary_crossentropy", "accuracy", "mse"])

    model.fit(data_x, data_y, epochs=20)
    model.save("model_X" + str(point[0]) + "_" + str(point[1]) + ".h5", save_format='h5')
    print("\n--- --- --- --- --- --- --- --- ---\n")

if __name__ == "__main__" : 
  pm_train() 





