#!/bin/bash

FLAG_ARM=$1

echo $FLAG_ARM

if [ $FLAG_ARM ]; then
    arm-none-eabi-gcc -v
else
    echo no installs checked
    echo $FLAG_ARM
fi