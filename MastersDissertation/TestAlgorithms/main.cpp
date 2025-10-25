#include "bignum.h"
int MinCountOfDigits=1,MaxCountOfDigits=5;
const int MaxFractPartLength=10,MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
int CountOfRanges=10,CountOfBignumPairs=100;
static char* normalize_positive_decimal(const char* s)
{
	if(!s)
	{
		char* r=(char*)malloc(2);
		if (!r) return NULL;
		r[0]='0'; r[1]='\0';
		return r;
	}
	// skip leading/trailing whitespace just in case (optional)
	// not strictly necessary if inputs are controlled
	while(*s && isspace((unsigned char)*s))
		++s;
	size_t n=strlen(s);
	// find dot
	const char* dot=strchr(s, '.');
	const char* int_start=s;
	const char* int_end=dot ? dot : s + n;
	const char* frac_start=dot ? dot + 1 : NULL;
	const char* frac_end=dot ? s + n : NULL;
	// compute integer part after trimming leading zeros: [p .. int_end)
	const char* p=int_start;
	while (p < int_end && *p == '0')
		++p;
	int int_all_zero=(p == int_end);
	// trim trailing zeros in fraction
	if (frac_start) 
		while(frac_end > frac_start && *(frac_end - 1) == '0')
			--frac_end;
	// estimate output length:
	size_t out_int_len=int_all_zero ? 1 : (size_t)(int_end - p);
	size_t out_frac_len=frac_start ? (size_t)(frac_end - frac_start) : 0;
	size_t out_len=out_int_len + (out_frac_len ? (1 + out_frac_len) : 0);
	// allocate (out_len + 1) bytes
	char* out=(char*)malloc(out_len + 1);
	if(!out)
		return NULL;
	char* q=out;
	// integer part
	if (int_all_zero) 
		*q++='0';
	else
	{
		memcpy(q, p, out_int_len);
		q += out_int_len;
	}
	// fractional part, if any
	if(out_frac_len)
	{
		*q++='.';
		memcpy(q, frac_start, out_frac_len);
		q += out_frac_len;
	}
	*q='\0';
	// Guarantee at least "0" (shouldn't be needed but safe)
	if (out[0] == '\0')
		out[0]='0'; out[1]='\0';
	return out;
}
// Return a newly-allocated POSITIVE normalized copy of |x| (no sign).
static char* abs_normalized(const char* x)
{
	if(!x)
		return NULL;
	const char* p=(x[0] == '-' || x[0] == '+') ? x + 1 : x;
	// char* norm=normalize_positive_decimal handles empty and dot cases
	char* r=normalize_positive_decimal(p);
	return r; // caller must free(r)
}

