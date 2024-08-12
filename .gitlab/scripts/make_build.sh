#!/bin/bash

FLAG_NINJA=$1

echo "make build"
if [ $FLAG_NINJA ]; then
    cmake -S. -Bbuild -GNinja
fi
cmake --build build -v