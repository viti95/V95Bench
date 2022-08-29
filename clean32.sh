#!/bin/sh

rm *.exe
rm *.map
rm *.err
rm *.obj
rm *.sym

wmake -f make32.mk v95_32.exe
mkdir -p build
cp v95_32.exe ./build/v95_32.exe
