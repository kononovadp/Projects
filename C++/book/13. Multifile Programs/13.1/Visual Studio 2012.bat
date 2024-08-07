@ECHO OFF
cls
if exist program.exe (del program.exe)
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
cl main.cpp ../UserFunctions.cpp bignum.cpp -o program.exe
del main.obj
del UserFunctions.obj
del bignum.obj
del BignumAccessories.obj
if exist program.exe (
	cls 
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)