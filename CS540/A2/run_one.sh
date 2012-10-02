#!/bin/bash

if [ $# -ne 1 ]
then
  echo "Usage: $0 FILENAME"
  exit
fi

for i in $(seq 144 144 2304); do
    ./$1 $i 144 >> "$1_144.dat"
done
