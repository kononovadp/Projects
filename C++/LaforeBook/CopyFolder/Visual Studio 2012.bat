echo off
cls
if exist program.exe (del program.exe)
windres icon.rc -O coff --target=pe-i386 -o icon.res
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
cl code.cpp -o program.exe icon.res
del code.obj
del icon.res
if exist program.exe (
	cls 
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)