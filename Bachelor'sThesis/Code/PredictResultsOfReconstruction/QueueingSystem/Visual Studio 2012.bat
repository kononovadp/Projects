echo off
cls
if exist code.exe (del code.exe)
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
cl /EHsc main.cpp SharedFunctions.cpp model.cpp device.cpp creator.cpp workshop.cpp robot.cpp -o code.exe
del main.obj
del SharedFunctions.obj
del model.obj
del device.obj
del creator.obj
del workshop.obj
del route.obj
del robot.obj
if exist code.exe (
	cls
	code.exe
	echo.
	pause
) else (
	echo.
	pause
)
