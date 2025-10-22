#!/bin/bash
touch notes.txt
echo "Write down text"
while true; do 
read input 
if [ "$input" == "exit" ]; then
break 
fi 
echo " $input" >> notes.txt
done
echo " Your text:"
cat notes.txt 
rm notes.txt 

