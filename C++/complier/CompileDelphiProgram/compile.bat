echo off
cls
if exist program.exe (del program.exe)
C:\lazarus\fpc\3.2.2\bin\x86_64-win64\fpc.exe program.pas
del program.o
if exist program.exe (
	cls
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)