#include "OptimizedBignum.h"
OptimizedBignum::OptimizedBignum(){}
int decimal_str_to_mpq(char *str, mpq_t rop)
{
	int sign = 1;
	char *s = str;
	if(*s == '-')
	{
		sign = -1;
		s++;
	}
	else	
		if(*s == '+')
			s++;
	char *dot = strchr(s, '.');
	char *int_str = NULL;
	char *frac_str = NULL;
	size_t int_len = dot ? (dot - s) : strlen(s);
	size_t frac_len = dot ? strlen(dot + 1) : 0;
	int_str = (char *)malloc(int_len + 1);
	if(int_str == NULL)
		return -1;
	memcpy(int_str, s, int_len);
	int_str[int_len] = '\0';
	if(frac_len > 0)
	{
		frac_str = (char *)malloc(frac_len + 1);
		if(frac_str == NULL)
		{
			free(int_str);
			return -1;
		}
		memcpy(frac_str, dot + 1, frac_len);
		frac_str[frac_len] = '\0';
	}
	mpz_t int_num;
	mpz_init(int_num);
	if(mpz_set_str(int_num, int_str[0] ? int_str : "0", 10) != 0)
	{
		mpz_clear(int_num);
		free(int_str);
		free(frac_str);
		return -1;
	}
	free(int_str);
	mpz_t frac_num;
	mpz_init(frac_num);
	if(frac_len > 0)
	{
		if(mpz_set_str(frac_num, frac_str, 10) != 0)
		{
			mpz_clear(int_num);
			mpz_clear(frac_num);
			free(frac_str);
			return -1;
		}
		free(frac_str);
	}
	mpz_t num, pow10, den;
	mpz_init(num);
	mpz_init(pow10);
	mpz_init(den);
	mpz_ui_pow_ui(pow10, 10, frac_len);
	mpz_mul(num, int_num, pow10);
	mpz_add(num, num, frac_num);
	if(sign == -1)
		mpz_neg(num, num);
	if(frac_len > 0)	
		mpz_set(den, pow10);
	else
		mpz_set_ui(den, 1UL);
	mpq_set_num(rop, num);
	mpq_set_den(rop, den);
	mpq_canonicalize(rop);
	mpz_clear(int_num);
	mpz_clear(frac_num);
	mpz_clear(num);
	mpz_clear(pow10);
	mpz_clear(den);
	return 0;
}
char* mpq_to_decimal_str(mpq_t q)
{
	if(mpq_sgn(q) == 0)
	{
		char *res = strdup("0");
		return res;
	}
	mpq_t abs_q;
	mpq_init(abs_q);
	mpq_abs(abs_q, q);
	mpz_t num, den;
	mpz_init(num);
	mpz_init(den);
	mpq_get_num(num, abs_q);
	mpq_get_den(den, abs_q);
	mpz_t int_part, rem;
	mpz_init(int_part);
	mpz_init(rem);
	mpz_tdiv_qr(int_part, rem, num, den);
	char *int_str = mpz_get_str(NULL, 10, int_part);
	const char *sign_str = (mpq_sgn(q) < 0) ? "-" : "";
	char *res = NULL;
	mpz_t den_copy, two, five;
	mpz_init(den_copy);
	mpz_init(two);
	mpz_init(five);
	mpz_set(den_copy, den);
	mpz_set_ui(two, 2);
	mpz_set_ui(five, 5);
	unsigned long val2 = mpz_remove(den_copy, den_copy, two);
	unsigned long val5 = mpz_remove(den_copy, den_copy, five);
	int has_frac = (mpz_sgn(rem) != 0);
	if(has_frac)
	{
		if(mpz_cmp_ui(den_copy, 1) != 0)
		{
			// Non-terminating decimal (unexpected)
			free(int_str);
			res = strdup("0");	// Fallback
			mpq_clear(abs_q);
			mpz_clear(num);
			mpz_clear(den);
			mpz_clear(int_part);
			mpz_clear(rem);
			return res;
		}
		unsigned long k = (val2 > val5) ? val2 : val5;
		// Compute frac_int = rem * 10^k / den
		mpz_t pow10, frac_num, frac_int;
		mpz_init(pow10);
		mpz_init(frac_num);
		mpz_init(frac_int);
		mpz_ui_pow_ui(pow10, 10, k);
		mpz_mul(frac_num, rem, pow10);
		mpz_divexact(frac_int, frac_num, den);
		char *frac_str = mpz_get_str(NULL, 10, frac_int);
		size_t frac_actual_len = strlen(frac_str);
		size_t pad_zeros = (k > frac_actual_len) ? (k - frac_actual_len) : 0;
		// Build result: sign + int + '.' + zeros + frac_str
		size_t len = strlen(sign_str) + strlen(int_str) + 1 + pad_zeros + frac_actual_len + 1;
		res = (char *)malloc(len);
		if(res != NULL)
		{
			char *ptr = res;
			strcpy(ptr, sign_str);
			ptr += strlen(sign_str);
			strcpy(ptr, int_str);
			ptr += strlen(int_str);
			if(pad_zeros + frac_actual_len > 0)
			{
				*ptr++ = '.';
				for(size_t i = 0; i < pad_zeros; i++)
					*ptr++ = '0';
				strcpy(ptr, frac_str);
				ptr += frac_actual_len;
			}
			*ptr = '\0';
			// Remove trailing zeros and dot ifno frac left
			char *dot_pos = strchr(res, '.');
			if(dot_pos)
			{
				char *end = res + strlen(res) - 1;
				while(end > dot_pos && *end == '0')
					end--;
				if(end == dot_pos)
					*end = '\0';
				else
					*(end + 1) = '\0';
			}
		}
		free(frac_str);
		mpz_clear(pow10);
		mpz_clear(frac_num);
		mpz_clear(frac_int);
		mpz_clear(den_copy);
		mpz_clear(two);
		mpz_clear(five);
		free(int_str);
		mpq_clear(abs_q);
		mpz_clear(num);
		mpz_clear(den);
		mpz_clear(int_part);
		mpz_clear(rem);
		return res;
	}
	else
	{
		// No fractional part
		size_t len = strlen(sign_str) + strlen(int_str) + 1;
		res = (char *)malloc(len);
		if(res != NULL)		
			snprintf(res, len, "%s%s", sign_str, int_str);		  
		free(int_str);
	}
	mpz_clear(den_copy);
	mpz_clear(two);
	mpz_clear(five);
	mpq_clear(abs_q);
	mpz_clear(num);
	mpz_clear(den);
	mpz_clear(int_part);
	mpz_clear(rem);
	return res;
}
char* OptimizedBignum::plus(char* bignum1, int Bignum1Length, char* bignum2, int Bignum2Length)
{
	char* str1 = (char*)malloc(Bignum1Length + 1);
	if(str1 == NULL) return NULL;
	memcpy(str1, bignum1, Bignum1Length);
	str1[Bignum1Length] = '\0';
	char* str2 = (char*)malloc(Bignum2Length + 1);
	if(str2 == NULL)
	{
		free(str1);
		return NULL;
	}
	memcpy(str2, bignum2, Bignum2Length);
	str2[Bignum2Length] = '\0';
	mpq_t num1, num2, result;
	mpq_init(num1);
	mpq_init(num2);
	mpq_init(result);
	if(decimal_str_to_mpq(str1, num1) != 0 || decimal_str_to_mpq(str2, num2) != 0)
	{
		mpq_clear(num1);
		mpq_clear(num2);
		mpq_clear(result);
		free(str1);
		free(str2);
		return NULL;
	}
	mpq_add(result, num1, num2);
	char* res = mpq_to_decimal_str(result);
	mpq_clear(num1);
	mpq_clear(num2);
	mpq_clear(result);
	free(str1);
	free(str2);
	return res;
}
char* OptimizedBignum::minus(char* bignum1, int Bignum1Length, char* bignum2, int Bignum2Length)
{
	char* str1 = (char*)malloc(Bignum1Length + 1);
	if(str1 == NULL) return NULL;
	memcpy(str1, bignum1, Bignum1Length);
	str1[Bignum1Length] = '\0';
	char* str2 = (char*)malloc(Bignum2Length + 1);
	if(str2 == NULL)
	{
		free(str1);
		return NULL;
	}
	memcpy(str2, bignum2, Bignum2Length);
	str2[Bignum2Length] = '\0';
	mpq_t num1, num2, result;
	mpq_init(num1);
	mpq_init(num2);
	mpq_init(result);
	if(decimal_str_to_mpq(str1, num1) != 0 || decimal_str_to_mpq(str2, num2) != 0)
	{
		mpq_clear(num1);
		mpq_clear(num2);
		mpq_clear(result);
		free(str1);
		free(str2);
		return NULL;
	}
	mpq_sub(result, num1, num2);
	char* res = mpq_to_decimal_str(result);
	mpq_clear(num1);
	mpq_clear(num2);
	mpq_clear(result);
	free(str1);
	free(str2);
	return res;
}
char* OptimizedBignum::multiply(char* bignum1, int Bignum1Length, char* bignum2, int Bignum2Length)
{
	char* str1 = (char*)malloc(Bignum1Length + 1);
	if(str1 == NULL) return NULL;
	memcpy(str1, bignum1, Bignum1Length);
	str1[Bignum1Length] = '\0';
	char* str2 = (char*)malloc(Bignum2Length + 1);
	if(str2 == NULL)
	{
		free(str1);
		return NULL;
	}
	memcpy(str2, bignum2, Bignum2Length);
	str2[Bignum2Length] = '\0';
	mpq_t num1, num2, result;
	mpq_init(num1);
	mpq_init(num2);
	mpq_init(result);
	if(decimal_str_to_mpq(str1, num1) != 0 || decimal_str_to_mpq(str2, num2) != 0)
	{
		mpq_clear(num1);
		mpq_clear(num2);
		mpq_clear(result);
		free(str1);
		free(str2);
		return NULL;
	}
	mpq_mul(result, num1, num2);
	char* res = mpq_to_decimal_str(result);
	mpq_clear(num1);
	mpq_clear(num2);
	mpq_clear(result);
	free(str1);
	free(str2);
	return res;
}
char* OptimizedBignum::divide(char* bignum1, int Bignum1Length, char* bignum2, int Bignum2Length)
{
	char* str1 = (char*)malloc(Bignum1Length + 1);
	if(str1 == NULL) return NULL;
	memcpy(str1, bignum1, Bignum1Length);
	str1[Bignum1Length] = '\0';
	char* str2 = (char*)malloc(Bignum2Length + 1);
	if(str2 == NULL)
	{
		free(str1);
		return NULL;
	}
	memcpy(str2, bignum2, Bignum2Length);
	str2[Bignum2Length] = '\0';
	mpq_t num1, num2, result;
	mpq_init(num1);
	mpq_init(num2);
	mpq_init(result);
	if(decimal_str_to_mpq(str1, num1) != 0 || decimal_str_to_mpq(str2, num2) != 0)
	{
		mpq_clear(num1);
		mpq_clear(num2);
		mpq_clear(result);
		free(str1);
		free(str2);
		return NULL;
	}
	// Check fordivision by zero
	if(mpq_sgn(num2) == 0)
	{
		mpq_clear(num1);
		mpq_clear(num2);
		mpq_clear(result);
		free(str1);
		free(str2);
		return NULL;
	}
	mpq_div(result, num1, num2);
	char* res = mpq_to_decimal_str(result);
	mpq_clear(num1);
	mpq_clear(num2);
	mpq_clear(result);
	free(str1);
	free(str2);
	return res;
}
// Requires: #include <gmp.h>, #include <mpfr.h>
// Configure these before including/compiling:
#ifndef MPFR_PREC_BITS
#define MPFR_PREC_BITS 256
#endif
#ifndef MPFR_MAX_PREC
#define MPFR_MAX_PREC 65536
#endif
#ifndef MAX_EXACT_INT_EXP_BITS
#define MAX_EXACT_INT_EXP_BITS 30
#endif
#ifndef MAX_RATIONAL_ROOT_BITS
#define MAX_RATIONAL_ROOT_BITS 20
#endif

