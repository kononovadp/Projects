#include "bignum.h"
#include "globals.h"
int CountOfRanges=10,CountOfBignumPairs=10;
int CountOfErrors=0,CountOfDivisionWarnings=0;
char buffer[409600000];
size_t WrittenMemory=0,BufferSize=sizeof(buffer),UsedMemory=0;
char* normalize_positive_decimal(const char* s)
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
char* abs_normalized(const char* x)
{
	if(!x)
		return NULL;
	const char* p=(x[0] == '-' || x[0] == '+') ? x + 1 : x;
	// char* norm=normalize_positive_decimal handles empty and dot cases
	char* result=normalize_positive_decimal(p);
	return result; // caller must free(result)
}

// Compare two POSITIVE normalized decimal strings by absolute value.
// Return -1,0,1
int cmp_pos_dec(const char* a, const char* b)
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
char* make_relative_epsilon(const char* X, int p)
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
void ParseDecimalToFractionOutputOn(const char* str, char*& numerator, char*& denominator)
{
	// Parse Q (finite or periodic) into fraction num/den
	string s(str);
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
		char* num=::minus(bigABC, (int)strlen(bigABC), bigAB, (int)strlen(bigAB));
		WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s - %s = %s\n",bigABC,bigAB,num);
		UsedMemory += (size_t)WrittenMemory;
		char* powB=PowerOf10((int)B.size());
		char* powC=PowerOf10((int)C.size());
		char one[]="1";
		char* powCminus1=::minus(powC, (int)strlen(powC), one, 1);
		WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s - %s = %s\n",powC,one,powCminus1);
		UsedMemory += (size_t)WrittenMemory;
		char* denom=multiply(powB, (int)strlen(powB), powCminus1, (int)strlen(powCminus1));
		WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s * %s = %s\n",powB,powCminus1,denom);
		UsedMemory += (size_t)WrittenMemory;
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
		size_t L=strlen(numerator);
		char* signedNum=(char*)calloc(L+4,sizeof(char));
		signedNum[0]='-';
		memcpy(signedNum+1, numerator, L+1);
		free(numerator);
		numerator=signedNum;
	}
	
}
// Full consistency check
bool IsDivisionConsistentOutputOn(char* A, char* B, char* Q, int precisionDigits)
{
	string s(Q);
	// Case 1: repeating decimal → exact rational check
	if(s[s.length()-1]==')') // if(s.find('(') != string::npos)
	{
		char* Qnum;
		char* Qden;
		ParseDecimalToFractionOutputOn(Q, Qnum, Qden);
		char* Left	= multiply(Qnum, (int)strlen(Qnum), B, (int)strlen(B));
		WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s * %s = %s\n",Qnum,B,Left);
		UsedMemory += (size_t)WrittenMemory;
		char* Right=multiply(Qden, (int)strlen(Qden), A, (int)strlen(A));
		WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s * %s = %s\n",Qden,A,Right);
		UsedMemory += (size_t)WrittenMemory;
		bool ok=IsEqual(Left, (int)strlen(Left), Right, (int)strlen(Right));
		free(Qnum);
		free(Qden);
		free(Left);
		free(Right);
		
		return ok;
	}
	// 1) QB=Q * B
	char* QB=multiply(Q,strlen(Q),B,strlen(B));
	WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s * %s = %s\n",Q,B,QB);
	UsedMemory += (size_t)WrittenMemory;
	// 2) Diff=QB - A
	char* Diff=::minus(QB,strlen(QB),A,strlen(A));
	WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s - %s = %s\n",QB,A,Diff);
	UsedMemory += (size_t)WrittenMemory;
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
	
	return ok;
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
		// parts[partIndex++]=GetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),(bool)GetRandomInt(0,2),0);
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
	char* expression=(char*)malloc(TotalLen+1);
	expression[0]='\0';
	for(i=0; i<TokensCount; i++)
	{
		strcat(expression, parts[i]);
		free(parts[i]);
	}
	return expression;
}
char *strdup_s(const char *s)
{
	if(!s)
		return NULL;
	size_t L = strlen(s);
	char *result = (char*)malloc(L + 1);
	if (!result) return NULL;
	memcpy(result, s, L + 1);
	return result;
}
int is_op_char(char c) {return c == '+' || c == '-' || c == '*' || c == '/';}
int precedence(const char *op)
{
	if (!op || !op[0]) return 0;
	switch (op[0])
	{
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
	return 0;
}
int is_right_assoc(const char *op)
{
	// we don't have ^ here; if you add ^ make it return 1
	(void)op;
	return 0;
}
typedef struct
{
	char **v;
	int top;
	int cap;
}StrStack;
StrStack *stack_new(int cap)
{
	StrStack *s = (StrStack*)malloc(sizeof(*s));
	if(!s) return NULL;
	s->v = (char**)calloc((size_t)cap, sizeof(char*));
	s->top = -1;
	s->cap = cap;
	return s;
}
void stack_free_all(StrStack *s)
{
	if(!s) return;
	for(int i = 0; i <= s->top; ++i)	
		if(s->v[i])
		{
			free(s->v[i]);
			s->v[i] = NULL;
		}	
	free(s->v);
	free(s);
}
int stack_push(StrStack *s, char *item)
{
	if (s->top + 1 >= s->cap)
	{
		int newcap = s->cap * 2;
		char **nv = (char**)realloc(s->v, (size_t)newcap * sizeof(char*));
		if (!nv) return 0;
		s->v = nv;
		s->cap = newcap;
	}
	s->v[++s->top] = item;
	return 1;
}
char *stack_pop(StrStack *s)
{
	if (s->top < 0) return NULL;
	char *result = s->v[s->top];
	s->v[s->top--] = NULL;
	return result;
}
char *stack_peek(StrStack *s)
{
	if (s->top < 0) return NULL;
	return s->v[s->top];
}
int stack_empty(StrStack *s){return s->top < 0;}
// Simplified ApplyOperation_OutputOn that frees left and right
char* ApplyOperation_OutputOn(char *bignum1, char *bignum2, char *operation)
{
	int i,j,PrevMaxFractPartLength,ResultLength;
	char* result,*CheckResult;
	WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s %c %s = ",bignum1,operation[0],bignum2);
	UsedMemory += (size_t)WrittenMemory;
	switch (operation[0])
	{
		case '+':
			result = ::plus(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			CheckResult=::minus(result,strlen(result),bignum2,strlen(bignum2));
			WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s\n%s - %s = %s\n",result,result,bignum2,CheckResult);
			UsedMemory += (size_t)WrittenMemory;
			if(IsNotEqual(CheckResult,strlen(CheckResult),bignum1,strlen(bignum1)))
			{
				CountOfErrors++;
				WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,
				"Calculation error: operation PLUS!\n%s %c %s = %s\n%s - %s = %s\n",
				bignum2,operation[0],bignum1,result,result,bignum1,CheckResult);
				UsedMemory += (size_t)WrittenMemory;
			}
			free(CheckResult);
		break;
		case '-':
			result = ::minus(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			CheckResult=::plus(result,strlen(result),bignum2,strlen(bignum2));
			WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s\n%s + %s = %s\n",result,result,bignum2,CheckResult);
			UsedMemory += (size_t)WrittenMemory;
			if(IsNotEqual(CheckResult,strlen(CheckResult),bignum1,strlen(bignum1)))
			{
				CountOfErrors++;
				WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,
				"Calculation error: operation MINUS!\n%s %c %s = %s\n%s + %s = %s\n",
				bignum2,operation[0],bignum1,result,result,bignum1,CheckResult);
				UsedMemory += (size_t)WrittenMemory;
			}
			free(CheckResult);
		break;
		case '*':
			result = multiply(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s\n",result);
			UsedMemory += (size_t)WrittenMemory;
			if((bignum2[0]!='0' || strlen(bignum2)!=1) && (bignum1[0]!='0' || strlen(bignum1)!=1))
			{
				PrevMaxFractPartLength=MaxFractPartLength;
				ResultLength=strlen(bignum1);
				MaxFractPartLength=GetPointPosition(bignum1,ResultLength);
				MaxFractPartLength=(MaxFractPartLength==ResultLength)?0:ResultLength-MaxFractPartLength-1;
				CheckResult=divide(result,strlen(result),bignum2,strlen(bignum2));
				WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s / %s = %s\n",result,bignum2,CheckResult);
				UsedMemory += (size_t)WrittenMemory;
				if(IsNotEqual(CheckResult,strlen(CheckResult),bignum1,strlen(bignum1)))
				{
					CountOfErrors++;
					WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,
					"MaxFractPartLength: %d\nCalculation error: operation MULTIPLY!\n%s %c %s = %s\n%s / %s = %s\n",
					MaxFractPartLength,bignum1,operation[0],bignum2,result,result,bignum2,CheckResult);
					UsedMemory += (size_t)WrittenMemory;
				}
				free(CheckResult);
				MaxFractPartLength=PrevMaxFractPartLength;
			}
			
		break;
		case '/':
			result = divide(bignum1,strlen(bignum1),bignum2,strlen(bignum2));
			WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"%s\n",result);
			UsedMemory += (size_t)WrittenMemory;
			if((bignum1[0]!='0' || strlen(bignum1)!=1) && (bignum2[0]!='0' || strlen(bignum2)!=1))
			{				
				if(!IsDivisionConsistentOutputOn(bignum1,bignum2,result,MaxFractPartLength))
				{
					WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,
					"Calculation warning: operation DIVIDE!\n%s %c %s != %s\n",
					bignum1,operation[0],bignum2,result);
					UsedMemory += (size_t)WrittenMemory;
					CountOfDivisionWarnings++;
				}
			}
		break;
		default: fprintf(stderr, "Unknown operator: %s\n", operation);
	}
	WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"---------------------------------------------\n");
	UsedMemory += (size_t)WrittenMemory;
	return result;
}
char* CalculateExpression(const char *expr, char* ApplyOperation(char *bignum1, char *bignum2, char *operation))
{
	int n = (int)strlen(expr);
	StrStack *nums = stack_new(2560);
	StrStack *ops = stack_new(2560);
	int i = 0;
	int prev_type = 0;	
	while (i < n)
	{
		if(isspace((unsigned char)expr[i]))
		{
			i++;
			continue;
		}
		char c = expr[i];
		if(c == '(')
		{
			stack_push(ops, strdup_s("("));
			i++;
			prev_type = 0;
			continue;
		}
		if(c == ')')
		{
			while(!stack_empty(ops) && strcmp(stack_peek(ops), "(") != 0)
			{
				char* op = stack_pop(ops);
				char* right = stack_pop(nums); // ← Right operand (top of stack)
				char* left = stack_pop(nums); // ← Left operand (below)
				stack_push(nums, ApplyOperation(left, right, op)); // ← LEFT first!
				free(op);
			}
			if(!stack_empty(ops) && strcmp(stack_peek(ops), "(") == 0)
				free(stack_pop(ops));
			i++;
			prev_type = 1;
			continue;
		}
		if(is_op_char(c))
		{
			if(c == '-' && prev_type == 0)
			{
				int j = i + 1;
				if(j < n && (isdigit((unsigned char)expr[j]) || expr[j] == '.'))
				{
					while(j < n && (isdigit((unsigned char)expr[j]) || expr[j] == '.'))
						j++;
					int len = j - i;
					char *num = (char*)malloc((size_t)len + 1);
					memcpy(num, expr + i, (size_t)len);
					num[len] = '\0';
					stack_push(nums, num);
					i = j; prev_type = 1; continue;
				}
				else
					stack_push(nums, strdup_s("0"));				
			}
			char op1[2] = { c, '\0' };
			while(!stack_empty(ops) && is_op_char(stack_peek(ops)[0]) && ( precedence(stack_peek(ops)) > precedence(op1) || (precedence(stack_peek(ops)) == precedence(op1) && !is_right_assoc(op1)) ))
			{
				char* op = stack_pop(ops);
				char* right = stack_pop(nums); // ← Right operand (top of stack)
				char* left = stack_pop(nums); // ← Left operand (below)
				stack_push(nums, ApplyOperation(left, right, op)); // ← LEFT first!
				free(op);
			}
			stack_push(ops, strdup_s(op1));
			i++;
			prev_type = 0;
			continue;
		}
		if(isdigit((unsigned char)c) || c == '.')
		{
			int j = i;
			while(j < n && (isdigit((unsigned char)expr[j]) || expr[j] == '.'))
				j++;
			int len = j - i;
			char *num = (char*)malloc((size_t)len + 1);
			memcpy(num, expr + i, (size_t)len);
			num[len] = '\0';
			stack_push(nums, num);
			i = j;
			prev_type = 1;
			continue;
		}
	}
	while(!stack_empty(ops))
	{
		char *op = stack_pop(ops);
		char* right = stack_pop(nums); // ← Right operand (top of stack)
		char* left = stack_pop(nums); // ← Left operand (below)
		stack_push(nums, ApplyOperation(left, right, op)); // ← LEFT first!
		free(op);
	}
	char *result = stack_pop(nums);
	free(nums->v);
	free(nums);
	stack_free_all(ops);
	return result;
}
DLL_EXPORT_FUNC char* TestExpressions()
{
	UsedMemory=0;
    buffer[0] = '\0';
	char* (*ApplyOperation)(char* a, char* b, char *op);
	ApplyOperation=ApplyOperation_OutputOn;
	WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,
	"MIN COUNT OF DIGITS: %d; MAX COUNT OF DIGITS  : %d; FRACT PART LENGTH : %d\nMAX BIGNUM LENGTH  : %d; COUNT OF BIGNUM PAIRS: %d;\nCOUNT OF EXPR.     : %d; MIN COUNT OF OPS.    : %d; MAX COUNT OF OPS. : %d\n",MinCountOfDigits,MaxCountOfDigits,MaxFractPartLength,MaxBignumLength,CountOfBignumPairs,CountOfExpressions,MinCountOfOperations,MaxCountOfOperations);
	UsedMemory += (size_t)WrittenMemory;
	WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"================================================================================================\n");
	UsedMemory += (size_t)WrittenMemory;
	/*char* RandomExpression=(char*)malloc(sizeof(char)*1000);
	strcpy(RandomExpression,"2.590439 + 4.9922014 - 0.53322419 / 60644425 + -65618 * -330.061 / 0.7422 + -75");
	WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory, "%s\n", RandomExpression);
	UsedMemory += (size_t)WrittenMemory;
	char* RandomExpressionResult=CalculateExpression(RandomExpression,ApplyOperation_OutputOn);
	WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"RESULT: %s\n",RandomExpressionResult);
	UsedMemory += (size_t)WrittenMemory;*/
	InitFloatingPointAndRandomNumbers();
	auto StartTime=chrono::system_clock::now();
	for(int i=0; i<CountOfExpressions; i++)
	{
		char* RandomExpression=GetRandomArithmeticExpression(GetRandomInt(MinCountOfOperations,MaxCountOfOperations));		
		WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory, "%d. %s\n", i+1, RandomExpression);
		UsedMemory += (size_t)WrittenMemory;
		char* RandomExpressionResult=CalculateExpression(RandomExpression,ApplyOperation);
		WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"RESULT: %s\n",RandomExpressionResult);
		UsedMemory += (size_t)WrittenMemory;
		free(RandomExpression);
		free(RandomExpressionResult);
		WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"================================================================================================\n");
		UsedMemory += (size_t)WrittenMemory;
	}
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	WrittenMemory=snprintf(buffer+UsedMemory,BufferSize-UsedMemory,"Count of errors: %d;\nCount of division warnings: %d\nTime: %.6f seconds",CountOfErrors,CountOfDivisionWarnings,duration.count());
	UsedMemory += (size_t)WrittenMemory;
	return buffer;
}
int main()
{

	return 0;
}