#!/bin/bash

if [[ -z $1 ]] || [[ ! -d $1 ]]; then
    echo "Please specify a valid directory"
    exit 1
fi

cd $1

echo "==================================="
echo "    Loading Nic"
echo "==================================="
sudo /opt/netronome/p4/bin/rtecli -p 20206 design-load -p out/pif_design.json -c rules.p4cfg -f ./out/app.nffw

echo "==================================="
echo "    Binding to igb_uio"
echo "==================================="
sudo $RTE_SDK/usertools/dpdk-devbind.py --bind igb_uio 0000:05:08.0
sudo $RTE_SDK/usertools/dpdk-devbind.py --bind igb_uio 0000:05:08.1
sudo $RTE_SDK/usertools/dpdk-devbind.py --bind igb_uio 0000:05:08.2
sudo $RTE_SDK/usertools/dpdk-devbind.py --bind igb_uio 0000:05:08.3

echo "==================================="
echo "    DONE"
echo "==================================="