// ----------------- Helper utilities -----------------

// Invert a rational: inv = 1/src. Returns 0 on success.
static int mpq_invert_safe(mpq_t inv, const mpq_t src)
{
    // inv = den(src) / num(src)
    mpz_t tnum, tden;
    mpz_inits(tnum, tden, NULL);
    mpz_set(tnum, mpq_denref(src));
    mpz_set(tden, mpq_numref(src));
    mpq_set_num(inv, tnum);
    mpq_set_den(inv, tden);
    mpq_canonicalize(inv);
    mpz_clears(tnum, tden, NULL);
    return 0;
}

// absolute value: dst = |src|
static void mpq_abs_safe(mpq_t dst, const mpq_t src)
{
    mpq_set(dst, src);
    if (mpq_sgn(dst) < 0) mpq_neg(dst, dst);
}

// Convert mpfr_t -> mpq_t via base-10 string (robust).
// Returns 0 on success, -1 on failure.
static int mpfr_to_mpq_via_string_safe(mpq_t rop, mpfr_t f)
{
    if (mpfr_nan_p(f) || mpfr_inf_p(f)) return -1;
    if (mpfr_zero_p(f)) { mpq_set_ui(rop, 0, 1); return 0; }

    mpfr_exp_t exp10;
    char *mant = mpfr_get_str(NULL, &exp10, 10, 0, f, MPFR_RNDN); // base 10, full precision
    if (!mant) return -1;

    int neg = 0;
    if (mant[0] == '-') { neg = 1; memmove(mant, mant + 1, strlen(mant)); } // remove sign for mpz parsing

    size_t mlen = strlen(mant);
    mpz_t num, den;
    mpz_inits(num, den, NULL);

    // num = integer represented by mant
    if (mpz_set_str(num, mant, 10) != 0) {
        mpfr_free_str(mant);
        mpz_clears(num, den, NULL);
        return -1;
    }

    // Determine denominator: if exp10 >= mlen -> integer * 10^(exp10-mlen)
    if (exp10 >= (mpfr_exp_t)mlen) {
        // multiply num by 10^(exp10-mlen); den = 1
        mpz_t pow10;
        mpz_init(pow10);
        mpz_ui_pow_ui(pow10, 10u, (unsigned)(exp10 - (mpfr_exp_t)mlen));
        mpz_mul(num, num, pow10);
        mpz_set_ui(den, 1u);
        mpz_clear(pow10);
    } else if (exp10 <= 0) {
        // number < 1: denominator = 10^{(-exp10)+mlen}
        unsigned long k = (unsigned long)(-exp10 + (mpfr_exp_t)mlen);
        mpz_ui_pow_ui(den, 10u, k);
    } else {
        // 0 < exp10 < mlen: decimal point inside mantissa
        unsigned long frac_digits = (unsigned long)(mlen - (size_t)exp10);
        mpz_ui_pow_ui(den, 10u, frac_digits);
    }

    if (neg) mpz_neg(num, num);

    mpq_set_num(rop, num);
    mpq_set_den(rop, den);
    mpq_canonicalize(rop);

    mpz_clears(num, den, NULL);
    mpfr_free_str(mant);
    return 0;
}

