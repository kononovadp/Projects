chcp 65001
@ECHO OFF
cls
if exist program.exe (del program.exe)
call "C:\Program Files\Microsoft Visual Studio\VC\Auxiliary\Build\vcvars32.bat"
cl code.cpp ../../accessories.cpp -o program.exe
del code.obj
del accessories.obj
if exist program.exe (
	cls 
	program.exe "D:\РЕЗЕРВНЫЕ КОПИИ\Образ ОС (19.07.2022)\win7hp-x64_full_b1_s1_v1.tib"
	echo.
	pause
) else (
	echo.
	pause
)