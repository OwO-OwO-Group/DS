#!/bin/bash
echo "[gen sorted]"
for i in $(ls pairs*.bin); do
    ./sort.py $i
done
