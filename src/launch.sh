#!/bin/bash
cd project/gtest-1.7.0
sh ./configure
make
cd ../fltk
mkdir lib
make
cd ..
make
cd ..
find . -name "*.ds" -type f -delete
find . -name "*.dsproj" -type f -delete
find . -name "*.bat" -type f -delete
rm $0
