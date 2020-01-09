echo off
cls
if exist LongNames.exe (del LongNames.exe)
gcc LongNames.c -o LongNames.exe
del LongNames.obj
if exist LongNames.exe (
	cls 
	LongNames.exe
	echo.
	echo.
	echo Программа выполнена успешно
	pause
) else (
	echo.
	pause
)