#include "bignum.h"
int CountOfBignumPairs,MinCountOfDigits,MaxCountOfDigits;
int MaxFractPartLength,MaxBignumLength,CountOfRanges=100,CountOfDivisionWarnings;
int CountOfExpressions=10,MinCountOfOperations=1,MaxCountOfOperations=10;
static char* normalize_positive_decimal(const char* s)
{
	if(!s)
	{
		char* result=(char*)malloc(2);
		if (!result) return NULL;
		result[0]='0'; result[1]='\0';
		return result;
	}
	// skip leading/trailing whitespace just in case (optional)
	// not strictly necessary if inputs are controlled
	while(*s && isspace((unsigned char)*s))
		++s;
	size_t n=strlen(s);
	// find dot
	const char* dot=strchr(s,'.');
	const char* int_start=s;
	const char* int_end=dot ? dot : s+n;
	const char* frac_start=dot ? dot+1 : NULL;
	const char* frac_end=dot ? s+n : NULL;
	// compute integer part after trimming leading zeros: [p .. int_end)
	const char* p=int_start;
	while (p<int_end && *p=='0')
		++p;
	int int_all_zero=(p==int_end);
	// trim trailing zeros in fraction
	if (frac_start) 
		while(frac_end > frac_start && *(frac_end-1)=='0')
			--frac_end;
	// estimate output length:
	size_t out_int_len=int_all_zero ? 1 : (size_t)(int_end-p);
	size_t out_frac_len=frac_start ? (size_t)(frac_end-frac_start) : 0;
	size_t out_len=out_int_len+(out_frac_len ? (1+out_frac_len) : 0);
	// allocate (out_len+1) bytes
	char* out=(char*)malloc(out_len+1);
	if(!out)
		return NULL;
	char* q=out;
	// integer part
	if (int_all_zero) 
		*q++='0';
	else
	{
		memcpy(q,p,out_int_len);
		q += out_int_len;
	}
	// fractional part,if any
	if(out_frac_len)
	{
		*q++='.';
		memcpy(q,frac_start,out_frac_len);
		q += out_frac_len;
	}
	*q='\0';
	// Guarantee at least "0" (shouldn't be needed but safe)
	if (out[0]=='\0')
	{
		out[0]='0';
		out[1]='\0';
	}
	return out;
}
static char* abs_normalized(const char* x)
{// Return a newly-allocated POSITIVE normalized copy of |x| (no sign).
	if(!x)
		return NULL;
	const char* p=(x[0]=='-' || x[0]=='+') ? x+1 : x;
	// char* norm=normalize_positive_decimal handles empty and dot cases
	char* result=normalize_positive_decimal(p);
	return result;
}
static int cmp_pos_dec(const char* a,const char* b)
{// Compare two POSITIVE normalized decimal strings by absolute value. // Return -1,0,1
	// Both must be normalized,positive,possibly with '.'.
	// Compare integer lengths first.
	const char* da=strchr(a,'.');
	const char* db=strchr(b,'.');
	size_t ai=da ? (size_t)(da-a) : strlen(a);
	size_t bi=db ? (size_t)(db-b) : strlen(b);
	if(ai != bi)
		return (ai<bi) ? -1 : 1;
	// Compare integer digits
	for (size_t i=0; i<ai; ++i)
		if(a[i]!=b[i])
			return (a[i]<b[i]) ? -1 : 1;	
	// Compare fractional digits
	const char* af=da ? da+1 : "";
	const char* bf=db ? db+1 : "";
	size_t alf=strlen(af);
	size_t blf=strlen(bf);
	size_t m=max(alf,blf);
	for (size_t i=0; i<m; ++i)
	{
		char ca=(i<alf)? af[i] : '0';
		char cb=(i<blf)? bf[i] : '0';
		if(ca!=cb)
			return (ca<cb) ? -1 : 1;
	}
	return 0;
}
char* shift_decimal_down(const char* A,int digits)
{
	// Shift decimal point of string A to the right by 'digits' places (i.e. divide by 10^digits)
	// Example: shift_decimal_down("12345",3) -> "12.345"
	// shift_decimal_down("123.45",2) -> "1.2345"
	// shift_decimal_down("0.00123",5) -> "0.0000123"
	
	if(!A)
		return nullptr;
	int len=(int)strlen(A);
	// Find existing decimal point (if any)
	const char* dot=strchr(A,'.');
	int intLen=dot ? (int)(dot-A) : len; // digits before decimal
	int fracLen=dot ? (len-intLen-1) : 0; // digits after decimal
	// New fractional length after shift
	int newFracLen=fracLen+digits;
	// Required length:
	// integer part+1 (possible '0')+1 (dot)+newFracLen+'\0'
	int newLen=intLen+1+newFracLen+1;
	char* out=(char*)malloc(newLen);
	FillArrayWithZeros(out,newLen);
	if(!out)
		return nullptr;
	char* p=out;
	// Copy integer part (or '0' if empty)
	if(intLen==0)
		*p++='0';
	else
	{
		memcpy(p,A,intLen);
		p += intLen;
	}
	// Add decimal point
	*p++='.';
	// Copy fractional digits (if any)
	if (fracLen > 0)
	{
		memcpy(p,dot+1,fracLen);
		p += fracLen;
	}
	// Add extra trailing zeros (digits shift)
	for (int i=0; i<digits; i++) 
		*p++='0';
	*p='\0';
	// Normalize: remove trailing zeros in fraction if not needed
	// but keep at least one digit after dot if there's a dot
	char* end=out+strlen(out)-1;
	while(end > out && *end=='0' && *(end-1) != '.')
		*end--='\0';
	return out;
}
char* PowerOf10(int n)
{
	char* res=(char*)malloc(n+4);
	FillArrayWithZeros(res,n+4);
	res[0]='1';
	for (int i=1; i <= n; i++)
		res[i]='0';
	res[n+1]='\0';
	return res;
}
template <typename BigNumClass> void ParseDecimalToFractionOutputOn(const char* str,char*& numerator,char*& denominator)
{
	// Parse Q (finite or periodic) into fraction num/den
	string s(str);
	BigNumClass CalculationClass;
	bool negative=false;
	if(!s.empty() && s[0]=='-')
	{
		negative=true;
		s=s.substr(1);
	}
	size_t dot=s.find('.');
	size_t lpar=s.find('(');
	size_t rpar=s.find(')');
	string A,B,C;
	if(dot==string::npos)
		A=s;
	else
	{
		A=s.substr(0,dot);
		if(lpar==string::npos)
			B=s.substr(dot+1);
		else
		{
			B=s.substr(dot+1,lpar-(dot+1));
			C=s.substr(lpar+1,rpar-lpar-1);
		}
	}
	if (C.empty())
	{
		// Finite decimal: numerator=int(AB),denominator=10^|B|
		string AB=A+B;
		if(AB.empty())
			AB="0";
		numerator=strdup(AB.c_str());
		denominator=PowerOf10((int)B.size());
	}
	else
	{
		// Repeating decimal
		string AB=A+B;
		string ABC=AB+C;
		char* bigABC=strdup(ABC.c_str());
		char* bigAB	=strdup(AB.c_str());
		// num=ABC-AB
		cout<<std::left<<bigABC<<"-";
		cout<<std::right<<bigAB<<"=";
		char* num=CalculationClass.minus(bigABC,(int)strlen(bigABC),bigAB,(int)strlen(bigAB));
		cout<<std::left<<num<<endl;
		char* powB=PowerOf10((int)B.size());
		char* powC=PowerOf10((int)C.size());
		char one[]="1";
		cout<<std::left<<powC<<"-";
		cout<<std::right<<one<<"=";
		char* powCminus1=CalculationClass.minus(powC,(int)strlen(powC),one,1);
		cout<<std::left<<powCminus1<<endl;		
		cout<<std::left<<powB<<"-";
		cout<<std::right<<powCminus1<<"=";
		char* denom=CalculationClass.multiply(powB,(int)strlen(powB),powCminus1,(int)strlen(powCminus1));
		cout<<std::left<<denom<<endl;
		numerator=num;
		denominator=denom;
		free(powB);
		free(powC);
		free(powCminus1);
		free(bigABC);
		free(bigAB);
	}
	if (negative && !(numerator[0]=='0' && numerator[1]=='\0'))
	{
		// prepend minus
		size_t L=strlen(numerator);
		char* signedNum=(char*)malloc(L+4);
		FillArrayWithZeros(signedNum,L+4);
		signedNum[0]='-';
		memcpy(signedNum+1,numerator,L+1);
		free(numerator);
		numerator=signedNum;
	}
}
template <typename BigNumClass> bool IsDivisionConsistentOutputOn(char* A,char* B,char* Q,int precisionDigits)
{
	BigNumClass CalculationClass;
	string s(Q);
	// Case 1: repeating decimal → exact rational check
	if(s[s.length()-1]==')') // if(s.find('(') != string::npos)
	{
		char* Qnum;
		char* Qden;
		ParseDecimalToFractionOutputOn<BigNumClass>(Q,Qnum,Qden);
		cout<<std::left<<Qnum<<" * ";
		cout<<std::right<<B<<"=";
		char* Left	= CalculationClass.multiply(Qnum,(int)strlen(Qnum),B,(int)strlen(B));
		cout<<std::left<<Left<<endl;		
		cout<<std::left<<Qden<<" * ";
		cout<<std::right<<A<<"=";
		char* Right=CalculationClass.multiply(Qden,(int)strlen(Qden),A,(int)strlen(A));
		cout<<std::left<<Right<<endl;
		bool ok=IsEqual(Left,(int)strlen(Left),Right,(int)strlen(Right));
		free(Qnum);
		free(Qden);
		free(Left);
		free(Right);
		;
		return ok;
	}
	/*cout<<std::left<<Q<<" * ";
	cout<<std::right<<B<<"=";
	char* Product=CalculationClass.multiply(Q,strlen(Q),B,strlen(B));
	cout<<std::left<<Product<<endl;	
	cout<<std::left<<Q<<"-";
	cout<<std::right<<B<<"=";
	char* Diff=CalculationClass.minus(A,strlen(A),Product,strlen(Product));
	cout<<std::left<<Diff<<endl;
	bool ok;
	if(Diff[0]!='-' && B[0]!='-')
		ok=(IsLess(Diff,strlen(Diff),B,strlen(B)));
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
		ok=(IsLess(Bignum1Abs,strlen(Bignum1Abs),Bignum2Abs,strlen(Bignum2Abs)));
	}
	free(Product);
	free(Diff);
	return ok;*/
	// 1) QB=Q * B
	cout<<std::left<<Q<<" * ";
	cout<<std::right<<B<<"=";
	char* QB=CalculationClass.multiply(Q,strlen(Q),B,strlen(B));
	cout<<std::left<<QB<<endl;
	// 2) Diff=QB-A
	cout<<std::left<<QB<<"-";
	cout<<std::right<<A<<"=";
	char* Diff=CalculationClass.minus(QB,strlen(QB),A,strlen(A));
	cout<<std::left<<Diff<<endl;
	// 3) abs(Diff)
	char* AbsDiff=abs_normalized(Diff);
	// 4) epsilon=max(|A|,|QB|) * 10^{-p},floor 10^{-p}
	char* AbsA	= abs_normalized(A);
	char* AbsQB=abs_normalized(QB);
	// Pick the larger magnitude between |A| and |QB|
	const char* baseline=(cmp_pos_dec(AbsA,AbsQB) >= 0) ? AbsA : AbsQB;
	// Build epsilon without multiply
	char* EpsFromBaseline=shift_decimal_down(baseline,precisionDigits);
	// Minimum epsilon=10^{-p}
	char* MinEps=NULL;
	{
		size_t cap=(precisionDigits>0? (size_t)precisionDigits+3 : 3);
		MinEps=(char*)malloc(cap);
		FillArrayWithZeros(MinEps,cap);
		if (precisionDigits<=0)
			strcpy(MinEps,"1");
		else
		{
			char* t=MinEps;
			*t++='0'; *t++='.';
			for (int i=1; i<precisionDigits; ++i) *t++='0';
			*t++='1'; *t='\0';
		}
	}
	char* Epsilon=NULL;
	if (cmp_pos_dec(EpsFromBaseline,MinEps) >= 0)
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
	bool ok=(cmp_pos_dec(AbsDiff,Epsilon) <= 0);
	free(QB);
	free(Diff);
	free(AbsDiff);
	free(AbsA);
	free(AbsQB);
	free(Epsilon);
	return ok;
}
template <typename BigNumClass> void ParseDecimalToFraction(const char* str,char*& numerator,char*& denominator)
{
	// Parse Q (finite or periodic) into fraction num/den
	string s(str);
	BigNumClass CalculationClass;
	bool negative=false;
	if(!s.empty() && s[0]=='-')
	{
		negative=true;
		s=s.substr(1);
	}
	size_t dot=s.find('.');
	size_t lpar=s.find('(');
	size_t rpar=s.find(')');
	string A,B,C;
	if (dot==string::npos)
		A=s;
	else
	{
		A=s.substr(0,dot);
		if (lpar==string::npos)
			B=s.substr(dot+1);
		else
		{
			B=s.substr(dot+1,lpar-(dot+1));
			C=s.substr(lpar+1,rpar-lpar-1);
		}
	}
	if (C.empty())
	{
		// Finite decimal: numerator=int(AB),denominator=10^|B|
		string AB=A+B;
		if(AB.empty())
			AB="0";
		numerator=strdup(AB.c_str());
		denominator=PowerOf10((int)B.size());
	}
	else
	{
		// Repeating decimal
		string AB=A+B;
		string ABC=AB+C;
		char* bigABC=strdup(ABC.c_str());
		char* bigAB	=strdup(AB.c_str());
		// num=ABC-AB
		char* num=CalculationClass.minus(bigABC,(int)strlen(bigABC),bigAB,(int)strlen(bigAB));
		char* powB=PowerOf10((int)B.size());
		char* powC=PowerOf10((int)C.size());
		char one[]="1";
		char* powCminus1=CalculationClass.minus(powC,(int)strlen(powC),one,1);
		char* denom=CalculationClass.multiply(powB,(int)strlen(powB),powCminus1,(int)strlen(powCminus1));
		numerator=num;
		denominator=denom;
		free(powB);
		free(powC);
		free(powCminus1);
		free(bigABC);
		free(bigAB);
	}
	if (negative && !(numerator[0]=='0' && numerator[1]=='\0'))
	{
		// prepend minus
		size_t L=strlen(numerator);
		char* signedNum=(char*)malloc(L+4);
		FillArrayWithZeros(signedNum,L+4);
		signedNum[0]='-';
		memcpy(signedNum+1,numerator,L+1);
		free(numerator);
		numerator=signedNum;
	}
}
template <typename BigNumClass> bool IsDivisionConsistent(char* A,char* B,char* Q,int precisionDigits)
{
	BigNumClass CalculationClass;
	string s(Q);
	// Case 1: repeating decimal → exact rational check
	if(s[s.length()-1]==')') // if(s.find('(') != string::npos)
	{
		char* Qnum;
		char* Qden;
		ParseDecimalToFraction<BigNumClass>(Q,Qnum,Qden);
		char* Left	= CalculationClass.multiply(Qnum,(int)strlen(Qnum),B,(int)strlen(B));
		char* Right=CalculationClass.multiply(Qden,(int)strlen(Qden),A,(int)strlen(A));
		bool ok=IsEqual(Left,(int)strlen(Left),Right,(int)strlen(Right));
		free(Qnum);
		free(Qden);
		free(Left);
		free(Right);
		;
		return ok;
	}
	/*char* Product=CalculationClass.multiply(Q,strlen(Q),B,strlen(B));
	char* Diff=CalculationClass.minus(A,strlen(A),Product,strlen(Product));
	bool ok;
	if(Diff[0]!='-' && B[0]!='-')
	{
		
		ok=(IsLess(Diff,strlen(Diff),B,strlen(B)));
	}
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
		
		ok=(IsLess(Bignum1Abs,strlen(Bignum1Abs),Bignum2Abs,strlen(Bignum2Abs)));
		
	}
	free(Product);
	free(Diff);
	return ok;*/
	// 1) QB=Q * B
	char* QB=CalculationClass.multiply(Q,strlen(Q),B,strlen(B));
	// 2) Diff=QB-A
	char* Diff=CalculationClass.minus(QB,strlen(QB),A,strlen(A));
	// 3) abs(Diff)
	char* AbsDiff=abs_normalized(Diff);
	// 4) epsilon=max(|A|,|QB|) * 10^{-p},floor 10^{-p}
	char* AbsA	= abs_normalized(A);
	char* AbsQB=abs_normalized(QB);
	// Pick the larger magnitude between |A| and |QB|
	const char* baseline=(cmp_pos_dec(AbsA,AbsQB) >= 0) ? AbsA : AbsQB;
	// Build epsilon without multiply
	char* EpsFromBaseline=shift_decimal_down(baseline,precisionDigits);
	// Minimum epsilon=10^{-p}
	char* MinEps=NULL;
	{
		size_t cap=(precisionDigits>0? (size_t)precisionDigits+3 : 3);
		MinEps=(char*)malloc(cap);
		FillArrayWithZeros(MinEps,cap);
		if (precisionDigits<=0)
			strcpy(MinEps,"1");
		else
		{
			char* t=MinEps;
			*t++='0'; *t++='.';
			for (int i=1; i<precisionDigits; ++i) *t++='0';
			*t++='1'; *t='\0';
		}
	}
	char* Epsilon=NULL;
	if (cmp_pos_dec(EpsFromBaseline,MinEps) >= 0)
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
	bool ok=(cmp_pos_dec(AbsDiff,Epsilon) <= 0);
	free(QB);
	free(Diff);
	free(AbsDiff);
	free(AbsA);
	free(AbsQB);
	free(Epsilon);
	return ok;
}
template <typename BigNumClass> void TestAllBignumOperations(char*** BignumPairs)
{
	BigNumClass CalculationClass;
	int i,j,CountOfErrors=0;
	char* result,*CheckResult;
	for(i=0; i<CountOfBignumPairs; i++)
	{
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<BignumPairs[i][0]<<"+";
		cout<<std::right<<BignumPairs[i][1]<<"=";
		result=CalculationClass.plus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<result<<endl;
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<result<<"-";
		cout<<std::right<<BignumPairs[i][1]<<"=";
		CheckResult=CalculationClass.minus(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<CheckResult<<endl;
		if(IsNotEqual(CheckResult,strlen(CheckResult),BignumPairs[i][0],strlen(BignumPairs[i][0])))
		{
			cout<<"Incorrect result: operation PLUS\n";
			CountOfErrors++;
			//my_getch();
		}
		free(result);
		free(CheckResult);
		for(j=0; j<90; j++)
			cout<<'-';
		cout<<endl;
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<BignumPairs[i][0]<<"-";
		cout<<std::right<<BignumPairs[i][1]<<"=";
		result=CalculationClass.minus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<result<<endl;
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<result<<"+";
		cout<<std::right<<BignumPairs[i][1]<<"=";
		CheckResult=CalculationClass.plus(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<CheckResult<<endl;
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
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<BignumPairs[i][0]<<" * ";
		cout<<std::right<<BignumPairs[i][1]<<"=";
		result=CalculationClass.multiply(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<result<<endl;
		if((BignumPairs[i][0][0]!='0' || strlen(BignumPairs[i][0])!=1) && (BignumPairs[i][1][0]!='0' || strlen(BignumPairs[i][1])!=1))
		{
			cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<result<<" / ";
			cout<<std::right<<BignumPairs[i][1]<<"=";
			CheckResult=CalculationClass.divide(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
			cout<<std::left<<CheckResult<<endl;
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
		cout<<std::right<<setw(3)<<i+1<<". "<<std::left<<BignumPairs[i][0]<<" / ";
		cout<<std::right<<BignumPairs[i][1]<<"=";
		result=CalculationClass.divide(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
		cout<<std::left<<result<<endl;
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
	cout<<"Count of errors: "<<CountOfErrors<<endl;
}
template <typename BigNumClass> void TestOneBignumOperationWithCheck(char operation,char*** BignumPairs)
{	
	auto StartTime=chrono::system_clock::now();
	int i,CountOfErrors=0;
	char* result,*CheckResult;
	BigNumClass CalculationClass;
	switch(operation)
	{
		case '+':
			cout<<"Testing operation PLUS with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass.plus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				CheckResult=CalculationClass.minus(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
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
				result=CalculationClass.minus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				CheckResult=CalculationClass.plus(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
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
				result=CalculationClass.multiply(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				if((BignumPairs[i][0][0]!='0' || strlen(BignumPairs[i][0])!=1) && (BignumPairs[i][1][0]!='0' || strlen(BignumPairs[i][1])!=1))
				{
					CheckResult=CalculationClass.divide(result,strlen(result),BignumPairs[i][1],strlen(BignumPairs[i][1]));
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
				result=CalculationClass.divide(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				if((BignumPairs[i][0][0]!='0' || strlen(BignumPairs[i][0])!=1) && (BignumPairs[i][1][0]!='0' || strlen(BignumPairs[i][1])!=1))
				{					
					if(!IsDivisionConsistent<BigNumClass>(BignumPairs[i][0],BignumPairs[i][1],result,MaxFractPartLength))
						CountOfErrors++;
				}
				free(result);
			}
			break;
	}
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Count of errors: "<<CountOfErrors<<". Time: "<<duration.count()<<" s.\n";
}
template <typename BigNumClass> void TestOneBignumOperation(char operation,char*** BignumPairs)
{	
	int i;
	char* result;
	BigNumClass CalculationClass;
	auto StartTime=chrono::system_clock::now();
	switch(operation)
	{
		case '+':
			cout<<"Testing operation PLUS...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass.plus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				free(result);
			}
			break;
		case '-':
			cout<<"Testing operation MINUS...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass.minus(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				free(result);
			}
			break;
		case '*':
			cout<<"Testing operation MULTIPLY...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass.multiply(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				free(result);
			}
			break;
		case '/':
			cout<<"Testing operation DIVIDE...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				result=CalculationClass.divide(BignumPairs[i][0],strlen(BignumPairs[i][0]),BignumPairs[i][1],strlen(BignumPairs[i][1]));
				free(result);
			}
			break;
	}
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" s.\n";
}
char*** GetBignumPairs()
{
	cout<<"Creating "<<CountOfBignumPairs<<" random bignum pairs...";
	auto EndTime=chrono::system_clock::now();
	auto StartTime=chrono::system_clock::now();
	int i,j,k,CountOfLengths=MaxCountOfDigits-MinCountOfDigits;
	int* lengths=(int*)malloc(sizeof(int)*CountOfLengths);
	int* MinLengths=(int*)malloc(sizeof(int)*CountOfRanges);
	int* MaxLengths=(int*)malloc(sizeof(int)*CountOfRanges);
	char** temp2,*temp1,***BignumRanges=(char***)malloc(sizeof(char**)*CountOfRanges);
	char*** BignumPairs=(char***)malloc(sizeof(char**)*CountOfBignumPairs);
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
		BignumRanges[i]=(char**)malloc(sizeof(char*)*2);
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
		}
		BignumPairs[i]=(char**)malloc(sizeof(char*)*2);
		// BignumPairs[i][0]=GetRandomBignum(BignumRanges[j][0],BignumRanges[j][1]);
		// BignumPairs[i][1]=GetRandomBignum(BignumRanges[j][0],BignumRanges[j][1]);
		BignumPairs[i][0]=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),(bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));
		BignumPairs[i][1]=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),(bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));

		// BignumPairs[i][0]=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),0,(bool)GetRandomInt(0,2));
		// BignumPairs[i][1]=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),0,(bool)GetRandomInt(0,2));
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
	cout<<" Time: "<<duration.count()<<" s.\n";
	return BignumPairs;
}
void TestOneMpq_tBignumOperation(char operation,mpq_t*** Mpq_tBignumPairs)
{
	int i;
	mpq_t result;
	auto StartTime=chrono::system_clock::now();
	switch(operation)
	{
		case '+':
			cout<<"Testing operation PLUS...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				mpq_init(result);
				mpq_add(result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				mpq_clear(result);
			}
			break;
		case '-':
			cout<<"Testing operation MINUS...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				mpq_init(result);
				mpq_sub(result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				mpq_clear(result);
			}
			break;
		case '*':
			cout<<"Testing operation MULTIPLY...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				mpq_init(result);
				mpq_mul(result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				mpq_clear(result);
			}
			break;
		case '/':
			cout<<"Testing operation DIVIDE...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				if(mpq_sgn(*Mpq_tBignumPairs[i][1]))
				{
					mpq_init(result);
					mpq_div(result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
					mpq_clear(result);
				}
			}
			break;
	}
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" s.\n";
}
void TestOneMpq_tBignumOperationWithCheck(char operation,mpq_t*** Mpq_tBignumPairs)
{
	int i,CountOfErrors=0;
	char* ZeroStr=(char*)malloc(2);
	ZeroStr[0]='0';
	ZeroStr[1]='\0';
	mpq_t result,CheckResult,zero;
	decimal_str_to_mpq(ZeroStr,zero);
	free(ZeroStr);
	auto StartTime=chrono::system_clock::now();
	switch(operation)
	{
		case '+':
			cout<<"Testing operation PLUS with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				mpq_init(result);
				mpq_add(result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				mpq_init(CheckResult);
				mpq_sub(CheckResult,result,*Mpq_tBignumPairs[i][1]);
				if(!mpq_equal(CheckResult,*Mpq_tBignumPairs[i][0]))
					CountOfErrors++;				
				mpq_clear(result);
				mpq_clear(CheckResult);
			}
			break;
		case '-':
			cout<<"Testing operation MINUS with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{				
				mpq_init(result);
				mpq_sub(result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				mpq_init(CheckResult);
				mpq_add(CheckResult,result,*Mpq_tBignumPairs[i][1]);
				if(!mpq_equal(CheckResult,*Mpq_tBignumPairs[i][0]))
					CountOfErrors++;				
				mpq_clear(result);
				mpq_clear(CheckResult);
			}
			break;
		case '*':
			cout<<"Testing operation MULTIPLY with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{				
				mpq_init(result);
				mpq_mul(result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
				if(!mpq_equal(zero,result) && !mpq_equal(zero,*Mpq_tBignumPairs[i][1]))
				{
					mpq_init(CheckResult);
					mpq_div(CheckResult,result,*Mpq_tBignumPairs[i][1]);
					if(!mpq_equal(CheckResult,*Mpq_tBignumPairs[i][0]))
						CountOfErrors++;
					mpq_clear(CheckResult);
				}
				mpq_clear(result);
			}
			break;
		case '/':
			cout<<"Testing operation DIVIDE with check...";
			for(i=0; i<CountOfBignumPairs; i++)
			{
				if(mpq_sgn(*Mpq_tBignumPairs[i][1]))
				{					
					mpq_init(result);
					mpq_div(result,*Mpq_tBignumPairs[i][0],*Mpq_tBignumPairs[i][1]);
					if(!mpq_equal(zero,result) && !mpq_equal(zero,*Mpq_tBignumPairs[i][1]))
					{
						mpq_init(CheckResult);
						mpq_mul(CheckResult,result,*Mpq_tBignumPairs[i][1]);
						if(!mpq_equal(CheckResult,*Mpq_tBignumPairs[i][0]))
							CountOfErrors++;
						mpq_clear(CheckResult);
					}
					mpq_clear(result);
				}
			}
			break;
	}
	mpq_clear(zero);
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Count of errors: "<<CountOfErrors<<". Time: "<<duration.count()<<" s.\n";
}
void TestMpq_tPower()
{
	cout<<"Testing power calculations...";
	auto StartTime=chrono::system_clock::now();
	int i,j,pow_result_length,is_valid;
	char* ZeroStr=(char*)malloc(2);
	char* base,*exp,*pow_result_str;
	ZeroStr[0]='0';
	ZeroStr[1]='\0';
	mpq_t zero,power_base,power_exp,pow_result;
	decimal_str_to_mpq(ZeroStr,zero);
	free(ZeroStr);
	FILE *file_with_results=fopen("power_results.txt","w");
	for(i=0; i<CountOfBignumPairs; i++)
	{
		mpq_init(pow_result);
		// base=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),(bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));
		// exp=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),(bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));
		base=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),0,0);
		exp=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),0,0);

		decimal_str_to_mpq(base,power_base);
		decimal_str_to_mpq(exp,power_exp);
		// cout<<i+1<<". base: "<<base<<"; exp: "<<exp<<"...";
		power(pow_result,power_base,power_exp);
		is_valid=validate_power_comprehensive(pow_result,power_base,power_exp,1e-6);
		// if(is_valid==0)
			// cout<<" Result is valid:\n";
		// else
			// cout<<" Result is NOT valid:\n";
		mpf_t mpf_t_power_exp;
		mpf_init2(mpf_t_power_exp,256);
		mpf_set_q(mpf_t_power_exp,pow_result);
		pow_result_length=gmp_snprintf(NULL,0,"%.Ff",mpf_t_power_exp);
		pow_result_str=(char*)malloc(pow_result_length+1);
		gmp_snprintf(pow_result_str,pow_result_length+1,"%.Ff",mpf_t_power_exp);
		pow_result_str[pow_result_length]='\0';
		// if(pow_result_length<90)
			// cout<<pow_result_str<<endl;
		// else
		// {
			// for(j=0; j<87; j++)
				// cout<<pow_result_str[j];
			// cout<<"...\n";
		// }
		fprintf(file_with_results,"%d. base: %s; exp: %s; result: %s\n",i,base,exp,pow_result_str);
		if(is_valid==0)
			fprintf(file_with_results,"Result is valid:\n");
		else
			fprintf(file_with_results,"Result is NOT valid:\n");
		fprintf(file_with_results,"------------------------------------------------------------\n");
		// cout<<"-----------------------------------------------------------\n";
		mpq_clear(power_base);
		mpq_clear(power_exp);
		mpq_clear(pow_result);
		mpf_clear(mpf_t_power_exp);
		free(base);
		free(exp);
		free(pow_result_str);
	}
	mpq_clear(zero);
	fclose(file_with_results);
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" s.\n";
	cout<<"The file power_results.txt was created.\n";
}
char* GetRandomExpression(int CountOfOperations)
{
	if(CountOfOperations<=0)
		return GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),(bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));
	char operators[]="+-*/",CountOfOperators=4;
	// if(MinCountOfDigits<1001 && MaxCountOfDigits<10001)
		// CountOfOperators=2;
	int i,TokensCount=CountOfOperations*2+1,partIndex=0;
	char** parts=(char**)malloc(sizeof(char*)*TokensCount);
	for(i=0; i<CountOfOperations; i++)
	{
		parts[partIndex++]=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),(bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));
		char* op=(char*)malloc(4);
		op[0]=' ';
		op[1]=operators[rand()%(int)4];
		op[2]=' ';
		op[3]='\0';
		parts[partIndex++]=op;				
	}
	parts[partIndex++]=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),(bool)GetRandomInt(0,2),(bool)GetRandomInt(0,2));
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
		sprintf(newR,"%s)",parts[RightIndex]);
		free(parts[RightIndex]);
		parts[RightIndex]=newR;
	}
	int TotalLength=0;
	for(i=0; i<TokensCount; i++)
		TotalLength+=strlen(parts[i]);
	char* expression=(char*)malloc(TotalLength+1);
	expression[0]='\0';
	for(i=0; i<TokensCount; i++)
	{
		strcat(expression,parts[i]);
		free(parts[i]);
	}
	free(parts);
	return expression;
}
char* GetRandomExpressionFromBignumPairs(char*** BignumPairs)
{
	cout<<"Creating an expression from "<<CountOfBignumPairs<<" bignum pairs...";
	auto StartTime=chrono::system_clock::now();
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	const char operators[]="+-*/";//CountOfOperators=4;
	int CountOfOperators = sizeof(operators)-1;
	if(MinCountOfDigits<1001 && MaxCountOfDigits<10001)
		CountOfOperators=2;
	for(int k=0;k<CountOfBignumPairs;k++)
	{
		if(!BignumPairs[k] || !BignumPairs[k][0] || !BignumPairs[k][1])
		{
			printf("Invalid BignumPairs[%d]\n",k);
			exit(1);
		}

		if(strlen(BignumPairs[k][0])==0 || strlen(BignumPairs[k][1])==0)
		{
			printf("Empty bignum detected\n");
			exit(1);
		}
	}
	size_t CountOfOperations=CountOfBignumPairs*2-1;
	size_t i,TokensCount=CountOfOperations*2+1,partIndex=0;
	char** parts=(char**)malloc(TokensCount*sizeof(char*));
	int* OpenBrackets=(int*)calloc(TokensCount,sizeof(int));
	int* ClosedBrackets=(int*)calloc(TokensCount,sizeof(int));
	for(i=0; i<CountOfOperations; i++)
	{
		parts[partIndex++]=*(*(BignumPairs+i/2)+i%2);
		parts[partIndex]=(char*)malloc(4);
		parts[partIndex][0]=' ';
		parts[partIndex][1]=operators[rand()%CountOfOperators];
		parts[partIndex][2]=' ';
		parts[partIndex++][3]='\0';
	}
	parts[partIndex]=*(*(BignumPairs+i/2)+i%2);
	int MaxPairs=TokensCount/4,LeftIndex,RightIndex,MaxRight;
	int PairCount=rand()%(MaxPairs+1),idx=0;
	for(i=0; i<PairCount; i++)
	{
		// Choose a valid left index (must be number token at even index)
		LeftIndex=(rand()%((TokensCount+1)/2))*2;
		// Choose RightIndex at least two tokens away (number at even index)
		MaxRight=((TokensCount-1)/2)*2;
		if(LeftIndex>=MaxRight)
			continue;
		RightIndex=LeftIndex+2+(rand()%(((MaxRight-LeftIndex)/2)+1))*2;
		if(RightIndex>=TokensCount)
			continue;
		OpenBrackets[LeftIndex]++;
		ClosedBrackets[RightIndex]++;
	}
	int TotalLength=0,j;
	for(i=0; i<TokensCount; i++)
		TotalLength+=strlen(parts[i]);
	char* expression=(char*)malloc(TotalLength+(PairCount*2)+1);
	char* p=expression;
	for(i=0; i<TokensCount; i++)
	{
		for(j=0; j<OpenBrackets[i]; j++)
			*p++='(';
		TotalLength=strlen(parts[i]);
		memcpy(p,parts[i],TotalLength);
		p += TotalLength;
		for(j=0; j<ClosedBrackets[i]; j++)
			*p++=')';
	}
	*p='\0';
	for(i=1; i<TokensCount; i+=2)
		free(parts[i]);
	free(parts);
	free(OpenBrackets);
	free(ClosedBrackets);
	EndTime=chrono::system_clock::now();
	duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" s.\n";
	return expression;
}
template <typename BigNumClass> static char* ApplyOperation_OutputOn(char *bignum1,char *bignum2,char *operation)
{	
	BigNumClass CalculationClass;
	int i,j;
	char* result,*CheckResult;
	cout<<bignum1<<" "<<operation[0]<<" "<<bignum2<<"=";
	switch (operation[0])
	{
		case '+':
			result=CalculationClass.plus(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			cout<<result<<endl<<result<<"-"<<bignum2<<"=";
			CheckResult=CalculationClass.minus(result,strlen(result),bignum2,strlen(bignum2));
			cout<<CheckResult<<endl;
			if(IsNotEqual(CheckResult,strlen(CheckResult),bignum1,strlen(bignum1)))
			{
				cout<<"Calculation error: operation PLUS!\n";
				cout<<bignum2<<" "<<operation[0]<<" "<<bignum1<<"="<<result<<endl;
				cout<<result<<"-"<<bignum1<<"="<<CheckResult;
				//my_getch();
			}
			free(CheckResult);
		break;
		case '-':
			result=CalculationClass.minus(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			cout<<result<<endl<<result<<"+"<<bignum2<<"=";
			CheckResult=CalculationClass.plus(result,strlen(result),bignum2,strlen(bignum2));
			cout<<CheckResult<<endl;
			if(IsNotEqual(CheckResult,strlen(CheckResult),bignum1,strlen(bignum1)))
			{
				cout<<"Calculation error: operation MINUS!\n";
				cout<<bignum2<<" "<<operation[0]<<" "<<bignum1<<"="<<result<<endl;;
				cout<<result<<"+"<<bignum1<<"="<<CheckResult;
				//my_getch();
			}
			free(CheckResult);
		break;
		case '*':
			result=CalculationClass.multiply(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			cout<<result<<endl;
			if((bignum1[0]!='0' || strlen(bignum1)!=1) && (bignum2[0]!='0' || strlen(bignum2)!=1))
			{
				CheckResult=CalculationClass.divide(result,strlen(result),bignum2,strlen(bignum2));
				if(IsNotEqual(CheckResult,strlen(CheckResult),bignum1,strlen(bignum1)))
				{
					cout<<"Calculation error: operation MULTIPLY!\n";
					cout<<bignum1<<" "<<operation[0]<<" "<<bignum2<<"="<<result<<endl;
					cout<<result<<" / "<<bignum2<<"="<<CheckResult;
				}
				free(CheckResult);
			}
		break;
		case '/':
			result=CalculationClass.divide(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			cout<<result<<endl;
			if((bignum1[0]!='0' || strlen(bignum1)!=1) && (bignum2[0]!='0' || strlen(bignum2)!=1))
			{				
				if(!IsDivisionConsistentOutputOn<BigNumClass>(bignum1,bignum2,result,MaxFractPartLength))
				{
					cout<<"Calculation warning: operation DIVIDE!\n";
					cout<<bignum1<<" "<<operation[0]<<" "<<bignum2<<" != "<<result<<endl;
					CountOfDivisionWarnings++;
					//my_getch();
				}
				for(i=0; i<strlen(result); i++)
					if(result[i]=='(')
					{
						for(j=i+1; result[j]!=')'; j++)
							result[j-1]=result[j];
						for(j++; j<strlen(result); j++)
							result[j-1]=result[j];
						result[j-2]='\0';
						int ResultLength=strlen(result);
						for(i=ResultLength-1; result[i]=='0'; i--,ResultLength--);
						result[ResultLength]='\0';
					}
			}
		break;
		default: fprintf(stderr,"Unknown operator: %s\n",operation); //my_getch();//exit(0);
	}
	cout<<"---------------------------------------------\n";
	return result;
}
template <typename BigNumClass> static char* ApplyOperation_OutputOff(char *bignum1,char *bignum2,char *operation)
{
	BigNumClass CalculationClass;
	int i,j;
	char* result,*CheckResult;
	switch (operation[0])
	{
		case '+':
			result=CalculationClass.plus(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			CheckResult=CalculationClass.minus(result,strlen(result),bignum2,strlen(bignum2));
			if(IsNotEqual(CheckResult,strlen(CheckResult),bignum1,strlen(bignum1)))
			{
				// cout<<"\nCalculation error: operation PLUS!\n";
				//my_getch();
				//exit(0);
			}
			free(CheckResult);
		break;
		case '-':
			result=CalculationClass.minus(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			CheckResult=CalculationClass.plus(result,strlen(result),bignum2,strlen(bignum2));
			if(IsNotEqual(CheckResult,strlen(CheckResult),bignum1,strlen(bignum1)))
			{
				// cout<<"\nCalculation error: operation MINUS!\n";
				//my_getch();
				//exit(0);
			}
			free(CheckResult);
		break;
		case '*':
			result=CalculationClass.multiply(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			if((bignum2[0]!='0' || strlen(bignum2)!=1) && (bignum1[0]!='0' || strlen(bignum1)!=1))
			{
				CheckResult=CalculationClass.divide(result,strlen(result),bignum2,strlen(bignum2));
				if(IsNotEqual(CheckResult,strlen(CheckResult),bignum1,strlen(bignum1)))
				{
					// cout<<"\nCalculation error: operation MULTIPLY!\n";
					// //my_getch();
				}
				free(CheckResult);
			}
			
		break;
		case '/':
			result=CalculationClass.divide(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			if((bignum1[0]!='0' || strlen(bignum1)!=1) && (bignum2[0]!='0' || strlen(bignum2)!=1))
			{				
				if(!IsDivisionConsistent<BigNumClass>(bignum1,bignum2,result,MaxFractPartLength))
					CountOfDivisionWarnings++;
				for(i=0; i<strlen(result); i++)
					if(result[i]=='(')
					{
						for(j=i+1; result[j]!=')'; j++)
							result[j-1]=result[j];
						for(j++; j<strlen(result); j++)
							result[j-1]=result[j];
						result[j-2]='\0';
						int ResultLength=strlen(result);
						for(i=ResultLength-1; result[i]=='0'; i--,ResultLength--);
						result[ResultLength]='\0';
					}
			}
		break;
		default: fprintf(stderr,"Unknown operator: %s\n",operation); //my_getch();//exit(0);
	}
	return result;
}
template <typename BigNumClass,typename ResultType> ResultType CalculateExpression(const char *expr,char* ApplyOperation(char *bignum1,char *bignum2,char *operation))
{
	typedef struct
	{
		char** v;
		int top;
		int size;
	}StrStack;
	int ExpressionLength=strlen(expr),i=0,prev_type=0,StrLen,j;
	char c,Op1Precedence,StackOpPrecedence;
	StrStack *nums=(StrStack*)malloc(sizeof(StrStack));
	nums->v=(char**)calloc(ExpressionLength,sizeof(char*));
	nums->top=-1;
	nums->size=0;
	StrStack *ops=(StrStack*)malloc(sizeof(StrStack));
	ops->v=(char**)calloc(ExpressionLength,sizeof(char*));
	ops->top=-1;
	ops->size=0;
	while (i<ExpressionLength)
	{
		if(isspace((unsigned char)expr[i]))
		{
			i++;
			continue;
		}
		c=expr[i];
		if(c=='(')
		{
			ops->v[++ops->top]=(char*)malloc(2);
			ops->v[ops->top][0]='(';
			ops->v[ops->top][1]='\0';
			i++;
			prev_type=0;
			continue;
		}
		if(c==')')
		{
			while(ops->top>-1 && strcmp(ops->v[ops->top],"(") != 0)
			{
				char* op=ops->v[ops->top];
				ops->v[ops->top--]=NULL;
				char* right=nums->v[nums->top];
				nums->v[nums->top--]=NULL;
				char* left=nums->v[nums->top];
				nums->v[nums->top--]=NULL;
				nums->v[++nums->top]=ApplyOperation(left,right,op);
				free(op);
				free(left);
				free(right);
			}
			if(ops->top>-1 && strcmp(ops->v[ops->top],"(")==0)
			{
				free(ops->v[ops->top]);
				ops->v[ops->top--]=NULL;
			}
			else
			{
				cout<<"EXPRESSION RESULT=NULL!!!\n";
				my_getch();
				exit(0);
			}
			i++;
			prev_type=1;
			continue;
		}
		if(c=='+' || c=='-' || c=='*' || c=='/')
		{
			if(c=='-' && prev_type==0)
			{
				j=i+1;
				if(j<ExpressionLength && (isdigit((unsigned char)expr[j]) || expr[j]=='.'))
				{
					while(j<ExpressionLength && (isdigit((unsigned char)expr[j]) || expr[j]=='.'))
						j++;
					StrLen=j-i;
					char *num=(char*)malloc(StrLen+1);
					memcpy(num,expr+i,(size_t)StrLen);
					num[StrLen]='\0';
					nums->v[++nums->top]=num;
					i=j; prev_type=1;
					continue;
				}
				else
				{
					ops->v[++ops->top]=(char*)malloc(2);
					ops->v[ops->top][0]='0';
					ops->v[ops->top][1]='\0';
				}
			}
			char op1[2]={c,'\0'};
			Op1Precedence=0;
			switch (op1[0])
			{
				case '+': case '-': Op1Precedence=1; break;
				case '*': case '/': Op1Precedence=2; break;
			}			
			if(ops->top>-1)				
				switch(ops->v[ops->top][0])
				{
					case '+': case '-': StackOpPrecedence=1; break;
					case '*': case '/': StackOpPrecedence=2; break;
					default: StackOpPrecedence = 0;
				}
			while(ops->top>-1 && (ops->v[ops->top][0]=='+' || ops->v[ops->top][0]=='-' || ops->v[ops->top][0]=='*' || ops->v[ops->top][0]=='/') && ( StackOpPrecedence > Op1Precedence || (StackOpPrecedence==Op1Precedence)))
			{
				char* op=ops->v[ops->top];
				ops->v[ops->top--]=NULL;
				char* right=nums->v[nums->top];
				nums->v[nums->top--]=NULL;
				char* left=nums->v[nums->top];
				nums->v[nums->top--]=NULL;
				nums->v[++nums->top]=ApplyOperation(left,right,op);
				free(op);
				free(left);
				free(right);
				if(ops->top>-1)				
					switch(ops->v[ops->top][0])
					{
						case '+': case '-': StackOpPrecedence=1; break;
						case '*': case '/': StackOpPrecedence=2; break;
						default: StackOpPrecedence = 0;
					}
			}
			ops->v[++ops->top]=(char*)malloc(2);
			ops->v[ops->top][0]=c;
			ops->v[ops->top][1]='\0';
			i++;
			prev_type=0;
			continue;
		}
		if(isdigit((unsigned char)c) || c=='.')
		{
			j=i;
			while(j<ExpressionLength && (isdigit((unsigned char)expr[j]) || expr[j]=='.'))
				j++;
			StrLen=j-i;
			char *num=(char*)malloc(StrLen+1);
			memcpy(num,expr+i,(size_t)StrLen);
			num[StrLen]='\0';
			nums->v[++nums->top]=num;
			i=j;
			prev_type=1;
			continue;
		}
		cout<<"EXPRESSION RESULT=NULL!!!\n";
		my_getch();
		exit(0);
	}
	while(ops->top>-1)
	{
		char* op=ops->v[ops->top];
		ops->v[ops->top--]=NULL;
		char* right=nums->v[nums->top];
		nums->v[nums->top--]=NULL;
		char* left=nums->v[nums->top];
		nums->v[nums->top--]=NULL;
		if(strcmp(op,"(")==0 || strcmp(op,")")==0)
		{
			cout<<"EXPRESSION RESULT=NULL!!!\n";
			my_getch();
			exit(0);
		}
		nums->v[++nums->top]=ApplyOperation(left,right,op);
		free(op);
		free(left);
		free(right);
	}
	if(nums->top != 0)
	{
		cout<<"EXPRESSION RESULT=NULL!!!\n";
		my_getch();
		exit(0);
	}
	char* result=nums->v[nums->top];
	nums->v[nums->top--]=NULL;
	for(i=0; i<=nums->top; i++)
		if(nums->v[i])
		{
			free(nums->v[i]);
			nums->v[i]=NULL;
		}
	free(nums->v);
	free(nums);
	for(i=0; i<=ops->top; i++)
		if(ops->v[i])
		{
			free(ops->v[i]);
			ops->v[i]=NULL;
		}
	free(ops->v);
	free(ops);
	return result;
}
// int precedence(const char* op)
// {
	// if(op[0]=='+' || op[0]=='-') return 1;
	// if(op[0]=='*' || op[0]=='/') return 2;
	// return 0;
// }
// char* EvaluateTokens(char** tokens,int count,char* ApplyOperation(char*,char*,char*))
// {
	// char** nums=(char**)malloc(sizeof(char*)*count);
	// char** ops =(char**)malloc(sizeof(char*)*count);
	// int ntop=-1;
	// int otop=-1;
	// for(int i=0;i<count;i++)
	// {
		// char* t=tokens[i];
		// // number
		// if(isdigit(t[0]) || t[0]=='.' || ((t[0]=='-'||t[0]=='+') && (isdigit(t[1])||t[1]=='.')))
		// {
			// nums[++ntop]=strdup(t);
			// continue;
		// }
		// if(t[0]=='(')
		// {
			// ops[++otop]=t;
			// continue;
		// }
		// if(t[0]==')')
		// {
			// while(otop>=0 && ops[otop][0]!='(')
			// {
				// char* op=ops[otop--];
				// char* r=nums[ntop--];
				// char* l=nums[ntop--];
				// nums[++ntop]=ApplyOperation(l,r,op);
				// free(l);
				// free(r);
			// }
			// otop--; // pop '('
			// continue;
		// }
		// // operator
		// while(otop>=0 && ops[otop][0] != '(' && precedence(ops[otop]) >= precedence(t))
		// {
			// char* op=ops[otop--];
			// if(ntop < 1)
			// {
				// printf("Stack underflow\n");
				// printf("Operator: %s\n", op);
				// exit(1);
			// }
			// char* r=nums[ntop--];
			// char* l=nums[ntop--];
			// nums[++ntop]=ApplyOperation(l,r,op);
			// free(l);
			// free(r);
		// }
		// ops[++otop]=t;
	// }
	// while(otop>=0)
	// {
		// char* op=ops[otop--];
		// char* r=nums[ntop--];
		// char* l=nums[ntop--];
		// nums[++ntop]=ApplyOperation(l,r,op);
		// free(l);
		// free(r);
	// }
	// char* result=nums[0];
	// free(nums);
	// free(ops);
	// return result;
// }
// char** tokenize(const char* expr, int* count)
// {
	// int len=strlen(expr),i=0,j,n=0;
	// char** tokens = (char**)malloc(sizeof(char*) * (len + 1));
	// while(i<len)
	// {
		// if(isspace((unsigned char)expr[i]))
		// {
			// i++;
			// continue;
		// }
		// if(strchr("+-*/()",expr[i]))
		// {
			// if((expr[i]=='+' || expr[i]=='-') && (n==0 || strchr("+-*/(", tokens[n-1][0]) != NULL))
			// {
				// j=i+1;
				// // signed number
				// if(j<len && (isdigit(expr[j]) || expr[j]=='.'))
				// {
					// while(j<len && (isdigit(expr[j]) || expr[j]=='.'))
						// j++;
					// int L=j-i;
					// tokens[n]=(char*)malloc(L+1);
					// memcpy(tokens[n],expr+i,L);
					// tokens[n][L]=0;
					// n++;
					// i=j;
					// continue;
				// }
				// // sign before bracket
				// if(j<len && expr[j]=='(')
				// {
					// tokens[n]=strdup("0");
					// n++;
					// tokens[n]=(char*)malloc(2);
					// tokens[n][0]=expr[i];
					// tokens[n][1]=0;
					// n++;
					// i++;
					// continue;
				// }
			// }
			// tokens[n]=(char*)malloc(2);
			// tokens[n][0]=expr[i];
			// tokens[n][1]=0;
			// n++; i++;
			// continue;
		// }
		// if(isdigit(expr[i]) || expr[i]=='.')
		// {
			// int j=i;
			// while(j<len && (isdigit(expr[j])||expr[j]=='.'))
				// j++;
			// int L=j-i;
			// tokens[n]=(char*)malloc(L+1);
			// memcpy(tokens[n],expr+i,L);
			// tokens[n][L]=0;
			// n++; i=j;
			// continue;
		// }
		// printf("Tokenizer error near: %s\n",expr+i);
		// exit(1);
	// }
	// *count=n;
	// return tokens;
// }
// template <typename BigNumClass,typename ResultType> char* CalculateExpression(const char* expr, char* ApplyOperation(char*,char*,char*))
// {
	// int count;
	// char** tokens=tokenize(expr,&count);
	// char* result=EvaluateTokens(tokens,count,ApplyOperation);
	// for(int i=0;i<count;i++)
		// free(tokens[i]);
	// free(tokens);
	// return result;
// }
template <typename BigNumClass> void TestExpressionsOutputOn(char*** BignumPairs)
{
	int i,j,CountOfOperations,TotalCountOfOperations;
	char* result,**expressions,*expression=GetRandomExpressionFromBignumPairs(BignumPairs);
	char* (*ApplyOperation)(char* a,char* b,char *op)=ApplyOperation_OutputOn<BigNumClass>;
	cout<<"Expression from bignum pairs:\n"<<expression<<endl;
	result=CalculateExpression<BigNumClass,char*>(expression,ApplyOperation);
	cout<<"RESULT: "<<result<<endl;
	for(i=0; i<90; i++)
		cout<<'-';
	cout<<endl;
	free(result);
	free(expression);
	for(i=0; i<CountOfExpressions; i++)
	{
		cout<<i+1<<". ";
		expression=GetRandomExpression(GetRandomInt(MinCountOfOperations,MaxCountOfOperations));
		cout<<expression<<endl;
		result=CalculateExpression<BigNumClass,char*>(expression,ApplyOperation);
		cout<<"RESULT: "<<result<<endl;
		for(j=0; j<90; j++)
			cout<<'-';
		cout<<endl;
		free(result);
		free(expression);
	}
}
void TestExpressions(char*** BignumPairs)
{
	auto StartTime=chrono::system_clock::now();
	auto EndTime=StartTime;
	chrono::duration<double> duration;
	int i,j,CountOfOperations,TotalCountOfOperations;
	char* result,**expressions,*expression=GetRandomExpressionFromBignumPairs(BignumPairs);
	char* (*ApplyOperationBignum)(char* a,char* b,char *op)=ApplyOperation_OutputOff<bignum>;
	char* (*ApplyOperationOptimizedBignum)(char* a,char* b,char *op)=ApplyOperation_OutputOff<OptimizedBignum>;
	if(MinCountOfDigits<1001 && MaxCountOfDigits<10001)
	{
		cout<<"Calculating an expression from bignum pairs (type bignum)...";
		StartTime=chrono::system_clock::now();
		result=CalculateExpression<bignum,char*>(expression,ApplyOperationBignum);
		EndTime=chrono::system_clock::now();
		duration=EndTime-StartTime;
		cout<<" Time: "<<duration.count()<<" s.\n";
		free(result);
	}
	cout<<"Calculating an expression from bignum pairs (type OptimizedBignum)...";
	StartTime=chrono::system_clock::now();
	result=CalculateExpression<OptimizedBignum,char*>(expression,ApplyOperationOptimizedBignum);
	EndTime=chrono::system_clock::now();
	duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" s.\n";
	free(result);
	free(expression);
	cout<<"Generating "<<CountOfExpressions<<" expressions...";
	StartTime=chrono::system_clock::now();
	expressions=(char**)malloc(sizeof(char*)*CountOfExpressions);
	for(i=0,TotalCountOfOperations=0; i<CountOfExpressions; i++)
	{
		CountOfOperations=GetRandomInt(MinCountOfOperations,MaxCountOfOperations);
		TotalCountOfOperations+=CountOfOperations;
		expressions[i]=GetRandomExpression(CountOfOperations);
	}
	EndTime=chrono::system_clock::now();
	duration=EndTime-StartTime;
	cout<<" Total count of operations: "<<TotalCountOfOperations<<":";
	cout<<" time: "<<duration.count()<<" s.\n";
	if(MinCountOfDigits<1001 && MaxCountOfDigits<10001)
	{
		cout<<"Calculating random expressions (type bignum)...";
		StartTime=chrono::system_clock::now();
		for(i=0; i<CountOfExpressions; i++)
		{
			result=CalculateExpression<bignum,char*>(expressions[i],ApplyOperationBignum);
			free(result);
		}
		EndTime=chrono::system_clock::now();
		duration=EndTime-StartTime;
		cout<<" Time: "<<duration.count()<<" s.\n";
	}
	cout<<"Calculating random expressions (type OptimizedBignum)...";
	StartTime=chrono::system_clock::now();
	for(i=0; i<CountOfExpressions; i++)
	{
		result=CalculateExpression<OptimizedBignum,char*>(expressions[i],ApplyOperationOptimizedBignum);
		free(result);
	}
	EndTime=chrono::system_clock::now();
	duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" s.\n";
	for(i=0; i<CountOfExpressions; i++)
		free(expressions[i]);
	free(expressions);
}
void TestBignums()
{
	int i;
	CountOfDivisionWarnings=0;
	auto StartTime=chrono::system_clock::now();
	auto EndTime=StartTime;
	chrono::duration<double> duration;
	cout<<"MIN COUNT OF DIGITS: "<<setw(7)<<MinCountOfDigits<<"; MAX COUNT OF DIGITS  : "<<setw(7)<<MaxCountOfDigits<<"; FRACT PART LENGTH : "<<setw(7)<<MaxFractPartLength<<endl;
	cout<<"MAX BIGNUM LENGTH  : "<<setw(7)<<MaxBignumLength<< "; COUNT OF BIGNUM PAIRS: "<<setw(7)<<CountOfBignumPairs<<";\n";
	for(i=0; i<90; i++)
		cout<<'-';
	cout<<endl;
	char*** BignumPairs=GetBignumPairs();
	MaxFractPartLength=MaxCountOfDigits*2;
	// TestAllBignumOperations<bignum>(BignumPairs);
	// TestAllBignumOperations<OptimizedBignum>(BignumPairs);
	TestOneBignumOperationWithCheck<bignum>('+',BignumPairs);
	TestOneBignumOperationWithCheck<bignum>('-',BignumPairs);
	if(MinCountOfDigits<1001 && MaxCountOfDigits<10001)
	{
		TestOneBignumOperationWithCheck<bignum>('*',BignumPairs);
		TestOneBignumOperationWithCheck<bignum>('/',BignumPairs);
	}
	TestOneBignumOperation<bignum>('+',BignumPairs);
	TestOneBignumOperation<bignum>('-',BignumPairs);
	if(MinCountOfDigits<1001 && MaxCountOfDigits<10001)
	{
		TestOneBignumOperation<bignum>('*',BignumPairs);
		TestOneBignumOperation<bignum>('/',BignumPairs);
	}
	cout<<"----------Multiple Precision Arithmetic Libraries (GMP and MPFR)----------\n";
	TestOneBignumOperationWithCheck<OptimizedBignum>('+',BignumPairs);
	TestOneBignumOperationWithCheck<OptimizedBignum>('-',BignumPairs);
	TestOneBignumOperationWithCheck<OptimizedBignum>('*',BignumPairs);
	TestOneBignumOperationWithCheck<OptimizedBignum>('/',BignumPairs);
	TestOneBignumOperation<OptimizedBignum>('+',BignumPairs);
	TestOneBignumOperation<OptimizedBignum>('-',BignumPairs);
	TestOneBignumOperation<OptimizedBignum>('*',BignumPairs);
	TestOneBignumOperation<OptimizedBignum>('/',BignumPairs);
	cout<<"Converting bignum pairs into mpq_t format...";
	StartTime=chrono::system_clock::now();
	mpq_t*** Mpq_tBignumPairs=(mpq_t***)malloc(sizeof(mpq_t**)*CountOfBignumPairs);
	for(i=0; i<CountOfBignumPairs; i++)
	{
		Mpq_tBignumPairs[i]=(mpq_t**)malloc(sizeof(mpq_t*)*2);
		Mpq_tBignumPairs[i][0]=(mpq_t*)malloc(sizeof(mpq_t));
		Mpq_tBignumPairs[i][1]=(mpq_t*)malloc(sizeof(mpq_t));
		decimal_str_to_mpq(BignumPairs[i][0],*Mpq_tBignumPairs[i][0]);
		decimal_str_to_mpq(BignumPairs[i][1],*Mpq_tBignumPairs[i][1]);
	}
	EndTime=chrono::system_clock::now();
	duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" s.\n";
	cout<<"----------Multiple Precision Arithmetic Libraries (GMP and MPFR) MPQ_T----------\n";
	TestOneMpq_tBignumOperationWithCheck('+',Mpq_tBignumPairs);
	TestOneMpq_tBignumOperationWithCheck('-',Mpq_tBignumPairs);
	TestOneMpq_tBignumOperationWithCheck('*',Mpq_tBignumPairs);
	TestOneMpq_tBignumOperationWithCheck('/',Mpq_tBignumPairs);
	TestOneMpq_tBignumOperation('+',Mpq_tBignumPairs);
	TestOneMpq_tBignumOperation('-',Mpq_tBignumPairs);
	TestOneMpq_tBignumOperation('*',Mpq_tBignumPairs);
	TestOneMpq_tBignumOperation('/',Mpq_tBignumPairs);
	cout<<"----------Bignum expressions----------\n";
	TestExpressions(BignumPairs);
	// TestExpressionsOutputOn<bignum>(BignumPairs); my_getch();
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
	free(BignumPairs);
	free(Mpq_tBignumPairs);
	cout<<"Count of division warnings: "<<CountOfDivisionWarnings<<endl;
	for(i=0; i<90; i++)
		cout<<'=';
	cout<<endl;
}
int main()
{
	InitFloatingPointAndRandomNumbers();
	auto StartTime=chrono::system_clock::now();

	CountOfBignumPairs=1000,MinCountOfDigits=1,MaxCountOfDigits=10;
	MaxFractPartLength=MaxCountOfDigits,MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
	TestBignums();

	CountOfBignumPairs=10000,MinCountOfDigits=1,MaxCountOfDigits=10;
	MaxFractPartLength=MaxCountOfDigits,MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
	TestBignums();

	CountOfBignumPairs=100000,MinCountOfDigits=1,MaxCountOfDigits=10;
	MaxFractPartLength=MaxCountOfDigits,MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
	TestBignums();

	CountOfBignumPairs=1000000,MinCountOfDigits=1,MaxCountOfDigits=10;
	MaxFractPartLength=MaxCountOfDigits,MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
	TestBignums();
	//===================================================================================
	CountOfBignumPairs=10,MinCountOfDigits=100,MaxCountOfDigits=1000;
	MaxFractPartLength=MaxCountOfDigits,MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
	TestBignums();

	CountOfBignumPairs=10,MinCountOfDigits=1000,MaxCountOfDigits=10000;
	MaxFractPartLength=MaxCountOfDigits,MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
	TestBignums();

	CountOfBignumPairs=10,MinCountOfDigits=10000,MaxCountOfDigits=100000;
	MaxFractPartLength=MaxCountOfDigits,MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
	TestBignums();

	// CountOfBignumPairs=10,MinCountOfDigits=100000,MaxCountOfDigits=1000000;
	// MaxFractPartLength=MaxCountOfDigits,MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
	// TestBignums();
	//===================================================================================
	CountOfBignumPairs=10,MinCountOfDigits=1,MaxCountOfDigits=8;
	MaxFractPartLength=MaxCountOfDigits,MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
	for(int i=0; i<90; i++)
		cout<<'-';
	cout<<endl;	
	cout<<"MIN COUNT OF DIGITS: "<<setw(7)<<MinCountOfDigits<<"; MAX COUNT OF DIGITS  : "<<setw(7)<<MaxCountOfDigits<<"; FRACT PART LENGTH : "<<setw(7)<<MaxFractPartLength<<endl;
	cout<<"MAX BIGNUM LENGTH  : "<<setw(7)<<MaxBignumLength<< "; COUNT OF BIGNUM PAIRS: "<<setw(7)<<CountOfBignumPairs<<";\n";	
	for(int i=0; i<90; i++)
		cout<<'-';
	cout<<endl;
	TestMpq_tPower();
	//===================================================================================
	/*char* (*ApplyOperation)(char* a,char* b,char *op);
	ApplyOperation=ApplyOperation_OutputOn<OptimizedBignum>;
	char* expression=(char*)malloc(sizeof(char)*100000);
	strcpy(expression,"93 + 60018392 * (469.507181 + 933)");
	cout<<expression<<endl;
	char* result=CalculateExpression<OptimizedBignum,char*>(expression,ApplyOperation);
	cout<<"RESULT: "<<result<<endl;
	free(expression);
	free(result);*/
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<"TOTAL TIME: "<<duration.count()<<" s.";
	my_getch();
	return 0;
}
