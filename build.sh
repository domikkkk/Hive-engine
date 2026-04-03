#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

VERSION=""
DEBUG_FLAG="-DDEBUG=0"
INFO_FLAG="-DINFO=0"
TEST_FLAG="-DTEST=0"
LEARN_FLAG="-DLEARN=0"

for arg in "$@"; do
    case "$arg" in
        DEBUG)
            DEBUG_FLAG="-DDEBUG=1"
            ;;
        INFO)
            INFO_FLAG="-DINFO=1"
            ;;
        TEST)
            TEST_FLAG="-DTEST=1"
            ;;
        LEARN)
            LEARN_FLAG="-DLEARN=1"
            ;;
        v[0-9]*.[0-9]*.[0-9]*)
            VERSION="$arg"
            ;;
    esac
done

if [ -n "$VERSION" ]; then
    echo "#pragma once" > version.h
    echo "#define VERSION \"$VERSION\"" >> version.h
    mv version.h include/
fi

cd build

cmake .. $DEBUG_FLAG $INFO_FLAG $TEST_FLAG $LEARN_FLAG
cmake --build .

mv hive_engine ..

if [ "$LEARN_FLAG" == "-DLEARN=1" ]; then
    mv nnue_network ..
fi

if [ "$TEST_FLAG" == "-DTEST=1" ]; then
    mv tests ..
fi

cd ..

if [ "$VERSION" != "" ]; then
    cp hive_engine hive_engine_$VERSION
fi
