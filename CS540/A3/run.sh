#!/bin/bash

if [ $# -ne 0 ]
then
  echo "Usage: $0" 
  exit
fi

find -type f -executable | while read FILENAME; do
    if [ $FILENAME != $0 ]; then
        for i in $(seq 16 4 80); do
            ./$FILENAME $i $i >> "${FILENAME}.dat"
        done
    fi
done


