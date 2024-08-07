#include "verylong.h"
void verylong::putvl() const
{
	char temp[SZ];
	strcpy(temp,vlstr);
	cout<<strrev(temp);	
}
void verylong::display()
{
	if(vlen>9)
		cout<<vlstr[0]<<vlstr[1]<<vlstr[2]<<"..."<<vlstr[vlen-3]<<vlstr[vlen-2]<<vlstr[vlen-1];
	else
		cout<<vlstr;
}
void verylong::getvl()
{
	cin>>vlstr;
	vlen=strlen(vlstr);
	strrev(vlstr);
}
char verylong::GetRandomDigit(char min,char max)
{
	if(min==max)
		return min;
	if(min>max)
	{
		char temp=min;
		min=max;
		max=temp;
	}
	char result=min+(rand()%(max-min));
	if(!isdigit(result))
		cout<<"Non-digit character!\n"
			<<"Min character: "<<min<<" = "<<(int)min<<"; max character: "<<max<<" = "<<(int)max<<endl;
	return result;
}
verylong verylong::GetRandomIntBignum(verylong& min,verylong& max)
{	
	bool RestrictedDigit=true;
	int i,size=GetRandomInt(min.vlen,max.vlen);
	char* bignum=new char[size+10];
	if(size==max.vlen)
	{
		for(i=0; min.vlstr[i]==max.vlstr[i]; i++)
			bignum[i]=min.vlstr[i];
		for(; i<size; i++)
		{
			if(RestrictedDigit)			
				bignum[i]=GetRandomDigit(min.vlstr[i],max.vlstr[i]);
			else			
				bignum[i]=GetRandomDigit('0','9');			
			if((i+1==min.vlen) || (bignum[i]<max.vlstr[i] && bignum[i]>min.vlstr[i]))
				RestrictedDigit=false;			
		}
	}
	else
	{		
		bignum[0]=GetRandomDigit(min.vlstr[0],'9');
		if(bignum[0]=='0' && size>0)
			bignum[0]=GetRandomDigit('1','9');
		if(min.vlen==1 || bignum[0]>min.vlstr[0])
			RestrictedDigit=false;
		for(i=1; i<size; i++)
		{
			if(RestrictedDigit)			
				bignum[i]=GetRandomDigit(min.vlstr[i],'9');			
			else
				bignum[i]=GetRandomDigit('0','9');
			if(i+1==min.vlen || bignum[i]>min.vlstr[i])
				RestrictedDigit=false;			
		}
	}
	bignum[i]='\0';
	verylong result(bignum);
	delete[]bignum;
	if(result<min)
		return min;
	if(result>max)
		return max;
	return result;
}
verylong verylong::GetRandomSignedIntBignum(verylong& min,verylong& max)
{
	verylong result;
	verylong MinWithoutSign=verylong(min.vlstr);
	verylong MaxWithoutSign=verylong(max.vlstr);
	verylong zero("0");
	verylong one("1");
	if(min==max)
	{
		verylong ten("10");
		max=max+ten;
	}
	if(min.vlstr[0]=='-' && max.vlstr[0]=='-')
	{
		verylong MinWithoutSign=verylong(min.vlstr);
		verylong MaxWithoutSign=verylong(max.vlstr);
		DeleteSignMinus(MinWithoutSign);
		DeleteSignMinus(MaxWithoutSign);
		result=GetRandomIntBignum(MaxWithoutSign,MinWithoutSign);
		AddSignMinus(result);
	}
	else
		if((min.vlstr[0]=='-' && max.vlstr[0]!='-') || (min.vlstr[0]!='-' && max.vlstr[0]=='-'))
		{			
			if(MinWithoutSign.vlstr[0]=='-')
				DeleteSignMinus(MinWithoutSign);
			else
				DeleteSignMinus(MaxWithoutSign);
			if(GetRandomInt(0,10)<5)
			{
				result=GetRandomIntBignum(one,MinWithoutSign);
				AddSignMinus(result);
			}
			else
				result=GetRandomIntBignum(zero,MaxWithoutSign);
		}
		else
			result=GetRandomIntBignum(min,max);	
	for(int i=(result.vlstr[0]=='-')?1:0; i<result.vlen; i++)
		if(!isdigit(result.vlstr[i]))
		{
			cout<<"Random bignum contains at least one non-digital symbol: "<<result.vlstr
			    <<"\nMin bignum: "<<min.vlstr<<"; max bignum: "<<max.vlstr;
			exit(0);
		}
	if(result.vlen>1 && result.vlstr[0]=='0')
	{
		cout<<"Incorrect random bignum: "<<result.vlstr;
		exit(0);
	}
	if(result==min || result==max)
		return result;
	if(result<min)
	{
		cout<<"Incorrect random bignum: "<<result.vlstr<<" < "<<min.vlstr;
		exit(0);
	}
	else
		if(result>max)
		{
			cout<<"Incorrect random bignum: "<<result.vlstr<<" > "<<max.vlstr;
			exit(0);
		}
	return result;
}
verylong verylong::operator+(verylong& v)
{
	if(vlstr[0]=='0' || v.vlstr[0]=='0')
	{
		if(vlstr[0]=='0')
			return v;
		else
			return *this;
	}
	bool SignMinus=false,SwappedOperands=false;
	bool FirstOperandSignMinus=false,SecondOperandSignMinus=false;
	if(vlstr[0]=='-' && v.vlstr[0]=='-')
	{
		DeleteSignMinus(*this);
		DeleteSignMinus(v);
		SignMinus=true;
		FirstOperandSignMinus=true;
		SecondOperandSignMinus=true;
	}
	else
		if((vlstr[0]=='-' && v.vlstr[0]!='-')||(vlstr[0]!='-' && v.vlstr[0]=='-'))
		{
			verylong operand1(vlstr);
			verylong operand2(v.vlstr);
			if(operand1.vlstr[0]=='-')
			{				
				DeleteSignMinus(operand1);
				FirstOperandSignMinus=true;
				if(operand1>operand2)
					SignMinus=true;				
			}
			else
			{
				DeleteSignMinus(operand2);
				SecondOperandSignMinus=true;
				if(operand2>operand1)
					SignMinus=true;
			}
			if(operand1<operand2)
				SwapOperands(operand1,operand2);
			verylong result=operand1-operand2;
			if(SignMinus && result.vlstr[0]!='0')
				AddSignMinus(result);
			return result;
		}
	strrev(vlstr);
	strrev(v.vlstr);
	char temp[SZ];
	int j;	
	int maxlen=(vlen>v.vlen)?vlen:v.vlen;
	int carry=0; //установить в 1, если сумма >= 10
	for(j=0; j<maxlen; j++) //и так для каждой позиции
	{
		int d1=(j>vlen-1)?0:vlstr[j]-'0'; //получить разряд
		int d2=(j>v.vlen-1)?0:v.vlstr[j]-'0'; //и еще
		int digitsum=d1+d2+carry; //сложить разряды
		if(digitsum>=10) //если перенос, то
		{
			digitsum-=10;
			carry=1;
		} //увеличить сумму на 10
		else //установить перенос в 1
			carry=0; //иначе перенос = 0
		temp[j]=digitsum+'0';//вставить символ в строку
	}
	if(carry==1) //если перенос в конце,
		temp[j++]='1'; //последняя цифра = 1
	temp[j]='\0'; //поставить ограничитель строки
	strrev(temp);
	verylong result(temp);	
	strrev(vlstr);
	strrev(v.vlstr);
	if(SignMinus)	
		AddSignMinus(result);
	if(FirstOperandSignMinus)
		AddSignMinus(*this);
	if(SecondOperandSignMinus)
		AddSignMinus(v);
	return result; //вернуть временный verylong
}
verylong verylong::OperatorPlusWithoutStrrev(verylong& v1,verylong& v2)
{
	char temp[SZ];
	int j;	
	int maxlen=(v1.vlen>v2.vlen)?v1.vlen:v2.vlen;
	int carry=0; //установить в 1, если сумма >= 10
	for(j=0; j<maxlen; j++) //и так для каждой позиции
	{
		int d1=(j>v1.vlen-1)?0:v1.vlstr[j]-'0'; //получить разряд
		int d2=(j>v2.vlen-1)?0:v2.vlstr[j]-'0'; //и еще
		int digitsum=d1+d2+carry; //сложить разряды
		if(digitsum>=10) //если перенос, то
		{
			digitsum-=10;
			carry=1;
		} //увеличить сумму на 10
		else //установить перенос в 1
			carry=0; //иначе перенос = 0
		temp[j]=digitsum+'0';//вставить символ в строку
	}
	if(carry==1) //если перенос в конце,
		temp[j++]='1'; //последняя цифра = 1
	temp[j]='\0'; //поставить ограничитель строки
	return verylong(temp); //вернуть временный verylong
}
verylong verylong::operator*(verylong& v)
{
	if(vlstr[0]=='0' || v.vlstr[0]=='0')
		return verylong("0");	
	bool SignMinus=false;
	bool FirstOperandSignMinus=false,SecondOperandSignMinus=false;
	if((vlstr[0]=='-' && v.vlstr[0]!='-')||(vlstr[0]!='-' && v.vlstr[0]=='-'))
		SignMinus=true;
	if(vlstr[0]=='-')
	{
		DeleteSignMinus(*this);
		FirstOperandSignMinus=true;
	}
	if(v.vlstr[0]=='-')
	{
		DeleteSignMinus(v);
		SecondOperandSignMinus=true;
	}
	strrev(vlstr);
	strrev(v.vlstr);
	verylong pprod; //произведение одного разряда
	verylong tempsum; //текущая сумма
	for(int j=0; j<v.vlen; j++) //для каждого разряда аргумента
	{
		int digit=v.vlstr[j]-'0'; //получить разряд
		pprod=multdigit(digit); //умножить текущий на него
		for(int k=0; k<j; k++) //умножить результат на
			pprod=mult10(pprod); //степень 10-ти
		tempsum=OperatorPlusWithoutStrrev(pprod,tempsum);
		//tempsum=tempsum+pprod; //прибавить произведение к текущей сумме
	}	
	strrev(tempsum.vlstr);	
	strrev(vlstr);
	strrev(v.vlstr);	
	if(SignMinus)
		AddSignMinus(tempsum);
	if(FirstOperandSignMinus)
		AddSignMinus(*this);
	if(SecondOperandSignMinus)
		AddSignMinus(v);
	return tempsum; //вернуть полученную текущую сумму
}
verylong verylong::mult10(const verylong v) const //умножение аргумента на 10
{
	char temp[SZ];
	for(int j=v.vlen-1; j>=0; j--) //сдвинуться на один разряд выше
		temp[j+1]=v.vlstr[j];
	temp[0]='0'; //обнулить самый младший разряд
	temp[v.vlen+1]='\0'; //поставить ограничитель строки
	return verylong(temp); //вернуть результат
}
verylong verylong::multdigit(const int d2) const //умножение числа на аргумент (цифру)
{
	char temp[SZ];
	int j,carry=0;
	for(j=0; j<vlen; j++) //для каждого разряда
    {
		int d1=vlstr[j]-'0'; //получить значение разряда
		int digitprod=d1*d2; //умножить на цифру
		digitprod+=carry; //добавить старый перенос
		if(digitprod>= 10) //если возник новый перенос,
		{
			carry=digitprod/10; //переносу присвоить значение старшего разряда
			digitprod-=carry*10; //результату - младшего
		}
		else
			carry=0; //иначе перенос = 0
		temp[j]=digitprod+'0'; //вставить символ в строку
	}
	if(carry!=0) //если на конце перенос,
		temp[j++]=carry+'0'; //это последний разряд
	temp[j]='\0'; //поставить ограничитель
	return verylong(temp); //вернуть сверхбольшое число
}
bool verylong::operator<(const verylong& v)
{
	int i;
	if(vlstr[0]=='-' && v.vlstr[0]!='-')
		return true;
	if(vlstr[0]!='-' && v.vlstr[0]=='-')
		return false;
	if(vlstr[0]=='-' && v.vlstr[0]=='-')
	{		
		if(vlen<v.vlen)
			return false;		
		if(vlen>v.vlen)
			return true;
		for(i=1; i<vlen && vlstr[i]==v.vlstr[i]; i++);
		for(; i<vlen; i++)
		{
			if(vlstr[i]<v.vlstr[i])
				return false;	
			if(vlstr[i]>=v.vlstr[i])
				return true;
		}
		return true;
	}
	if(vlen<v.vlen)
		return true;
	if(vlen>v.vlen)
		return false;
	for(i=0; i<vlen && vlstr[i]==v.vlstr[i]; i++);
	for(i; i<vlen; i++)
	{
		if(vlstr[i]<v.vlstr[i])
			return true;
		if(vlstr[i]>=v.vlstr[i])
			return false;		
	}
	return false;
}
bool verylong::operator>(const verylong& v)
{
	int i;
	if(vlstr[0]=='-' && v.vlstr[0]!='-')
		return false;
	if(vlstr[0]!='-' && v.vlstr[0]=='-')
		return true;
	if(vlstr[0]=='-' && v.vlstr[0]=='-')
	{
		if(vlen<v.vlen)
			return true;
		if(vlen>v.vlen)
			return false;
		for(i=1; i<vlen && vlstr[i]==v.vlstr[i]; i++);
		for(; i<vlen; i++)
		{
			if(vlstr[i]<v.vlstr[i])
				return true;	
			if(vlstr[i]>=v.vlstr[i])
				return false;
		}
		return false;
	}
	if(vlen<v.vlen)
		return false;
	if(vlen>v.vlen)
		return true;
	for(i=0; i<vlen && vlstr[i]==v.vlstr[i]; i++);
	for(i; i<vlen; i++)
	{
		if(vlstr[i]<v.vlstr[i])
			return false;
		if(vlstr[i]>=v.vlstr[i])
			return true;		
	}
	return true;
}
bool verylong::operator!=(const verylong& v)
{
	if(vlen!=v.vlen)
		return true;
	for(int i=0; i<vlen; i++)
		if(vlstr[i]!=v.vlstr[i])
			return true;
	return false;
}
bool verylong::operator==(const verylong& v)
{
	if(vlen!=v.vlen)
		return false;
	for(int i=0; i<vlen; i++)
		if(vlstr[i]!=v.vlstr[i])
			return false;
	return true;
}
void verylong::DeleteSignMinus(verylong& bignum)
{
	int i;
	for(i=1; i<bignum.vlen; i++)
		bignum.vlstr[i-1]=bignum.vlstr[i];
	bignum.vlstr[i-1]='\0';
	bignum.vlen--;
}
void verylong::AddSignMinus(verylong& bignum)
{
	int i;
	char* temp=new char[bignum.vlen+1];
	temp[0]='-';
	for(i=1; i<bignum.vlen; i++)
		temp[i]=bignum.vlstr[i-1];
	temp[i]=bignum.vlstr[i-1];
	temp[i+1]='\0';
	bignum.vlen++;
	strcpy(bignum.vlstr,temp);
}
void verylong::AddChar(verylong& bignum,char ch)
{
	bignum.vlstr[bignum.vlen++]=ch;
	bignum.vlstr[bignum.vlen]='\0';
}
void verylong::SwapOperands(verylong& operand1,verylong& operand2)
{
	char temp[SZ];
	int TempLength;
	strcpy(temp,operand1.vlstr);
	TempLength=operand1.vlen;
	strcpy(operand1.vlstr,operand2.vlstr);
	operand1.vlen=operand2.vlen;
	strcpy(operand2.vlstr,temp);
	operand2.vlen=TempLength;
}
verylong verylong::operator-(verylong& operand2)
{
	bool SignMinus=false,carry=0,SwappedOperands=false;
	bool FirstOperandSignMinus=false,SecondOperandSignMinus=false;	
	if(*this<operand2)
	{
		if((vlstr[0]!='-' && operand2.vlstr[0]!='-') || (vlstr[0]=='-' && operand2.vlstr[0]!='-'))
		{			
			SwapOperands(*this,operand2);
			SwappedOperands=true;
		}
		SignMinus=true;
	}
	else
		if(vlstr[0]=='-' && operand2.vlstr[0]=='-')
		{
			SwapOperands(*this,operand2);
			SwappedOperands=true;
		}
	if(vlstr[0]=='-' && operand2.vlstr[0]=='-')
	{
		DeleteSignMinus(*this);
		DeleteSignMinus(operand2);
		FirstOperandSignMinus=true;
		SecondOperandSignMinus=true;
	}
	else
		if(vlstr[0]!='-' && operand2.vlstr[0]=='-')
		{
			verylong op1(vlstr);
			verylong op2(operand2.vlstr);
			DeleteSignMinus(op2);
			verylong result=op1+op2;
			if(SignMinus && result.vlstr[0]!='0')
				AddSignMinus(result);
			if(SwappedOperands)
				SwapOperands(*this,operand2);
			return result;
		}	
	int i,j;
	char* bignum1=new char[vlen+10],OperationResult;
	char* bignum2=new char[vlen+10];
	char* result=new char[vlen+10];
	strcpy(bignum1,vlstr);
	for(i=0; i<vlen-operand2.vlen; i++)
		bignum2[i]='0';
	for(j=0; j<operand2.vlen; j++,i++)
		bignum2[i]=operand2.vlstr[j];
	bignum2[i]='\0';
	result[vlen]='\0';
	for(i=vlen-1; i>-1; i--)	
		if(bignum1[i]-carry<bignum2[i])
		{
			result[i]=((bignum1[i]-carry+10)-bignum2[i])+'0';
			carry=1;
		}		
		else
		{
			result[i]=(bignum1[i]-bignum2[i]-carry)+'0';
			carry=0;			
		}
	result[0]-=carry;
	for(i=0; result[i]=='0' && i<vlen; i++);
	if(i==vlen)
		i--;
	verylong VerylongResult(&result[i]);	
	if(SwappedOperands)
		SwapOperands(*this,operand2);	
	delete[]bignum1;
	delete[]bignum2;	
	delete[]result;
	if(SignMinus && VerylongResult.vlstr[0]!='0')	
		AddSignMinus(VerylongResult);
	if(FirstOperandSignMinus)
		AddSignMinus(*this);
	if(SecondOperandSignMinus)
		AddSignMinus(operand2);
	return VerylongResult;
}
void verylong::CopyVerylong(verylong& destination,verylong& source)
{
	strcpy(destination.vlstr,source.vlstr);
	destination.vlen=source.vlen;	
}
verylong verylong::operator/(verylong& operand2)
{
	if(vlstr[0]=='0' || operand2.vlstr[0]=='0')
		return verylong("0");
	bool SignMinus=false;
	bool FirstOperandSignMinus=false,SecondOperandSignMinus=false;
	verylong one("1");
	verylong zero("0");
	if(vlstr[0]=='-' && operand2.vlstr[0]=='-')
	{
		DeleteSignMinus(*this);
		DeleteSignMinus(operand2);
		FirstOperandSignMinus=true;
		SecondOperandSignMinus=true;
	}
	if((vlstr[0]=='-' && operand2.vlstr[0]!='-')||(vlstr[0]!='-' && operand2.vlstr[0]=='-'))
	{
		SignMinus=true;
		if(vlstr[0]=='-')
		{
			DeleteSignMinus(*this);
			FirstOperandSignMinus=true;
		}
		else
			if(operand2.vlstr[0]=='-')
			{
				DeleteSignMinus(operand2);
				SecondOperandSignMinus=true;
			}
	}
	verylong dividend(vlstr);
	verylong result("0");
	verylong quotient("0");
	dividend=dividend-operand2;
	while(dividend>zero)
	{		
		result=result+one;
		dividend=dividend-operand2;
	}	
	if(IntegerDivision || dividend+operand2==zero)
	{
		if(SignMinus)
			AddSignMinus(result);	
		if(FirstOperandSignMinus)
			AddSignMinus(*this);
		if(SecondOperandSignMinus)
			AddSignMinus(operand2);
		IntegerDivision=false;
		return result;
	}	
	int precision=DevisionPrecision;
	verylong minuend(vlstr);
	verylong product(result*operand2);	
	verylong difference=minuend-product;
	AddChar(result,'.');	
	while(precision-->0 && difference!=zero)
	{
		AddChar(difference,'0');
		CopyVerylong(minuend,difference);
		CopyVerylong(dividend,difference);
		CopyVerylong(quotient,zero);
		dividend=dividend-operand2;		
		while(dividend>zero)
		{
			quotient=quotient+one;
			dividend=dividend-operand2;
		}
		AddChar(result,quotient.vlstr[0]);
		product=quotient*operand2;
		difference=minuend-product;
	}
	if(SignMinus)
		AddSignMinus(result);	
	if(FirstOperandSignMinus)
		AddSignMinus(*this);
	if(SecondOperandSignMinus)
		AddSignMinus(operand2);
	return result;
}