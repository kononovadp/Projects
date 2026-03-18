chcp 65001
echo off
cls
if exist program.exe (del program.exe)
E:\compliers\gcc_msys\ucrt64\bin\g++.exe -O3 -march=native *.cpp -lgmp -lgmpxx -lmpfr -o program.exe
if exist program.exe (
	REM cls 
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)