// Try exact integer root: rop = round(n^(1/q)); return 1 if exact else 0.
// q must be small enough to fit in unsigned long.
static int try_exact_root(mpz_t rop, const mpz_t n, unsigned long q)
{
    if (q == 0) return 0;
    mpz_root(rop, n, q); // floor(root)
    mpz_t temp;
    mpz_init(temp);
    mpz_pow_ui(temp, rop, q);
    int ok = (mpz_cmp(temp, n) == 0);
    mpz_clear(temp);
    return ok;
}

// ----------------- Integer exponentiation -----------------
// rop = base^(exp_int) where exp_int is mpz_t (>= 0).
// Returns 0 on success, -1 on error.
static int mpq_pow_integer_exp(mpq_t rop, const mpq_t base, const mpz_t exp_int)
{
    if (mpz_sgn(exp_int) == 0) { mpq_set_ui(rop, 1, 1); return 0; }
    if (mpz_sgn(exp_int) < 0) return -1; // caller should pass non-negative only

    // result = 1
    mpq_t result, base_copy;
    mpq_init(result); mpq_init(base_copy);
    mpq_set_ui(result, 1, 1);
    mpq_set(base_copy, base);

    mpz_t e;
    mpz_init_set(e, exp_int);

    // binary exponentiation
    while (mpz_sgn(e) > 0) {
        if (mpz_tstbit(e, 0)) {
            mpq_mul(result, result, base_copy);
        }
        // square base_copy
        mpq_mul(base_copy, base_copy, base_copy);
        mpz_fdiv_q_2exp(e, e, 1); // e >>= 1
    }

    mpq_set(rop, result);
    mpq_canonicalize(rop);

    mpq_clear(result); mpq_clear(base_copy);
    mpz_clear(e);
    return 0;
}

