#!/bin/bash

set -m
set -e

manifest_name=$2
me=$1

./build.sh cm-sketch $me
./load.sh cm-sketch

sudo /users/anup/Netmon/netronome-agilio/dpdk-receiver/build/app/l2fwd \
     -c 0x5555 \
     -w 0000:05:08.0 -w 0000:05:08.1 -w 0000:05:08.2 -w 0000:05:08.3 \
     --socket-mem "256,256" --log-level=8 -- -p 0xF \
     > "runs/${manifest_name}.log" 2>&1 &
pid=$!

echo "Running dpdk-receiver with pid: $pid"

sleep 40
sudo kill $pid

set +e
set +m
