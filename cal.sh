#!/bin/zsh
NUM_C=$(find . -name "*.c"|xargs wc -l|grep total|tr -s ' '|cut -d ' ' -f2)
NUM_H=$(find . -name "*.h"|xargs wc -l|grep total|tr -s ' '|cut -d ' ' -f2)

echo $((${NUM_C}+${NUM_H}))

