import tensorflow as tf
from tensorflow import keras

import numpy as np
import pandas as pd

def get_dataset( X, Y, max_rows ):
  path = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/"
  file = "csv_NMSSM_XYH_ttbb_MX_" + str(X) + "_MY_" + str(Y) + ".csv"

  df1 = pd.read_csv( path + file , sep=" ", nrows=max_rows)
  return df1

def pm_train():

  points = [(650, 375), (900, 600), (1300, 475), (1300, 975), (1700, 475), (1700, 1225), (1900, 475), (1900, 1600)]
  datasets = []
  for X, Y in points:
    dt = get_dataset( X, Y, 5000 )
    datasets += [ dt ]

  vars_y = []
  vars_x = []

  for j in range(0, 10) :
    vars_y += [ "JetMatch" + str(j) + "_H"  ]
    vars_y += [ "JetMatch" + str(j) + "_tq" ]
    vars_y += [ "JetMatch" + str(j) + "_tl" ]

    vars_x += [ "JetPt" + str(j) ]
    vars_x += [ "JetEta" + str(j) ]
    vars_x += [ "JetPhi" + str(j) ]
    vars_x += [ "JetM" + str(j) ]
    vars_x += [ "JetBtag" + str(j) ]
  vars_x += [ "nuPt", "nuPhi", "lPt", "lEta", "lPhi", "Nmu", "Ne", "wlPt", "WlEta", "WlPhi", "WlM" ];


  df = datasets [ 0 ]
  x_features = df[ vars_x ]
  y_features = df[ vars_y ]

  # xft = tf.convert_to_tensor( x_features )
  # yft = tf.convert_to_tensor( y_features )

  #normalizer = tf.keras.layers.experimental.preprocessing.Normalization( axis=-1 ); # keras.layers.Normalization(axis=-1)
  #normalizer.adapt( x_features )

  model = keras.Sequential([
    tf.keras.layers.InputLayer(input_shape=(len(vars_x),)),
    #keras.layers.Dense(units=10*len(vars_y), activation='relu'),
    #keras.layers.Dense(units=8*len(vars_y), activation='relu'),
    keras.layers.Dense(units=6*len(vars_y), activation='relu'),
    keras.layers.Dense(units=4*len(vars_y), activation='relu'),
    keras.layers.Dense(units=4*len(vars_y), activation='relu'),
    keras.layers.Dense(units=1*len(vars_y), activation='relu'),
  ])
  model.compile(optimizer='adam', loss="cosine_similarity", metrics=["binary_crossentropy", "accuracy"])

  BATCH_SIZE = 1
  model.fit(x_features, y_features, epochs=5, steps_per_epoch=1000, batch_size=BATCH_SIZE)

  print( x_features.loc[0].to_numpy() )

  start  = 100
  checks = 3
  predictions = model.predict( x_features.iloc[start:start+checks] )

  for check in range( checks ) :
    data_true = y_features.iloc[ start+check ]
    data_pred = predictions[ check ]
    for entry1, entry2 in zip(data_true, data_pred) :
      print( entry1, entry2 )
    print("\n--- --- --- --- --- --- --- --- ---\n")

if __name__ == "__main__" : 
  pm_train() 





