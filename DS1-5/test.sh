#!/bin/bash
g++ main.cpp
rm *_sort*.txt
files=( 1 201 202 203 204 205 501 502 503 300 )
for i in "${files[@]}"
do
    echo "***$i***"
    echo 1 $i |./a.out| grep 'ms'
    echo 2 $i |./a.out| grep 'ms'
    echo 3 $i |./a.out| grep 'ms'
done

./test.py *_sort*.txt
