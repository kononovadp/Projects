echo off
cls
if exist code.exe (del code.exe)
C:\Windows\Microsoft.NET\Framework\v4.0.30319\csc.exe code.cs
del code.obj
if exist code.exe (
	cls 
	code.exe
	echo.
	echo.
	echo Программа выполнена успешно
	pause
) else (
	echo.
	pause
)