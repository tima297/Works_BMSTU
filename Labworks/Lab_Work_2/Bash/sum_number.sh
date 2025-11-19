#!/bin/bash 
if [ $# -ne 2 ]; then
echo "write 2 numbers "
exit 1
fi  
num1=$1
num2=$2
sum=$((num1+num2))   
echo $sum 


