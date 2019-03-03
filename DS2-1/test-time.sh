#!/bin/bash
rm time.txt

function testTime()
{
    g++ main.cpp
    for i in {1..40}
    do
        (( time ./a.out <<< "1 105 2 105" ) | grep s) 2>> time.txt
    done
}

git checkout master main.cpp
testTime
mv time.txt time.txt.2

git checkout d7955a5 main.cpp
testTime
git checkout master main.cpp
