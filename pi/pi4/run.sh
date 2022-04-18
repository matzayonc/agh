#!/bin/bash

# echo $1

if [ -z "$1" ]; then
        exit 1
fi

gcc -std=gnu11 -O2 -Wall -Wconversion -o "$1" "$1.c" -lm

echo 
echo "Running: $1"
echo

"./$1"
