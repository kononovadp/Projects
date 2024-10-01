@ECHO OFF
cls
if exist program.exe (del program.exe)
call "C:\Program Files\Microsoft Visual Studio\VC\Auxiliary\Build\vcvars32.bat"
cl main.cpp elev.cpp ../../msoftcon.cpp -o program.exe
del elev.obj
del main.obj
del msoftcon.obj
del accessories.obj
if exist program.exe (
	cls 
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)