echo off
cls
if exist ShortNames.exe (del ShortNames.exe)
gcc ShortNames.c -o ShortNames.exe
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