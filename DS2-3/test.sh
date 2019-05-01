#!/bin/bash

./build.sh

echo "1 301 1 302 2 301 2 302" | ./a.out

# check demo
for file in $(ls -1 demo/*.txt)
do
    vim -d $(basename $file) $file
done

