
for i in $(seq 0 8); do
  for j in $(seq 0 125); do
    python3 var_importance.py $i $j
  done; 
done