// ----------------- exact rational power attempt -----------------
// compute base^(p/q) exactly when possible. p,q are mpz_t (p may be >=0 only).
// negate_exp indicates original exponent sign (if true, invert result).
// return 0 on exact success, -1 otherwise.
static int try_exact_rational_power(mpq_t rop, const mpq_t base, const mpz_t p, const mpz_t q, int negate_exp)
{
    // Only attempt for p and q that fit in unsigned long and not too large
    if (!mpz_fits_ulong_p(p) || !mpz_fits_ulong_p(q)) return -1;
    unsigned long p_ul = mpz_get_ui(p);
    unsigned long q_ul = mpz_get_ui(q);
    if (p_ul > 1000000UL || q_ul > 1000000UL) return -1;

    int base_neg = (mpq_sgn(base) < 0);
    if (base_neg && (q_ul % 2 == 0)) return -1; // even root of negative is non-real

    // work with absolute base
    mpq_t abs_base;
    mpq_init(abs_base);
    mpq_abs_safe(abs_base, base);

    // compute num_pow = num(abs_base)^p_ul, den_pow = den(abs_base)^p_ul
    mpz_t num_pow, den_pow;
    mpz_inits(num_pow, den_pow, NULL);
    mpz_pow_ui(num_pow, mpq_numref(abs_base), p_ul);
    mpz_pow_ui(den_pow, mpq_denref(abs_base), p_ul);

    // try q-th root
    mpz_t root_num, root_den;
    mpz_inits(root_num, root_den, NULL);
    int num_ok = try_exact_root(root_num, num_pow, q_ul);
    int den_ok = try_exact_root(root_den, den_pow, q_ul);

    if (num_ok && den_ok) {
        if (base_neg && (q_ul % 2 == 1)) mpz_neg(root_num, root_num);
        mpq_set_num(rop, root_num);
        mpq_set_den(rop, root_den);
        if (negate_exp) {
            // invert rational: swap numerator/denominator
            mpz_t tnum, tden;
            mpz_inits(tnum, tden, NULL);
            mpz_set(tnum, mpq_denref(rop));
            mpz_set(tden, mpq_numref(rop));
            mpq_set_num(rop, tnum);
            mpq_set_den(rop, tden);
            mpz_clears(tnum, tden, NULL);
        }
        mpq_canonicalize(rop);
        mpz_clears(num_pow, den_pow, root_num, root_den, NULL);
        mpq_clear(abs_base);
        return 0;
    }

    mpz_clears(num_pow, den_pow, root_num, root_den, NULL);
    mpq_clear(abs_base);
    return -1;
}

