#!/bin/bash

echo "==================================="
echo "    Re-loading Rules Nic"
echo "==================================="

sudo /opt/netronome/p4/bin/rtecli -p 20206 config-reload -c rules.p4cfg

echo "==================================="
echo "    DONE"
echo "==================================="

