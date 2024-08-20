#!/bin/bash

FLAG_ARM=$1
ARM_PATH=$2
ARM_TAR_PATH=$3
ARM_DIR_PATH=$4
ARM_CONDTION=$5

echo "script install pipeline specific"
if [ $FLAG_ARM ]; then
    wget -q $ARM_PATH
    tar -xf $ARM_TAR_PATH
    GITHUB_PATH=$ARM_DIR_PATH
fi