// ----------------- MPFR fallback with adaptive precision -----------------
// Return 0 on success (converted result in rop), -1 on error.
static int approximate_pow_with_retry(mpq_t rop, const mpq_t base, const mpq_t exp)
{
    mpfr_prec_t prec = MPFR_PREC_BITS;
    const mpfr_prec_t max_prec = (mpfr_prec_t)MPFR_MAX_PREC;

    // If base negative and exponent non-integer -> reject early if denominator even
    if (mpq_sgn(base) < 0) {
        mpz_t q = {0};
        mpz_init_set(q, mpq_denref(exp));
        if (!mpz_cmp_ui(q, 1)) { /* integer exponent -> allowed */ }
        else if (mpz_even_p(q)) { mpz_clear(q); return -1; }
        mpz_clear(q);
    }

    while (prec <= max_prec) {
        mpfr_t fbase, fexp, fres;
        mpfr_init2(fbase, prec);
        mpfr_init2(fexp, prec);
        mpfr_init2(fres, prec);

        // set mpfr from mpq
        if (mpfr_set_q(fbase, base, MPFR_RNDN) != 0) { /* ignore */ }
        if (mpfr_set_q(fexp, exp, MPFR_RNDN) != 0) { /* ignore */ }

        // If base negative: we handle only integer exponents here (non-integer handled earlier)
        if (mpfr_sgn(fbase) < 0) {
            // mpfr_pow can produce NaN for non-integer exponents; but we already checked q parity.
            // For safety, compute pow(|base|, exp) and later reapply sign if exponent is rational with odd denom.
            mpfr_t fabsbase;
            mpfr_init2(fabsbase, prec);
            mpfr_abs(fabsbase, fbase, MPFR_RNDN);
            mpfr_pow(fres, fabsbase, fexp, MPFR_RNDN);
            mpfr_clear(fabsbase);
            // decide sign reapplication:
            int should_neg = 0;
            mpz_t qtmp; mpz_init_set(qtmp, mpq_denref(exp));
            if (mpz_cmp_ui(qtmp, 1) == 0) {
                // integer exponent: if odd, negative
                mpz_t ptmp; mpz_init_set(ptmp, mpq_numref(exp));
                if (mpz_odd_p(ptmp)) should_neg = 1;
                mpz_clear(ptmp);
            } else {
                if (mpz_fits_ulong_p(qtmp)) {
                    unsigned long q_ui = mpz_get_ui(qtmp);
                    if ((q_ui & 1u) != 0) {
                        // if numerator odd -> negative (approx heuristic)
                        if (mpz_odd_p(mpq_numref(exp))) should_neg = 1;
                    }
                }
            }
            mpz_clear(qtmp);
            if (should_neg) mpfr_neg(fres, fres, MPFR_RNDN);
        } else {
            mpfr_pow(fres, fbase, fexp, MPFR_RNDN);
        }

        // If regular number -> convert
        if (mpfr_regular_p(fres)) {
            int conv = mpfr_to_mpq_via_string_safe(rop, fres);
            mpfr_clears(fbase, fexp, fres, (mpfr_ptr)0);
            if (conv == 0) return 0;
            // else increase precision and retry
        } else if (mpfr_zero_p(fres)) {
            // maybe underflow — try increasing precision
            // heuristic: check if |base| < 1 and exp big positive -> underflow, or |base|>1 and exp big negative
            mpfr_t absbase, absexp;
            mpfr_init2(absbase, prec);
            mpfr_init2(absexp, prec);
            mpfr_abs(absbase, fbase, MPFR_RNDN);
            mpfr_abs(absexp, fexp, MPFR_RNDN);
            int underflow = 0;
            if (mpfr_cmp_ui(absbase, 1) < 0 && mpfr_cmp_ui(absexp, 10) > 0 && mpfr_sgn(fexp) > 0) underflow = 1;
            if (mpfr_cmp_ui(absbase, 1) > 0 && mpfr_cmp_ui(absexp, 10) > 0 && mpfr_sgn(fexp) < 0) underflow = 1;
            mpfr_clears(absbase, absexp, (mpfr_ptr)0);
            mpfr_clears(fbase, fexp, fres, (mpfr_ptr)0);
            if (!underflow) {
                // genuine zero
                mpq_set_ui(rop, 0, 1);
                return 0;
            }
            // else increase precision and retry
        } else if (mpfr_inf_p(fres) || mpfr_nan_p(fres)) {
            mpfr_clears(fbase, fexp, fres, (mpfr_ptr)0);
            // try higher precision unless already at max
        } else {
            mpfr_clears(fbase, fexp, fres, (mpfr_ptr)0);
        }

        // increase precision
        if (prec >= max_prec) break;
        // adaptive step: scale based on magnitude of exponent (approx)
        // get decimal magnitude of exponent (use mpq -> double fallback)
        double ed = mpq_get_d(exp);
        if (ed == 0.0) prec = (prec < max_prec/2) ? prec*2 : max_prec;
        else {
            double factor = fabs(ed);
            // clamp factor to reasonable range
            if (factor < 1.0) factor = 2.0;
            if (factor > 1e6) factor = 1e6;
            mpfr_prec_t increase = (mpfr_prec_t)(prec * (log10(1.0 + factor) + 1.0));
            if (increase <= prec) increase = prec * 2;
            if (increase > max_prec) increase = max_prec;
            prec = increase;
        }
    }

    return -1;
}

