#!/bin/bash

if [[ $@ == "" ]]; then
    echo "[ERROR] Please type: 'all' or 'clean'"
    exit 1
fi

for param in $@
do
    if [[ $param == "all" ]]; then
    	make
    	cd plugins
    	cd add
    	make
    	cd ../mul
    	make
    	cd ../sub
    	make
    	cd ../div
    	make
    fi

    if [[ $param == "clean" ]]; then
    	make clean
    	cd plugins
    	cd add
    	make clean
    	cd ../mul
    	make clean
    	cd ../sub
    	make clean
    	cd ../div
    	make clean
    fi
done
