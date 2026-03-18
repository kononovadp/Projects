echo off
cls
if exist code.exe (del code.exe)
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
cl /EHsc main.cpp -o code.exe
del main.obj
if exist code.exe (
	cls
	code.exe
	echo.
	pause
) else (
	echo.
	pause
)
