echo off
cls
if exist program.exe (del program.exe)
g++.exe main.cpp SharedFunctions.cpp model.cpp object.cpp manager.cpp car.cpp city.cpp construction.cpp -o program.exe
if exist program.exe (
	REM cls 
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)