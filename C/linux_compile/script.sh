#!/bin/bash
gcc -Wall -o hello Hello.c
./hello
echo Program executed successfully
read -n 1
killall konsole
