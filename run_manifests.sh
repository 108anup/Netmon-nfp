#!/bin/bash

sudo killall l2fwd

set -m
set -e

get_manifest_file_name(){
    base_name=$(basename -- $1)
    extension=${base_name##*.}
    echo ${base_name%.$extension}
}

manifests_file=$1
num_manifests=$(python get_num_manifests.py $1)
me=54
manifests_file_name=$(get_manifest_file_name $manifests_file)

mkdir -p "runs/${manifests_file_name}"

for i in $(seq 1 $num_manifests); do
    python implement_manifest.py $1 $i

    ./build.sh cm-sketch $me
    ./load.sh cm-sketch

    sudo /users/anup/Netmon/netronome-agilio/dpdk-receiver/build/app/l2fwd \
         -c 0x5555 \
         -w 0000:05:08.0 -w 0000:05:08.1 -w 0000:05:08.2 -w 0000:05:08.3 \
         --socket-mem "256,256" --log-level=8 -- -p 0xF \
         > "runs/${manifests_file_name}/${manifests_file_name}_${i}.log" 2>&1 &
    pid=$!

    echo "Running dpdk-receiver with pid: $pid"

    sleep 40
    sudo kill $pid
    # sudo killall l2fwd
done

set +m
set +e
