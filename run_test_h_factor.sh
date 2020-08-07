#!/usr/bin/sh

i=1

while [ ${i} -lt 10 ]
do
  j=`python -c "print $i/10.0"`
  sed -i "s/const float H_FACTOR =.*/const float H_FACTOR =${j};/" pic_puzzle4.cpp
  echo -e "${j}"
  g++ pic_puzzle4.cpp -o pic_puzzle4
  ./pic_puzzle4.exe < input3 |grep dis
  i=$((i + 1))
done