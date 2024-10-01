@ECHO OFF
cls
if exist program.exe (del program.exe)
call "C:\Program Files\Microsoft Visual Studio\VC\Auxiliary\Build\vcvars32.bat"
cl main.cpp ../../accessories.cpp bignum.cpp -o program.exe
del main.obj
del accessories.obj
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