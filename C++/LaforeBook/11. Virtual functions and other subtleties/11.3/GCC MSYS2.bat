echo off
cls
if exist program.exe (del program.exe)
C:\msys64\ucrt64\bin\g++.exe code.cpp ../../accessories.cpp -o program.exe
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