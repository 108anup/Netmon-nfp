#!/bin/bash

cols=(
    1024
    3072
    8192
    10240
    20480
    51200
    245760
)

for c in ${cols[@]}; do
    echo $c
    sed s/#define NUM_COLS ([0-9]*)/#define NUM_COLS $c/g sandbox.c
done
