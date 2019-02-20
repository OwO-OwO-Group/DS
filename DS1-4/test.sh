#!/bin/bash
g++ main_kao.cpp

cat test.txt | ./a.out >stdout;

function cmpfiles ()
{
    { echo "$1" ; diff ./$1 <(sed 's/\r//g' ./out/$1 ) ; } |less
}

function auto ()
{
    for num in 1000 2000
    do
        cmpfiles sort$num.txt
        cmpfiles one$num.txt
        cmpfiles two$num.txt
    done
}

function manual ()
{
    echo "manual"
    while true
    do
        read -p "fileNum:" num
        echo $num

        cmpfiles sort$num.txt
        cmpfiles one$num.txt
        cmpfiles two$num.txt
    done
}

if [ $1 = "man" ]
then
    manual
else
    auto
fi
