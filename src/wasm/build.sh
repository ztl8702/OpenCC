#!/bin/bash

em++ OpenCCTest.cpp \
     ../../build/wasm/src/libopencc.a -O0 \
     -o OpenCCTest.html \
     -s WASM=1 -s ASSERTIONS=1 -s DISABLE_EXCEPTION_CATCHING=0 \
     -std=c++11 \
     -Wall --emrun \
     --preload-file ../../build/linux32/data@data