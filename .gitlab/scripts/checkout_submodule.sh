#!/bin/bash

FLAG_SUBMODULE=$1

if [ $FLAG_SUBMODULE]; then
    git submodule update --init --remote --recursive
fi