// ----------------- top-level power function -----------------
// Returns: 0 = exact (mpq), 1 = approximate (mpq via MPFR), -1 = error
int power(mpq_t rop, const mpq_t base, const mpq_t exp)
{
    // If base is negative and exponent is not integer -> not real
	if (mpq_sgn(base) < 0) {
		if (mpz_cmp_ui(mpq_denref(exp), 1) != 0) {
			// non-integer exponent for negative base
			return -1;  // mark as invalid
		}
	}

	// handle exponent == 0
    if (mpq_sgn(exp) == 0) { mpq_set_ui(rop, 1, 1); return 0; }
    // handle base == 0
    if (mpq_sgn(base) == 0) {
        if (mpq_sgn(exp) > 0) { mpq_set_ui(rop, 0, 1); return 0; }
        return -1;
    }
	mpq_t new_exp;
	mpq_init(new_exp);        // re-init exp
    mpq_set(new_exp, exp); 
    // decompose exp = p/q
    mpz_t p, q;
    mpz_inits(p, q, NULL);
    mpz_set(p, mpq_numref(exp));
    mpz_set(q, mpq_denref(exp));

    int exp_neg = (mpz_sgn(p) < 0);
	
    // If integer exponent (q==1)
    if (mpz_cmp_ui(q, 1) == 0) {
		if (exp_neg)
	{
		mpz_neg(p, p); // make exponent positive

		mpz_t one;
		mpz_init_set_ui(one, 1);

		mpf_t fa, fb, result;
		mpf_inits(fa, fb, result, NULL);

		mpf_set_z(fa, one);
		mpf_set_z(fb, p);
		mpf_div(result, fa, fb);  // result = 1 / p

		// convert mpf_t → mpq_t exp
		mpq_clear(new_exp);       // clear old exp if already initialized
		mpq_init(new_exp);        // re-init exp
		mpq_set_f(new_exp, result);  // exp = 1/p

		mpf_clears(fa, fb, result, NULL);
		mpz_clear(one);
		// exp_neg=0;
	}
		
		
        // small exponents -> exact binary exponentiation
        size_t bits = mpz_sizeinbase(p, 2);
        if (bits <= MAX_EXACT_INT_EXP_BITS && mpz_fits_ulong_p(p)) {
            // p fits into unsigned long
            mpz_t pcopy; mpz_init_set(pcopy, p);
            // If exponent negative: compute with positive exponent then invert
            if (exp_neg) {
                // compute for positive exp using mpq_pow_integer_exp on pos exp
                mpq_t temp;
                mpq_init(temp);
                mpq_t inv_base;
                mpq_init(inv_base);
                mpq_invert_safe(inv_base, base); // inv_base = 1/base
                if (mpq_pow_integer_exp(temp, inv_base, pcopy) == 0) {
                    mpq_set(rop, temp);
                    mpq_canonicalize(rop);
                    mpq_clear(temp);
                    mpq_clear(inv_base);
                    mpz_clears(p, q, pcopy, NULL);
                    return 0;
                }
                mpq_clear(temp); mpq_clear(inv_base);
            } else {
                mpq_t temp;
                mpq_init(temp);
                if (mpq_pow_integer_exp(temp, base, pcopy) == 0) {
                    mpq_set(rop, temp);
                    mpq_canonicalize(rop);
                    mpq_clear(temp);
                    mpz_clears(p, q, pcopy, NULL);
                    return 0;
                }
                mpq_clear(temp);
            }
            mpz_clear(pcopy);
            // fall through to MPFR fallback
        }

        // else fallback to MPFR approximate
        int ar = approximate_pow_with_retry(rop, base, new_exp);
        mpz_clears(p, q, NULL);
        return (ar == 0) ? 1 : -1;
    }

    // Rational exponent with q>1:
    // if negative base and q even -> non-real
    // if (mpq_sgn(base) < 0 && mpz_even_p(q)) { mpz_clears(p, q, NULL); return -1; }

    // try exact rational method if p,q small
    if (mpz_fits_ulong_p(p) && mpz_fits_ulong_p(q)) {
		// exp_neg=0;
        unsigned long p_ul = mpz_get_ui(p);
        unsigned long q_ul = mpz_get_ui(q);
        if (p_ul <= 1000000UL && q_ul <= 1000000UL) {
            int exact = try_exact_rational_power(rop, base, p, q, exp_neg);
            if (exact == 0) { mpz_clears(p,q,NULL); return 0; }
        }
    }

    // MPFR approximate fallback
    int ar = approximate_pow_with_retry(rop, base, new_exp);
    mpz_clears(p, q, NULL);
    return (ar == 0) ? 1 : -1;
}
int validate_power_result(const mpq_t result, const mpq_t base, const mpq_t exp, double tolerance)
{    
    // Can't validate if exp is zero (result should be 1)
    if(mpq_sgn(exp) == 0) {
		if (mpq_sgn(exp) > 0 && mpq_sgn(result) == 0) {
            return 0;  // Valid: 0^positive = 0
        }
        mpq_t one;
        mpq_init(one);
        mpq_set_ui(one, 1, 1);
        int valid = (mpq_cmp(result, one) == 0);
        mpq_clear(one);
        return valid ? 0 : -1;
    }
    /*if (mpq_sgn(base) < 0) {
		if (mpz_cmp_ui(mpq_denref(exp), 1) != 0) {
			// non-integer exponent for negative base
			return 0;  // mark as invalid
		}
	}*/
    // Use MPFR for validation with high precision
    mpfr_prec_t prec = MPFR_PREC_BITS * 2;  // Use higher precision for validation
    
    mpfr_t f_base, f_exp, f_result, f_computed, f_diff, f_rel_error;
    mpfr_inits2(prec, f_base, f_exp, f_result, f_computed, f_diff, f_rel_error, NULL);
    
    // Convert to MPFR
    mpfr_set_q(f_base, base, MPFR_RNDN);
    mpfr_set_q(f_exp, exp, MPFR_RNDN);
    mpfr_set_q(f_result, result, MPFR_RNDN);
    
    // Compute base^exp for comparison
    mpfr_pow(f_computed, f_base, f_exp, MPFR_RNDN);
    
    // Check for special cases
    if (mpfr_inf_p(f_computed) || mpfr_nan_p(f_computed)) {
        mpfr_clears(f_base, f_exp, f_result, f_computed, f_diff, f_rel_error, NULL);
        return -1;  // Invalid computation
    }
    
    if (mpfr_zero_p(f_computed) && mpfr_zero_p(f_result)) {
        mpfr_clears(f_base, f_exp, f_result, f_computed, f_diff, f_rel_error, NULL);
        return 0;  // Both zero - valid
    }
    
    // Compute relative error: |result - computed| / |computed|
    mpfr_sub(f_diff, f_result, f_computed, MPFR_RNDN);
    mpfr_abs(f_diff, f_diff, MPFR_RNDN);
    mpfr_abs(f_rel_error, f_computed, MPFR_RNDN);
    
    if (mpfr_zero_p(f_rel_error)) {
        mpfr_clears(f_base, f_exp, f_result, f_computed, f_diff, f_rel_error, NULL);
        return -1;  // Cannot compute relative error
    }
    
    mpfr_div(f_rel_error, f_diff, f_rel_error, MPFR_RNDN);
    
    // Check if relative error is within tolerance
    double rel_error = mpfr_get_d(f_rel_error, MPFR_RNDN);
    
    mpfr_clears(f_base, f_exp, f_result, f_computed, f_diff, f_rel_error, NULL);
    
    if (rel_error <= tolerance) {
        return 0;  // Valid
    }
    
    return -1;  // Invalid - error too large
}

