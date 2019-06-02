#!/bin/bash

mkdir test_dir
cp *.cpp *.h ./test_dir
cp test/*.cpp test/*.h ./test_dir

echo test buffer
g++ test_dir/Buffer.cpp test_dir/Test_Buffer.cpp
./a.out

# ls *.bin | grep '[0-9]*' -o
echo test task1

./build.sh
echo "1 501 0" | ./a.out
clear
./testWeight.py sort501.bin
