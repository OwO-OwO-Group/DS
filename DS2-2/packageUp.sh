#!/bin/bash
name="DS2ex2_10_10627116_10612150"

git pull

rm $name -r
mkdir $name

cp *.cpp $name
cp *.h $name

zip $name.zip $name/*.cpp $name/*.h
