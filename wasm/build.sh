#!/bin/bash

em++ OpenCC.cpp \
     ../build/wasm/src/libopencc.a -O0 \
     -o opencc_bindings.js \
     -s WASM=1 -s ASSERTIONS=1 -s DISABLE_EXCEPTION_CATCHING=0 \
     -s ALLOW_MEMORY_GROWTH=1 \
     -std=c++11 \
     -Wall \
     -O3 \
     --preload-file ../build/linux32/data@data \
     --bind