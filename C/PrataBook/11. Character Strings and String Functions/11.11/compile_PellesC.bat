echo off
cls
if exist code.exe (del code.exe)
call "C:\Program Files\PellesC\Bin\povars32.bat"
cc code.c
del code.obj
if exist code.exe (
	cls 
	code.exe <textfile2.txt
	echo.
	echo.
	echo Программа выполнена успешно
	pause
) else (
	echo.
	pause
)