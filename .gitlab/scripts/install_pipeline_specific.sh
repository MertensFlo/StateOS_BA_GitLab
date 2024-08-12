#!/bin/bash

FLAG_ARM=$1
ARM_VERSION=$2

if [ $FLAG_ARM ]; then
    wget -q https://developer.arm.com/-/media/Files/downloads/gnu/$ARM_VERSION/binrel/arm-gnu-toolchain-$ARM_VERSION-x86_64-arm-none-eabi.tar.xz
    tar -xf arm-gnu-toolchain-$ARM_VERSION-x86_64-arm-none-eabi.tar.xz
    GITHUB_PATH="$( cd $(git rev-parse --show-cdup); pwd)/arm-gnu-toolchain-$ARM_VERSION-x86_64-arm-none-eabi/bin"
fi