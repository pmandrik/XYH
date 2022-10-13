













# if( reader4->jet_btag->at(i) <  0.890 ) ljet_candidates.push_back(i);
# 8%
# if( reader4->jet_btag->at(i) <  0.605 ) ljet_candidates.push_back(i); // DEFAULT ONE
# 11%

# 1232 SELECTED ttH
# L = 35.9
# sigma = 507
# Br = 0.5824
# 


inf = 0
dic={}

dic["ttbar-ljets"]=[3238, inf, 3227.43]
dic["ttbar"]=[7135, inf, 7111.72]
dic["ttbar-cc"]=[1600, inf, 1594.78]
dic["ttbar-bb"]=[1757, inf, 1751.27]
dic["ttbar-b"]=[2, inf, 1.99347]

dic["ttbar-cc"]=[417, inf, 416.724]
dic["ttbar-bb"]=[57, inf, 56.9623]
dic["ttbar"]=[1345, inf, 1344.11]
dic["ttbar-ljets"]=[874, inf, 873.421]
dic["ttbar-b"]=[86, inf, 85.9431]

dic["ttbar-ljets"]=[664, inf, 0.238849]
dic["ttbar-"]=[1445, inf, 0.519784]
dic["ttbar-cc"]=[333, inf, 0.119784]
dic["ttbar-bb"]=[323, inf, 0.116187]
dic["ttbar-b"]=[14, inf, 0.00503597]

dic["ttbar-cc"]=[16007, inf, 0.146735]
dic["ttbar-bb"]=[2352, inf, 0.0215606]
dic["ttbar-"]=[51965, inf, 0.476359]
dic["ttbar-ljets"]=[34664, inf, 0.317762]
dic["ttbar-b"]=[4099, inf, 0.0375752]

dic["ttbar-"]=[1733, inf, 0.623381]
dic["ttbar-cc"]=[297, inf, 0.106835]
dic["ttbar-bb"]=[205, inf, 0.073741]
dic["ttbar-ljets"]=[479, inf, 0.172302]
dic["ttbar-b"]=[65, inf, 0.0233813]

dic["ttbar-cc"]=[289, inf, 0.103957]
dic["ttbar-"]=[1598, inf, 0.57482]
dic["ttbar-bb"]=[101, inf, 0.0363309]
dic["ttbar-ljets"]=[695, inf, 0.25]
dic["ttbar-b"]=[96, inf, 0.0345324]

all = dic["ttbar-ljets"][0] + dic["ttbar-"][0] + dic["ttbar-cc"][0] + dic["ttbar-bb"][0] + dic["ttbar-b"][0]

print("!!!")
print( (dic["ttbar-ljets"][0] + dic["ttbar-"][0]) / all  )
print( (dic["ttbar-cc"][0]) / all  )
print( (dic["ttbar-bb"][0] + dic["ttbar-b"][0]) / all  )
print( (dic["ttbar-bb"][0]) / all  )
print( (dic["ttbar-b"][0]) / all  )


ttlf = 463
ttcc = 76
ttb  = 22
tt2b = 9
ttbb = 10

all2 = ttlf + ttcc + ttb + tt2b + ttbb

print("!!!")
print( ttlf / all2  )
print( ttcc / all2  )
print( (ttb + tt2b + ttbb) / all2  )
print( (tt2b + ttbb) / all2  )
print( (ttb) / all2  )


