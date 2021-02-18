#!/bin/bash

threadcts=(1 2 4 8 12 16)

if [ -d "bench_out" ]
then
  rm -r bench_out
fi
mkdir bench_out
cd bench_out
cp ../spaceship.input .

#Strong scaling
for th in ${threadcts[@]}
do
  echo "Running $th"
  export OMP_NUM_THREADS=$th
  cp ../spaceship_template.cfg spaceship_$th.cfg
  sed -i".bak" -e "s/XXOUTFILEXX/$th/g" spaceship_$th.cfg
  (time ../../build/GameOfLife spaceship_$th.cfg) >> stdout_$th.txt 2>> time_$th.txt
done

# Show times
grep 'real' time_*.txt | sed 's/.txt.*real//g' | awk -F '_' '{print $2}'
