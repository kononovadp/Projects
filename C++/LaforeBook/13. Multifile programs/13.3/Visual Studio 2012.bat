@ECHO OFF
cls
if exist program.exe (del program.exe)
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
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