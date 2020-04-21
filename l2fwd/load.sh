#!/bin/bash

echo "==================================="
echo "    Loading Nic"
echo "==================================="
sudo /opt/netronome/p4/bin/rtecli -p 20206 design-load -p out/pif_design.json -c rules.p4cfg -f ./out/app.nffw

echo "==================================="
echo "    DONE"
echo "==================================="
