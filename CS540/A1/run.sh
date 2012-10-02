#!/bin/bash

if [ $# -ne 2 ]
then
  echo "Usage: $0 MAX_SIZE INTERVAL"
  exit
fi

find -type f -executable | while read FILENAME; do
    if [ $FILENAME != $0 ]; then
        for i in $(seq 0 $2 $1); do
            ./$FILENAME $i >> "${FILENAME}.dat"
        done
    fi
done


