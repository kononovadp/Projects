echo off
cls
if exist code.exe (del code.exe)
call "C:\Program Files\PellesC\Bin\povars32.bat"
cc code.c
del code.obj
if exist code.exe (
	cls 
	code.exe 1.txt 2.txt code.c compile_PellesC.bat
	echo.
	echo.
	echo Программа выполнена успешно
	pause
) else (
	echo.
	pause
)