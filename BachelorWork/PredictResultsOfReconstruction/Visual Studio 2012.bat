echo off
cls
if exist program.exe (del program.exe)
call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
cl /EHsc main.cpp SharedFunctions.cpp model.cpp object.cpp manager.cpp car.cpp city.cpp construction.cpp -o program.exe
if exist main.obj (
	del main.obj)
if exist SharedFunctions.obj (
	del SharedFunctions.obj)
if exist model.obj (
	del model.obj)
if exist object.obj (
	del object.obj)
if exist manager.obj (
	del manager.obj)
if exist city.obj (
	del city.obj)
if exist car.obj (
	del car.obj)
if exist construction.obj (
	del construction.obj)
if exist program.exe (
	cls
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)
