#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

VERSION=""
DEBUG_FLAG="-DDEBUG=0"
INFO_FLAG="-DINFO=0"

if [ "$1" == "DEBUG" ]; then
    DEBUG_FLAG="-DDEBUG=1"
elif [ "$1" == "INFO" ]; then
    INFO_FLAG="-DINFO=1"
elif [[ "$1" =~ ^v[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
    VERSION="$1"
fi

if [ -n "$VERSION" ]; then
    echo "#pragma once" > version.h
    echo "#define VERSION \"$VERSION\"" >> version.h
    mv version.h include/
fi

cd build

cmake .. $DEBUG_FLAG $INFO_FLAG
cmake --build .

mv hive_engine ..
mv tests ..

cd ..

if [ "$VERSION" != "" ]; then
    cp hive_engine hive_engine_$VERSION
fi
