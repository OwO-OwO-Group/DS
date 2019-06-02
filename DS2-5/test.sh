#!/bin/bash

mkdir test_dir
cp *.cpp *.h ./test_dir
cp test/*.cpp test/*.h ./test_dir

echo [test buffer]
g++ test_dir/Buffer.cpp test_dir/Test_Buffer.cpp
./a.out

#list=$(ls pairs*.bin | grep '[0-9]*' -o)
echo [test task1]

./build.sh

task1list=""
for i in $(ls pairs*.bin | grep '[0-9]*' -o); do
    task1list="$task1list 1 $i"
done
task1list="$task1list 0"


echo $task1list | ./a.out &> /dev/null

for i in $(ls pairs*.bin | grep '[0-9]*' -o); do
    ./testWeight.py sorted$i.bin
done

./testGenSroted.sh

echo "[check diff]"
for i in $(ls pairs*.bin | grep '[0-9]*' -o); do
    ./diff.py sorted$i.bin pairs$i.bin.sorted
done
