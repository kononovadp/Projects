#include "bignum.h"
#include "globals.h"
int decimal_str_to_mpq(char *in_s, mpq_t out)
{
	if (!in_s) return 1;

	// Trim spaces
	while (*in_s==' ' || *in_s=='\t' || *in_s=='\n') in_s++;

	size_t len = strlen(in_s);
	while (len>0 && (in_s[len-1]==' ' || in_s[len-1]=='\t' || in_s[len-1]=='\n'))
		in_s[--len] = '\0';

	if (len == 0) return 2;

	// Handle sign
	int sign = 1;
	size_t pos = 0;
	if (in_s[pos] == '+' || in_s[pos]=='-') {
		if (in_s[pos]=='-') sign = -1;
		pos++;
	}

	const char *p = in_s + pos;
	const char *dot = strchr(p, '.');

	mpz_t intpart, fracpart, pow10, num;
	mpz_init(intpart);
	mpz_init(fracpart);
	mpz_init(pow10);
	mpz_init(num);

	if (!dot) {
		// integer-only
		if (mpz_set_str(intpart, p, 10) != 0) {
			mpz_clear(intpart); mpz_clear(fracpart);
			mpz_clear(pow10); mpz_clear(num);
			return 3;
		}
		mpz_set(num, intpart);
		if (sign < 0) mpz_neg(num, num);
		mpq_set_z(out, num);
	}
	else {
		size_t int_len = dot - p;
		size_t frac_len = strlen(dot + 1);

		// parse integer part
		if (int_len == 0) {
			mpz_set_ui(intpart, 0);
		} else {
			char *ibuf = (char*)malloc(int_len + 1);
			memcpy(ibuf, p, int_len);
			ibuf[int_len] = '\0';
			if (mpz_set_str(intpart, ibuf, 10) != 0) {
				free(ibuf);
				mpz_clear(intpart); mpz_clear(fracpart);
				mpz_clear(pow10); mpz_clear(num);
				return 4;
			}
			free(ibuf);
		}

		// parse fractional part
		if (frac_len == 0) {
			mpz_set(num, intpart);
			if (sign < 0) mpz_neg(num, num);
			mpq_set_z(out, num);
		} else {
			if (mpz_set_str(fracpart, dot + 1, 10) != 0) {
				mpz_clear(intpart); mpz_clear(fracpart);
				mpz_clear(pow10); mpz_clear(num);
				return 5;
			}

			mpz_ui_pow_ui(pow10, 10, frac_len);

			mpz_mul(num, intpart, pow10);
			mpz_add(num, num, fracpart);

			if (sign < 0) mpz_neg(num, num);

			mpq_set_num(out, num);
			mpq_set_den(out, pow10);
			mpq_canonicalize(out);
		}
	}

	mpz_clear(intpart);
	mpz_clear(fracpart);
	mpz_clear(pow10);
	mpz_clear(num);
	return 0;
}
char* mpq_to_decimal_str(mpq_t q)
{
	mpz_t num, den, integer, rem, tmp10;
	mpz_inits(num, den, integer, rem, tmp10, NULL);
	mpq_get_num(num, q);
	mpq_get_den(den, q);
	int negative = mpz_sgn(num) < 0;
	mpz_abs(num, num);
	// integer = num / den
	mpz_tdiv_qr(integer, rem, num, den);
	// convert integer part to string
	char *int_str = mpz_get_str(NULL, 10, integer);
	// decide how many fractional digits to print
	int frac_digits = MaxFractPartLength;	// e.g. 20, 50, etc.
	// allocate output buffer
	char *out = (char*)malloc(strlen(int_str) + frac_digits + 3);
	char *p = out;
	if (negative) *p++ = '-';
	strcpy(p, int_str);
	p += strlen(int_str);
	if (frac_digits > 0) {
		*p++ = '.';
		for (int i = 0; i < frac_digits; i++) {
			mpz_mul_ui(rem, rem, 10);
			mpz_tdiv_qr(tmp10, rem, rem, den);
			*p++ = (char)('0' + mpz_get_ui(tmp10));
		}
	}
	*p = '\0';
	mpz_clears(num, den, integer, rem, tmp10, NULL);
	free(int_str);
	int i,ResultLength=strlen(out);
	if(GetPointPosition(out,ResultLength)<ResultLength)
	{
		for(i=ResultLength-1; out[i]=='0'; i--);
		if(out[i]=='.')
			i--;
		if(i<ResultLength-1)
			out[i+1]='\0';
		if(out[0]=='-' && i==1 && out[i]=='0')
		{
			out[0]='0';
			out[1]='\0';
		}
	}	
	return out;
}
char* plus(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length)
{
	char* orig1 = bignum1;
	char* orig2 = bignum2;
	if(Bignum1Length==1 && bignum1[0]=='0')
	{
		char *result=(char*)malloc(Bignum2Length+1*sizeof(char));
		strcpy(result,bignum2);
		return result;
	}
	if(Bignum2Length==1 && bignum2[0]=='0')
	{
		char *result=(char*)malloc(Bignum1Length+1*sizeof(char));
		strcpy(result,bignum1);
		return result;
	}
	bool SignMinus=false;
	bool Operand1SignMinus=false,Operand2SignMinus=false;
	if(bignum1[0]=='-' && bignum2[0]=='-')
	{
		SignMinus=true;
		Operand1SignMinus=true;
		Operand2SignMinus=true;
		bignum1++;
		Bignum1Length--;
		bignum2++;
		Bignum2Length--;
	}
	else
		if(bignum1[0]=='-' && bignum2[0]!='-')
		{
			/*bignum1++;
			Bignum1Length--;
			return minus(bignum2,Bignum2Length,bignum1,Bignum1Length);*/
			    char* temp1 = strdup(bignum1+1); // copy without '-'
				int len1 = Bignum1Length-1;
				char* result = ::minus(bignum2, Bignum2Length, temp1, len1);
				free(temp1);
				return result;
		}
		else
			if(bignum1[0]!='-' && bignum2[0]=='-')
			{
				/*bignum2++;
				Bignum2Length--;
				// bignum* MinusResult=*bignum1-bignum2;
				return minus(bignum1,Bignum1Length,bignum2,Bignum2Length);*/
				char* temp1 = strdup(bignum2+1); // copy without '-'
				int len2 = Bignum2Length-1;
				char* result = ::minus(bignum1, Bignum1Length, temp1, len2);
				free(temp1);
				return result;
			}		
	
	char SumOfDigits,*result=(char*)malloc(MaxBignumLength+MaxFractPartLength+Bignum1Length+Bignum2Length*sizeof(char));
	int Operand1PointPosition=GetPointPosition(bignum1,Bignum1Length);
	int Operand2PointPosition=GetPointPosition(bignum2,Bignum2Length);
	int i,j,k,carry=0,ResultLength;
	result[SignMinus]='A';
	if(Operand1PointPosition==Bignum1Length && Operand2PointPosition==Bignum2Length)
	{
		if(Operand1PointPosition<Operand2PointPosition)
		{			
			for(i=Operand2PointPosition+SignMinus,result[i+1]='\0',ResultLength=i,j=Operand1PointPosition-1,k=Operand2PointPosition-1; j>-1; i--,j--,k--)
			{
				SumOfDigits=(bignum1[j]-'0')+(bignum2[k]-'0')+carry;
				if(SumOfDigits<10)
				{
					carry=0;
					result[i]=SumOfDigits+'0';
				}
				else
				{
					carry=1;
					result[i]=(SumOfDigits%10)+'0';
				}
			}
			j=Operand2PointPosition-Operand1PointPosition-1;
			for(; carry==1 && j>-1; j--,i--)
			{
				SumOfDigits=bignum2[j]-'0'+carry;
				if(SumOfDigits<10)
				{
					carry=0;
					result[i]=SumOfDigits+'0';
				}
				else
				{
					carry=1;
					result[i]=(SumOfDigits%10)+'0';
				}
			}
			for(; j>-1; j--,i--)			
				result[i]=bignum2[j];
		}
		else
			if(Operand1PointPosition>Operand2PointPosition)
			{
				for(i=Operand1PointPosition+SignMinus,result[i+1]='\0',ResultLength=i,j=Operand1PointPosition-1,k=Operand2PointPosition-1; k>-1; i--,j--,k--)
				{
					SumOfDigits=(bignum1[j]-'0')+(bignum2[k]-'0')+carry;
					if(SumOfDigits<10)
					{
						carry=0;
						result[i]=SumOfDigits+'0';
					}
					else
					{
						carry=1;
						result[i]=(SumOfDigits%10)+'0';
					}
				}
				j=Operand1PointPosition-Operand2PointPosition-1;
				for(; carry==1 && j>-1; j--,i--)
				{
					SumOfDigits=(bignum1[j]-'0')+carry;
					if(SumOfDigits<10)
					{
						carry=0;
						result[i]=SumOfDigits+'0';
					}
					else
					{
						carry=1;
						result[i]=(SumOfDigits%10)+'0';
					}
				}
				for(; j>-1; j--,i--)
					result[i]=bignum1[j];
			}
			else
			{
				for(i=Operand1PointPosition+SignMinus,result[i+1]='\0',ResultLength=i,j=Operand1PointPosition-1; j>-1; i--,j--)
				{
					SumOfDigits=(bignum1[j]-'0')+(bignum2[j]-'0')+carry;
					if(SumOfDigits<10)
					{
						carry=0;
						result[i]=SumOfDigits+'0';
					}
					else
					{
						carry=1;
						result[i]=(SumOfDigits%10)+'0';
					}
				}
			}
	}
	else
	{
		int Operand1FractPartSize=Operand1PointPosition; //bignum1->GetPointPosition();
		int Operand2FractPartSize=Operand2PointPosition; //bignum2->GetPointPosition();
		Operand1FractPartSize=(Operand1FractPartSize==Bignum1Length)?0:Bignum1Length-Operand1FractPartSize-1;
		Operand2FractPartSize=(Operand2FractPartSize==Bignum2Length)?0:Bignum2Length-Operand2FractPartSize-1;
		int Operand1IntPartSize=(Operand1FractPartSize==0)?Bignum1Length-Operand1FractPartSize:Bignum1Length-Operand1FractPartSize-1;
		int Operand2IntPartSize=(Operand2FractPartSize==0)?Bignum2Length-Operand2FractPartSize:Bignum2Length-Operand2FractPartSize-1;
		i=(Operand1IntPartSize>Operand2IntPartSize)?Operand1IntPartSize+SignMinus+1:Operand2IntPartSize+SignMinus+1;
		i+=(Operand1FractPartSize>Operand2FractPartSize)?Operand1FractPartSize:Operand2FractPartSize;
		ResultLength=i;
		result[i+1]='\0';
		if(Operand1FractPartSize>Operand2FractPartSize)
		{
			int DifferenceOfFractPartSizes=Operand1FractPartSize-Operand2FractPartSize;
			for(j=Bignum1Length-1,k=0; k<DifferenceOfFractPartSizes; i--,j--,k++)
				result[i]=bignum1[j];
			for(k=Bignum2Length-1; j>Operand1PointPosition; j--,k--,i--)
			{
				SumOfDigits=(bignum1[j]-'0')+(bignum2[k]-'0')+carry;
				if(SumOfDigits<10)
				{
					carry=0;
					result[i]=SumOfDigits+'0';
				}
				else
				{
					carry=1;
					result[i]=(SumOfDigits%10)+'0';
				}
			}
		}
		else
			if(Operand2FractPartSize>Operand1FractPartSize)
			{
				int DifferenceOfFractPartSizes=Operand2FractPartSize-Operand1FractPartSize;
				for(j=Bignum2Length-1,k=0; k<DifferenceOfFractPartSizes; i--,j--,k++)
					result[i]=bignum2[j];
				for(k=Bignum1Length-1; j>Operand2PointPosition; j--,k--,i--)
				{
					SumOfDigits=(bignum1[k]-'0')+(bignum2[j]-'0')+carry;
					if(SumOfDigits<10)
					{
						carry=0;
						result[i]=SumOfDigits+'0';
					}
					else
					{
						carry=1;
						result[i]=(SumOfDigits%10)+'0';
					}
				}
			}
			else
			{
				for(j=Bignum1Length-1,k=Bignum2Length-1; j>Operand1PointPosition; j--,k--,i--)
				{
					SumOfDigits=(bignum1[j]-'0')+(bignum2[k]-'0')+carry;
					if(SumOfDigits<10)
					{
						carry=0;
						result[i]=SumOfDigits+'0';
					}
					else
					{
						carry=1;
						result[i]=(SumOfDigits%10)+'0';
					}
				}
			}
		result[i--]='.';
		if(Operand1PointPosition<Operand2PointPosition)
		{
			for(j=Operand1PointPosition-1,k=Operand2PointPosition-1; j>-1; i--,j--,k--)
			{
				SumOfDigits=(bignum1[j]-'0')+(bignum2[k]-'0')+carry;
				if(SumOfDigits<10)
				{
					carry=0;
					result[i]=SumOfDigits+'0';
				}
				else
				{
					carry=1;
					result[i]=(SumOfDigits%10)+'0';
				}
			}
			j=Operand2PointPosition-Operand1PointPosition-1;
			for(; carry==1 && j>-1; j--,i--)
			{
				SumOfDigits=bignum2[j]-'0'+carry;
				if(SumOfDigits<10)
				{
					carry=0;
					result[i]=SumOfDigits+'0';
				}
				else
				{
					carry=1;
					result[i]=(SumOfDigits%10)+'0';
				}
			}
			for(; j>-1; j--,i--)
				result[i]=bignum2[j];
		}
		else
			if(Operand1PointPosition>Operand2PointPosition)
			{
				for(j=Operand1PointPosition-1,k=Operand2PointPosition-1; k>-1; i--,j--,k--)
				{
					SumOfDigits=(bignum1[j]-'0')+(bignum2[k]-'0')+carry;
					if(SumOfDigits<10)
					{
						carry=0;
						result[i]=SumOfDigits+'0';
					}
					else
					{
						carry=1;
						result[i]=(SumOfDigits%10)+'0';
					}
				}
				j=Operand1PointPosition-Operand2PointPosition-1;
				for(; carry==1 && j>-1; j--,i--)
				{
					SumOfDigits=(bignum1[j]-'0')+carry;
					if(SumOfDigits<10)
					{
						carry=0;
						result[i]=SumOfDigits+'0';
					}
					else
					{
						carry=1;
						result[i]=(SumOfDigits%10)+'0';
					}
				}
				for(; j>-1; j--,i--)
					result[i]=bignum1[j];
			}
			else
			{
				for(j=Operand1PointPosition-1; j>-1; i--,j--)
				{
					SumOfDigits=(bignum1[j]-'0')+(bignum2[j]-'0')+carry;
					if(SumOfDigits<10)
					{
						carry=0;
						result[i]=SumOfDigits+'0';
					}
					else
					{
						carry=1;
						result[i]=(SumOfDigits%10)+'0';
					}
				}
			}
		for(j=ResultLength+1; result[j-1]=='0' && result[j-1]!='.'; j--);
		if(result[j-1]=='.')
			j--;
		result[j]='\0';		
	}
	if(carry==1)
		result[i]='1';
	/*if(Operand1SignMinus)
	{
		bignum1=&bignum1[0]-1;
		Bignum1Length++;
	}
	if(Operand2SignMinus)
	{
		bignum2=&bignum2[0]-1;
		Bignum2Length++;
	}*/
	if(SignMinus)	
		result[0]='-';
	if(result[SignMinus]=='A')
	{
		for(i=SignMinus; i<ResultLength+1; i++)
			result[i]=result[i+1];
		result[i-1]='\0';
	}
	bignum1 = orig1;
	bignum2 = orig2;
	return result;
}
char* minus(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length)
{
	int i,j,k,carry=0,ResultLength;
	bool Operand1SignMinus=false,Operand2SignMinus=false,SignMinus=false;
	char* bignum1_orig=bignum1;
	char* bignum2_orig=bignum2;
	if((bignum2[0]=='0' && Bignum2Length==1))
	{
		char *result=(char*)malloc(Bignum1Length+1*sizeof(char));
		strcpy(result,bignum1);
		return result;
	}
	if(IsEqual(bignum1,Bignum1Length,bignum2,Bignum2Length))
	{
		char *result=(char*)malloc(2*sizeof(char));
		result[0]='0';
		result[1]='\0';
		return result;
	}
	if(IsLess(bignum1,Bignum1Length,bignum2,Bignum2Length))
	{
		SignMinus=true;
		if((bignum1[0]!='-' && bignum2[0]!='-') || (bignum1[0]=='-' && bignum2[0]!='-'))		
			SwapBignums(bignum1,Bignum1Length,bignum2,Bignum2Length);		
	}
	if(bignum1[0]=='-' && bignum2[0]=='-')
	{
		Operand1SignMinus=true;
		Operand2SignMinus=true;
		bignum1=&bignum1[1];
		Bignum1Length--;
		bignum2=&bignum2[1];
		Bignum2Length--;		
	}
	else
		if(bignum1[0]!='-' && bignum2[0]=='-')
		{
			bignum2++;
			Bignum2Length--;
			char* PlusResult=::plus(bignum1,Bignum1Length,bignum2,Bignum2Length);
			if(SignMinus)
			{
				ResultLength=strlen(PlusResult);
				for(i=strlen(PlusResult)-1; i>-1; i--)
					PlusResult[i+1]=PlusResult[i];
				PlusResult[0]='-';
				PlusResult[ResultLength+1]='\0';
			}
			return PlusResult;
		}
	if(IsLess(bignum1,Bignum1Length,bignum2,Bignum2Length))	
		SwapBignums(bignum1,Bignum1Length,bignum2,Bignum2Length);	
	char difference,*result=(char*)malloc(MaxBignumLength+MaxFractPartLength+Bignum1Length+Bignum2Length*sizeof(char));
	int Operand1PointPosition=GetPointPosition(bignum1,Bignum1Length);
	int Operand2PointPosition=GetPointPosition(bignum2,Bignum2Length);
	if(Operand1PointPosition==Bignum1Length && Operand2PointPosition==Bignum2Length)
	{
		for(i=Operand1PointPosition-1,j=Operand2PointPosition-1,k=i+SignMinus,result[k+1]='\0',ResultLength=k; j>-1; i--,j--,k--)
			if(bignum1[i]-carry<bignum2[j])
			{
				result[k]=((bignum1[i]-carry+10)-bignum2[j])+'0';
				carry=1;
			}
			else
			{
				result[k]=(bignum1[i]-bignum2[j]-carry)+'0';
				carry=0;
			}
		
		if(Operand1PointPosition>Operand2PointPosition)
			for(; i>-1; i--,k--)
			{
				difference=bignum1[i]-carry;
				if(difference>='0')
				{
					result[k]=difference;
					carry=0;
				}
				else
					result[k]='9';
			}
		for(i=SignMinus; result[i]=='0' && i<ResultLength; i++);
		for(j=i,i=SignMinus; j<ResultLength+1; j++,i++)
			result[i]=result[j];
		result[i]='\0';
	}
	else
	{
		int Operand1FractPartSize=Operand1PointPosition;
		int Operand2FractPartSize=Operand2PointPosition;
		Operand1FractPartSize=(Operand1FractPartSize==Bignum1Length)?0:Bignum1Length-Operand1FractPartSize-1;
		Operand2FractPartSize=(Operand2FractPartSize==Bignum2Length)?0:Bignum2Length-Operand2FractPartSize-1;
		int Operand1IntPartSize=(Operand1FractPartSize==0)?Bignum1Length-Operand1FractPartSize:Bignum1Length-Operand1FractPartSize-1;
		int Operand2IntPartSize=(Operand2FractPartSize==0)?Bignum2Length-Operand2FractPartSize:Bignum2Length-Operand2FractPartSize-1;
		i=(Operand1IntPartSize>Operand2IntPartSize)?Operand1IntPartSize+SignMinus:Operand2IntPartSize+SignMinus;
		i+=(Operand1FractPartSize>Operand2FractPartSize)?Operand1FractPartSize:Operand2FractPartSize;
		ResultLength=i+1;
		result[i+1]='\0';
		if(Operand1FractPartSize>Operand2FractPartSize)
		{
			int DifferenceOfFractPartSizes=Operand1FractPartSize-Operand2FractPartSize;
			for(j=Bignum1Length-1,k=0; k<DifferenceOfFractPartSizes; i--,j--,k++)		
				result[i]=bignum1[j];
			for(k=Bignum2Length-1; k>Operand2PointPosition; i--,j--,k--)			
				if(bignum1[j]-carry<bignum2[k])
				{
					result[i]=((bignum1[j]-carry+10)-bignum2[k])+'0';
					carry=1;
				}
				else
				{
					result[i]=(bignum1[j]-bignum2[k]-carry)+'0';
					carry=0;
				}			
		}
		else
			if(Operand2FractPartSize>Operand1FractPartSize)
			{
				int DifferenceOfFractPartSizes=Operand2FractPartSize-Operand1FractPartSize-1;
				j=Bignum2Length-1;
				result[i--]=('9'+1)-bignum2[j--]+'0';
				for(k=0; k<DifferenceOfFractPartSizes; i--,j--,k++)				
					result[i]='9'-bignum2[j]+'0';
				for(k=Bignum1Length-1,carry=1; k>Operand1PointPosition; i--,j--,k--)				
					if(bignum1[k]-carry<bignum2[j])
					{
						result[i]=((bignum1[k]-carry+10)-bignum2[j])+'0';
						carry=1;
					}
					else
					{
						result[i]=(bignum1[k]-bignum2[j]-carry)+'0';
						carry=0;
					}
			}
			else
			{
				for(j=Bignum1Length-1,k=Bignum2Length-1; j>Operand1PointPosition; i--,j--,k--)
					if(bignum1[j]-carry<bignum2[k])
					{
						result[i]=((bignum1[j]-carry+10)-bignum2[k])+'0';
						carry=1;
					}
					else
					{
						result[i]=(bignum1[j]-bignum2[k]-carry)+'0';
						carry=0;
					}
			}
		result[i]='.';
		int ResultPointPosition=i;
		for(j=ResultLength; result[j-1]=='0' && j>i; j--);
		if(result[j-1]=='.')
			j--;
		result[j]='\0';
		for(i=Operand1PointPosition-1,j=Operand2PointPosition-1,k=i+SignMinus; j>-1; i--,j--,k--)
			if(bignum1[i]-carry<bignum2[j])
			{
				result[k]=((bignum1[i]-carry+10)-bignum2[j])+'0';
				carry=1;
			}
			else
			{
				result[k]=(bignum1[i]-bignum2[j]-carry)+'0';
				carry=0;
			}		
		if(Operand1PointPosition>Operand2PointPosition)
			for(; i>-1; i--,k--)
			{
				difference=bignum1[i]-carry;
				if(difference>='0')
				{
					result[k]=difference;
					carry=0;
				}
				else
					result[k]='9';
			}		
		if(ResultPointPosition>SignMinus+1)
		{
			for(i=SignMinus; result[i]=='0' && i<ResultPointPosition; i++);
			if(i==ResultPointPosition)
				i--;
			for(j=i,i=SignMinus; j<ResultLength+1; j++,i++)
				result[i]=result[j];
			result[i]='\0';
		}
	}
	if(SignMinus)
		result[0]='-';
	return result;
}
char* multiply(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length)
{
	if((bignum1[0]=='0' && Bignum1Length==1) || (bignum2[0]=='0' && Bignum2Length==1))
	{
		char* result=(char*)malloc(2*sizeof(char));
		result[0]='0';
		result[1]='\0';
		return result;
	}
	int i,j,k,l;
	bool Operand1SignMinus=false,Operand2SignMinus=false,SignMinus=false;	
	if((bignum1[0]=='-' && bignum2[0]!='-')||(bignum1[0]!='-' && bignum2[0]=='-'))
		SignMinus=true;
	if(bignum1[0]=='-')
	{
		Operand1SignMinus=true;
		bignum1=&bignum1[1];
		Bignum1Length--;
	}
	if(bignum2[0]=='-')
	{
		Operand2SignMinus=true;
		bignum2=&bignum2[1];
		Bignum2Length--;
	}
	char MultiplicationResult,carry=0,*result=(char*)malloc(MaxBignumLength+MaxFractPartLength+Bignum1Length+Bignum2Length*sizeof(char));
	int Operand1PointPosition=GetPointPosition(bignum1,Bignum1Length);
	int Operand2PointPosition=GetPointPosition(bignum2,Bignum2Length);
	int ResultLastIndex=Bignum1Length+Bignum2Length+SignMinus;
	int ResultLength=ResultLastIndex;
	char* multiplication=(char*)malloc(MaxBignumLength+MaxFractPartLength+Bignum1Length+Bignum2Length*sizeof(char));
	result[ResultLastIndex+1]='\0';
	for(i=SignMinus; i<=ResultLastIndex; i++)
		result[i]='0';
	if(Operand1PointPosition==Bignum1Length && Operand2PointPosition==Bignum2Length)
	{
		ResultLength=ResultLastIndex+1;
		for(i=Operand1PointPosition-1,j=ResultLastIndex; i>-1; i--,j--)
		{
			MultiplicationResult=(bignum1[i]-'0')*(bignum2[Operand2PointPosition-1]-'0')+carry;
			if(MultiplicationResult>9)
			{
				result[j]=(MultiplicationResult%10)+'0';
				carry=MultiplicationResult/10;
			}
			else
			{
				result[j]=MultiplicationResult+'0';
				carry=0;
			}
		}			
		if(carry>0)
			result[j]=carry+'0';
		else
			result[j]='0';
		for(i=Operand2PointPosition-2,l=1; i>-1; i--,l++)
		{
			for(j=Operand1PointPosition-1,k=j+1,multiplication[0]='0',multiplication[k+1]='\0',carry=0; j>-1; j--,k--)
			{
				MultiplicationResult=(bignum1[j]-'0')*(bignum2[i]-'0')+carry;
				if(MultiplicationResult>9)
				{
					multiplication[k]=(MultiplicationResult%10)+'0';
					carry=MultiplicationResult/10;
				}
				else
				{
					multiplication[k]=MultiplicationResult+'0';
					carry=0;
				}
			}
			if(carry>0)
				multiplication[k]=carry+'0';
			else
				multiplication[k]='0';
			for(j=ResultLastIndex-l,k=Operand1PointPosition,carry=0; k>0; k--,j--)
			{
				result[j]=(multiplication[k]-'0')+(result[j]-'0')+carry;					
				if(result[j]>9)
				{
					carry=1;
					result[j]%=10;
				}
				else
					carry=0;
				result[j]+='0';
			}
			result[j]=(multiplication[k]-'0')+carry;
			if(result[j]>9)
				result[j]=(result[j]%10)+'0';
			else
				result[j]+='0';
		}
		while(result[SignMinus]=='0')
		{
			for(i=SignMinus; i<ResultLastIndex; i++)
				result[i]=result[i+1];
			result[i]='\0';
			ResultLength--;
		}
	}
	else
	{
		bool SwappedOperands=false;
		int Operand1CountOfDigits=(Operand1PointPosition==Bignum1Length)?Bignum1Length:Bignum1Length-1;
		int Operand2CountOfDigits=(Operand2PointPosition==Bignum2Length)?Bignum2Length:Bignum2Length-1;
		if(Operand1CountOfDigits<Operand2CountOfDigits)
		{
			SwapBignums(bignum1,Bignum1Length,bignum2,Bignum2Length);
			SwappedOperands=true;
			i=Operand1PointPosition;
			Operand1PointPosition=Operand2PointPosition;
			Operand2PointPosition=i;
		}
		int Operand1FractPartSize=Bignum1Length-Operand1PointPosition-1;
		int Operand2FractPartSize=Bignum2Length-Operand2PointPosition-1;
		if(Operand1FractPartSize<1)
			Operand1FractPartSize=0;
		if(Operand2FractPartSize<1)
			Operand2FractPartSize=0;
		if(Operand1PointPosition==Bignum1Length)
		{
			Operand1PointPosition=-1;
			Operand1FractPartSize=0;
		}
		else
			if(Operand2PointPosition==Bignum2Length)
			{
				Operand2PointPosition=-1;
				Operand2FractPartSize=0;
			}
		int ResultFractPartSize=Operand1FractPartSize+Operand2FractPartSize;
		int ResultPointPosition=ResultLastIndex-ResultFractPartSize;
		result[ResultPointPosition]='.';
		for(i=Bignum2Length-1,l=0; i>Operand2PointPosition; i--,l++)
		{
			for(j=Bignum1Length-1,k=j+1,multiplication[0]='0',multiplication[k+1]='\0',carry=0; j>Operand1PointPosition; j--,k--)
			{
				MultiplicationResult=(bignum1[j]-'0')*(bignum2[i]-'0')+carry;
				if(MultiplicationResult>9)
				{
					multiplication[k]=(MultiplicationResult%10)+'0';
					carry=MultiplicationResult/10;
				}
				else
				{
					multiplication[k]=MultiplicationResult+'0';
					carry=0;
				}
			}
			for(j--; j>-1; j--,k--)
			{
				MultiplicationResult=(bignum1[j]-'0')*(bignum2[i]-'0')+carry;
				if(MultiplicationResult>9)
				{
					multiplication[k]=(MultiplicationResult%10)+'0';
					carry=MultiplicationResult/10;
				}
				else
				{
					multiplication[k]=MultiplicationResult+'0';
					carry=0;
				}
			}
			if(carry>0)
				multiplication[k]=carry+'0';
			else
				multiplication[k]='0';
			for(j=ResultLastIndex-l,k=Bignum1Length,carry=0; j>ResultPointPosition && k>0; k--,j--)
			{
				result[j]=(multiplication[k]-'0')+(result[j]-'0')+carry;
				if(result[j]>9)
				{
					carry=1;
					result[j]%=10;
				}
				else
					carry=0;
				result[j]+='0';
			}
			for(j--; k>-1; k--,j--)
			{
				result[j]=(multiplication[k]-'0')+(result[j]-'0')+carry;					
				if(result[j]>9)
				{
					carry=1;
					result[j]%=10;
				}
				else
					carry=0;
				result[j]+='0';
			}
		}
		for(i--; i>-1; i--,l++)
		{
			for(j=Bignum1Length-1,k=j+1,multiplication[0]='0',multiplication[k+1]='\0',carry=0; j>Operand1PointPosition; j--,k--)
			{
				MultiplicationResult=(bignum1[j]-'0')*(bignum2[i]-'0')+carry;
				if(MultiplicationResult>9)
				{
					multiplication[k]=(MultiplicationResult%10)+'0';
					carry=MultiplicationResult/10;
				}
				else
				{
					multiplication[k]=MultiplicationResult+'0';
					carry=0;
				}
			}
			for(j--; j>-1; j--,k--)
			{
				MultiplicationResult=(bignum1[j]-'0')*(bignum2[i]-'0')+carry;
				if(MultiplicationResult>9)
				{
					multiplication[k]=(MultiplicationResult%10)+'0';
					carry=MultiplicationResult/10;
				}
				else
				{
					multiplication[k]=MultiplicationResult+'0';
					carry=0;
				}
			}
			if(carry>0)
				multiplication[k]=carry+'0';
			else
				multiplication[k]='0';
			for(j=ResultLastIndex-l,k=Bignum1Length,carry=0; j>ResultPointPosition; k--,j--)
			{
				result[j]=(multiplication[k]-'0')+(result[j]-'0')+carry;
				if(result[j]>9)
				{
					carry=1;
					result[j]%=10;
				}
				else
					carry=0;
				result[j]+='0';
			}
			for(j--; k>-1; k--,j--)
			{
				result[j]=(multiplication[k]-'0')+(result[j]-'0')+carry;					
				if(result[j]>9)
				{
					carry=1;
					result[j]%=10;
				}
				else
					carry=0;
				result[j]+='0';
			}
		}
		for(i=ResultLastIndex; result[i]=='0' && i>ResultPointPosition; i--);
		if(i==ResultPointPosition)
			i--;
		result[i+1]='\0';
		ResultLength=i+1+SignMinus;
		if(ResultPointPosition>SignMinus+1)
		{
			for(i=SignMinus; result[i]=='0' && i<ResultPointPosition; i++);
			if(i==ResultPointPosition)
				i--;
			ResultLength-=i;
			for(j=i,i=SignMinus; j<=ResultLastIndex+1; j++,i++)
				result[i]=result[j];
			result[i]='\0';
		}
		//if(SwappedOperands)	
		//	SwapBignums(bignum1,Bignum1Length,bignum2,Bignum2Length);
	}
	if(SignMinus)
		result[0]='-';
	if(GetPointPosition(result,ResultLength)<ResultLength)
	{
		for(i=ResultLength-1; result[i]=='0'; i--);
		if(result[i]=='.')
			i--;
		if(i<ResultLength-1)
			result[i+1]='\0';
	}
	/*if(Operand1SignMinus)
	{
		bignum1=&bignum1[0]-1;
		Bignum1Length++;
	}
	if(Operand2SignMinus)
	{
		bignum2=&bignum2[0]-1;
		Bignum2Length++;
	}*/	
	free(multiplication);
	return result;
}
char* divide(char* bignum1, int Bignum1Length, char* bignum2, int Bignum2Length)
{
	if((bignum1[0]=='0' && Bignum1Length==1) || (bignum2[0]=='0' && Bignum2Length==1))
	{
		char* result=(char*)malloc(2*sizeof(char));
		result[0]='0';
		result[1]='\0';
		return result;
	}
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
	mpq_div(result, num1, num2);
	char* res = mpq_to_decimal_str(result);
	mpq_clear(num1);
	mpq_clear(num2);
	mpq_clear(result);
	free(str1);
	free(str2);
	return res;
}