#!/bin/bash

FLAG_GIT=$1
FLAG_WGET=$2
FLAG_XZ_UTILS=$3
FLAG_ARM=$4
FLAG_BUILD_ESSENTIAL=$5
FLAG_NINJA=$6

echo $FLAG_GIT
echo $FLAG_WGET
echo $FLAG_XZ_UTILS
echo $FLAG_ARM
echo $FLAG_BUILD_ESSENTIAL
echo $FLAG_NINJA
echo "script install dependencies"
echo $1
echo 1
echo "$1"
echo "end of variable test"
if [ $FLAG_GIT ]; then
    apt-get update && apt-get install -y git
fi

if [ $FLAG_WGET ]; then
    apt-get install -y wget
fi

if [ $FLAG_XZ_UTILS ]; then
    apt-get install -y xz-utils 
fi

if [ $FLAG_ARM ]; then
    apt-get install -y gcc-arm-none-eabi
fi

if [ $FLAG_BUILD_ESSENTIAL ]; then
    apt-get install -y build-essential
fi

if [ $FLAG_NINJA ]; then
    apt-get -y -qq install cmake ninja-build
fi