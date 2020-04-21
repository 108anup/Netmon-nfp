#!/bin/bash

if [[ -z $1 ]] || [[ ! -d $1 ]]; then
    echo "Please specify a valid directory"
    exit 1
fi

cd $1

rm -rf *.list out *.nffw *.yml *.json Makefile-nfp4build *.mak *.bat
