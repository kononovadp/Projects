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

:: Check if DLL exists
if not exist "%DLL%" (
    echo ERROR: DLL file not found: %DLL%
    pause
    exit /b 1
)

:: Check if BCC tools directory exists
if not exist "%BCC_BIN%" (
    echo ERROR: BCC tools directory not found: %BCC_BIN%
    echo Please verify your RAD Studio installation path
    pause
    exit /b 1
)

echo DLL found: %DLL%
echo BCC tools directory: %BCC_BIN%
echo Output library: %LIB_OUT%
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
) else (
    echo mkexp.exe not found, skipping method 1
    echo.
)

:: Method 2: Direct implib from DLL
if exist "%BCC_BIN%\implib.exe" (
    echo Method 2: Using implib directly on DLL...
    
    :: First, try with -a flag
    echo Running: "%BCC_BIN%\implib.exe" -a "%LIB_OUT%" "%DLL%"
    "%BCC_BIN%\implib.exe" -a "%LIB_OUT%" "%DLL%"
    if !errorlevel! equ 0 (
        if exist "%LIB_OUT%" (
            echo SUCCESS: Library created with implib -a
            goto :verify
        )
    )
    
    :: Try without flags
    echo Trying implib without flags...
    echo Running: "%BCC_BIN%\implib.exe" "%LIB_OUT%" "%DLL%"
    "%BCC_BIN%\implib.exe" "%LIB_OUT%" "%DLL%"
    if !errorlevel! equ 0 (
        if exist "%LIB_OUT%" (
            echo SUCCESS: Library created with implib
            goto :verify
        )
    )
    
    echo implib method failed, trying next method...
    echo.
) else (
    echo implib.exe not found at "%BCC_BIN%\implib.exe"
    echo.
)

:: Method 3: Use MinGW dlltool (most reliable for this case)
echo Method 3: Using MinGW dlltool...
set "DLLTOOL_FOUND="

if exist "C:\msys64\mingw64\bin\dlltool.exe" (
    set "DLLTOOL_FOUND=C:\msys64\mingw64\bin\dlltool.exe"
) else if exist "C:\msys64\ucrt64\bin\dlltool.exe" (
    set "DLLTOOL_FOUND=C:\msys64\ucrt64\bin\dlltool.exe"
) else if exist "C:\msys64\usr\bin\dlltool.exe" (
    set "DLLTOOL_FOUND=C:\msys64\usr\bin\dlltool.exe"
)

if defined DLLTOOL_FOUND (
    echo Found dlltool at: !DLLTOOL_FOUND!
    echo Running: "!DLLTOOL_FOUND!" -D "%DLL%" -l "%LIB_OUT%"
    "!DLLTOOL_FOUND!" -D "%DLL%" -l "%LIB_OUT%"
    if !errorlevel! equ 0 (
        if exist "%LIB_OUT%" (
            echo SUCCESS: Library created with dlltool
            goto :verify
        )
    )
    echo dlltool method failed, trying DEF file method...
    echo.
) else (
    echo dlltool not found, trying DEF file method...
    echo.
)

:: Method 4: Extract exports and create DEF file
echo Method 4: Creating DEF file from exports...
set "EXPORTS_FILE=%~dp0exports.txt"
set "DEF_FILE=%~dp0complete_gmp.def"

:: Try to extract exports with objdump
set "OBJDUMP_FOUND="
if exist "C:\msys64\mingw64\bin\objdump.exe" (
    set "OBJDUMP_FOUND=C:\msys64\mingw64\bin\objdump.exe"
) else if exist "C:\msys64\ucrt64\bin\objdump.exe" (
    set "OBJDUMP_FOUND=C:\msys64\ucrt64\bin\objdump.exe"
)

if defined OBJDUMP_FOUND (
    echo Found objdump at: !OBJDUMP_FOUND!
    echo Extracting exports...
    "!OBJDUMP_FOUND!" -p "%DLL%" | findstr "DLL Name\|^\[" > "!EXPORTS_FILE!"
    
    if exist "!EXPORTS_FILE!" (
        echo Creating DEF file from extracted exports...
        > "!DEF_FILE!" (
            echo LIBRARY libgmp-10
            echo EXPORTS
        )
        
        :: Process exports
        for /f "usebackq tokens=*" %%a in ("!EXPORTS_FILE!") do (
            set "line=%%a"
            echo !line! | findstr "^\[" >nul
            if !errorlevel! equ 0 (
                for /f "tokens=2 delims=]" %%b in ("!line!") do (
                    set "func=%%b"
                    set "func=!func: =!"
                    if "!func!" neq "" if "!func!" neq "DLL" echo !func!>> "!DEF_FILE!"
                )
            )
        )
        
        del "!EXPORTS_FILE!" 2>nul
        
        :: Now try to create library with implib using DEF file
        if exist "%BCC_BIN%\implib.exe" (
            echo Creating library from DEF file using implib...
            echo Current directory: %CD%
            echo DEF file: "!DEF_FILE!"
            echo Output library: "%LIB_OUT%"
            
            :: Make sure we're in the right directory
            pushd "%~dp0"
            "%BCC_BIN%\implib.exe" -a -f "%LIB_OUT%" "complete_gmp.def"
            set "IMPLIB_ERROR=!errorlevel!"
            popd
            
            if !IMPLIB_ERROR! equ 0 (
                if exist "%LIB_OUT%" (
                    echo SUCCESS: Library created from DEF file
                    del "!DEF_FILE!" 2>nul
                    goto :verify
                )
            )
            echo implib with DEF file failed (error code: !IMPLIB_ERROR!)
        ) else (
            echo implib.exe not found for DEF file method
        )
        
        :: Try dlltool with DEF file
        if defined DLLTOOL_FOUND (
            echo Trying dlltool with DEF file...
            pushd "%~dp0"
            "!DLLTOOL_FOUND!" --input-def "complete_gmp.def" --output-lib "%LIB_OUT%"
            set "DLLTOOL_ERROR=!errorlevel!"
            popd
            
            if !DLLTOOL_ERROR! equ 0 (
                if exist "%LIB_OUT%" (
                    echo SUCCESS: Library created with dlltool and DEF file
                    del "!DEF_FILE!" 2>nul
                    goto :verify
                )
            )
            echo dlltool with DEF file failed (error code: !DLLTOOL_ERROR!)
        )
        
        del "!DEF_FILE!" 2>nul
    ) else (
        echo Failed to extract exports
    )
) else (
    echo objdump not found, cannot extract exports automatically
)

