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
	echo ��������� ��������� �������
	pause
) else (
	echo.
	pause
)