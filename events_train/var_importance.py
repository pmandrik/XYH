
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '0' 

import tensorflow as tf
#tf.debugging.set_log_device_placement(True)
#tf.autograph.set_verbosity(3)
#tf.logging.set_verbosity(tf.logging.ERROR)

from tensorflow import keras

import numpy as np
import pandas as pd

import sys

def call(mass_point, var_index):

  def get_dataset( X, Y, max_rows ):
    path = "/home/pmandrik/work/projects/XYH/gitrepo/XYH/events_process/"
    file = "csv_NMSSM_XYH_ttbb_MX_" + str(X) + "_MY_" + str(Y) + ".csv"

    df1 = pd.read_csv( path + file , sep=" ", nrows=max_rows)
    return df1

  points = [(650, 375), (900, 600), (1300, 475), (1300, 975), (1700, 475), (1700, 1225), (1900, 475), (1900, 1600)]

  session_ = tf.compat.v1.Session()

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


  points = [ points[ int( mass_point ) ] ]

  for point in points:

    model = tf.keras.models.load_model("model_" + str(point[0]) + "_" + str(point[1]) + ".h5")

    print( "MODEL:===============================================================" )
    print( point )

    #df = get_dataset( point[0], point[1], 999 )
    df = get_dataset( point[0], point[1], 999900 )
    df=(df-df.min())/(df.max()-df.min()+0.000000001)
    x_features = df[ vars_x ]
    y_features = df[ vars_y ]
    #y_predict = model.predict( x_features )


    #for index, row in x_features.iterrows():
    #  for var in vars_x: print( row[var], end=", " ) 
    #  # for var in vars_y: print( row[var], endline=", " ) 
    #  print()

    ### print( x_features )
    ### print( len(vars_x) )

    def base_model():
      return model

    if True:
      from tensorflow.keras.wrappers.scikit_learn import KerasClassifier, KerasRegressor
      from eli5.permutation_importance import get_score_importances
      import copy
      import sys

      # ... load data, define score function
      def score(X, y):
        y_pred = model.predict(X)
        accuracy = tf.keras.losses.binary_crossentropy( y, y_pred )
        return accuracy

      def get_score_importances(score, x_features, y_features):
        accuracy = score(x_features, y_features)
        def_acc = accuracy.eval(session=tf.compat.v1.Session())
        for var in vars_x :
          if var != vars_x[int(var_index)] : continue

          x_clone = copy.deepcopy( x_features )
          #print( x_clone[vars_x[0]] )
          #print( x_clone[var] )
          x_clone[var].values[:] = x_clone[var].sample(frac = 1).values[:]
          #print( x_clone[vars_x[0]] )
          #print( x_clone[var] )

          accuracy_clone = score(x_clone, y_features)

          sess = tf.compat.v1.Session()
          acc = accuracy_clone.eval(session=sess)
          sess.close()

          average = 0
          for i in range( len(def_acc) ) :
            average += pow(def_acc[i] - acc[i], 2)
          average = pow(average, 0.5)
          print( var, average )

          del accuracy_clone
          del x_clone
          del acc

      get_score_importances(score, x_features, y_features)

      #feature_importances = np.mean(score_decreases, axis=0)
      #print( feature_importances )

    if False:
      import shap

      # load your data here, e.g. X and y
      # create and fit your model here

      # load JS visualization code to notebook
      shap.initjs()

      # explain the model's predictions using SHAP
      # (same syntax works for LightGBM, CatBoost, scikit-learn and spark models)
      explainer = shap.KernelExplainer(model.predict, x_features, link="logit")
      shap_values = explainer.shap_values(x_features, nsamples=100)

      # visualize the first prediction's explanation (use matplotlib=True to avoid Javascript)
      #shap.force_plot(explainer.expected_value, shap_values[0,:], X.iloc[0,:])

      shap.force_plot(explainer.expected_value[0], shap_values[0][0,:], X_test.iloc[0,:], link="logit")


call(sys.argv[1], sys.argv[2])









