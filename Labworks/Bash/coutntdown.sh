#!/bin/bash 
echo "write down the number" 
read i
while [ $i -gt 0 ]; do
echo "Numbers: $i"
i=$((i-1))
done 
