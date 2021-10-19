echo off
cls
if exist code.exe (del code.exe)
gcc code.c -o code.exe
del code.obj
if exist code.exe (
	cls 
	code.exe
	echo.
	echo.
	echo Программа выполнена успешно
	pause
) else (
	echo.
	pause
)