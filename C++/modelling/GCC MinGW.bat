echo off
cls
if exist code.exe (del code.exe)
C:\MinGW\bin\g++.exe main.cpp -o code.exe
REM del code.obj
if exist code.exe (
	REM cls 
	code.exe
	echo.
	pause
) else (
	echo.
	pause
)