#!/bin/bash

set -m

rows=(
    4
)
# cols=(
#     1024
#     3072
#     8192
#     10240
#     20480
#     51200
#     245760
# )

# cols=(
#     2048
#     3000
#     4000
#     4096
#     6000
#     11000
#     15000
# )

cols=(
    2048
)
for r in ${rows[@]}; do

    sed -i "s/#define NUM_ROWS .*/#define NUM_ROWS $r/g" cm-sketch/sandbox.c
    python update_rows.py $r

    for c in ${cols[@]}; do

        echo "Running for rows, cols: $rows, $c"
        sed -i "s/#define NUM_COLS .*/#define NUM_COLS $c/g" cm-sketch/sandbox.c

        ./build.sh cm-sketch
        ./load.sh cm-sketch

        sudo /users/anup/Netmon/netronome-agilio/dpdk-receiver/build/app/l2fwd \
             -c 0x5555 \
             -w 0000:05:08.0 -w 0000:05:08.1 -w 0000:05:08.2 -w 0000:05:08.3 \
             --socket-mem "256,256" --log-level=8 -- -p 0xF \
             > "runs/${r}_${c}.log" 2>&1 &
        pid=$!

        echo "Running dpdk-receiver with pid: $pid"
        sleep 40
        sudo kill $pid

    done
done
