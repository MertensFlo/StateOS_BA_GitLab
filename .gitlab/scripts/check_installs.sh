#!/bin/bash

FLAG_ARM=$1

if [ $FLAG_ARM ]; then
    arm-none-eabi-gcc -v
else
    echo no installs checked
fi