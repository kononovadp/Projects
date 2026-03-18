@echo off
setlocal enabledelayedexpansion

:: === Configuration ===
set "DLL=C:\compliers\gcc_msys\ucrt64\bin\libgmp-10.dll"
set "LIB_OUT=mpir_Embarcadero_compliers.lib"
set "BCC_BIN=C:\compliers\Embarcadero_RAD_Studio\bin"

echo ==========================================
echo Direct DLL to Import Library Conversion
echo ==========================================
echo.

:: Method 1: Try mkexp if available
if exist "%BCC_BIN%\mkexp.exe" (
    echo Method 1: Using mkexp...
    "%BCC_BIN%\mkexp.exe" "%LIB_OUT%" "%DLL%"
    if !errorlevel! equ 0 (
        if exist "%LIB_OUT%" (
            echo SUCCESS: Library created with mkexp
            goto :verify
        )
    )
    echo mkexp method failed, trying next method...
    echo.
)

:: Method 2: Direct implib from DLL
if exist "%BCC_BIN%\implib.exe" (
    echo Method 2: Using implib directly on DLL...
    
    :: First, try with -a flag (add/extract mode)
    "%BCC_BIN%\implib.exe" -a "%LIB_OUT%" "%DLL%"
    if !errorlevel! equ 0 (
        if exist "%LIB_OUT%" (
            echo SUCCESS: Library created with implib -a
            goto :verify
        )
    )
    
    :: Try without flags
    echo Trying implib without flags...
    "%BCC_BIN%\implib.exe" "%LIB_OUT%" "%DLL%"
    if !errorlevel! equ 0 (
        if exist "%LIB_OUT%" (
            echo SUCCESS: Library created with implib
            goto :verify
        )
    )
    
    echo implib method failed, trying next method...
    echo.
)

:: Method 3: Use COFF2OMF if available (for 32-bit compatibility)
if exist "%BCC_BIN%\coff2omf.exe" (
    echo Method 3: Trying coff2omf conversion...
    echo Note: This is typically for 32-bit libraries
    
    :: First, we'd need a COFF .lib file
    :: This method won't work directly with DLL
    echo Skipping coff2omf - requires COFF library input
    echo.
)

:: Method 4: Manual DEF creation and implib
echo Method 4: Creating minimal DEF file...
set "DEF_FILE=%~dp0minimal_gmp.def"

(
echo LIBRARY libgmp-10.dll
echo EXPORTS
echo ; Common GMP functions - add more as needed
echo __gmpz_init
echo __gmpz_clear
echo __gmpz_set
echo __gmpz_set_ui
echo __gmpz_set_si
echo __gmpz_set_str
echo __gmpz_get_str
echo __gmpz_get_ui
echo __gmpz_get_si
echo __gmpz_add
echo __gmpz_sub
echo __gmpz_mul
echo __gmpz_div
echo __gmpz_mod
echo __gmpz_pow_ui
echo __gmpz_cmp
echo __gmpz_cmp_ui
echo __gmpz_cmp_si
echo __gmpz_sizeinbase
echo __gmpz_import
echo __gmpz_export
echo __gmp_randinit_default
echo __gmp_randseed_ui
echo __gmpz_urandomb
echo __gmpz_urandomm
echo __gmp_randclear
) > "!DEF_FILE!"

"%BCC_BIN%\implib.exe" -a -f "%LIB_OUT%" "!DEF_FILE!"
if !errorlevel! equ 0 (
    if exist "%LIB_OUT%" (
        echo SUCCESS: Library created from minimal DEF
        del "!DEF_FILE!" 2>nul
        goto :verify
    )
)
del "!DEF_FILE!" 2>nul

echo.
echo ERROR: All methods failed
echo.
echo Possible solutions:
echo 1. Use a different GMP build that includes .lib files
echo 2. Build GMP from source using BCC64
echo 3. Use Visual Studio's lib.exe to create the import library:
echo    lib /def:libgmp.def /out:mpir_gmp_import.lib /machine:x64
echo 4. Download pre-built GMP libraries for Windows
echo.
pause
exit /b 1

:verify
echo.
echo Verifying library...
if not exist "%LIB_OUT%" (
    echo ERROR: Library file not found after creation
    pause
    exit /b 1
)

echo Library details:
dir "%LIB_OUT%" | findstr /v "Directory"

:: Try to dump library contents with tdump if available
if exist "%BCC_BIN%\tdump.exe" (
    echo.
    echo Library exports ^(first 20^):
    "%BCC_BIN%\tdump.exe" -ee "%LIB_OUT%" 2>nul | findstr "^  "
)

echo.
echo SUCCESS: Import library is ready at:
echo %LIB_OUT%
echo.
echo You can now use it in your compilation with:
echo   ilink64 ... mpir_gmp_import.lib
echo.
pause
endlocal