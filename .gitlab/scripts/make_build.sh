#!/bin/bash

FLAG_NINJA=$1

if [ $FLAG_NINJA ]; then
    cmake -S. -Bbuild -GNinja
fi
cmake --build build -v