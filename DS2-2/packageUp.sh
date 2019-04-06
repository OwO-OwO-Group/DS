#!/bin/bash
name="DS2ex2_10_10627116_10612150"

git pull

rm $name -r
mkdir $name

cp *.cpp $name
cp *.h $name
cp ./README.txt $name
cp ./Group10.cbp $name


zip $name.zip $name/*.cpp $name/*.h $name/README.txt $name/Group10.cbp
