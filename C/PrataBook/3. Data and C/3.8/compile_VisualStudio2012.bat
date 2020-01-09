echo off
cls
if exist code.exe (del code.exe)
call "C:\Program Files\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
cl code.c
del code.obj
if exist code.exe (
	cls 
	code.exe
) else (
	echo.
	pause
)