#!/bin/bash
cd "$(dirname "$0")"
ulimit -s 65536  # stack size
clang++ -o program -O3 -march=native *.cpp -lgmpxx -lgmp -lmpfr
# clang++ -Wall -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer *.cpp -lgmpxx -lgmp -lmpfr -o program
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    read -n 1 -s
    exit 1
fi
echo "Compilation successful."
clear
./program
# Check if program crashed
if [ $? -eq 139 ]; then
    printf "/nProgram crashed with segmentation fault."
fi
printf '\nPress any key to exit...'
read -n 1 -s
