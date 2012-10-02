#!/bin/bash

if [ $# -ne 1 ]
then
  echo "Usage: $0 FILENAME"
  exit
fi

for i in $(seq 100 100 900); do
    ./$1 $i >> "$1.dat"
done
