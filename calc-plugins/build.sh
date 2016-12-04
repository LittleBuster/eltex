#!/bin/bash

if [[ $@ == "" ]]; then
    echo "[ERROR] Please type: 'all' or 'clean' or 'test'"
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

    if [[ $param == "test" ]]; then
        cd plugins
        cd add
        cd test
        make
        ./test-add
        make clean

        cd ../../mul
        cd test
        make
        ./test-mul
        make clean

        cd ../../div
        cd test
        make
        ./test-div
        make clean

        cd ../../sub
        cd test
        make
        ./test-sub
        make clean
    fi
done