// Compare two POSITIVE normalized decimal strings by absolute value.
// Return -1,0,1
static int cmp_pos_dec(const char* a, const char* b)
{
	// Both must be normalized, positive, possibly with '.'.
	// Compare integer lengths first.
	const char* da=strchr(a, '.');
	const char* db=strchr(b, '.');
	size_t ai=da ? (size_t)(da - a) : strlen(a);
	size_t bi=db ? (size_t)(db - b) : strlen(b);
	if(ai != bi)
		return (ai < bi) ? -1 : 1;
	// Compare integer digits
	for (size_t i=0; i<ai; ++i)
		if(a[i]!=b[i])
			return (a[i]<b[i]) ? -1 : 1;	
	// Compare fractional digits
	const char* af=da ? da+1 : "";
	const char* bf=db ? db+1 : "";
	size_t alf=strlen(af);
	size_t blf=strlen(bf);
	size_t m=max(alf, blf);
	for (size_t i=0; i<m; ++i)
	{
		char ca=(i<alf)? af[i] : '0';
		char cb=(i<blf)? bf[i] : '0';
		if(ca!=cb)
			return (ca<cb) ? -1 : 1;
	}
	return 0;
}
// Shift decimal point of string A to the right by 'digits' places (i.e. divide by 10^digits)
// Example: shift_decimal_down("12345", 3) -> "12.345"
//			shift_decimal_down("123.45", 2) -> "1.2345"
//			shift_decimal_down("0.00123", 5) -> "0.0000123"
char* shift_decimal_down(const char* A, int digits)
{
	if(!A)
		return nullptr;
	int len=(int)strlen(A);
	// Find existing decimal point (if any)
	const char* dot=strchr(A, '.');
	int intLen=dot ? (int)(dot - A) : len; // digits before decimal
	int fracLen=dot ? (len - intLen - 1) : 0; // digits after decimal
	// New fractional length after shift
	int newFracLen=fracLen + digits;
	// Required length:
	// integer part + 1 (possible '0') + 1 (dot) + newFracLen + '\0'
	int newLen=intLen + 1 + newFracLen + 1;
	char* out=(char*)calloc(newLen, sizeof(char));
	if(!out)
		return nullptr;
	char* p=out;
	// Copy integer part (or '0' if empty)
	if(intLen == 0)
		*p++='0';
	else
	{
		memcpy(p, A, intLen);
		p += intLen;
	}
	// Add decimal point
	*p++='.';
	// Copy fractional digits (if any)
	if (fracLen > 0)
	{
		memcpy(p, dot + 1, fracLen);
		p += fracLen;
	}
	// Add extra trailing zeros (digits shift)
	for (int i=0; i < digits; i++) 
		*p++='0';
	*p='\0';
	// Normalize: remove trailing zeros in fraction if not needed
	// but keep at least one digit after dot if there's a dot
	char* end=out + strlen(out) - 1;
	while(end > out && *end == '0' && *(end - 1) != '.')
		*end--='\0';
	return out;
}
// Make epsilon=max(|X|*10^{-p}, 10^{-p})
static char* make_relative_epsilon(const char* X, int p)
{
	char* absX=abs_normalized(X);
	char* rel =shift_decimal_down(absX, p);
	free(absX);
	// build min=10^{-p} as string "0." + (p-1)*'0' + '1'
	size_t cap=(p>0? (size_t)p+3 : 3);
	char* minE=(char*)calloc(cap+4, sizeof(char));
	if (p<=0) // 10^0=1, but we want 10^{-p} with p<=0 → ≥1, keep "1" as minimal guard
		strcpy(minE, "1");
	else
	{
		char* t=minE;
		*t++='0'; *t++='.';
		for (int i=1; i<p; ++i) *t++='0';
		*t++='1'; *t='\0';
	}
	// epsilon=max(rel, minE)
	char* eps=NULL;
	int c=cmp_pos_dec(rel, minE);
	if (c>=0)
	{
		eps=rel;
		free(minE);
	}
	else
	{
		eps=minE;
		free(rel);
	}
	return eps;
}
char* PowerOf10(int n)
{
	char* res=(char*)calloc(n+4,sizeof(char));
	res[0]='1';
	for (int i=1; i <= n; i++)
		res[i]='0';
	res[n+1]='\0';
	return res;
}
template <typename BigNumClass> void ParseDecimalToFractionOutputOn(const char* str, char*& numerator, char*& denominator)
{
	// Parse Q (finite or periodic) into fraction num/den
	string s(str);
	BigNumClass* CalculationClass=new BigNumClass();
	bool negative=false;
	if(!s.empty() && s[0] == '-')
	{
		negative=true;
		s=s.substr(1);
	}
	size_t dot=s.find('.');
	size_t lpar=s.find('(');
	size_t rpar=s.find(')');
	string A, B, C;
	if(dot == string::npos)
		A=s;
	else
	{
		A=s.substr(0, dot);
		if(lpar == string::npos)
			B=s.substr(dot+1);
		else
		{
			B=s.substr(dot+1, lpar - (dot+1));
			C=s.substr(lpar+1, rpar - lpar - 1);
		}
	}
	if (C.empty())
	{
		// Finite decimal: numerator=int(AB), denominator=10^|B|
		string AB=A + B;
		if(AB.empty())
			AB="0";
		numerator=strdup(AB.c_str());
		denominator=PowerOf10((int)B.size());
	}
	else
	{
		// Repeating decimal
		string AB=A + B;
		string ABC=AB + C;
		char* bigABC=strdup(ABC.c_str());
		char* bigAB	=strdup(AB.c_str());
		// num=ABC - AB
		cout<<std::left<<setw(MaxBignumLength)<<bigABC<<" - ";
		cout<<std::right<<setw(MaxBignumLength)<<bigAB<<"=";
		char* num=CalculationClass->minus(bigABC, (int)strlen(bigABC), bigAB, (int)strlen(bigAB));
		cout<<std::left<<setw(MaxBignumLength)<<num<<endl;
		char* powB=PowerOf10((int)B.size());
		char* powC=PowerOf10((int)C.size());
		char one[]="1";
		cout<<std::left<<setw(MaxBignumLength)<<powC<<" - ";
		cout<<std::right<<setw(MaxBignumLength)<<one<<"=";
		char* powCminus1=CalculationClass->minus(powC, (int)strlen(powC), one, 1);
		cout<<std::left<<setw(MaxBignumLength)<<powCminus1<<endl;		
		cout<<std::left<<setw(MaxBignumLength)<<powB<<" - ";
		cout<<std::right<<setw(MaxBignumLength)<<powCminus1<<"=";
		char* denom=CalculationClass->multiply(powB, (int)strlen(powB), powCminus1, (int)strlen(powCminus1));
		cout<<std::left<<setw(MaxBignumLength)<<denom<<endl;
		numerator=num;
		denominator=denom;
		free(powB);
		free(powC);
		free(powCminus1);
		free(bigABC);
		free(bigAB);
	}
	if (negative && !(numerator[0] == '0' && numerator[1] == '\0'))
	{
		// prepend minus
		size_t L=strlen(numerator);
		char* signedNum=(char*)calloc(L+4,sizeof(char));
		signedNum[0]='-';
		memcpy(signedNum+1, numerator, L+1);
		free(numerator);
		numerator=signedNum;
	}
	delete CalculationClass;
}
// Full consistency check
template <typename BigNumClass> bool IsDivisionConsistentOutputOn(char* A, char* B, char* Q, int precisionDigits)
{
	BigNumClass* CalculationClass=new BigNumClass();
	string s(Q);
	// Case 1: repeating decimal → exact rational check
	if(s[s.length()-1]==')') // if(s.find('(') != string::npos)
	{
		char* Qnum;
		char* Qden;
		ParseDecimalToFractionOutputOn<BigNumClass>(Q, Qnum, Qden);
		cout<<std::left<<setw(MaxBignumLength)<<Qnum<<" * ";
		cout<<std::right<<setw(MaxBignumLength)<<B<<"=";
		char* Left	= CalculationClass->multiply(Qnum, (int)strlen(Qnum), B, (int)strlen(B));
		cout<<std::left<<setw(MaxBignumLength)<<Left<<endl;		
		cout<<std::left<<setw(MaxBignumLength)<<Qden<<" * ";
		cout<<std::right<<setw(MaxBignumLength)<<A<<"=";
		char* Right=CalculationClass->multiply(Qden, (int)strlen(Qden), A, (int)strlen(A));
		cout<<std::left<<setw(MaxBignumLength)<<Right<<endl;
		bool ok=IsEqual(Left, (int)strlen(Left), Right, (int)strlen(Right));
		free(Qnum);
		free(Qden);
		free(Left);
		free(Right);
		delete CalculationClass;
		return ok;
	}
	/*cout<<std::left<<setw(MaxBignumLength)<<Q<<" * ";
	cout<<std::right<<setw(MaxBignumLength)<<B<<"=";
	char* Product=CalculationClass->multiply(Q, strlen(Q), B, strlen(B));
	cout<<std::left<<setw(MaxBignumLength)<<Product<<endl;	
	cout<<std::left<<setw(MaxBignumLength)<<Q<<" - ";
	cout<<std::right<<setw(MaxBignumLength)<<B<<"=";
	char* Diff=CalculationClass->minus(A, strlen(A), Product, strlen(Product));
	cout<<std::left<<setw(MaxBignumLength)<<Diff<<endl;
	bool ok;
	if(Diff[0]!='-' && B[0]!='-')
		ok=(IsLess(Diff, strlen(Diff), B, strlen(B)));
	else
	{
		char* Bignum1Abs,*Bignum2Abs;
		if(Diff[0]!='-')
			Bignum1Abs=Diff;
		else
			Bignum1Abs=&Diff[1];
		
		if(B[0]!='-')
			Bignum2Abs=B;
		else
			Bignum2Abs=&B[1];
		ok=(IsLess(Bignum1Abs, strlen(Bignum1Abs), Bignum2Abs, strlen(Bignum2Abs)));
	}
	free(Product);
	free(Diff);
	return ok;*/
	// 1) QB=Q * B
	cout<<std::left<<setw(MaxBignumLength)<<Q<<" * ";
	cout<<std::right<<setw(MaxBignumLength)<<B<<"=";
	char* QB=CalculationClass->multiply(Q,strlen(Q),B,strlen(B));
	cout<<std::left<<setw(MaxBignumLength)<<QB<<endl;
	// 2) Diff=QB - A
	cout<<std::left<<setw(MaxBignumLength)<<QB<<" - ";
	cout<<std::right<<setw(MaxBignumLength)<<A<<"=";
	char* Diff=CalculationClass->minus(QB,strlen(QB),A,strlen(A));
	cout<<std::left<<setw(MaxBignumLength)<<Diff<<endl;
	// 3) abs(Diff)
	char* AbsDiff=abs_normalized(Diff);
	// 4) epsilon=max(|A|, |QB|) * 10^{-p}, floor 10^{-p}
	char* AbsA	= abs_normalized(A);
	char* AbsQB=abs_normalized(QB);
	// Pick the larger magnitude between |A| and |QB|
	const char* baseline=(cmp_pos_dec(AbsA, AbsQB) >= 0) ? AbsA : AbsQB;
	// Build epsilon without multiply
	char* EpsFromBaseline=shift_decimal_down(baseline, precisionDigits);
	// Minimum epsilon=10^{-p}
	char* MinEps=NULL;
	{
		size_t cap=(precisionDigits>0? (size_t)precisionDigits+3 : 3);
		MinEps=(char*)calloc(cap, sizeof(char));
		if (precisionDigits<=0)
			strcpy(MinEps, "1");
		else
		{
			char* t=MinEps;
			*t++='0'; *t++='.';
			for (int i=1; i<precisionDigits; ++i) *t++='0';
			*t++='1'; *t='\0';
		}
	}
	char* Epsilon=NULL;
	if (cmp_pos_dec(EpsFromBaseline, MinEps) >= 0)
	{
		Epsilon=EpsFromBaseline;
		free(MinEps);
	}
	else
	{
		Epsilon=MinEps;
		free(EpsFromBaseline);
	}
	// 5) Compare |Diff| <= Epsilon ?
	bool ok=(cmp_pos_dec(AbsDiff, Epsilon) <= 0);
	free(QB);
	free(Diff);
	free(AbsDiff);
	free(AbsA);
	free(AbsQB);
	free(Epsilon);
	delete CalculationClass;
	return ok;
}
template <typename BigNumClass> void ParseDecimalToFraction(const char* str, char*& numerator, char*& denominator)
{
	// Parse Q (finite or periodic) into fraction num/den
	string s(str);
	BigNumClass* CalculationClass=new BigNumClass();
	bool negative=false;
	if(!s.empty() && s[0] == '-')
	{
		negative=true;
		s=s.substr(1);
	}
	size_t dot=s.find('.');
	size_t lpar=s.find('(');
	size_t rpar=s.find(')');
	string A, B, C;
	if (dot == string::npos)
		A=s;
	else
	{
		A=s.substr(0, dot);
		if (lpar == string::npos)
			B=s.substr(dot+1);
		else
		{
			B=s.substr(dot+1, lpar - (dot+1));
			C=s.substr(lpar+1, rpar - lpar - 1);
		}
	}
	if (C.empty())
	{
		// Finite decimal: numerator=int(AB), denominator=10^|B|
		string AB=A + B;
		if(AB.empty())
			AB="0";
		numerator=strdup(AB.c_str());
		denominator=PowerOf10((int)B.size());
	}
	else
	{
		// Repeating decimal
		string AB=A + B;
		string ABC=AB + C;
		char* bigABC=strdup(ABC.c_str());
		char* bigAB	=strdup(AB.c_str());
		// num=ABC - AB
		char* num=CalculationClass->minus(bigABC, (int)strlen(bigABC), bigAB, (int)strlen(bigAB));
		char* powB=PowerOf10((int)B.size());
		char* powC=PowerOf10((int)C.size());
		char one[]="1";
		char* powCminus1=CalculationClass->minus(powC, (int)strlen(powC), one, 1);
		char* denom=CalculationClass->multiply(powB, (int)strlen(powB), powCminus1, (int)strlen(powCminus1));
		numerator=num;
		denominator=denom;
		free(powB);
		free(powC);
		free(powCminus1);
		free(bigABC);
		free(bigAB);
	}
	if (negative && !(numerator[0] == '0' && numerator[1] == '\0'))
	{
		// prepend minus
		size_t L=strlen(numerator);
		char* signedNum=(char*)calloc(L+4,sizeof(char));
		signedNum[0]='-';
		memcpy(signedNum+1, numerator, L+1);
		free(numerator);
		numerator=signedNum;
	}
	delete CalculationClass;
}
template <typename BigNumClass> bool IsDivisionConsistent(char* A, char* B, char* Q, int precisionDigits)
{
	BigNumClass* CalculationClass=new BigNumClass();
	string s(Q);
	// Case 1: repeating decimal → exact rational check
	if(s[s.length()-1]==')') // if(s.find('(') != string::npos)
	{
		char* Qnum;
		char* Qden;
		ParseDecimalToFraction<BigNumClass>(Q, Qnum, Qden);
		char* Left	= CalculationClass->multiply(Qnum, (int)strlen(Qnum), B, (int)strlen(B));
		char* Right=CalculationClass->multiply(Qden, (int)strlen(Qden), A, (int)strlen(A));
		bool ok=IsEqual(Left, (int)strlen(Left), Right, (int)strlen(Right));
		free(Qnum);
		free(Qden);
		free(Left);
		free(Right);
		delete CalculationClass;
		return ok;
	}
	/*char* Product=CalculationClass->multiply(Q, strlen(Q), B, strlen(B));
	char* Diff=CalculationClass->minus(A, strlen(A), Product, strlen(Product));
	bool ok;
	if(Diff[0]!='-' && B[0]!='-')
		ok=(IsLess(Diff, strlen(Diff), B, strlen(B)));
	else
	{
		char* Bignum1Abs,*Bignum2Abs;
		if(Diff[0]!='-')
			Bignum1Abs=Diff;
		else
			Bignum1Abs=&Diff[1];
		
		if(B[0]!='-')
			Bignum2Abs=B;
		else
			Bignum2Abs=&B[1];
		ok=(IsLess(Bignum1Abs, strlen(Bignum1Abs), Bignum2Abs, strlen(Bignum2Abs)));
	}
	free(Product);
	free(Diff);
	return ok;*/
	// 1) QB=Q * B
	char* QB=CalculationClass->multiply(Q,strlen(Q),B,strlen(B));
	// 2) Diff=QB - A
	char* Diff=CalculationClass->minus(QB,strlen(QB),A,strlen(A));
	// 3) abs(Diff)
	char* AbsDiff=abs_normalized(Diff);
	// 4) epsilon=max(|A|, |QB|) * 10^{-p}, floor 10^{-p}
	char* AbsA	= abs_normalized(A);
	char* AbsQB=abs_normalized(QB);
	// Pick the larger magnitude between |A| and |QB|
	const char* baseline=(cmp_pos_dec(AbsA, AbsQB) >= 0) ? AbsA : AbsQB;
	// Build epsilon without multiply
	char* EpsFromBaseline=shift_decimal_down(baseline, precisionDigits);
	// Minimum epsilon=10^{-p}
	char* MinEps=NULL;
	{
		size_t cap=(precisionDigits>0? (size_t)precisionDigits+3 : 3);
		MinEps=(char*)calloc(cap, sizeof(char));
		if (precisionDigits<=0)
			strcpy(MinEps, "1");
		else
		{
			char* t=MinEps;
			*t++='0'; *t++='.';
			for (int i=1; i<precisionDigits; ++i) *t++='0';
			*t++='1'; *t='\0';
		}
	}
	char* Epsilon=NULL;
	if (cmp_pos_dec(EpsFromBaseline, MinEps) >= 0)
	{
		Epsilon=EpsFromBaseline;
		free(MinEps);
	}
	else
	{
		Epsilon=MinEps;
		free(EpsFromBaseline);
	}
	// 5) Compare |Diff| <= Epsilon ?
	bool ok=(cmp_pos_dec(AbsDiff, Epsilon) <= 0);
	free(QB);
	free(Diff);
	free(AbsDiff);
	free(AbsA);
	free(AbsQB);
	free(Epsilon);
	delete CalculationClass;
	return ok;
}

