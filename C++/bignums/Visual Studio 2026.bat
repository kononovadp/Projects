@ECHO OFF
cls
if exist program.exe (del program.exe)
call "D:\Visual_Studio_2026\18\Community\VC\Auxiliary\Build\vcvars64.bat"
cl /EHsc /std:c++17 ^
   /Zi /Od /MD /fsanitize=address ^
   *.cpp ^
   /I"mpir\include" /I"mpfr\include" ^
   /link /DEBUG ^
   /LIBPATH:"mpir" mpir_Visual_Studio_2022.lib ^
   /LIBPATH:"mpfr" mpfr_Visual_Studio_2022.lib ^
   /OUT:program.exe
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