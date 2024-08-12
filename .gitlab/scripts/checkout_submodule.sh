#!/bin/bash

FLAG_SUBMODULE=$1

echo $FLAG_SUBMODULE
echo "checkout submodule"
if [ $FLAG_SUBMODULE]; then
    git submodule update --init --remote --recursive
fi