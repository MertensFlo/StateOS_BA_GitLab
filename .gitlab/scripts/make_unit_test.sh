#!/bin/bash

UNIT_TEST=$1

if [ $UNIT_TEST ]; then
    make all -f .unit-test.make
fi