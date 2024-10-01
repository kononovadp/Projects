echo off
cls
if exist program.exe (del program.exe)
windres icon.rc -O coff -o icon.res
C:\msys64\ucrt64\bin\g++.exe code.cpp -lcomdlg32 -o program.exe icon.res
del program.obj
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