template <typename BigNumClass> void TestAllBignumOperations(char*** BignumPairs)
{
	BigNumClass* CalculationClass=new BigNumClass();
	int i,j,CountOfErrors=0;
	char* result,*CheckResult;
	for(i=0; i<CountOfBignumPairs; i++)
	{
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<setw(MaxBignumLength)<<BignumPairs[i][0]<<" + ";
		cout<<std::right<<setw(MaxBignumLength)<<BignumPairs[i][1]<<"=";
		result=CalculationClass->plus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<setw(MaxBignumLength)<<result<<endl;
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<setw(MaxBignumLength)<<result<<" - ";
		cout<<std::right<<setw(MaxBignumLength)<<BignumPairs[i][1]<<"=";
		CheckResult=CalculationClass->minus(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<setw(MaxBignumLength)<<CheckResult<<endl;
		if(IsNotEqual(CheckResult,strlen(CheckResult),BignumPairs[i][0],strlen(BignumPairs[i][0])))
		{
			cout<<"Incorrect result: operation PLUS\n";
			CountOfErrors++;
		}
		free(result);
		free(CheckResult);
		for(j=0; j<90; j++)
			cout<<'-';
		cout<<endl;
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<setw(MaxBignumLength)<<BignumPairs[i][0]<<" - ";
		cout<<std::right<<setw(MaxBignumLength)<<BignumPairs[i][1]<<"=";
		result=CalculationClass->minus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<setw(MaxBignumLength)<<result<<endl;
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<setw(MaxBignumLength)<<result<<" + ";
		cout<<std::right<<setw(MaxBignumLength)<<BignumPairs[i][1]<<"=";
		CheckResult=CalculationClass->plus(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<setw(MaxBignumLength)<<CheckResult<<endl;
		if(IsNotEqual(CheckResult,strlen(CheckResult),BignumPairs[i][0],strlen(BignumPairs[i][0])))
		{
			cout<<"Incorrect result: operation MINUS\n";
			CountOfErrors++;
		}
		free(result);
		free(CheckResult);
		for(j=0; j<90; j++)
			cout<<'-';
		cout<<endl;
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<setw(MaxBignumLength)<<BignumPairs[i][0]<<" * ";
		cout<<std::right<<setw(MaxBignumLength)<<BignumPairs[i][1]<<"=";
		result=CalculationClass->multiply(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<setw(MaxBignumLength)<<result<<endl;
		if((BignumPairs[i][0][0]!='0' || strlen(BignumPairs[i][0])!=1) && (BignumPairs[i][1][0]!='0' || strlen(BignumPairs[i][1])!=1))
		{
			cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<setw(MaxBignumLength)<<result<<" / ";
			cout<<std::right<<setw(MaxBignumLength)<<BignumPairs[i][1]<<"=";
			CheckResult=CalculationClass->divide(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
			cout<<std::left<<setw(MaxBignumLength)<<CheckResult<<endl;
			if(IsNotEqual(CheckResult,strlen(CheckResult),BignumPairs[i][0],strlen(BignumPairs[i][0])))
			{
				cout<<"Incorrect result: operation MULTIPLY\n";
				CountOfErrors++;
			}
			free(CheckResult);
		}
		free(result);		
		for(j=0; j<90; j++)
			cout<<'-';
		cout<<endl;
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<setw(MaxBignumLength)<<BignumPairs[i][0]<<" / ";
		cout<<std::right<<setw(MaxBignumLength)<<BignumPairs[i][1]<<"=";
		result=CalculationClass->divide(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<setw(MaxBignumLength)<<result<<endl;
		if((BignumPairs[i][0][0]!='0' || strlen(BignumPairs[i][0])!=1) && (BignumPairs[i][1][0]!='0' || strlen(BignumPairs[i][1])!=1))
		{
			if (!IsDivisionConsistentOutputOn<BigNumClass>(BignumPairs[i][0],BignumPairs[i][1],result,MaxFractPartLength))
			{
				cout << "Incorrect result: operation DIVIDE\n";
				CountOfErrors++;
			}
		}
		free(result);
		for(j=0; j<90; j++)
			cout<<'=';
		cout<<endl;
	}
	delete CalculationClass;
	cout<<"Count of errors: "<<CountOfErrors<<endl;
}
template <typename BigNumClass> void TestOneBignumOperationWithCheck(char operation,char*** BignumPairs)
{	
	auto StartTime=chrono::system_clock::now();
	int i,j,CountOfErrors=0;
	char* result,*CheckResult;
	BigNumClass* CalculationClass=new BigNumClass();
	switch(operation)
	{
		case '+':
			cout<<"Testing operation PLUS with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass->plus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				CheckResult=CalculationClass->minus(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				if(IsNotEqual(CheckResult,strlen(CheckResult),BignumPairs[i][0],strlen(BignumPairs[i][0])))
					CountOfErrors++;
				free(result);
				free(CheckResult);
			}
			break;
		case '-':
			cout<<"Testing operation MINUS with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass->minus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				CheckResult=CalculationClass->plus(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				if(IsNotEqual(CheckResult,strlen(CheckResult),BignumPairs[i][0],strlen(BignumPairs[i][0])))
					CountOfErrors++;
				free(result);
				free(CheckResult);
			}
			break;
		case '*':
			cout<<"Testing operation MULTIPLY with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass->multiply(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				if((BignumPairs[i][0][0]!='0' || strlen(BignumPairs[i][0])!=1) && (BignumPairs[i][1][0]!='0' || strlen(BignumPairs[i][1])!=1))
				{
					CheckResult=CalculationClass->divide(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
					if(IsNotEqual(CheckResult,strlen(CheckResult),BignumPairs[i][0],strlen(BignumPairs[i][0])))
						CountOfErrors++;
					free(CheckResult);
				}
				free(result);
			}
			break;			
		case '/':
			cout<<"Testing operation DIVIDE with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass->divide(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				if((BignumPairs[i][0][0]!='0' || strlen(BignumPairs[i][0])!=1) && (BignumPairs[i][1][0]!='0' || strlen(BignumPairs[i][1])!=1))
				{					
					if(!IsDivisionConsistent<BigNumClass>(BignumPairs[i][0],BignumPairs[i][1],result,MaxFractPartLength))
						CountOfErrors++;
				}
				free(result);
			}
			break;
	}
	delete CalculationClass;
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Count of errors: "<<CountOfErrors<<" Time: "<<duration.count()<<" seconds\n";
}
template <typename BigNumClass> void TestOneBignumOperation(char operation,char*** BignumPairs)
{	
	int i;
	char* result;
	BigNumClass* CalculationClass=new BigNumClass();
	auto StartTime=chrono::system_clock::now();
	switch(operation)
	{
		case '+':
			cout<<"Testing operation PLUS...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass->plus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				free(result);
			}
			break;
		case '-':
			cout<<"Testing operation MINUS...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass->minus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				free(result);
			}
			break;
		case '*':
			cout<<"Testing operation MULTIPLY...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass->multiply(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				free(result);
			}
			break;
		case '/':
			cout<<"Testing operation DIVIDE...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass->divide(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				free(result);
			}
			break;
	}
	delete CalculationClass;
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" seconds\n";
}
char*** GetBignumPairs(int MinCountOfDigits,int MaxCountOfDigits,int CountOfRanges,int CountOfBignumPairs)
{
	cout<<"Creating "<<CountOfBignumPairs<<" random bignum pairs...";
	auto EndTime=chrono::system_clock::now();
	auto StartTime=chrono::system_clock::now();
	int i,j,k,CountOfLengths=MaxCountOfDigits-MinCountOfDigits;
	int* lengths=(int*)calloc(CountOfLengths,sizeof(int)); //new int[CountOfLengths];
	int* MinLengths=(int*)calloc(CountOfRanges,sizeof(int));//new int[CountOfRanges];
	int* MaxLengths=(int*)calloc(CountOfRanges,sizeof(int));//new int[CountOfRanges];
	char**temp2,*temp1,***BignumRanges=(char***)calloc(CountOfRanges,sizeof(char**));
	//new char**[CountOfRanges];
	char*** BignumPairs=(char***)calloc(CountOfBignumPairs,sizeof(char**));
	//new char**[CountOfBignumPairs];
	for(i=0,j=MinCountOfDigits; j<MaxCountOfDigits; i++,j++)
		lengths[i]=j;
	ShuffleArrayOfIntegers(lengths,CountOfLengths);
	for(i=0,j=0; i<CountOfRanges; i++,j++)
	{
		if(j==CountOfLengths)
			j=0;
		MinLengths[i]=lengths[j];
		MaxLengths[i]=lengths[j];
	}
	ShuffleArrayOfIntegers(MinLengths,CountOfRanges);
	ShuffleArrayOfIntegers(MaxLengths,CountOfRanges);
	for(i=0; i<CountOfRanges; i++)
	{
		BignumRanges[i]=(char**)calloc(2,sizeof(char*));
		BignumRanges[i][0]=GetRandomBignum(MinLengths[i],(bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));
		BignumRanges[i][1]=GetRandomBignum(MinLengths[i],(bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));
		if(IsGreater(BignumRanges[i][0],strlen(BignumRanges[i][0]),BignumRanges[i][1],strlen(BignumRanges[i][1])))
		{
			temp1=BignumRanges[i][0];
			BignumRanges[i][0]=BignumRanges[i][1];
			BignumRanges[i][1]=temp1;
		}
	}
	for(i=0,j=0; i<CountOfBignumPairs; i++,j++)
	{
		if(j==CountOfRanges)
		{
			for(j=0; j<CountOfRanges; j++)
			{
				k=rand()%CountOfRanges;
				temp2=BignumRanges[j];
				BignumRanges[j]=BignumRanges[k];
				BignumRanges[k]=temp2;
			}
			j=0;
			// cout<<"----------------------------------\n";
		}
		// cout<<setw(MaxCountOfDigits+2)<<BignumRanges[j][0]<<"  |	 "<<BignumRanges[j][1]<<endl;
		BignumPairs[i]=(char**)calloc(2,sizeof(char*));//new char*[2];
		BignumPairs[i][0]=GetRandomBignum(BignumRanges[j][0],BignumRanges[j][1]);
		BignumPairs[i][1]=GetRandomBignum(BignumRanges[j][0],BignumRanges[j][1]);
		// BignumPairs[i][0]=GetRandomBignum(GetRandomInt(2,5),0,1);
		// BignumPairs[i][1]=GetRandomBignum(GetRandomInt(2,5),1,1);
	}
	free(lengths);
	free(MinLengths);
	free(MaxLengths);
	for(i=0; i<CountOfRanges; i++)
	{
		free(BignumRanges[i][0]);
		free(BignumRanges[i][1]);
		free(BignumRanges[i]);
	}
	free(BignumRanges);
	EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" seconds\n";
	return BignumPairs;
}
void TestOneMpq_tBignumOperation(char operation,mpq_t*** Mpq_tBignumPairs)
{
	int i;
	mpq_t* result;
	auto StartTime=chrono::system_clock::now();
	switch(operation)
	{
		case '+':
			cout<<"Testing operation PLUS...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=(mpq_t*)malloc(sizeof(mpq_t));
				mpq_init(*result);
				mpq_add(*result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				mpq_clear(*result);
				free(result);
			}
			break;
		case '-':
			cout<<"Testing operation MINUS...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=(mpq_t*)malloc(sizeof(mpq_t));
				mpq_init(*result);
				mpq_sub(*result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				mpq_clear(*result);
				free(result);
			}
			break;
		case '*':
			cout<<"Testing operation MULTIPLY...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=(mpq_t*)malloc(sizeof(mpq_t));
				mpq_init(*result);
				mpq_mul(*result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				mpq_clear(*result);
				free(result);
			}
			break;
		case '/':
			cout<<"Testing operation DIVIDE...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				if(mpq_sgn(*Mpq_tBignumPairs[i][1]))
				{
					result=(mpq_t*)malloc(sizeof(mpq_t));
					mpq_init(*result);
					mpq_div(*result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
					mpq_clear(*result);
					free(result);
				}
			}
			break;
	}
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" seconds\n";
}
void TestOneMpq_tBignumOperationWithCheck(char operation,mpq_t*** Mpq_tBignumPairs)
{
	int i,CountOfErrors=0;
	char* ZeroStr=(char*)malloc(2*sizeof(char));
	ZeroStr[0]='0';
	ZeroStr[1]='\n';
	mpq_t* result,*CheckResult,*zero;
	zero=(mpq_t*)malloc(sizeof(mpq_t));
	mpq_init(*zero);
	decimal_str_to_mpq(ZeroStr,*zero);
	free(ZeroStr);
	auto StartTime=chrono::system_clock::now();
	switch(operation)
	{
		case '+':
			cout<<"Testing operation PLUS with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=(mpq_t*)malloc(sizeof(mpq_t));
				mpq_init(*result);
				mpq_add(*result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				CheckResult=(mpq_t*)malloc(sizeof(mpq_t));
				mpq_init(*CheckResult);
				mpq_sub(*CheckResult,*result,*Mpq_tBignumPairs[i][1]);
				if(!mpq_equal(*CheckResult,*Mpq_tBignumPairs[i][0]))
					CountOfErrors++;				
				mpq_clear(*result);
				free(result);
				mpq_clear(*CheckResult);
				free(CheckResult);
			}
			break;
		case '-':
			cout<<"Testing operation MINUS with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=(mpq_t*)malloc(sizeof(mpq_t));
				mpq_init(*result);
				mpq_sub(*result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				CheckResult=(mpq_t*)malloc(sizeof(mpq_t));
				mpq_init(*CheckResult);
				mpq_add(*CheckResult,*result,*Mpq_tBignumPairs[i][1]);
				if(!mpq_equal(*CheckResult,*Mpq_tBignumPairs[i][0]))
					CountOfErrors++;				
				mpq_clear(*result);
				free(result);
				mpq_clear(*CheckResult);
				free(CheckResult);
			}
			break;
		case '*':
			cout<<"Testing operation MULTIPLY with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=(mpq_t*)malloc(sizeof(mpq_t));
				mpq_init(*result);
				mpq_mul(*result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				CheckResult=(mpq_t*)malloc(sizeof(mpq_t));
				if(!mpq_equal(*zero,*result) && !mpq_equal(*zero,*Mpq_tBignumPairs[i][1]))
				{
					mpq_init(*CheckResult);
					mpq_div(*CheckResult,*result,*Mpq_tBignumPairs[i][1]);
					if(!mpq_equal(*CheckResult,*Mpq_tBignumPairs[i][0]))
						CountOfErrors++;
					mpq_clear(*CheckResult);
					free(CheckResult);
				}
				mpq_clear(*result);
				free(result);				
			}
			break;
		case '/':
			cout<<"Testing operation DIVIDE with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				if(mpq_sgn(*Mpq_tBignumPairs[i][1]))
				{
					result=(mpq_t*)malloc(sizeof(mpq_t));
					mpq_init(*result);
					mpq_div(*result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
					CheckResult=(mpq_t*)malloc(sizeof(mpq_t));
					if(!mpq_equal(*zero,*result) && !mpq_equal(*zero,*Mpq_tBignumPairs[i][1]))
					{
						mpq_init(*CheckResult);
						mpq_mul(*CheckResult,*result,*Mpq_tBignumPairs[i][1]);
						if(!mpq_equal(*CheckResult,*Mpq_tBignumPairs[i][0]))
							CountOfErrors++;
						mpq_clear(*CheckResult);
						free(CheckResult);
					}
					mpq_clear(*result);
					free(result);
				}
			}
			break;
	}
	free(zero);
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Count of errors: "<<CountOfErrors<<" Time: "<<duration.count()<<" seconds\n";
}
void TestMpq_tPower(char*** BignumPairs)
{
	int i,pow_result_length;
	char* ZeroStr=(char*)malloc(2*sizeof(char));
	ZeroStr[0]='0';
	ZeroStr[1]='\n';
	mpq_t*zero;
	zero=(mpq_t*)malloc(sizeof(mpq_t));
	mpq_init(*zero);
	decimal_str_to_mpq(ZeroStr,*zero);
	free(ZeroStr);
	FILE *file_with_results=fopen("power_results.txt", "w");
	for(i=0; i<CountOfBignumPairs; i++)
	{		
		mpq_t* pow_result=(mpq_t*)malloc(sizeof(mpq_t));
		mpq_init(*pow_result);		
		mpq_t* power_base=(mpq_t*)malloc(sizeof(mpq_t));
		mpq_t* power_exp=(mpq_t*)malloc(sizeof(mpq_t));
		mpq_init(*power_base);
		mpq_init(*power_exp);
		decimal_str_to_mpq(BignumPairs[i][0], *power_base);
		decimal_str_to_mpq(BignumPairs[i][1], *power_exp);
		cout<<i<<". base: "<<BignumPairs[i][0]<<"; exp: "<<BignumPairs[i][1]<<"...";
		power(*pow_result,*power_base,*power_exp);
		int is_valid=validate_power_comprehensive(*pow_result, *power_base, *power_exp, 1e-6);
		if(is_valid == 0)
			cout<<" Result is valid.\n";
		else
			cout<<" Result is NOT valid.\n";
		mpf_t mpf_t_power_exp;
		mpf_init2(mpf_t_power_exp, 256);
		mpf_set_q(mpf_t_power_exp, *pow_result);
		pow_result_length=gmp_snprintf(NULL, 0, "%.Ff", mpf_t_power_exp);
		char *pow_result_str=(char*)calloc(pow_result_length + 1,sizeof(char));
		gmp_snprintf(pow_result_str, pow_result_length + 1, "%.Ff", mpf_t_power_exp);
		fprintf(file_with_results, "%d. base: %s; exp: %s; result: %s\n", i, BignumPairs[i][0], BignumPairs[i][1],pow_result_str);
		fprintf(file_with_results, "------------------------------------------------------------\n");
		cout<<"-----------------------------------------------------------\n";
		mpq_clear(*power_base);
		mpq_clear(*power_exp);
		mpq_clear(*pow_result);
		free(power_base);
		free(power_exp);
		free(pow_result);
	}
	mpq_clear(*zero);
	free(zero);	
	fclose(file_with_results);
}
char* GetRandomArithmeticExpression(int OperationCount)
{
	if(OperationCount<=0)
		return GetRandomBignum(GetRandomInt(MinCountOfDigits, MaxCountOfDigits), (bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));
	char operators[]="+-*/";
	int i,TokensCount=OperationCount*2+1,partIndex=0;
	char** parts=(char**)malloc(TokensCount*sizeof(char*));
	for(i=0; i<=OperationCount; i++)
	{
		parts[partIndex++]=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),(bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));
		if(i<OperationCount)
		{
			char* op=(char*)malloc(4);
			op[0]=' ';
			op[1]=operators[rand()%(int)4];
			op[2]=' ';
			op[3]='\0';
			parts[partIndex++]=op;
		}		
	}
	int MaxPairs=TokensCount/4;
	int PairCount=rand()%(MaxPairs+1);
	for(i=0; i<PairCount; i++)
	{
		// Choose a valid left index (must be number token at even index)
		int LeftIndex=(rand()%((TokensCount+1)/2))*2;
		// Choose RightIndex at least two tokens away (number at even index)
		int MaxRight=((TokensCount-1)/2)*2;
		if(LeftIndex>=MaxRight)
			continue;
		int RightIndex=LeftIndex+2+(rand()%(((MaxRight-LeftIndex)/2)+1))*2;
		if(RightIndex>=TokensCount)
			continue;
		// Wrap left
		size_t lenL=strlen(parts[LeftIndex]);
		char* newL=(char*)malloc(lenL+2);
		sprintf(newL,"(%s",parts[LeftIndex]);
		free(parts[LeftIndex]);
		parts[LeftIndex]=newL;
		// Wrap right
		size_t lenR=strlen(parts[RightIndex]);
		char* newR=(char*)malloc(lenR+2);
		sprintf(newR, "%s)",parts[RightIndex]);
		free(parts[RightIndex]);
		parts[RightIndex]=newR;
	}
	int TotalLen=0;
	for(i=0; i<TokensCount; i++) 
		TotalLen+=strlen(parts[i]);
	char* expression=(char*)malloc(TotalLen);
	expression[0]='\0';
	for(i=0; i<TokensCount; i++)
	{
		strcat(expression, parts[i]);
		free(parts[i]);
	}
	free(parts);
	return expression;
}
typedef struct {
    long double *v;
    int top;
    int cap;
} NumStack;

