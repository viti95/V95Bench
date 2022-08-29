#!/bin/sh

rm *.exe
rm *.map
rm *.err
rm *.obj
rm *.sym

wmake -f make16.mk v95_16.exe
mkdir -p build
cp v95_16.exe ./build/v95_16.exe
