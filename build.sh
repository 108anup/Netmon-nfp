#!/bin/bash

if [[ -z $1 ]] || [[ ! -d $1 ]]; then
    echo "Please specify a valid directory"
    exit 1
fi

cd $1

SANDBOX=""
if [[ -e ./sandbox.c ]]; then
    SANDBOX="--sandbox-c sandbox.c"
fi

# set -x
nfp4build --output-nffw-filename ./out/app.nffw \
          --incl-p4-build ./main.p4 \
          --sku AMDA0081-0001:0 \
          --platform hydrogen \
          --reduced-thread-usage \
          --no-shared-codestore \
          --disable-component gro \
          --no-debug-info \
          --nfp4c_p4_version 1.0 \
          --nfirc_default_table_size 65536 \
          --nfirc_no_all_header_ops \
          --nfirc_implicit_header_valid \
          --nfirc_no_zero_new_headers \
          --nfirc_multicast_group_count 00 \
          --nfirc_multicast_group_size 16 \
          --nfp4c_p4_compiler hlir \
          $SANDBOX
          # --nfirc_no_mac_ingress_timestamp
# set +x
