echo off
cls
if exist code.exe (del code.exe)
call "C:\Program Files\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
cl code.cpp
del code.obj
if exist code.exe (
	cls 
	code.exe
	echo.
	echo.
	echo Программа выполнена успешно
	pause
) else (
	echo.
	pause
)