@ECHO OFF
cls
if exist program.exe (del program.exe)
mkdir build
pushd build
D:\Embarcadero\bin\bcc64.exe -std=c++17 -w -use ^
  -I"D:\Embarcadero\include" ^
  -I"D:\Embarcadero\include\dinkumware64" ^
  -I"D:\Embarcadero\include\windows\crtl" ^
  -I"D:\Embarcadero\include\windows\sdk" ^
  -c ../code.cpp ../accessories.cpp
D:\Embarcadero\bin\ilink64.exe -L"D:\Embarcadero\lib\win64\release" c0x64 code.o accessories.o, program.exe,, import64 cw64mt,,
move /Y program.exe ../program.exe
popd
rd /s /q build
if exist program.exe (
	cls
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)