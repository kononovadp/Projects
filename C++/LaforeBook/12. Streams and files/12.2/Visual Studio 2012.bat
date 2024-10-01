@ECHO OFF
cls
if exist program.exe (del program.exe)
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
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