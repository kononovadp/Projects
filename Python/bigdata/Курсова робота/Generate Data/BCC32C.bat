@ECHO OFF
cls
if exist program.exe (del program.exe)
C:\BCC32\bin\bcc32x.exe code.cpp accessories.cpp -o program.exe
del program.tds
if exist program.exe (
	cls
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)