typedef struct {
    char **v;
    int top;
    int cap;
} OpStack;

static NumStack *newNumStack(int cap) {
    NumStack *s = (NumStack*)malloc(sizeof(*s));
    s->v = (long double*)malloc(sizeof(long double) * cap);
    s->top = -1; s->cap = cap; return s;
}
static void pushNum(NumStack *s, long double x) { s->v[++s->top] = x; }
static long double popNum(NumStack *s) { return s->v[s->top--]; }
static bool emptyNum(NumStack *s) { return s->top < 0; }

static OpStack *newOpStack(int cap) {
    OpStack *s = (OpStack*)malloc(sizeof(*s));
    s->v = (char**)malloc(sizeof(char*) * cap);
    s->top = -1; s->cap = cap; return s;
}
static void pushOp(OpStack *s, const char *tok) {
    s->v[++s->top] = strdup(tok);
}
static char *popOp(OpStack *s) {
    char *r = s->v[s->top]; s->top--; return r;
}
static char *peekOp(OpStack *s) { return s->v[s->top]; }
static bool emptyOp(OpStack *s) { return s->top < 0; }

/* --- precedence / associativity --- */

static int precedence(const char *op) {
    switch (op[0]) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
    }
    return 0;
}
static bool rightAssoc(const char *op) { return op[0] == '^'; }
static bool isOpChar(char c) { return c=='+'||c=='-'||c=='*'||c=='/'||c=='^'; }

