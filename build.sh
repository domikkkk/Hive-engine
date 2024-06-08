#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

if [ "$1" == "DEBUG" ]; then
    DEBUG_FLAG="-DDEBUG=1"
else
    DEBUG_FLAG="-DDEBUG=0"
fi

cd build

cmake .. $DEBUG_FLAG
cmake --build .

mv hive_engine ..
mv tests ..
