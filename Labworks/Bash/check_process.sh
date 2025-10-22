#!/bin/bash 
if [ $# -eq 0 ]; then 
echo " Please write name of your process"
exit 1
fi
process_name=$1
if pgrep "$process_name";
then 
echo "Process start"
else
echo "Process is not start"
fi 
