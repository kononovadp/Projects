echo off
cls
if exist code.exe (del code.exe)
C:\MinGW\bin\g++.exe code.cpp -o code.exe
del code.obj
if exist code.exe (
	cls 
	code.exe
	echo.
	echo.
	echo ��������� ��������� �������
	pause
) else (
	echo.
	pause
)