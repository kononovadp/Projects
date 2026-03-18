@ECHO OFF
cls
if exist program.exe (del program.exe)
call "C:\compliers\Microsoft_Visual_Studio_2022\VC\Auxiliary\Build\vcvars64.bat"
REM === Compile sources ===
C:\compliers\Microsoft_Visual_Studio_2022\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe /EHsc /O2 /std:c++17 /MT ^
  /I"mpir\include" ^
  /I"mpfr\include" ^
  main.cpp accessories.cpp bignum.cpp OptimizedBignum.cpp RandomBignum.cpp
REM === Link objects with MPIR + MPFR ===
C:\compliers\Microsoft_Visual_Studio_2022\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\link.exe ^
  /OUT:program.exe main.obj accessories.obj bignum.obj OptimizedBignum.obj RandomBignum.obj ^
  /LIBPATH:"mpir" mpir_Visual_Studio_2022.lib ^
  /LIBPATH:"mpfr" mpfr_Visual_Studio_2022.lib
REM === Cleanup ===
del main.obj
del accessories.obj
del bignum.obj
del OptimizedBignum.obj
del RandomBignum.obj
set PATH=mpir;%PATH%
set PATH=mpfr;%PATH%
REM === Run if build succeeded ===
if exist program.exe (
	cls
	program.exe
	echo.
	pause
) else (
	echo.
	pause
)


