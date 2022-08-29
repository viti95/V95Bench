#!/bin/sh

wmake -f make32.mk v95_32.exe
mkdir -p build
cp v95_32.exe ./build/v95_32.exe
