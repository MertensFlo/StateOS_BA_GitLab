#!/bin/bash

FLAG_NINJA=$1

echo "make build"
echo "$PWD"
if [ $FLAG_NINJA ]; then
    cmake -S. -Bbuild -GNinja
fi
cmake --build build -v