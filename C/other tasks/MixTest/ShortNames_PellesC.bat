echo off
cls
if exist ShortNames.exe (del ShortNames.exe)
call "C:\Program Files\PellesC\Bin\povars32.bat"
cc -Ze ShortNames.c
del ShortNames.obj
if exist ShortNames.exe (
	cls
	ShortNames.exe
	echo.
	echo.
	echo ��������� ��������� �������
	pause
) else (
	echo.
	pause
)