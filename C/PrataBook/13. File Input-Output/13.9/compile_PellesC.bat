echo off
cls
if exist code.exe (del code.exe)
call "C:\Program Files\PellesC\Bin\povars32.bat"
cc code.c
del code.obj
if exist code.exe (
	cls 
	code.exe f 3.txt 4.txt 5.txt
	echo.
	echo.
	echo ��������� ��������� �������
	pause
) else (
	echo.
	pause
)