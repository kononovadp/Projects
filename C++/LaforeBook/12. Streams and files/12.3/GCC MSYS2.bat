chcp 65001
echo off
cls
if exist program.exe (del program.exe)
C:\msys64\ucrt64\bin\g++.exe code.cpp ../../accessories.cpp -o program.exe
del program.obj
if exist program.exe (
	cls 
	program.exe "D:\РЕЗЕРВНЫЕ КОПИИ\Образ ОС (19.07.2022)\win7hp-x64_full_b1_s1_v1.tib"
	echo.
	pause
) else (
	echo.
	pause
)