echo off
cls
if exist LongNames.exe (del LongNames.exe)
call "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vsvars32.bat"
cl LongNames.c
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