@ECHO OFF
cls
if exist program.exe (del program.exe)
windres icon.rc -O coff -o icon.res
call "C:\Program Files\Microsoft Visual Studio\VC\Auxiliary\Build\vcvars64.bat"
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