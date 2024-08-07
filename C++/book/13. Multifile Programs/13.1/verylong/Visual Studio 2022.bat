@ECHO OFF
cls
if exist program.exe (del program.exe)
call "C:\Program Files\Microsoft Visual Studio\VC\Auxiliary\Build\vcvars32.bat"
cl code.cpp ../../UserFunctions.cpp verylong.cpp -o program.exe
del code.obj
del UserFunctions.obj
del verylong.obj
if exist program.exe (
	cls 
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)