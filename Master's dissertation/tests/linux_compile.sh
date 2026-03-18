#!/bin/bash
# Increase stack size limit
ulimit -s 65536  # 16MB stack size
echo "Stack limit set to: $(ulimit -s)KB"
# Compile the C++ program
g++ -Wall -o program main.cpp accessories.cpp bignum.cpp OptimizedBignum.cpp RandomBignum.cpp -lgmpxx -lgmp -lmpfr
# Check if compilation succeeded
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    read -n 1 -s
    exit 1
fi
echo "Compilation successful."
# Run the program
./program
# Check if program crashed
if [ $? -eq 139 ]; then
    echo "Program crashed with segmentation fault."
else
    echo "Program executed successfully."
fi

echo "Press any key to exit..."
read -n 1 -s
echo ""

