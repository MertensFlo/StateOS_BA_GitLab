#!/bin/bash

STATIC_TEST=$1

if [ $STATIC_TEST ]; then
    bash ./.stdc++-test.sh
fi
