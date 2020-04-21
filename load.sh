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
echo "    DONE"
echo "==================================="