// Alternative validation using logarithms: check if exp * log(base) ≈ log(result)
// More numerically stable for very large or very small results
// Returns: 0 if valid, -1 if invalid
int validate_power_result_log(const mpq_t result, const mpq_t base, const mpq_t exp, double tolerance)
{
    // Special cases
    if (mpq_sgn(base) <= 0 || mpq_sgn(result) <= 0) {
        return -1;  // Can't use logarithm with non-positive numbers
    }
    
    if (mpq_sgn(exp) == 0) {
        mpq_t one;
        mpq_init(one);
        mpq_set_ui(one, 1, 1);
        int valid = (mpq_cmp(result, one) == 0);
        mpq_clear(one);
        return valid ? 0 : -1;
    }
    
    mpfr_prec_t prec = MPFR_PREC_BITS * 2;
    
    mpfr_t f_base, f_exp, f_result;
    mpfr_t f_log_base, f_log_result, f_expected_log, f_diff;
    mpfr_inits2(prec, f_base, f_exp, f_result, f_log_base, f_log_result, 
                f_expected_log, f_diff, NULL);
    
    // Convert to MPFR
    mpfr_set_q(f_base, base, MPFR_RNDN);
    mpfr_set_q(f_exp, exp, MPFR_RNDN);
    mpfr_set_q(f_result, result, MPFR_RNDN);
    
    // Compute log(base) and log(result)
    mpfr_log(f_log_base, f_base, MPFR_RNDN);
    mpfr_log(f_log_result, f_result, MPFR_RNDN);
    
    // Compute expected: exp * log(base)
    mpfr_mul(f_expected_log, f_exp, f_log_base, MPFR_RNDN);
    
    // Compute difference
    mpfr_sub(f_diff, f_log_result, f_expected_log, MPFR_RNDN);
    mpfr_abs(f_diff, f_diff, MPFR_RNDN);
    
    // For log space, we compare absolute difference
    // Since log(a/b) = log(a) - log(b), and a/b ≈ 1 means log(a/b) ≈ 0
    double log_diff = mpfr_get_d(f_diff, MPFR_RNDN);
    
    mpfr_clears(f_base, f_exp, f_result, f_log_base, f_log_result, 
                f_expected_log, f_diff, NULL);
    
    // tolerance in log space roughly corresponds to relative error
    // log(1 + ε) ≈ ε for small ε
    if (log_diff <= tolerance) {
        return 0;  // Valid
    }
    
    return -1;  // Invalid
}

