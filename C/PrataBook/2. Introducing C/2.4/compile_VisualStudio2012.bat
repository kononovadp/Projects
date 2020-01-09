echo off
cls
if exist a.exe (del a.exe)
g++ code.c
if exist a.exe (a.exe) else (
	echo.
	pause
)