#!/bin/bash
g++ main.cpp -o main
./testGen.py 
cat stdin.txt | ./main > test-dump.txt 
grep 'Ans' test-dump.txt > test-stdout.txt 
grep 'Ans\|Postfix' test-dump.txt > test-stdout2.txt 

less test-dump.txt
less ans.txt test-stdout.txt 

