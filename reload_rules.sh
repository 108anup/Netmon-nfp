#!/bin/bash

if [[ -z $1 ]] || [[ ! -d $1 ]]; then
    echo "Please specify a valid directory"
    exit 1
fi

cd $1

echo "==================================="
echo "    Re-loading Rules Nic"
echo "==================================="

sudo /opt/netronome/p4/bin/rtecli -p 20206 config-reload -c rules.p4cfg

echo "==================================="
echo "    DONE"
echo "==================================="

