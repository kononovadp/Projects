chcp 65001
echo off
cls
if exist program.exe (del program.exe)
C:\compliers\gcc_msys\ucrt64\bin\g++ -shared -DBUILD_DLL -o ../\EngineeringCalc2.0\bignums.dll globals.cpp main.cpp accessories.cpp bignum.cpp RandomBignum.cpp -lgmp -lgmpxx -lmpfr
echo.
pause