data = """
\begin{tabular}{| c | c | c | c | c |c |c | c|}
\hline
$M_{H}$ & $M_{H_{S}}$ & $h\to bb$ & $h\to \tau\tau$ & $h\to \gamma\gamma$ &
$H_{S} \to h + h$ &$H_{S}\to tt$\\
\hline
  408 &   60$^{(2)}$ &  7.112 $\cdot 10^{-2}$ &  7.582 $\cdot 10^{-3}$ &  1.847 $\cdot 10^{-4}$ & - & - \\
  408 &   80$^{(2)}$ &  6.986 $\cdot 10^{-2}$ &  7.447 $\cdot 10^{-3}$ &  1.822 $\cdot 10^{-4}$ & - & - \\
  401 &   90$^{(2)}$ &  1.058 $\cdot 10^{-1}$ &  1.127 $\cdot 10^{-2}$ &  2.805 $\cdot 10^{-4}$ & - & - \\
  401 &  100$^{(2)}$ &  1.060 $\cdot 10^{-1}$ &  1.130 $\cdot 10^{-2}$ &  2.835 $\cdot 10^{-4}$ & - & - \\
  400 &  150$^{(3)}$ &  1.203 $\cdot 10^{-1}$ &  1.282 $\cdot 10^{-2}$ &  3.538 $\cdot 10^{-4}$ & - & - \\
  400 &  200$^{(3)}$ &  8.029 $\cdot 10^{-2}$ &  8.559 $\cdot 10^{-3}$ &  2.182 $\cdot 10^{-4}$ & - & - \\
  400 &  250 &  5.134 $\cdot 10^{-3}$ &  5.473 $\cdot 10^{-4}$ &  1.408 $\cdot 10^{-5}$ & - & - \\
\hline
  500 &   60 &  5.792 $\cdot 10^{-3}$ &  6.172 $\cdot 10^{-4}$ &  1.608 $\cdot 10^{-5}$ & - & - \\
  500 &   80$^{(1)}$ &  3.224 $\cdot 10^{-2}$ &  3.437 $\cdot 10^{-3}$ &  9.136 $\cdot 10^{-5}$ & - & - \\
  500 &   90$^{(1)}$ &  3.727 $\cdot 10^{-2}$ &  3.973 $\cdot 10^{-3}$ &  1.064 $\cdot 10^{-4}$ & - & - \\
  500 &  100 &  1.786 $\cdot 10^{-2}$ &  1.903 $\cdot 10^{-3}$ &  4.555 $\cdot 10^{-5}$ & - & - \\
  500 &  150$^{(3)}$ &  2.222 $\cdot 10^{-2}$ &  2.368 $\cdot 10^{-3}$ &  6.577 $\cdot 10^{-5}$ & - & - \\
  500 &  200$^{(3)}$ &  2.194 $\cdot 10^{-2}$ &  2.341 $\cdot 10^{-3}$ &  7.415 $\cdot 10^{-5}$ & - & - \\
  500 &  250$^{(3)}$ &  4.259 $\cdot 10^{-2}$ &  4.546 $\cdot 10^{-3}$ &  1.487 $\cdot 10^{-4}$ & - & - \\
  500 &  300$^{(3)}$ &  2.617 $\cdot 10^{-2}$ &  2.795 $\cdot 10^{-3}$ &  9.755 $\cdot 10^{-5}$ &  1.570 $\cdot 10^{-3}$ & - \\
\hline
  600 &   60 &  2.913 $\cdot 10^{-3}$ &  3.102 $\cdot 10^{-4}$ &  8.732 $\cdot 10^{-6}$ & - & - \\
  600 &   80$^{(1)}$ &  2.839 $\cdot 10^{-2}$ &  3.026 $\cdot 10^{-3}$ &  9.022 $\cdot 10^{-5}$ & - & - \\
  600 &   90$^{(1)}$ &  2.275 $\cdot 10^{-2}$ &  2.421 $\cdot 10^{-3}$ &  6.950 $\cdot 10^{-5}$ & - & - \\
  600 &  100$^{(1)}$ &  2.237 $\cdot 10^{-2}$ &  2.383 $\cdot 10^{-3}$ &  6.957 $\cdot 10^{-5}$ & - & - \\
  600 &  150$^{(3)}$ &  1.053 $\cdot 10^{-2}$ &  1.122 $\cdot 10^{-3}$ &  3.383 $\cdot 10^{-5}$ & - & - \\
  600 &  200$^{(3)}$ &  2.496 $\cdot 10^{-2}$ &  2.658 $\cdot 10^{-3}$ &  9.316 $\cdot 10^{-5}$ & - & - \\
  600 &  250$^{(3)}$ &  1.185 $\cdot 10^{-2}$ &  1.266 $\cdot 10^{-3}$ &  4.227 $\cdot 10^{-5}$ & - & - \\
  600 &  300$^{(3)}$ &  1.840 $\cdot 10^{-2}$ &  1.965 $\cdot 10^{-3}$ &  7.080 $\cdot 10^{-5}$ &  3.498 $\cdot 10^{-2}$ & - \\
  600 &  400 &  2.707 $\cdot 10^{-3}$ &  2.892 $\cdot 10^{-4}$ &  1.021 $\cdot 10^{-5}$ &  1.564 $\cdot 10^{-3}$ &  9.361 $\cdot 10^{-3}$ \\
\hline
\end{tabular}
\end{center}
\end{table}

\begin{table}[ht]
\caption*{Table 1 continued}
\begin{center}
\begin{tabular}{| c | c | c | c | c |c |c | c|}
\hline
$M_{H}$ & $M_{H_{S}}$ & $h\to bb$ & $h\to \tau\tau$ & $h\to \gamma\gamma$ &
$H_{S} \to h+h$ &$H_{S}\to tt$\\
\hline
  700 &   60 &  1.856 $\cdot 10^{-2}$ &  1.976 $\cdot 10^{-3}$ &  7.059 $\cdot 10^{-5}$ & - & - \\
  700 &   80 &  1.924 $\cdot 10^{-2}$ &  2.048 $\cdot 10^{-3}$ &  7.247 $\cdot 10^{-5}$ & - & - \\
  700 &   90 &  1.941 $\cdot 10^{-2}$ &  2.065 $\cdot 10^{-3}$ &  7.200 $\cdot 10^{-5}$ & - & - \\
  700 &  100 &  1.941 $\cdot 10^{-2}$ &  2.067 $\cdot 10^{-3}$ &  7.276 $\cdot 10^{-5}$ & - & - \\
  700 &  150$^{(3)}$ &  7.745 $\cdot 10^{-3}$ &  8.242 $\cdot 10^{-4}$ &  3.548 $\cdot 10^{-5}$ & - & - \\
  700 &  200$^{(3)}$ &  6.454 $\cdot 10^{-3}$ &  6.880 $\cdot 10^{-4}$ &  2.351 $\cdot 10^{-5}$ & - & - \\
  700 &  250$^{(3)}$ &  1.436 $\cdot 10^{-2}$ &  1.534 $\cdot 10^{-3}$ &  5.573 $\cdot 10^{-5}$ & - & - \\
  700 &  300$^{(3)}$ &  7.742 $\cdot 10^{-3}$ &  8.273 $\cdot 10^{-4}$ &  3.007 $\cdot 10^{-5}$ &  2.319 $\cdot 10^{-2}$ & - \\
  700 &  400 &  3.427 $\cdot 10^{-3}$ &  3.662 $\cdot 10^{-4}$ &  1.287 $\cdot 10^{-5}$ &  3.305 $\cdot 10^{-4}$ &  9.333 $\cdot 10^{-3}$ \\
  700 &  500 &  5.079 $\cdot 10^{-4}$ &  5.430 $\cdot 10^{-5}$ &  1.963 $\cdot 10^{-6}$ &  7.304 $\cdot 10^{-4}$ &  6.373 $\cdot 10^{-3}$ \\
\hline
  800 &   60 &  8.404 $\cdot 10^{-3}$ &  8.961 $\cdot 10^{-4}$ &  3.193 $\cdot 10^{-5}$ & - & - \\
  800 &   80 &  8.447 $\cdot 10^{-3}$ &  9.000 $\cdot 10^{-4}$ &  3.202 $\cdot 10^{-5}$ & - & - \\
  800 &   90 &  8.520 $\cdot 10^{-3}$ &  9.070 $\cdot 10^{-4}$ &  3.167 $\cdot 10^{-5}$ & - & - \\
  800 &  100 &  8.648 $\cdot 10^{-3}$ &  9.207 $\cdot 10^{-4}$ &  3.227 $\cdot 10^{-5}$ & - & - \\
  800 &  150$^{(3)}$ &  2.825 $\cdot 10^{-3}$ &  3.005 $\cdot 10^{-4}$ &  1.332 $\cdot 10^{-5}$ & - & - \\
  800 &  200$^{(3)}$ &  3.934 $\cdot 10^{-3}$ &  4.189 $\cdot 10^{-4}$ &  1.473 $\cdot 10^{-5}$ & - & - \\
  800 &  250$^{(3)}$ &  5.297 $\cdot 10^{-3}$ &  5.636 $\cdot 10^{-4}$ &  1.925 $\cdot 10^{-5}$ & - & - \\
  800 &  300$^{(3)}$ &  3.844 $\cdot 10^{-3}$ &  4.104 $\cdot 10^{-4}$ &  1.479 $\cdot 10^{-5}$ &  1.160 $\cdot 10^{-2}$ & - \\
  800 &  400 &  1.727 $\cdot 10^{-3}$ &  1.839 $\cdot 10^{-4}$ &  6.346 $\cdot 10^{-6}$ &  1.839 $\cdot 10^{-5}$ &  9.374 $\cdot 10^{-3}$ \\
  800 &  500 &  6.218 $\cdot 10^{-4}$ &  6.621 $\cdot 10^{-5}$ &  2.293 $\cdot 10^{-6}$ &  2.574 $\cdot 10^{-4}$ &  8.400 $\cdot 10^{-3}$ \\
  800 &  600 &  1.236 $\cdot 10^{-4}$ &  1.317 $\cdot 10^{-5}$ &  4.618 $\cdot 10^{-7}$ &  1.074 $\cdot 10^{-4}$ &  4.794 $\cdot 10^{-3}$ \\
\hline
  900 &   60 &  4.060 $\cdot 10^{-3}$ &  4.322 $\cdot 10^{-4}$ &  1.466 $\cdot 10^{-5}$ & - & - \\
  900 &   80 &  4.081 $\cdot 10^{-3}$ &  4.341 $\cdot 10^{-4}$ &  1.503 $\cdot 10^{-5}$ & - & - \\
  900 &   90 &  4.108 $\cdot 10^{-3}$ &  4.370 $\cdot 10^{-4}$ &  1.506 $\cdot 10^{-5}$ & - & - \\
  900 &  100 &  4.056 $\cdot 10^{-3}$ &  4.315 $\cdot 10^{-4}$ &  1.489 $\cdot 10^{-5}$ & - & - \\
  900 &  150 &  4.203 $\cdot 10^{-3}$ &  4.472 $\cdot 10^{-4}$ &  1.513 $\cdot 10^{-5}$ & - & - \\
  900 &  200 &  4.209 $\cdot 10^{-3}$ &  4.479 $\cdot 10^{-4}$ &  1.499 $\cdot 10^{-5}$ & - & - \\
  900 &  250 &  3.157 $\cdot 10^{-3}$ &  3.377 $\cdot 10^{-4}$ &  1.288 $\cdot 10^{-5}$ & - & - \\
  900 &  300 &  3.390 $\cdot 10^{-3}$ &  3.606 $\cdot 10^{-4}$ &  1.253 $\cdot 10^{-5}$ &  3.586 $\cdot 10^{-6}$ & - \\
  900 &  400 &  5.960 $\cdot 10^{-4}$ &  6.342 $\cdot 10^{-5}$ &  2.156 $\cdot 10^{-6}$ &  5.370 $\cdot 10^{-6}$ &  3.933 $\cdot 10^{-3}$ \\
  900 &  500 &  3.302 $\cdot 10^{-4}$ &  3.512 $\cdot 10^{-5}$ &  1.152 $\cdot 10^{-6}$ &  3.281 $\cdot 10^{-7}$ &  3.232 $\cdot 10^{-3}$ \\
  900 &  600 &  1.803 $\cdot 10^{-4}$ &  1.919 $\cdot 10^{-5}$ &  6.271 $\cdot 10^{-7}$ &  1.790 $\cdot 10^{-5}$ &  2.556 $\cdot 10^{-3}$ \\
900 &  700 &  2.469 $\cdot 10^{-5}$ &  2.639 $\cdot 10^{-6}$ &  9.232 $\cdot 10^{-8}$ &  1.209 $\cdot 10^{-5}$ &   5.133 $\cdot 10^{-4}$ \\
\hline
\end{tabular}
\end{center}
\end{table}


\begin{table}[ht]
\caption*{Table 1 continued}
\begin{center}
\begin{tabular}{| c | c | c | c | c |c |c | c|}
\hline
$M_{H}$ & $M_{H_{S}}$ & $h\to bb$ & $h\to \tau\tau$ & $h\to \gamma\gamma$ &
$H_{S} \to h+h$ &$H_{S}\to tt$\\
\hline
 1000 &   60 &  1.893 $\cdot 10^{-3}$ &  2.014 $\cdot 10^{-4}$ &  6.774 $\cdot 10^{-6}$ & - & - \\
 1000 &   80 &  1.905 $\cdot 10^{-3}$ &  2.027 $\cdot 10^{-4}$ &  6.978 $\cdot 10^{-6}$ & - & - \\
 1000 &   90 &  1.917 $\cdot 10^{-3}$ &  2.039 $\cdot 10^{-4}$ &  7.022 $\cdot 10^{-6}$ & - & - \\
 1000 &  100 &  1.888 $\cdot 10^{-3}$ &  2.008 $\cdot 10^{-4}$ &  7.057 $\cdot 10^{-6}$ & - & - \\
 1000 &  150 &  2.062 $\cdot 10^{-3}$ &  2.194 $\cdot 10^{-4}$ &  7.513 $\cdot 10^{-6}$ & - & - \\
 1000 &  200 &  2.196 $\cdot 10^{-3}$ &  2.338 $\cdot 10^{-4}$ &  7.634 $\cdot 10^{-6}$ & - & - \\
 1000 &  250 &  1.442 $\cdot 10^{-3}$ &  1.537 $\cdot 10^{-4}$ &  5.518 $\cdot 10^{-6}$ & - & - \\
 1000 &  300 &  1.366 $\cdot 10^{-3}$ &  1.453 $\cdot 10^{-4}$ &  5.045 $\cdot 10^{-6}$ &  3.186 $\cdot 10^{-4}$ & - \\
 1000 &  400 &  3.429 $\cdot 10^{-4}$ &  3.648 $\cdot 10^{-5}$ &  1.247 $\cdot 10^{-6}$ &  3.837 $\cdot 10^{-6}$ &  2.084 $\cdot 10^{-3}$ \\
 1000 &  500 &  1.725 $\cdot 10^{-4}$ &  1.836 $\cdot 10^{-5}$ &  6.153 $\cdot 10^{-7}$ &  9.341 $\cdot 10^{-6}$ &  2.184 $\cdot 10^{-3}$ \\
 1000 &  600 &  1.328 $\cdot 10^{-4}$ &  1.413 $\cdot 10^{-5}$ &  4.706 $\cdot 10^{-7}$ &  7.819 $\cdot 10^{-6}$ &  1.694 $\cdot 10^{-3}$ \\
 1000 &  700 &  6.114 $\cdot 10^{-5}$ &  6.509 $\cdot 10^{-6}$ &  2.195 $\cdot 10^{-7}$ &  1.736 $\cdot 10^{-4}$ &  9.241 $\cdot 10^{-4}$ \\
 1000 &  800 &  6.678 $\cdot 10^{-6}$ &  7.106 $\cdot 10^{-7}$ &  2.355 $\cdot 10^{-8}$ &  1.629 $\cdot 10^{-7}$ &  2.034 $\cdot 10^{-4}$ \\
\hline
 1200 &   60 &  5.087 $\cdot 10^{-4}$ &  5.418 $\cdot 10^{-5}$ &  1.834 $\cdot 10^{-6}$ & - & - \\
 1200 &   80 &  5.125 $\cdot 10^{-4}$ &  5.456 $\cdot 10^{-5}$ &  1.895 $\cdot 10^{-6}$ & - & - \\
 1200 &  100 &  5.033 $\cdot 10^{-4}$ &  5.353 $\cdot 10^{-5}$ &  1.833 $\cdot 10^{-6}$ & - & - \\
 1200 &  150 &  4.917 $\cdot 10^{-4}$ &  5.263 $\cdot 10^{-5}$ &  1.933 $\cdot 10^{-6}$ & - & - \\
 1200 &  200 &  5.434 $\cdot 10^{-4}$ &  5.783 $\cdot 10^{-5}$ &  1.902 $\cdot 10^{-6}$ & - & - \\
 1200 &  300 &  4.484 $\cdot 10^{-4}$ &  4.770 $\cdot 10^{-5}$ &  1.632 $\cdot 10^{-6}$ &  8.027 $\cdot 10^{-5}$ & - \\
 1200 &  400 &  1.108 $\cdot 10^{-4}$ &  1.178 $\cdot 10^{-5}$ &  3.999 $\cdot 10^{-7}$ &  2.211 $\cdot 10^{-5}$ &  5.664 $\cdot 10^{-4}$ \\
 1200 &  500 &  5.677 $\cdot 10^{-5}$ &  6.040 $\cdot 10^{-6}$ &  2.025 $\cdot 10^{-7}$ &  1.249 $\cdot 10^{-5}$ &  6.287 $\cdot 10^{-4}$ \\
 1200 &  600 &  4.245 $\cdot 10^{-5}$ &  4.518 $\cdot 10^{-6}$ &  1.497 $\cdot 10^{-7}$ &  1.769 $\cdot 10^{-5}$ &  6.805 $\cdot 10^{-4}$ \\
 1200 &  700 &  3.157 $\cdot 10^{-5}$ &  3.360 $\cdot 10^{-6}$ &  1.122 $\cdot 10^{-7}$ &  8.340 $\cdot 10^{-7}$ &  6.422 $\cdot 10^{-4}$ \\
 1200 &  800 &  2.214 $\cdot 10^{-5}$ &  2.356 $\cdot 10^{-6}$ &  7.851 $\cdot 10^{-8}$ &  4.322 $\cdot 10^{-6}$ &  6.238 $\cdot 10^{-4}$ \\
\hline
 1400 &   60 &  1.595 $\cdot 10^{-4}$ &  1.702 $\cdot 10^{-5}$ &  5.937 $\cdot 10^{-7}$ & - & - \\
 1400 &   80 &  1.677 $\cdot 10^{-4}$ &  1.786 $\cdot 10^{-5}$ &  6.258 $\cdot 10^{-7}$ & - & - \\
 1400 &  100 &  1.543 $\cdot 10^{-4}$ &  1.646 $\cdot 10^{-5}$ &  5.871 $\cdot 10^{-7}$ & - & - \\
 1400 &  150 &  1.562 $\cdot 10^{-4}$ &  1.662 $\cdot 10^{-5}$ &  5.650 $\cdot 10^{-7}$ & - & - \\
 1400 &  200 &  1.392 $\cdot 10^{-4}$ &  1.481 $\cdot 10^{-5}$ &  4.901 $\cdot 10^{-7}$ & - & - \\
 1400 &  300 &  1.295 $\cdot 10^{-4}$ &  1.378 $\cdot 10^{-5}$ &  4.716 $\cdot 10^{-7}$ &  3.941 $\cdot 10^{-5}$ & - \\
 1400 &  400 &  4.102 $\cdot 10^{-5}$ &  4.364 $\cdot 10^{-6}$ &  1.493 $\cdot 10^{-7}$ &  1.035 $\cdot 10^{-5}$ &  1.598 $\cdot 10^{-4}$ \\
 1400 &  500 &  2.150 $\cdot 10^{-5}$ &  2.288 $\cdot 10^{-6}$ &  7.743 $\cdot 10^{-8}$ &  5.671 $\cdot 10^{-6}$ &  1.921 $\cdot 10^{-4}$ \\
 1400 &  600 &  1.619 $\cdot 10^{-5}$ &  1.722 $\cdot 10^{-6}$ &  5.779 $\cdot 10^{-8}$ &  9.012 $\cdot 10^{-6}$ &  2.207 $\cdot 10^{-4}$ \\
 1400 &  700 &  9.399 $\cdot 10^{-6}$ &  1.000 $\cdot 10^{-6}$ &  3.386 $\cdot 10^{-8}$ &  2.049 $\cdot 10^{-5}$ &  8.678 $\cdot 10^{-5}$ \\
 1400 &  800 &  4.745 $\cdot 10^{-6}$ &  5.079 $\cdot 10^{-7}$ &  1.879 $\cdot 10^{-8}$ &  3.354 $\cdot 10^{-5}$ &  3.992 $\cdot 10^{-5}$ \\
\hline
\end{tabular}
\end{center}
\end{table}


\begin{table}[ht]
\caption*{Table 1 continued}
\begin{center}
\begin{tabular}{| c | c | c | c | c |c |c | c|}
\hline
$M_{H}$ & $M_{H_{S}}$ & $h\to bb$ & $h\to \tau\tau$ & $h\to \gamma\gamma$ &
$H_{S} \to h+h$ &$H_{S}\to tt$\\
\hline
 1600 &   60 &  4.685 $\cdot 10^{-5}$ &  4.995 $\cdot 10^{-6}$ &  1.710 $\cdot 10^{-7}$ & - & - \\
 1600 &   80 &  4.723 $\cdot 10^{-5}$ &  5.035 $\cdot 10^{-6}$ &  1.809 $\cdot 10^{-7}$ & - & - \\
 1600 &  100 &  4.387 $\cdot 10^{-5}$ &  4.673 $\cdot 10^{-6}$ &  1.756 $\cdot 10^{-7}$ & - & - \\
 1600 &  150 &  4.293 $\cdot 10^{-5}$ &  4.566 $\cdot 10^{-6}$ &  1.567 $\cdot 10^{-7}$ & - & - \\
 1600 &  200 &  4.493 $\cdot 10^{-5}$ &  4.781 $\cdot 10^{-6}$ &  1.595 $\cdot 10^{-7}$ & - & - \\
 1600 &  300 &  3.124 $\cdot 10^{-5}$ &  3.323 $\cdot 10^{-6}$ &  1.138 $\cdot 10^{-7}$ &  1.537 $\cdot 10^{-5}$ & - \\
 1600 &  400 &  1.261 $\cdot 10^{-5}$ &  1.342 $\cdot 10^{-6}$ &  4.633 $\cdot 10^{-8}$ &  3.343 $\cdot 10^{-6}$ &  3.869 $\cdot 10^{-5}$ \\
 1600 &  500 &  6.427 $\cdot 10^{-6}$ &  6.837 $\cdot 10^{-7}$ &  2.332 $\cdot 10^{-8}$ &  2.602 $\cdot 10^{-6}$ &  4.814 $\cdot 10^{-5}$ \\
 1600 &  600 &  4.705 $\cdot 10^{-6}$ &  5.005 $\cdot 10^{-7}$ &  1.690 $\cdot 10^{-8}$ &  5.436 $\cdot 10^{-6}$ &  5.417 $\cdot 10^{-5}$ \\
 1600 &  700 &  1.827 $\cdot 10^{-6}$ &  1.949 $\cdot 10^{-7}$ &  6.878 $\cdot 10^{-9}$ &  4.369 $\cdot 10^{-6}$ &  7.397 $\cdot 10^{-6}$ \\
 1600 &  800 &  1.097 $\cdot 10^{-6}$ &  1.170 $\cdot 10^{-7}$ &  4.077 $\cdot 10^{-9}$ &  1.117 $\cdot 10^{-5}$ &  3.752 $\cdot 10^{-6}$ \\
\hline
 1800 &   60 &  1.646 $\cdot 10^{-5}$ &  1.752 $\cdot 10^{-6}$ &  5.836 $\cdot 10^{-8}$ & - & - \\
 1800 &   80 &  1.681 $\cdot 10^{-5}$ &  1.788 $\cdot 10^{-6}$ &  6.117 $\cdot 10^{-8}$ & - & - \\
 1800 &  100 &  1.650 $\cdot 10^{-5}$ &  1.757 $\cdot 10^{-6}$ &  6.081 $\cdot 10^{-8}$ & - & - \\
 1800 &  150 &  1.494 $\cdot 10^{-5}$ &  1.589 $\cdot 10^{-6}$ &  5.463 $\cdot 10^{-8}$ & - & - \\
 1800 &  200 &  1.537 $\cdot 10^{-5}$ &  1.636 $\cdot 10^{-6}$ &  5.534 $\cdot 10^{-8}$ & - & - \\
 1800 &  300 &  8.187 $\cdot 10^{-6}$ &  8.708 $\cdot 10^{-7}$ &  2.982 $\cdot 10^{-8}$ &  7.933 $\cdot 10^{-6}$ & - \\
 1800 &  400 &  4.731 $\cdot 10^{-6}$ &  5.033 $\cdot 10^{-7}$ &  1.723 $\cdot 10^{-8}$ &  1.246 $\cdot 10^{-6}$ &  1.200 $\cdot 10^{-5}$ \\
 1800 &  500 &  2.567 $\cdot 10^{-6}$ &  2.730 $\cdot 10^{-7}$ &  9.341 $\cdot 10^{-9}$ &  1.156 $\cdot 10^{-7}$ &  1.666 $\cdot 10^{-5}$ \\
 1800 &  600 &  1.898 $\cdot 10^{-6}$ &  2.019 $\cdot 10^{-7}$ &  6.901 $\cdot 10^{-9}$ &  2.693 $\cdot 10^{-8}$ &  1.880 $\cdot 10^{-5}$ \\
 1800 &  700 &  4.127 $\cdot 10^{-7}$ &  4.390 $\cdot 10^{-8}$ &  1.510 $\cdot 10^{-9}$ &  5.860 $\cdot 10^{-6}$ &  5.633 $\cdot 10^{-7}$ \\
 1800 &  800 &  2.237 $\cdot 10^{-7}$ &  2.379 $\cdot 10^{-8}$ &  8.196 $\cdot 10^{-10}$ &  7.165 $\cdot 10^{-6}$ &  1.242 $\cdot 10^{-7}$ \\
\hline
 2000 &   60 &  6.318 $\cdot 10^{-6}$ &  6.722 $\cdot 10^{-7}$ &  2.232 $\cdot 10^{-8}$ & - & - \\
 2000 &   80 &  6.409 $\cdot 10^{-6}$ &  6.817 $\cdot 10^{-7}$ &  2.403 $\cdot 10^{-8}$ & - & - \\
 2000 &  100 &  6.335 $\cdot 10^{-6}$ &  6.737 $\cdot 10^{-7}$ &  2.394 $\cdot 10^{-8}$ & - & - \\
 2000 &  150 &  6.583 $\cdot 10^{-6}$ &  7.003 $\cdot 10^{-7}$ &  2.388 $\cdot 10^{-8}$ & - & - \\
 2000 &  200 &  6.366 $\cdot 10^{-6}$ &  6.774 $\cdot 10^{-7}$ &  2.314 $\cdot 10^{-8}$ & - & - \\
 2000 &  300 &  1.430 $\cdot 10^{-6}$ &  1.521 $\cdot 10^{-7}$ &  5.217 $\cdot 10^{-9}$ &  5.406 $\cdot 10^{-6}$ & - \\
 2000 &  400 &  1.927 $\cdot 10^{-6}$ &  2.050 $\cdot 10^{-7}$ &  7.025 $\cdot 10^{-9}$ &  7.781 $\cdot 10^{-7}$ &  3.990 $\cdot 10^{-6}$ \\
 2000 &  500 &  1.242 $\cdot 10^{-6}$ &  1.321 $\cdot 10^{-7}$ &  4.529 $\cdot 10^{-9}$ &  3.862 $\cdot 10^{-10}$ &  7.134 $\cdot 10^{-6}$ \\
 2000 &  600 &  1.076 $\cdot 10^{-6}$ &  1.145 $\cdot 10^{-7}$ &  3.935 $\cdot 10^{-9}$ &  2.395 $\cdot 10^{-7}$ &  9.240 $\cdot 10^{-6}$ \\
 2000 &  700 &  6.211 $\cdot 10^{-7}$ &  6.616 $\cdot 10^{-8}$ &  2.341 $\cdot 10^{-9}$ &  2.359 $\cdot 10^{-6}$ &  4.109 $\cdot 10^{-6}$ \\
 2000 &  800 &  1.730 $\cdot 10^{-7}$ &  1.841 $\cdot 10^{-8}$ &  6.394 $\cdot 10^{-10}$ &  4.016 $\cdot 10^{-6}$ &  2.455 $\cdot 10^{-7}$ \\
\hline
\end{tabular}
\end{center}

\end{table}"""

print("nmssm_data = [", end='')
for line in data.split("\n"):
  xx = line.split("&")
  if len( xx ) < 7 : continue

  m1 = xx[0]
  m2 = xx[1]

  xxx = xx[-1].split("$\cdot ")
  if len(xxx) != 2 : continue

  # print( xxx )
  xxxx = xxx[1].split("-")
  if len(xxxx) != 2 : continue

  xxxx = xxxx[1][:1]

  # print( m1, m2, float(xxx[0]), int(xxxx) - 3 )
  print( "[", m1, ",", m2, ",", float(xxx[0]) * pow(10, -int(xxxx) + 3), "]", end=',' )

print("]")
  # pb 10^-12 -> 10^-15




















