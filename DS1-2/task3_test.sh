#!/bin/bash
g++ main.cpp -o main
time cat task3_command.txt | ./main
vimdiff output204_205.txt ./task3_test.txt