// Comprehensive validation that tries multiple methods
// Returns: 0 if valid, -1 if invalid, 1 if uncertain
int validate_power_comprehensive(const mpq_t result, const mpq_t base, const mpq_t exp, double tolerance)
{
    // Try direct validation first
    int direct_valid = validate_power_result(result, base, exp, tolerance);
    
    // If direct validation succeeds, we're done
    if (direct_valid == 0) {
        return 0;
    }
    
    // Try logarithmic validation for positive values
    if (mpq_sgn(base) > 0 && mpq_sgn(result) > 0) {
        int log_valid = validate_power_result_log(result, base, exp, tolerance);
        if (log_valid == 0) {
            return 0;
        }
    }
    
    // For integer exponents, we can verify by computing result^(1/exp)
    if (mpz_cmp_ui(mpq_denref(exp), 1) == 0) {
        // Integer exponent - try inverse power
        mpq_t inv_exp, recovered_base;
        mpq_init(inv_exp);
        mpq_init(recovered_base);
        
        mpq_inv(inv_exp, exp);  // 1/exp
        
        // Compute result^(1/exp) - should equal base
        int inv_result = power(recovered_base, result, inv_exp);
        
        if (inv_result >= 0) {
            // Compare recovered_base with base
            mpfr_t f_recovered, f_base, f_diff, f_rel_error;
            mpfr_prec_t prec = MPFR_PREC_BITS;
            mpfr_inits2(prec, f_recovered, f_base, f_diff, f_rel_error, NULL);
            
            mpfr_set_q(f_recovered, recovered_base, MPFR_RNDN);
            mpfr_set_q(f_base, base, MPFR_RNDN);
            
            mpfr_sub(f_diff, f_recovered, f_base, MPFR_RNDN);
            mpfr_abs(f_diff, f_diff, MPFR_RNDN);
            mpfr_abs(f_rel_error, f_base, MPFR_RNDN);
            
            if (!mpfr_zero_p(f_rel_error)) {
                mpfr_div(f_rel_error, f_diff, f_rel_error, MPFR_RNDN);
                double rel_error = mpfr_get_d(f_rel_error, MPFR_RNDN);
                
                mpfr_clears(f_recovered, f_base, f_diff, f_rel_error, NULL);
                mpq_clear(inv_exp);
                mpq_clear(recovered_base);
                
                if (rel_error <= tolerance * 10) {  // More lenient for inverse
                    return 0;
                }
            } else {
                mpfr_clears(f_recovered, f_base, f_diff, f_rel_error, NULL);
            }
        }
        
        mpq_clear(inv_exp);
        mpq_clear(recovered_base);
    }
    
    // All validation methods failed
    return -1;
}