:: Method 5: Manual comprehensive DEF file
echo Method 5: Using comprehensive manual DEF file...
> "!DEF_FILE!" (
echo LIBRARY libgmp-10
echo EXPORTS
echo __gmp_0
echo __gmp_allocate_func
echo __gmp_asprintf
echo __gmp_asprintf_final
echo __gmp_asprintf_funs
echo __gmp_asprintf_memory
echo __gmp_asprintf_reps
echo __gmp_assert_fail
echo __gmp_assert_header
echo __gmp_binvert_limb_table
echo __gmp_bits_per_limb
echo __gmp_default_allocate
echo __gmp_default_fp_limb_precision
echo __gmp_default_free
echo __gmp_default_reallocate
echo __gmp_digit_value_tab
echo __gmp_divide_by_zero
echo __gmp_doprnt
echo __gmp_doprnt_integer
echo __gmp_doprnt_mpf2
echo __gmp_doscan
echo __gmp_errno
echo __gmp_exception
echo __gmp_extract_double
echo __gmp_fac2cnt_table
echo __gmp_fib_table
echo __gmp_fprintf
echo __gmp_fprintf_funs
echo __gmp_free_func
echo __gmp_fscanf
echo __gmp_fscanf_funs
echo __gmp_get_memory_functions
echo __gmp_init_primesieve
echo __gmp_invalid_operation
echo __gmp_jacobi_table
echo __gmp_junk
echo __gmp_limbroots_table
echo __gmp_mt_recalc_buffer
echo __gmp_nextprime
echo __gmp_odd2fac_table
echo __gmp_oddfac_table
echo __gmp_primesieve
echo __gmp_printf
echo __gmp_randclear
echo __gmp_randclear_mt
echo __gmp_randget_mt
echo __gmp_randinit
echo __gmp_randinit_default
echo __gmp_randinit_lc_2exp
echo __gmp_randinit_lc_2exp_size
echo __gmp_randinit_mt
echo __gmp_randinit_mt_noseed
echo __gmp_randinit_set
echo __gmp_randiset_mt
echo __gmp_rands
echo __gmp_rands_initialized
echo __gmp_randseed
echo __gmp_randseed_ui
echo __gmp_reallocate_func
echo __gmp_scanf
echo __gmp_set_memory_functions
echo __gmp_snprintf
echo __gmp_snprintf_funs
echo __gmp_sprintf
echo __gmp_sprintf_funs
echo __gmp_sqrt_of_negative
echo __gmp_sscanf
echo __gmp_sscanf_funs
echo __gmp_tmp_reentrant_alloc
echo __gmp_tmp_reentrant_free
echo __gmp_urandomb_ui
echo __gmp_urandomm_ui
echo __gmp_vasprintf
echo __gmp_version
echo __gmp_vfprintf
echo __gmp_vfscanf
echo __gmp_vprintf
echo __gmp_vscanf
echo __gmp_vsnprintf
echo __gmp_vsprintf
echo __gmp_vsscanf
echo __gmpf_abs
echo __gmpf_add
echo __gmpf_add_ui
echo __gmpf_ceil
echo __gmpf_clear
echo __gmpf_clears
echo __gmpf_cmp
echo __gmpf_cmp_d
echo __gmpf_cmp_si
echo __gmpf_cmp_ui
echo __gmpf_cmp_z
echo __gmpf_div
echo __gmpf_div_2exp
echo __gmpf_div_ui
echo __gmpf_dump
echo __gmpf_eq
echo __gmpf_fits_sint_p
echo __gmpf_fits_slong_p
echo __gmpf_fits_sshort_p
echo __gmpf_fits_uint_p
echo __gmpf_fits_ulong_p
echo __gmpf_fits_ushort_p
echo __gmpf_floor
echo __gmpf_get_d
echo __gmpf_get_d_2exp
echo __gmpf_get_default_prec
echo __gmpf_get_prec
echo __gmpf_get_si
echo __gmpf_get_str
echo __gmpf_get_ui
echo __gmpf_init
echo __gmpf_init2
echo __gmpf_init_set
echo __gmpf_init_set_d
echo __gmpf_init_set_si
echo __gmpf_init_set_str
echo __gmpf_init_set_ui
echo __gmpf_inits
echo __gmpf_inp_str
echo __gmpf_integer_p
echo __gmpf_mul
echo __gmpf_mul_2exp
echo __gmpf_mul_ui
echo __gmpf_neg
echo __gmpf_out_str
echo __gmpf_pow_ui
echo __gmpf_random2
echo __gmpf_reldiff
echo __gmpf_set
echo __gmpf_set_d
echo __gmpf_set_default_prec
echo __gmpf_set_prec
echo __gmpf_set_prec_raw
echo __gmpf_set_q
echo __gmpf_set_si
echo __gmpf_set_str
echo __gmpf_set_ui
echo __gmpf_set_z
echo __gmpf_size
echo __gmpf_sqrt
echo __gmpf_sqrt_ui
echo __gmpf_sub
echo __gmpf_sub_ui
echo __gmpf_swap
echo __gmpf_trunc
echo __gmpf_ui_div
echo __gmpf_ui_sub
echo __gmpf_urandomb
echo __gmpn_add
echo __gmpn_add_1
echo __gmpn_add_err1_n
echo __gmpn_add_err2_n
echo __gmpn_add_err3_n
echo __gmpn_add_n
echo __gmpn_add_n_atom
echo __gmpn_add_n_bd1
echo __gmpn_add_n_bt1
echo __gmpn_add_n_core2
echo __gmpn_add_n_coreihwl
echo __gmpn_add_n_coreisbr
echo __gmpn_add_n_goldmont
echo __gmpn_add_n_init
echo __gmpn_add_n_pentium4
echo __gmpn_add_n_silvermont
echo __gmpn_add_n_sub_n
echo __gmpn_add_n_x86_64
echo __gmpn_add_nc_atom
echo __gmpn_add_nc_bd1
echo __gmpn_add_nc_bt1
echo __gmpn_add_nc_core2
echo __gmpn_add_nc_coreihwl
echo __gmpn_add_nc_coreisbr
echo __gmpn_add_nc_goldmont
echo __gmpn_add_nc_pentium4
echo __gmpn_add_nc_silvermont
echo __gmpn_add_nc_x86_64
echo __gmpn_addlsh1_n
echo __gmpn_addlsh1_n_atom
echo __gmpn_addlsh1_n_bd1
echo __gmpn_addlsh1_n_core2
echo __gmpn_addlsh1_n_coreisbr
echo __gmpn_addlsh1_n_init
echo __gmpn_addlsh1_n_pentium4
echo __gmpn_addlsh1_n_silvermont
echo __gmpn_addlsh1_n_x86_64
echo __gmpn_addlsh1_n_zen
echo __gmpn_addlsh1_nc_atom
echo __gmpn_addlsh1_nc_bd1
echo __gmpn_addlsh1_nc_coreisbr
echo __gmpn_addlsh1_nc_zen
echo __gmpn_addlsh2_n
echo __gmpn_addlsh2_n_atom
echo __gmpn_addlsh2_n_core2
echo __gmpn_addlsh2_n_coreisbr
echo __gmpn_addlsh2_n_init
echo __gmpn_addlsh2_n_pentium4
echo __gmpn_addlsh2_n_silvermont
echo __gmpn_addlsh2_n_x86_64
echo __gmpn_addlsh2_nc_coreisbr
echo __gmpn_addlsh_n
echo __gmpn_addmul_1
echo __gmpn_addmul_1_atom
echo __gmpn_addmul_1_bd1
echo __gmpn_addmul_1_bt1
echo __gmpn_addmul_1_core2
echo __gmpn_addmul_1_coreibwl
echo __gmpn_addmul_1_coreihwl
echo __gmpn_addmul_1_coreinhm
echo __gmpn_addmul_1_coreisbr
echo __gmpn_addmul_1_goldmont
echo __gmpn_addmul_1_init
echo __gmpn_addmul_1_pentium4
echo __gmpn_addmul_1_silvermont
echo __gmpn_addmul_1_x86_64
echo __gmpn_addmul_1_zen
echo __gmpn_addmul_1c_core2
echo __gmpn_addmul_1c_silvermont
echo __gmpn_addmul_2
echo __gmpn_addmul_2_atom
echo __gmpn_addmul_2_bd1
echo __gmpn_addmul_2_coreihwl
echo __gmpn_addmul_2_coreisbr
echo __gmpn_addmul_2_fat
echo __gmpn_addmul_2_init
echo __gmpn_addmul_2_k8
echo __gmpn_addmul_2_pentium4
echo __gmpn_and_n
echo __gmpn_andn_n
echo __gmpn_bases
echo __gmpn_bc_mulmod_bnm1
echo __gmpn_bc_set_str
echo __gmpn_bdiv_dbm1c
echo __gmpn_bdiv_dbm1c_init
echo __gmpn_bdiv_dbm1c_x86_64
echo __gmpn_bdiv_q
echo __gmpn_bdiv_q_1
echo __gmpn_bdiv_q_itch
echo __gmpn_bdiv_qr
echo __gmpn_bdiv_qr_itch
echo __gmpn_binvert
echo __gmpn_binvert_itch
echo __gmpn_broot
echo __gmpn_broot_invm1
echo __gmpn_brootinv
echo __gmpn_bsqrt
echo __gmpn_bsqrtinv
echo __gmpn_cmp
echo __gmpn_cnd_add_n
echo __gmpn_cnd_add_n_atom
echo __gmpn_cnd_add_n_coreisbr
echo __gmpn_cnd_add_n_init
echo __gmpn_cnd_add_n_x86_64
echo __gmpn_cnd_sub_n
echo __gmpn_cnd_sub_n_atom
echo __gmpn_cnd_sub_n_coreisbr
echo __gmpn_cnd_sub_n_init
echo __gmpn_cnd_sub_n_x86_64
echo __gmpn_cnd_swap
echo __gmpn_com
echo __gmpn_com_atom
echo __gmpn_com_bd1
echo __gmpn_com_bt2
echo __gmpn_com_core2
echo __gmpn_com_init
echo __gmpn_com_x86_64
echo __gmpn_com_zen
echo __gmpn_compute_powtab
echo __gmpn_copyd
echo __gmpn_copyd_atom
echo __gmpn_copyd_bd1
echo __gmpn_copyd_bt1
echo __gmpn_copyd_bt2
echo __gmpn_copyd_core2
echo __gmpn_copyd_init
echo __gmpn_copyd_nano
echo __gmpn_copyd_x86_64
echo __gmpn_copyd_zen
echo __gmpn_copyi
echo __gmpn_copyi_atom
echo __gmpn_copyi_bd1
echo __gmpn_copyi_bt1
echo __gmpn_copyi_bt2
echo __gmpn_copyi_core2
echo __gmpn_copyi_init
echo __gmpn_copyi_nano
echo __gmpn_copyi_x86_64
echo __gmpn_copyi_zen
echo __gmpn_cpuid
echo __gmpn_cpuvec
echo __gmpn_cpuvec_init
echo __gmpn_cpuvec_initialized
echo __gmpn_dc_set_str
echo __gmpn_dcpi1_bdiv_q
echo __gmpn_dcpi1_bdiv_qr
echo __gmpn_dcpi1_bdiv_qr_n
echo __gmpn_dcpi1_bdiv_qr_n_itch
echo __gmpn_dcpi1_div_q
echo __gmpn_dcpi1_div_qr
echo __gmpn_dcpi1_div_qr_n
echo __gmpn_dcpi1_divappr_q
echo __gmpn_div_q
echo __gmpn_div_qr_1
echo __gmpn_div_qr_1n_pi1
echo __gmpn_div_qr_2
echo __gmpn_div_qr_2n_pi1
echo __gmpn_div_qr_2u_pi1
echo __gmpn_divexact
echo __gmpn_divexact_1
echo __gmpn_divexact_1_atom
echo __gmpn_divexact_1_init
echo __gmpn_divexact_1_nano
echo __gmpn_divexact_1_x86_64
echo __gmpn_divexact_by3
echo __gmpn_divexact_by3c
echo __gmpn_divisible_p
echo __gmpn_divmod_1
echo __gmpn_divrem
echo __gmpn_divrem_1
echo __gmpn_divrem_1_core2
echo __gmpn_divrem_1_coreisbr
echo __gmpn_divrem_1_init
echo __gmpn_divrem_1_x86_64
echo __gmpn_divrem_2
echo __gmpn_dump
echo __gmpn_fft_best_k
echo __gmpn_fft_next_size
echo __gmpn_fib2_ui
echo __gmpn_fib2m
echo __gmpn_gcd
echo __gmpn_gcd_1
echo __gmpn_gcd_11
echo __gmpn_gcd_11_bd1
echo __gmpn_gcd_11_bt1
echo __gmpn_gcd_11_bt2
echo __gmpn_gcd_11_core2
echo __gmpn_gcd_11_coreisbr
echo __gmpn_gcd_11_init
echo __gmpn_gcd_11_k10
echo __gmpn_gcd_11_nano
echo __gmpn_gcd_11_x86_64
echo __gmpn_gcd_11_zen
echo __gmpn_gcd_22
echo __gmpn_gcd_subdiv_step
echo __gmpn_gcdext
echo __gmpn_gcdext_1
echo __gmpn_gcdext_hook
echo __gmpn_gcdext_lehmer_n
echo __gmpn_get_d
echo __gmpn_get_str
echo __gmpn_hamdist
echo __gmpn_hgcd
echo __gmpn_hgcd2
echo __gmpn_hgcd2_jacobi
echo __gmpn_hgcd_appr
echo __gmpn_hgcd_appr_itch
echo __gmpn_hgcd_itch
echo __gmpn_hgcd_jacobi
echo __gmpn_hgcd_matrix_adjust
echo __gmpn_hgcd_matrix_init
echo __gmpn_hgcd_matrix_mul
echo __gmpn_hgcd_matrix_mul_1
echo __gmpn_hgcd_matrix_update_q
echo __gmpn_hgcd_mul_matrix1_vector
echo __gmpn_hgcd_reduce
echo __gmpn_hgcd_reduce_itch
echo __gmpn_hgcd_step
echo __gmpn_invert
echo __gmpn_invert_limb
echo __gmpn_invert_limb_table
echo __gmpn_invertappr
echo __gmpn_ior_n
echo __gmpn_iorn_n
echo __gmpn_jacobi_2
echo __gmpn_jacobi_base
echo __gmpn_jacobi_n
echo __gmpn_lshift
echo __gmpn_lshift_atom
echo __gmpn_lshift_core2
echo __gmpn_lshift_coreisbr
echo __gmpn_lshift_init
echo __gmpn_lshift_k10
echo __gmpn_lshift_pentium4
echo __gmpn_lshift_silvermont
echo __gmpn_lshift_x86_64
echo __gmpn_lshift_zen
echo __gmpn_lshiftc
echo __gmpn_lshiftc_atom
echo __gmpn_lshiftc_core2
echo __gmpn_lshiftc_coreisbr
echo __gmpn_lshiftc_init
echo __gmpn_lshiftc_k10
echo __gmpn_lshiftc_pentium4
echo __gmpn_lshiftc_silvermont
echo __gmpn_lshiftc_x86_64
echo __gmpn_lshiftc_zen
echo __gmpn_matrix22_mul
echo __gmpn_matrix22_mul1_inverse_vector
echo __gmpn_matrix22_mul_itch
echo __gmpn_mod_1
echo __gmpn_mod_1_1p
echo __gmpn_mod_1_1p_cps
echo __gmpn_mod_1_1p_cps_init
echo __gmpn_mod_1_1p_cps_x86_64
echo __gmpn_mod_1_1p_init
echo __gmpn_mod_1_1p_x86_64
echo __gmpn_mod_1_fat
echo __gmpn_mod_1_init
echo __gmpn_mod_1s_2p
echo __gmpn_mod_1s_2p_cps
echo __gmpn_mod_1s_2p_cps_init
echo __gmpn_mod_1s_2p_cps_x86_64
echo __gmpn_mod_1s_2p_init
echo __gmpn_mod_1s_2p_x86_64
echo __gmpn_mod_1s_3p
echo __gmpn_mod_1s_3p_cps
echo __gmpn_mod_1s_4p
echo __gmpn_mod_1s_4p_cps
echo __gmpn_mod_1s_4p_cps_init
echo __gmpn_mod_1s_4p_cps_x86_64
echo __gmpn_mod_1s_4p_init
echo __gmpn_mod_1s_4p_x86_64
echo __gmpn_mod_34lsub1
echo __gmpn_mod_34lsub1_init
echo __gmpn_mod_34lsub1_pentium4
echo __gmpn_mod_34lsub1_x86_64
echo __gmpn_modexact_1_odd_x86_64
echo __gmpn_modexact_1c_odd
echo __gmpn_modexact_1c_odd_init
echo __gmpn_modexact_1c_odd_x86_64
echo __gmpn_mu_bdiv_q
echo __gmpn_mu_bdiv_q_itch
echo __gmpn_mu_bdiv_qr
echo __gmpn_mu_bdiv_qr_itch
echo __gmpn_mu_div_q
echo __gmpn_mu_div_q_itch
echo __gmpn_mu_div_qr
echo __gmpn_mu_div_qr_itch
echo __gmpn_mu_divappr_q
echo __gmpn_mu_divappr_q_itch
echo __gmpn_mul
echo __gmpn_mul_1
echo __gmpn_mul_1_atom
echo __gmpn_mul_1_bd1
echo __gmpn_mul_1_bt1
echo __gmpn_mul_1_coreihwl
echo __gmpn_mul_1_coreisbr
echo __gmpn_mul_1_goldmont
echo __gmpn_mul_1_init
echo __gmpn_mul_1_pentium4
echo __gmpn_mul_1_silvermont
echo __gmpn_mul_1_x86_64
echo __gmpn_mul_1_zen
echo __gmpn_mul_1c_atom
echo __gmpn_mul_1c_bd1
echo __gmpn_mul_1c_bt1
echo __gmpn_mul_1c_coreisbr
echo __gmpn_mul_1c_goldmont
echo __gmpn_mul_1c_pentium4
echo __gmpn_mul_1c_silvermont
echo __gmpn_mul_1c_x86_64
echo __gmpn_mul_1c_zen
echo __gmpn_mul_2
echo __gmpn_mul_basecase
echo __gmpn_mul_basecase_bd1
echo __gmpn_mul_basecase_bt1
echo __gmpn_mul_basecase_core2
echo __gmpn_mul_basecase_coreibwl
echo __gmpn_mul_basecase_coreihwl
echo __gmpn_mul_basecase_coreisbr
echo __gmpn_mul_basecase_fat
echo __gmpn_mul_basecase_init
echo __gmpn_mul_basecase_k8
echo __gmpn_mul_basecase_pentium4
echo __gmpn_mul_basecase_silvermont
echo __gmpn_mul_basecase_zen
echo __gmpn_mul_fft
echo __gmpn_mul_n
echo __gmpn_mullo_basecase
echo __gmpn_mullo_basecase_core2
echo __gmpn_mullo_basecase_coreibwl
echo __gmpn_mullo_basecase_coreihwl
echo __gmpn_mullo_basecase_coreisbr
echo __gmpn_mullo_basecase_fat
echo __gmpn_mullo_basecase_init
echo __gmpn_mullo_basecase_k8
echo __gmpn_mullo_basecase_pentium4
echo __gmpn_mullo_basecase_silvermont
echo __gmpn_mullo_basecase_zen
echo __gmpn_mullo_n
echo __gmpn_mulmid
echo __gmpn_mulmid_basecase
echo __gmpn_mulmid_n
echo __gmpn_mulmod_bnm1
echo __gmpn_mulmod_bnm1_next_size
echo __gmpn_nand_n
echo __gmpn_neg
echo __gmpn_ni_invertappr
echo __gmpn_nior_n
echo __gmpn_nussbaumer_mul
echo __gmpn_perfect_power_p
echo __gmpn_perfect_square_p
echo __gmpn_pi1_bdiv_q_1
echo __gmpn_popcount
echo __gmpn_pow_1
echo __gmpn_powlo
echo __gmpn_powm
echo __gmpn_preinv_divrem_1
echo __gmpn_preinv_divrem_1_core2
echo __gmpn_preinv_divrem_1_coreisbr
echo __gmpn_preinv_divrem_1_init
echo __gmpn_preinv_divrem_1_x86_64
echo __gmpn_preinv_mod_1
echo __gmpn_preinv_mod_1_init
echo __gmpn_preinv_mu_div_qr
echo __gmpn_preinv_mu_div_qr_itch
echo __gmpn_random
echo __gmpn_random2
echo __gmpn_redc_1
echo __gmpn_redc_1_atom
echo __gmpn_redc_1_bt1
echo __gmpn_redc_1_core2
echo __gmpn_redc_1_coreihwl
echo __gmpn_redc_1_coreinhm
echo __gmpn_redc_1_coreisbr
echo __gmpn_redc_1_fat
echo __gmpn_redc_1_goldmont
echo __gmpn_redc_1_init
echo __gmpn_redc_1_k8
echo __gmpn_redc_1_pentium4
echo __gmpn_redc_2
echo __gmpn_redc_2_fat
echo __gmpn_redc_2_init
echo __gmpn_redc_n
echo __gmpn_remove
echo __gmpn_rootrem
echo __gmpn_rsblsh1_n
echo __gmpn_rsblsh2_n
echo __gmpn_rsblsh_n
echo __gmpn_rsh1add_n
echo __gmpn_rsh1add_nc
echo __gmpn_rsh1sub_n
echo __gmpn_rsh1sub_nc
echo __gmpn_rshift
echo __gmpn_rshift_atom
echo __gmpn_rshift_core2
echo __gmpn_rshift_coreisbr
echo __gmpn_rshift_init
echo __gmpn_rshift_k10
echo __gmpn_rshift_pentium4
echo __gmpn_rshift_silvermont
echo __gmpn_rshift_x86_64
echo __gmpn_rshift_zen
echo __gmpn_sbpi1_bdiv_q
echo __gmpn_sbpi1_bdiv_qr
echo __gmpn_sbpi1_bdiv_r
echo __gmpn_sbpi1_div_q
echo __gmpn_sbpi1_div_qr
echo __gmpn_sbpi1_divappr_q
echo __gmpn_scan0
echo __gmpn_scan1
echo __gmpn_sec_add_1
echo __gmpn_sec_add_1_itch
echo __gmpn_sec_div_qr
echo __gmpn_sec_div_qr_itch
echo __gmpn_sec_div_r
echo __gmpn_sec_div_r_itch
echo __gmpn_sec_invert
echo __gmpn_sec_invert_itch
echo __gmpn_sec_mul
echo __gmpn_sec_mul_itch
echo __gmpn_sec_pi1_div_qr
echo __gmpn_sec_pi1_div_r
echo __gmpn_sec_powm
echo __gmpn_sec_powm_itch
echo __gmpn_sec_sqr
echo __gmpn_sec_sqr_itch
echo __gmpn_sec_sub_1
echo __gmpn_sec_sub_1_itch
echo __gmpn_sec_tabselect
echo __gmpn_set_str
echo __gmpn_sizeinbase
echo __gmpn_sqr
echo __gmpn_sqr_basecase
echo __gmpn_sqr_basecase_bt1
echo __gmpn_sqr_basecase_core2
echo __gmpn_sqr_basecase_coreibwl
echo __gmpn_sqr_basecase_coreihwl
echo __gmpn_sqr_basecase_coreisbr
echo __gmpn_sqr_basecase_fat
echo __gmpn_sqr_basecase_init
echo __gmpn_sqr_basecase_k8
echo __gmpn_sqr_basecase_pentium4
echo __gmpn_sqr_basecase_silvermont
echo __gmpn_sqr_basecase_zen
echo __gmpn_sqr_diag_addlsh1
echo __gmpn_sqrlo
echo __gmpn_sqrlo_basecase
echo __gmpn_sqrmod_bnm1
echo __gmpn_sqrmod_bnm1_next_size
echo __gmpn_sqrtrem
echo __gmpn_strongfibo
echo __gmpn_sub
echo __gmpn_sub_1
echo __gmpn_sub_err1_n
echo __gmpn_sub_err2_n
echo __gmpn_sub_err3_n
echo __gmpn_sub_n
echo __gmpn_sub_n_atom
echo __gmpn_sub_n_bd1
echo __gmpn_sub_n_bt1
echo __gmpn_sub_n_core2
echo __gmpn_sub_n_coreihwl
echo __gmpn_sub_n_coreisbr
echo __gmpn_sub_n_goldmont
echo __gmpn_sub_n_init
echo __gmpn_sub_n_pentium4
echo __gmpn_sub_n_silvermont
echo __gmpn_sub_n_x86_64
echo __gmpn_sub_nc_atom
echo __gmpn_sub_nc_bd1
echo __gmpn_sub_nc_bt1
echo __gmpn_sub_nc_core2
echo __gmpn_sub_nc_coreihwl
echo __gmpn_sub_nc_coreisbr
echo __gmpn_sub_nc_goldmont
echo __gmpn_sub_nc_pentium4
echo __gmpn_sub_nc_silvermont
echo __gmpn_sub_nc_x86_64
echo __gmpn_sublsh1_n
echo __gmpn_sublsh1_n_atom
echo __gmpn_sublsh1_n_bd1
echo __gmpn_sublsh1_n_core2
echo __gmpn_sublsh1_n_init
echo __gmpn_sublsh1_n_pentium4
echo __gmpn_sublsh1_n_x86_64
echo __gmpn_sublsh1_n_zen
echo __gmpn_sublsh1_nc_atom
echo __gmpn_sublsh1_nc_bd1
echo __gmpn_sublsh1_nc_zen
echo __gmpn_submul_1
echo __gmpn_submul_1_atom
echo __gmpn_submul_1_bd1
echo __gmpn_submul_1_bt1
echo __gmpn_submul_1_core2
echo __gmpn_submul_1_coreihwl
echo __gmpn_submul_1_coreinhm
echo __gmpn_submul_1_coreisbr
echo __gmpn_submul_1_goldmont
echo __gmpn_submul_1_init
echo __gmpn_submul_1_pentium4
echo __gmpn_submul_1_silvermont
echo __gmpn_submul_1_x86_64
echo __gmpn_submul_1_zen
echo __gmpn_submul_1c_core2
echo __gmpn_submul_1c_silvermont
echo __gmpn_tdiv_qr
echo __gmpn_toom22_mul
echo __gmpn_toom2_sqr
echo __gmpn_toom32_mul
echo __gmpn_toom33_mul
echo __gmpn_toom3_sqr
echo __gmpn_toom42_mul
echo __gmpn_toom42_mulmid
echo __gmpn_toom43_mul
echo __gmpn_toom44_mul
echo __gmpn_toom4_sqr
echo __gmpn_toom52_mul
echo __gmpn_toom53_mul
echo __gmpn_toom54_mul
echo __gmpn_toom62_mul
echo __gmpn_toom63_mul
echo __gmpn_toom6_sqr
echo __gmpn_toom6h_mul
echo __gmpn_toom8_sqr
echo __gmpn_toom8h_mul
echo __gmpn_toom_couple_handling
echo __gmpn_toom_eval_dgr3_pm1
echo __gmpn_toom_eval_dgr3_pm2
echo __gmpn_toom_eval_pm1
echo __gmpn_toom_eval_pm2
echo __gmpn_toom_eval_pm2exp
echo __gmpn_toom_eval_pm2rexp
echo __gmpn_toom_interpolate_12pts
echo __gmpn_toom_interpolate_16pts
echo __gmpn_toom_interpolate_5pts
echo __gmpn_toom_interpolate_6pts
echo __gmpn_toom_interpolate_7pts
echo __gmpn_toom_interpolate_8pts
echo __gmpn_trialdiv
echo __gmpn_xnor_n
echo __gmpn_xor_n
echo __gmpn_zero
echo __gmpn_zero_p
echo __gmpq_abs
echo __gmpq_add
echo __gmpq_canonicalize
echo __gmpq_clear
echo __gmpq_clears
echo __gmpq_cmp
echo __gmpq_cmp_si
echo __gmpq_cmp_ui
echo __gmpq_cmp_z
echo __gmpq_div
echo __gmpq_div_2exp
echo __gmpq_equal
echo __gmpq_get_d
echo __gmpq_get_den
echo __gmpq_get_num
echo __gmpq_get_str
echo __gmpq_init
echo __gmpq_inits
echo __gmpq_inp_str
echo __gmpq_inv
echo __gmpq_mul
echo __gmpq_mul_2exp
echo __gmpq_neg
echo __gmpq_out_str
echo __gmpq_set
echo __gmpq_set_d
echo __gmpq_set_den
echo __gmpq_set_f
echo __gmpq_set_num
echo __gmpq_set_si
echo __gmpq_set_str
echo __gmpq_set_ui
echo __gmpq_set_z
echo __gmpq_sub
echo __gmpq_swap
echo __gmpz_2fac_ui
echo __gmpz_abs
echo __gmpz_add
echo __gmpz_add_ui
echo __gmpz_addmul
echo __gmpz_addmul_ui
echo __gmpz_and
echo __gmpz_aorsmul_1
echo __gmpz_array_init
echo __gmpz_bin_ui
echo __gmpz_bin_uiui
echo __gmpz_cdiv_q
echo __gmpz_cdiv_q_2exp
echo __gmpz_cdiv_q_ui
echo __gmpz_cdiv_qr
echo __gmpz_cdiv_qr_ui
echo __gmpz_cdiv_r
echo __gmpz_cdiv_r_2exp
echo __gmpz_cdiv_r_ui
echo __gmpz_cdiv_ui
echo __gmpz_clear
echo __gmpz_clears
echo __gmpz_clrbit
echo __gmpz_cmp
echo __gmpz_cmp_d
echo __gmpz_cmp_si
echo __gmpz_cmp_ui
echo __gmpz_cmpabs
echo __gmpz_cmpabs_d
echo __gmpz_cmpabs_ui
echo __gmpz_com
echo __gmpz_combit
echo __gmpz_congruent_2exp_p
echo __gmpz_congruent_p
echo __gmpz_congruent_ui_p
echo __gmpz_divexact
echo __gmpz_divexact_gcd
echo __gmpz_divexact_ui
echo __gmpz_divisible_2exp_p
echo __gmpz_divisible_p
echo __gmpz_divisible_ui_p
echo __gmpz_dump
echo __gmpz_export
echo __gmpz_fac_ui
echo __gmpz_fdiv_q
echo __gmpz_fdiv_q_2exp
echo __gmpz_fdiv_q_ui
echo __gmpz_fdiv_qr
echo __gmpz_fdiv_qr_ui
echo __gmpz_fdiv_r
echo __gmpz_fdiv_r_2exp
echo __gmpz_fdiv_r_ui
echo __gmpz_fdiv_ui
echo __gmpz_fib2_ui
echo __gmpz_fib_ui
echo __gmpz_fits_sint_p
echo __gmpz_fits_slong_p
echo __gmpz_fits_sshort_p
echo __gmpz_fits_uint_p
echo __gmpz_fits_ulong_p
echo __gmpz_fits_ushort_p
echo __gmpz_gcd
echo __gmpz_gcd_ui
echo __gmpz_gcdext
echo __gmpz_get_d
echo __gmpz_get_d_2exp
echo __gmpz_get_si
echo __gmpz_get_str
echo __gmpz_get_ui
echo __gmpz_getlimbn
echo __gmpz_hamdist
echo __gmpz_import
echo __gmpz_init
echo __gmpz_init2
echo __gmpz_init_set
echo __gmpz_init_set_d
echo __gmpz_init_set_si
echo __gmpz_init_set_str
echo __gmpz_init_set_ui
echo __gmpz_inits
echo __gmpz_inp_raw
echo __gmpz_inp_str
echo __gmpz_inp_str_nowhite
echo __gmpz_invert
echo __gmpz_ior
echo __gmpz_jacobi
echo __gmpz_kronecker_si
echo __gmpz_kronecker_ui
echo __gmpz_lcm
echo __gmpz_lcm_ui
echo __gmpz_legendre
echo __gmpz_limbs_finish
echo __gmpz_limbs_modify
echo __gmpz_limbs_read
echo __gmpz_limbs_write
echo __gmpz_lucas_mod
echo __gmpz_lucnum2_ui
echo __gmpz_lucnum_ui
echo __gmpz_mfac_uiui
echo __gmpz_millerrabin
echo __gmpz_mod
echo __gmpz_mul
echo __gmpz_mul_2exp
echo __gmpz_mul_si
echo __gmpz_mul_ui
echo __gmpz_n_pow_ui
echo __gmpz_neg
echo __gmpz_nextprime
echo __gmpz_oddfac_1
echo __gmpz_out_raw
echo __gmpz_out_str
echo __gmpz_perfect_power_p
echo __gmpz_perfect_square_p
echo __gmpz_popcount
echo __gmpz_pow_ui
echo __gmpz_powm
echo __gmpz_powm_sec
echo __gmpz_powm_ui
echo __gmpz_primorial_ui
echo __gmpz_probab_prime_p
echo __gmpz_prodlimbs
echo __gmpz_random
echo __gmpz_random2
echo __gmpz_realloc
echo __gmpz_realloc2
echo __gmpz_remove
echo __gmpz_roinit_n
echo __gmpz_root
echo __gmpz_rootrem
echo __gmpz_rrandomb
echo __gmpz_scan0
echo __gmpz_scan1
echo __gmpz_set
echo __gmpz_set_d
echo __gmpz_set_f
echo __gmpz_set_q
echo __gmpz_set_si
echo __gmpz_set_str
echo __gmpz_set_ui
echo __gmpz_setbit
echo __gmpz_si_kronecker
echo __gmpz_size
echo __gmpz_sizeinbase
echo __gmpz_sqrt
echo __gmpz_sqrtrem
echo __gmpz_stronglucas
echo __gmpz_sub
echo __gmpz_sub_ui
echo __gmpz_submul
echo __gmpz_submul_ui
echo __gmpz_swap
echo __gmpz_tdiv_q
echo __gmpz_tdiv_q_2exp
echo __gmpz_tdiv_q_ui
echo __gmpz_tdiv_qr
echo __gmpz_tdiv_qr_ui
echo __gmpz_tdiv_r
echo __gmpz_tdiv_r_2exp
echo __gmpz_tdiv_r_ui
echo __gmpz_tdiv_ui
echo __gmpz_tstbit
echo __gmpz_ui_kronecker
echo __gmpz_ui_pow_ui
echo __gmpz_ui_sub
echo __gmpz_urandomb
echo __gmpz_urandomm
echo __gmpz_xor
)

