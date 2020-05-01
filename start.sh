#!/bin/bash

echo "==================================="
echo "    Setting up kmod"
echo "==================================="

# from ~/tools/functions.bash
load_igb_uio_module

sudo modprobe -r nfp
sudo modprobe nfp nfp_dev_cpp=1 nfp_pf_netdev=0
sudo systemctl start nfp-sdk6-rte

# RTE only works when netdev PFs are off
# I don't know why netronome had this in example P4_INT
# sudo ifconfig eth8 up

echo "==================================="
echo "    DONE"
echo "==================================="
