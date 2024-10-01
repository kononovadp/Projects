@ECHO OFF
cls
if exist program.exe (del program.exe)
call "C:\Program Files\Microsoft Visual Studio\VC\Auxiliary\Build\vcvars32.bat"
cl code.cpp ../../accessories.cpp -o program.exe
del code.obj
del accessories.obj
if exist program.exe (
	cls 
	program.exe "Exe file to copy.exe" "New exe file.exe"
	echo.
	pause
) else (
	echo.
	pause
)