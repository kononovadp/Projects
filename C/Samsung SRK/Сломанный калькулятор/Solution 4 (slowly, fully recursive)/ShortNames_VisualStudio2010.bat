echo off
cls
if exist ShortNames.exe (del ShortNames.exe)
call "C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vsvars32.bat"
cl ShortNames.c
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