/* --- apply operator (uses long double) --- */

static void applyOp(NumStack *nums, const char *op) {
    if (nums->top < 1) {
        fprintf(stderr, "Error: insufficient operands for operator %s\n", op);
        exit(EXIT_FAILURE);
    }
    long double b = popNum(nums);
    long double a = popNum(nums);
    long double r = 0.0L;
    switch (op[0]) {
        case '+': r = a + b; break;
        case '-': r = a - b; break;
        case '*': r = a * b; break;
        case '/': r = (b != 0.0L) ? (a / b) : (a >= 0 ? INFINITY : -INFINITY); break;
        case '^': r = powl(a, b); break;
        default:
            fprintf(stderr, "Unknown operator: %s\n", op); exit(EXIT_FAILURE);
    }
    pushNum(nums, r);
}

/* --- tokenizer + evaluator (handles parentheses and unary minus) --- */

long double EvaluateExpression(const char *s) {
    /* We'll scan the string and emit tokens on the fly:
       tokens are: numbers (with optional leading sign), operators + - * / ^, parentheses */
    int n = (int)strlen(s);
    NumStack *nums = newNumStack(1024);
    OpStack *ops  = newOpStack(1024);

    int i = 0;
    /* previous token type:
       0 = start or operator or '('  => next '-' could be unary (part of number)
       1 = number or ')'             => next '-' is binary operator
    */
    int prev_type = 0;

    while (i < n) {
        if (isspace((unsigned char)s[i])) { i++; continue; }

        char c = s[i];

        if (c == '(') {
            pushOp(ops, "(");
            i++;
            prev_type = 0; /* after '(' a '-' is unary */
            continue;
        }

        if (c == ')') {
            /* pop until matching '(' */
            while (!emptyOp(ops) && strcmp(peekOp(ops), "(") != 0) {
                char *op = popOp(ops);
                applyOp(nums, op);
                free(op);
            }
            if (!emptyOp(ops) && strcmp(peekOp(ops), "(") == 0) {
                free(popOp(ops)); /* remove "(" */
            } else {
                fprintf(stderr, "Mismatched parentheses\n");
                exit(EXIT_FAILURE);
            }
            i++;
            prev_type = 1; /* ')' acts like a number */
            continue;
        }

        /* operator char (could be unary minus if prev_type==0 and next is digit/. ) */
        if (isOpChar(c)) {
            if (c == '-' && prev_type == 0) {
                /* unary minus: parse number starting with '-' */
                int j = i + 1;
                bool hasDigits = false;
                /* allow digits and decimal point */
                if (j < n && (isdigit((unsigned char)s[j]) || s[j] == '.')) {
                    while (j < n && (isdigit((unsigned char)s[j]) || s[j] == '.')) j++;
                    /* substring s[i..j-1] is the number including leading '-' */
                    int len = j - i;
                    char *numstr = (char*)malloc(len + 1);
                    memcpy(numstr, s + i, len);
                    numstr[len] = '\0';
                    long double val = strtold(numstr, NULL);
                    pushNum(nums, val);
                    free(numstr);
                    i = j;
                    prev_type = 1;
                    continue;
                } else {
                    /* isolated unary minus not followed by number (treat as 0 - ...):
                       fall-through to treat as binary '-' operator by inserting a zero */
                    pushNum(nums, 0.0L);
                    /* now treat '-' as binary operator below */
                }
            }

            /* binary operator handling: pop higher/equal precedence operators first */
            char op1[2] = { c, '\0' };
            while (!emptyOp(ops) && isOpChar(peekOp(ops)[0]) &&
                   ( precedence(peekOp(ops)) > precedence(op1) ||
                    ( precedence(peekOp(ops)) == precedence(op1) && !rightAssoc(op1) ) )) {
                char *op = popOp(ops);
                applyOp(nums, op);
                free(op);
            }
            pushOp(ops, op1);
            i++;
            prev_type = 0;
            continue;
        }

        /* number (positive) starting here */
        if (isdigit((unsigned char)c) || c == '.') {
            int j = i;
            while (j < n && (isdigit((unsigned char)s[j]) || s[j] == '.')) j++;
            int len = j - i;
            char *numstr = (char*)malloc(len + 1);
            memcpy(numstr, s + i, len);
            numstr[len] = '\0';
            long double val = strtold(numstr, NULL);
            pushNum(nums, val);
            free(numstr);
            i = j;
            prev_type = 1;
            continue;
        }

        /* unknown character */
        fprintf(stderr, "Unexpected character '%c' in expression\n", s[i]);
        exit(EXIT_FAILURE);
    }

    /* end: apply remaining operators */
    while (!emptyOp(ops)) {
        char *op = popOp(ops);
        if (strcmp(op, "(") == 0 || strcmp(op, ")") == 0) {
            fprintf(stderr, "Mismatched parentheses at end\n");
            exit(EXIT_FAILURE);
        }
        applyOp(nums, op);
        free(op);
    }

    if (nums->top != 0) {
        fprintf(stderr, "Malformed expression: values stack has %d elements\n", nums->top + 1);
        exit(EXIT_FAILURE);
    }

    long double result = popNum(nums);
    free(nums->v); free(nums);
    free(ops->v); free(ops);
    return result;
}
int main()
{
	InitFloatingPointAndRandomNumbers();
	int i,j;	
	char*** BignumPairs=GetBignumPairs(MinCountOfDigits,MaxCountOfDigits,CountOfRanges,CountOfBignumPairs);
	// TestAllBignumOperations<OptimizedBignum>(BignumPairs);	
	// TestAllBignumOperations<bignum>(BignumPairs);	
	
	// TestOneBignumOperationWithCheck<bignum>('+',BignumPairs);
	// TestOneBignumOperationWithCheck<bignum>('-',BignumPairs);
	// TestOneBignumOperationWithCheck<bignum>('*',BignumPairs);
	// TestOneBignumOperationWithCheck<bignum>('/',BignumPairs);
	// TestOneBignumOperationWithCheck<OptimizedBignum>('+',BignumPairs);
	// TestOneBignumOperationWithCheck<OptimizedBignum>('-',BignumPairs);
	// TestOneBignumOperationWithCheck<OptimizedBignum>('*',BignumPairs);
	// TestOneBignumOperationWithCheck<OptimizedBignum>('/',BignumPairs);
	
	// TestOneBignumOperation<bignum>('+',BignumPairs);
	// TestOneBignumOperation<bignum>('-',BignumPairs);
	// TestOneBignumOperation<bignum>('*',BignumPairs);
	// TestOneBignumOperation<bignum>('/',BignumPairs);	
	// TestOneBignumOperation<OptimizedBignum>('+',BignumPairs);
	// TestOneBignumOperation<OptimizedBignum>('-',BignumPairs);
	// TestOneBignumOperation<OptimizedBignum>('*',BignumPairs);
	// TestOneBignumOperation<OptimizedBignum>('/',BignumPairs);
	cout<<"Converting bignum pairs into mpq_t format...";
	auto StartTime=chrono::system_clock::now();
	mpq_t*** Mpq_tBignumPairs=(mpq_t***)malloc(CountOfBignumPairs*sizeof(mpq_t**));
	for(i=0; i<CountOfBignumPairs; i++)
	{
		Mpq_tBignumPairs[i]=(mpq_t**)malloc(2*sizeof(mpq_t*));
		Mpq_tBignumPairs[i][0]=(mpq_t*)malloc(sizeof(mpq_t));
		Mpq_tBignumPairs[i][1]=(mpq_t*)malloc(sizeof(mpq_t));
		mpq_init(*Mpq_tBignumPairs[i][0]);
		mpq_init(*Mpq_tBignumPairs[i][1]);
		decimal_str_to_mpq(BignumPairs[i][0], *Mpq_tBignumPairs[i][0]);
		decimal_str_to_mpq(BignumPairs[i][1], *Mpq_tBignumPairs[i][1]);
	}
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" seconds\n";
	// TestOneMpq_tBignumOperation('+',Mpq_tBignumPairs);
	// TestOneMpq_tBignumOperation('-',Mpq_tBignumPairs);
	// TestOneMpq_tBignumOperation('*',Mpq_tBignumPairs);
	// TestOneMpq_tBignumOperation('/',Mpq_tBignumPairs);	
	// TestOneMpq_tBignumOperationWithCheck('+',Mpq_tBignumPairs);
	// TestOneMpq_tBignumOperationWithCheck('-',Mpq_tBignumPairs);
	// TestOneMpq_tBignumOperationWithCheck('*',Mpq_tBignumPairs);
	// TestOneMpq_tBignumOperationWithCheck('/',Mpq_tBignumPairs);
	// TestMpq_tPower(BignumPairs);
	for(i=0; i<CountOfBignumPairs; i++)
	{
		free(BignumPairs[i][0]);
		free(BignumPairs[i][1]);
		free(BignumPairs[i]);
		mpq_clear(*Mpq_tBignumPairs[i][0]);
		mpq_clear(*Mpq_tBignumPairs[i][1]);
		free(Mpq_tBignumPairs[i][0]);
		free(Mpq_tBignumPairs[i][1]);
		free(Mpq_tBignumPairs[i]);
	}
	int CountOfOperations=5;
	char* RandomExpression=GetRandomArithmeticExpression(CountOfOperations);
	printf("Random Expression: %s\n", RandomExpression);
	long double RandomExpressionResult=EvaluateExpression(RandomExpression);
	cout<<"RandomExpressionResult: "<<RandomExpressionResult;
	free(BignumPairs);
	free(Mpq_tBignumPairs);
	cout<<"\ndone.";
	return 0;
}
