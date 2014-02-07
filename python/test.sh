#!/bin/bash

cat < $1 &

echo "++ver" > $1
echo "++addr" > $1
echo "++addr 12" > $1
echo "++addr" > $1

while true
do
    read CMD
    echo $CMD > $1
done
