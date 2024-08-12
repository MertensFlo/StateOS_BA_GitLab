#!/bin/bash

FLAG_NINJA=$1

echo $FLAG_NINJA

if [ $FLAG_NINJA ]; then
    cmake -S. -Bbuild -GNinja
fi
cmake --build build -v