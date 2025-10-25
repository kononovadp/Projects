chcp 65001
echo off
cls
if exist program.exe (del program.exe)
C:\compliers\gcc_msys\ucrt64\bin\g++.exe main.cpp accessories.cpp bignum.cpp OptimizedBignum.cpp RandomBignum.cpp -lgmp -lgmpxx -lmpfr -o program.exe
del program.obj
if exist program.exe (
	cls 
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)