echo Created comprehensive manual DEF file
echo DEF file location: !DEF_FILE!

:: Try with implib
if exist "%BCC_BIN%\implib.exe" (
    echo Trying implib with manual DEF file...
    pushd "%~dp0"
    "%BCC_BIN%\implib.exe" -a -f "%LIB_OUT%" "complete_gmp.def"
    set "IMPLIB_ERROR=!errorlevel!"
    popd
    
    if !IMPLIB_ERROR! equ 0 (
        if exist "%LIB_OUT%" (
            echo SUCCESS: Library created with manual DEF file
            del "!DEF_FILE!" 2>nul
            goto :verify
        )
    )
    echo Manual DEF + implib failed (error: !IMPLIB_ERROR!)
)

:: Try with dlltool
if defined DLLTOOL_FOUND (
    echo Trying dlltool with manual DEF file...
    pushd "%~dp0"
    "!DLLTOOL_FOUND!" --input-def "complete_gmp.def" --output-lib "%LIB_OUT%"
    set "DLLTOOL_ERROR=!errorlevel!"
    popd
    
    if !DLLTOOL_ERROR! equ 0 (
        if exist "%LIB_OUT%" (
            echo SUCCESS: Library created with dlltool and manual DEF
            del "!DEF_FILE!" 2>nul
            goto :verify
        )
    )
    echo Manual DEF + dlltool failed (error: !DLLTOOL_ERROR!)
)

