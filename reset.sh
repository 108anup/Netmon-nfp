#!/bin/bash

sudo systemctl stop nfp-sdk6-rte

echo "==================================="
echo "      Loading default FW"
echo "==================================="

sudo modprobe -r nfp
sudo modprobe nfp

echo "==================================="
echo "    DONE"
echo "==================================="
