echo off
cls
if exist LongNames.exe (del LongNames.exe)
call "C:\Program Files\PellesC\Bin\povars32.bat"
cc -Ze LongNames.c
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