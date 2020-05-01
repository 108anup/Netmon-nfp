#!/bin/bash

set -m
set -e
# trap printout SIGINT
# printout() {
#     echo "Exiting"
#     set +m
#     set +e
#     exit 1
# }

rows=(
    1
    2
    3
    4
    5
    6
    7
    8
    9
    10
    11
    12
)

# rows=(
#     1
#     4
#     5
#     7
#     8
#     12
#     16
#     24
#     30
#     45
#     60
#     75
#     80
#     90
#     240
#     300
# )

cols=(
    1024
    # 2048
    # 3072
    # 8192
    # 10240
    # 16384
    # 20480
    # 32768
    # 51200
    # 65536
    # 131072
    # 245760
    # 262144
    # 524288
    # 1048576 # 4MB
    # 2097152
    # 4194304  # 16MB
)

# cols=(
#     2048
#     3000
#     4000
#     4096
#     6000
#     11000
#     15000
# )

# cols=(
#     2048
# )

for r in ${rows[@]}; do
    sed -i "s/#define NUM_ROWS .*/#define NUM_ROWS $r/g" cm-sketch/sandbox.c
    python update_rows.py $r

    for c in ${cols[@]}; do

        echo "Running for rows, cols: $r, $c"
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

set +m
set +e