del "!DEF_FILE!" 2>nul

echo.
echo ========================================
echo ERROR: All methods failed
echo ========================================
echo.
echo Diagnostic information:
echo - DLL exists: %DLL%
echo - BCC tools directory: %BCC_BIN%
if exist "%BCC_BIN%\implib.exe" (echo - implib.exe: FOUND) else (echo - implib.exe: NOT FOUND)
if defined DLLTOOL_FOUND (echo - dlltool: FOUND at !DLLTOOL_FOUND!) else (echo - dlltool: NOT FOUND)
if defined OBJDUMP_FOUND (echo - objdump: FOUND at !OBJDUMP_FOUND!) else (echo - objdump: NOT FOUND)
echo.
echo Alternative solutions:
echo 1. Use MinGW directly: dlltool -D libgmp-10.dll -l mpir_Embarcadero_compliers.lib
echo 2. Use Visual Studio: lib /def:gmp.def /out:mpir_Embarcadero_compliers.lib
echo 3. Download pre-built GMP libraries for Windows
echo 4. Build GMP from source with your compiler
echo.
pause
exit /b 1

:verify
echo.
echo ========================================
echo SUCCESS: Library verification
echo ========================================
if not exist "%LIB_OUT%" (
    echo ERROR: Library file not found after creation
    pause
    exit /b 1
)

echo Library created successfully: %LIB_OUT%
for %%F in ("%LIB_OUT%") do echo File size: %%~zF bytes

if exist "%BCC_BIN%\tdump.exe" (
    echo.
    echo Library contents sample:
    "%BCC_BIN%\tdump.exe" -ee "%LIB_OUT%" 2>nul | findstr "^  " | more +1
) else (
    echo Note: tdump.exe not available for library verification
)

echo.
echo SUCCESS: Import library ready for use
echo File: %LIB_OUT%
echo.
echo Usage in your projects:
echo   bcc64 -I"path\to\gmp\headers" yourfile.cpp mpir_Embarcadero_compliers.lib
echo   or
echo   ilink64 ... mpir_Embarcadero_compliers.lib
echo.
pause
endlocal