#!/bin/bash
g++ main.cpp
files=( {101..105} 1000 )

rm maxheap.txt deap.txt

for i in "${files[@]}"
do
    echo "=== $i ===" >> maxheap.txt
    echo 1 $i |./a.out| grep "\[" >> maxheap.txt
done

for i in "${files[@]}"
do
    echo "=== $i ===" >> deap.txt
    echo 2 $i |./a.out| grep "\[" >> deap.txt
done

echo
g++ main.cpp -DDEBUG1111
echo "0" |./a.out >> debug.txt
