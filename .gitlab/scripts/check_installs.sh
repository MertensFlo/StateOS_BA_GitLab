#!/bin/bash

FLAG_ARM=$1

echo "script check installs"
if [ $FLAG_ARM ]; then
    arm-none-eabi-gcc -v
else
    echo "no installs checked"
fi