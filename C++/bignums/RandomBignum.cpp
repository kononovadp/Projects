#include "RandomBignum.h"
int GetPointPosition(char* number,int length)
{
	int i,position=length;
	for(i=0; i<length; i++)
		if(number[i]=='.')
			return i;
	return position;
}
bool IsLess(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length)
{
	if(bignum1[0]=='-' && bignum2[0]!='-')
		return true;
	if(bignum1[0]!='-' && bignum2[0]=='-')
		return false;
	int i,Operand1PointPos=GetPointPosition(bignum1,Bignum1Length);
	int Operand2PointPos=GetPointPosition(bignum2,Bignum2Length);
	if(bignum1[0]=='-' && bignum2[0]=='-')
	{
		if(Operand1PointPos<Operand2PointPos)
			return false;
		if(Operand1PointPos>Operand2PointPos)
			return true;
		for(i=0; i<Bignum1Length && i<Bignum2Length && bignum1[i]==bignum2[i]; i++);
		for(; i<Operand1PointPos && i<Operand2PointPos; i++)
		{
			if(bignum1[i]<bignum2[i])
				return false;
			if(bignum1[i]>bignum2[i])
				return true;
		}
		int Operand1FractPartSize=Bignum1Length-Operand1PointPos-1;
		int Operand2FractPartSize=Bignum2Length-Operand2PointPos-1;
		if(Operand1FractPartSize<Operand2FractPartSize)
		{
			for(i=Operand1PointPos+1; i<Bignum1Length; i++)
			{
				if(bignum1[i]<bignum2[i])
					return false;
				if(bignum1[i]>bignum2[i])
					return true;
			}
			for(; i<Bignum2Length; i++)		
				if(bignum2[i]>'0')
					return false;
		}
		else
			if(Operand1FractPartSize>Operand2FractPartSize)
			{
				for(i=Operand2PointPos+1; i<Bignum1Length && i<Bignum2Length && bignum1[i]==bignum2[i]; i++);
				for(; i<Bignum2Length; i++)
				{
					if(bignum1[i]<bignum2[i])
						return false;
					if(bignum1[i]>bignum2[i])
						return true;
				}
				for(; i<Bignum1Length; i++)
					if(bignum1[i]>'0')
						return true;
			}
		for(i=Operand1PointPos+1; i<Bignum1Length; i++)
		{
			if(bignum1[i]<bignum2[i])
				return false;
			if(bignum1[i]>bignum2[i])
				return true;
		}
		return true;
	}
	if(Operand1PointPos<Operand2PointPos)
		return true;
	if(Operand1PointPos>Operand2PointPos)
		return false;
	for(i=0; i<Bignum1Length && i<Bignum2Length && bignum1[i]==bignum2[i]; i++);
	for(; i<Operand1PointPos && i<Operand2PointPos; i++)
	{
		if(bignum1[i]<bignum2[i])
			return true;
		if(bignum1[i]>bignum2[i])
			return false;
	}
	int Operand1FractPartSize=Bignum1Length-Operand1PointPos-1;
	int Operand2FractPartSize=Bignum2Length-Operand2PointPos-1;
	if(Operand1FractPartSize<Operand2FractPartSize)
	{
		for(i=Operand1PointPos+1; i<Bignum1Length; i++)
		{
			if(bignum1[i]<bignum2[i])
				return true;
			if(bignum1[i]>bignum2[i])
				return false;
		}
		for(; i<Bignum2Length; i++)		
			if(bignum2[i]>'0')
				return true;
	}
	else
		if(Operand1FractPartSize>Operand2FractPartSize)
		{
			for(i=Operand2PointPos+1; i<Bignum1Length && i<Bignum2Length && bignum1[i]==bignum2[i]; i++);
			for(; i<Bignum2Length; i++)
			{
				if(bignum1[i]<bignum2[i])
					return true;
				if(bignum1[i]>bignum2[i])
					return false;
			}
			for(; i<Bignum1Length; i++)
				if(bignum1[i]>'0')
					return false;
		}
	for(i=Operand1PointPos+1; i<Bignum1Length; i++)
	{
		if(bignum1[i]<bignum2[i])
			return true;
		if(bignum1[i]>bignum2[i])
			return false;
	}
	return false;
}
bool IsGreater(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length)
{
	if(bignum1[0]=='-' && bignum2[0]!='-')
		return false;
	if(bignum1[0]!='-' && bignum2[0]=='-')
		return true;
	int i,Operand1PointPos=GetPointPosition(bignum1,Bignum1Length);
	int Operand2PointPos=GetPointPosition(bignum2,Bignum2Length);
	if(bignum1[0]=='-' && bignum2[0]=='-')
	{
		if(Operand1PointPos<Operand2PointPos)
			return true;
		if(Operand1PointPos>Operand2PointPos)
			return false;
		for(i=0; i<Bignum1Length && i<Bignum2Length && bignum1[i]==bignum2[i]; i++);
		for(; i<Operand1PointPos && i<Operand2PointPos; i++)
		{
			if(bignum1[i]<bignum2[i])
				return true;
			if(bignum1[i]>bignum2[i])
				return false;
		}
		int Operand1FractPartSize=Bignum1Length-Operand1PointPos-1;
		int Operand2FractPartSize=Bignum2Length-Operand2PointPos-1;
		if(Operand1FractPartSize<Operand2FractPartSize)
		{
			for(i=Operand1PointPos+1; i<Bignum1Length; i++)
			{
				if(bignum1[i]<bignum2[i])
					return true;
				if(bignum1[i]>bignum2[i])
					return false;
			}
			for(; i<Bignum2Length; i++)
				if(bignum2[i]>'0')
					return true;
		}
		else
		{
			if(Operand1FractPartSize>Operand2FractPartSize)
			{
				for(i=Operand2PointPos+1; i<Bignum1Length && i<Bignum2Length && bignum1[i]==bignum2[i]; i++);
				for(; i<Bignum2Length; i++)
				{
					if(bignum1[i]<bignum2[i])
						return true;
					if(bignum1[i]>bignum2[i])
						return false;
				}
				for(; i<Bignum1Length; i++)
					if(bignum1[i]>'0')
						return false;
			}
			for(i=Operand1PointPos+1; i<Bignum1Length; i++)
			{
				if(bignum1[i]<bignum2[i])
					return true;
				if(bignum1[i]>bignum2[i])
					return false;
			}
			return false;
		}
	}
	if(Operand1PointPos<Operand2PointPos)
		return false;
	if(Operand1PointPos>Operand2PointPos)
		return true;
	for(i=0; i<Bignum1Length && i<Bignum2Length && bignum1[i]==bignum2[i]; i++);
	for(; i<Operand1PointPos && i<Operand2PointPos; i++)
	{
		if(bignum1[i]<bignum2[i])
			return false;
		if(bignum1[i]>bignum2[i])
			return true;
	}
	int Operand1FractPartSize=Bignum1Length-Operand1PointPos-1;
	int Operand2FractPartSize=Bignum2Length-Operand2PointPos-1;
	if(Operand1FractPartSize<Operand2FractPartSize)
	{
		for(i=Operand1PointPos+1; i<Bignum1Length; i++)
		{
			if(bignum1[i]<bignum2[i])
				return false;
			if(bignum1[i]>bignum2[i])
				return true;
		}
		for(; i<Bignum2Length; i++)		
			if(bignum2[i]>'0')
				return false;
	}
	else
		if(Operand1FractPartSize>Operand2FractPartSize)
		{
			for(i=Operand2PointPos+1; i<Bignum1Length && i<Bignum2Length && bignum1[i]==bignum2[i]; i++);
			for(; i<Bignum2Length; i++)
			{
				if(bignum1[i]<bignum2[i])
					return false;
				if(bignum1[i]>bignum2[i])
					return true;
			}
			for(; i<Bignum1Length; i++)
				if(bignum1[i]>'0')
					return true;
		}
	for(i=Operand1PointPos+1; i<Bignum1Length; i++)
	{
		if(bignum1[i]<bignum2[i])
			return false;
		if(bignum1[i]>bignum2[i])
			return true;
	}
	return true;
}
bool IsEqual(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length)
{
	if(Bignum1Length!=Bignum2Length)
		return false;
	for(int i=0; i<Bignum1Length; i++)
		if(bignum1[i]!=bignum2[i])
			return false;
	return true;
}
bool IsNotEqual(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length)
{
	if(Bignum1Length!=Bignum2Length)
		return true;
	for(int i=0; i<Bignum1Length; i++)
		if(bignum1[i]!=bignum2[i])
			return true;
	return false;
}
void DisplayBignum(char* number,int length)
{
	bool SignMinus=(number[0]=='-')?1:0;
	int i,j;
	if(length-SignMinus<11)
		cout<<number;
	else
	{
		int PointPosition=GetPointPosition(number,length);
		if(PointPosition==length)
		{
			if(!SignMinus)
				cout<<number[0]<<number[1]<<number[2]<<number[3]<<".."<<number[length-4]<<number[length-3]<<number[length-2]<<number[length-1];
			else
				cout<<number[0]<<number[1]<<number[2]<<number[3]<<number[4]<<".."<<number[length-4]<<number[length-3]<<number[length-2]<<number[length-1];
		}
		else
		{
			if(PointPosition-SignMinus<11)
				for(i=0; i<PointPosition; i++)
					cout<<number[i];
			else
			{
				if(!SignMinus)
					cout<<number[0]<<number[1]<<number[2]<<number[3]<<".."<<number[PointPosition-4]<<number[PointPosition-3]<<number[PointPosition-2]<<number[PointPosition-1];
				else
					cout<<number[0]<<number[1]<<number[2]<<number[3]<<number[4]<<".."<<number[PointPosition-4]<<number[PointPosition-3]<<number[PointPosition-2]<<number[PointPosition-1];
			}
			cout<<".";
			int FractionalPartLength=length-PointPosition-1;
			if(FractionalPartLength<11)
				for(i=PointPosition+1; i<length; i++)
					cout<<number[i];
			else
			{
				if(number[length-1]=='.')
				{
					FractionalPartLength-=3;
					if(FractionalPartLength<11)
						for(i=PointPosition+1; i<length; i++)
							cout<<number[i];
					else
						cout<<number[PointPosition+1]<<number[PointPosition+2]<<number[PointPosition+3]<<number[PointPosition+4]<<".."<<number[length-7]<<number[length-6]<<number[length-5]<<number[length-4]<<"...";
				}
				else
					if(number[length-1]==')')
					{
						int LengthOfNonperiodicPart=0;
						for(i=PointPosition; number[i]!='('; i++,LengthOfNonperiodicPart++);
						if(LengthOfNonperiodicPart<11)
							for(j=PointPosition+1; j<i; j++)
								cout<<number[j];
						else
							cout<<number[PointPosition+1]<<number[PointPosition+2]<<number[PointPosition+3]<<number[PointPosition+4]<<".."<<number[i-4]<<number[i-3]<<number[i-2]<<number[i-1];
						if(length-i<11)
							for(; i<length; i++)
								cout<<number[i];
						else
							cout<<number[i]<<number[i+1]<<number[i+2]<<number[i+3]<<number[i+4]<<".."<<number[length-5]<<number[length-4]<<number[length-3]<<number[length-2]<<number[length-1];
					}
					else					
						cout<<number[PointPosition+1]<<number[PointPosition+2]<<number[PointPosition+3]<<number[PointPosition+4]<<".."<<number[length-4]<<number[length-3]<<number[length-2]<<number[length-1];
			}			
		}
	}
	cout<<"L"<<length;
}
char* GetRandomBignum(int CountOfDigits,bool SignMinus,bool FloatingPoint)
{
	// SignMinus=false;
	// FloatingPoint=false;
	int length=CountOfDigits+SignMinus+FloatingPoint;
	// char* RandomBignum=(char*)calloc(MaxBignumLength+MaxFractPartLength+3,sizeof(char));
	char* RandomBignum=(char*)malloc(MaxBignumLength+MaxFractPartLength+3);
	RandomBignum[length]=0;
	int i=SignMinus,FloatingPointPosition;
	if(SignMinus)
		RandomBignum[0]='-';
	if(CountOfDigits<2)
	{
		length-=FloatingPoint;
		FloatingPoint=false;
	}
	if(FloatingPoint)
	{
		RandomBignum[i]=GetRandomDigit('0','9');
		if(RandomBignum[i]=='0' || CountOfDigits==2)
			FloatingPointPosition=1;
		else
			FloatingPointPosition=GetRandomInt(1,length-1);
		for(i++; i<FloatingPointPosition; i++)
			RandomBignum[i]=GetRandomDigit('0','9');
		RandomBignum[i]='.';
		for(i++; i<length-1; i++)
			RandomBignum[i]=GetRandomDigit('0','9');
		RandomBignum[i++]=GetRandomDigit('1','9');
	}
	else
		for(RandomBignum[i++]=GetRandomDigit('1','9'); i<length; i++)
			RandomBignum[i]=GetRandomDigit('0','9');
	RandomBignum[i]='\0';
	length=i;
	return RandomBignum;
}
void SetRandomIntBignum(char* number,int& length,char* min,char* max,int MinPointPos,int MaxPointPos)
{
	int i;
	length=GetRandomInt(MinPointPos,MaxPointPos+1);
	for(i=0; i<length && i<MinPointPos && i<MaxPointPos && min[i]==max[i]; i++)
		number[i]=min[i];
	if(length==MaxPointPos)
	{
		if(i<MinPointPos && ((min[i]=='0' && length==1) || (min[i]>'0' && length>=1)))
			number[i]=GetRandomDigit(min[i],max[i]);
		else
			number[i]=GetRandomDigit('1',max[i]);
		if(number[i]==min[i])
		{
			for(i++; i<MinPointPos; i++)
			{
				number[i]=GetRandomDigit(min[i],'9');
				if(number[i]>min[i] && number[i]<='9')
				{
					for(i++; i<length; i++)
						number[i]=GetRandomDigit('0','9');
					break;
				}
			}
			for(; i<length; i++)
				number[i]=GetRandomDigit('0','9');
		}
		else
			if(number[i]==max[i])
			{
				for(i++; i<MaxPointPos; i++)
				{
					number[i]=GetRandomDigit('0',max[i]);
					if(number[i]<max[i] && number[i]>='0')
					{
						for(i++; i<length; i++)
							number[i]=GetRandomDigit('0','9');
						break;
					}
				}
				for(; i<length; i++)
					number[i]=GetRandomDigit('0','9');
			}
			else
				for(i++; i<length; i++)
					number[i]=GetRandomDigit('0','9');
	}
	else
	{
		if(length==MinPointPos)
		{
			for(; i<length; i++)
			{
				number[i]=GetRandomDigit(min[i],'9');
				if(number[i]>min[i] && number[i]<='9')
				{
					for(i++; i<length; i++)
						number[i]=GetRandomDigit('0','9');
					break;
				}
			}
		}
		else
		{
			if(length==1)
				number[0]=GetRandomDigit('0','9');
			else
				for(number[0]=GetRandomDigit('1','9'),i=1; i<length; i++)
					number[i]=GetRandomDigit('0','9');
		}
	}
	number[length]='\0';
}
void SetRandomFloatBignum(char* number,int& length,char* min,char* max,int MinPointPos,int MaxPointPos)
{
	int MinLength=strlen(min),MaxLength=strlen(max);
	int i,MinFractPartLength,MaxFractPartLength,RandomFractPartLength;
	char* MinFractPart=(char*)malloc(MaxBignumLength+3);
	char* MaxFractPart=(char*)malloc(MaxBignumLength+3);
	char* RandomFractPart=(char*)malloc(MaxBignumLength+3);
	for(i=MinPointPos+1,MinFractPartLength=0; i<MinLength; i++,MinFractPartLength++)
		MinFractPart[MinFractPartLength]=min[i];
	for(i=MaxPointPos+1,MaxFractPartLength=0; i<MaxLength; i++,MaxFractPartLength++)
		MaxFractPart[MaxFractPartLength]=max[i];
	if(MinFractPartLength<MaxFractPartLength)
		RandomFractPartLength=GetRandomInt(MinFractPartLength,MaxFractPartLength+1);
	else
		RandomFractPartLength=MinFractPartLength;
	for(; MinFractPartLength<MaxFractPartLength; MinFractPartLength++)
		MinFractPart[MinFractPartLength]='0';
	for(; MaxFractPartLength<MinFractPartLength; MaxFractPartLength++)
		MaxFractPart[MaxFractPartLength]='0';
	MinFractPart[MinFractPartLength]='\0';
	MaxFractPart[MaxFractPartLength]='\0';
	for(i=0; i<MinFractPartLength && i<MaxFractPartLength && MinFractPart[i]==MaxFractPart[i]; i++)
		RandomFractPart[i]=MinFractPart[i];
	if(i<MinFractPartLength)
	{
		RandomFractPart[i]=GetRandomDigit(MinFractPart[i],MaxFractPart[i]);
		if(RandomFractPart[i]==MinFractPart[i])
		{
			for(i++; i<RandomFractPartLength; i++)
			{
				RandomFractPart[i]=GetRandomDigit(MinFractPart[i],'9');
				if(RandomFractPart[i]>MinFractPart[i] && RandomFractPart[i]<'9')
				{
					for(i++; i<RandomFractPartLength; i++)
						RandomFractPart[i]=GetRandomDigit('0','9');
					break;
				}
			}
		}
		else
			if(RandomFractPart[i]==MaxFractPart[i])
			{
				for(i++; i<RandomFractPartLength; i++)
				{
					RandomFractPart[i]=GetRandomDigit('0',MaxFractPart[i]);
					if(RandomFractPart[i]>'0' && RandomFractPart[i]<MaxFractPart[i])
					{
						for(i++; i<RandomFractPartLength; i++)
							RandomFractPart[i]=GetRandomDigit('0','9');
						break;
					}
				}
			}
			else
				for(i++; i<RandomFractPartLength; i++)
					RandomFractPart[i]=GetRandomDigit('0','9');
	}
	RandomFractPart[i]='\0';
	RandomFractPartLength=i;
	if(RandomFractPartLength>0)
	{
		number[length++]='.';
		for(i=0; i<RandomFractPartLength; i++,length++)
			number[length]=RandomFractPart[i];
		i=length-1;
		while(number[i]=='0')
			i--;
		if(number[i]=='.')
			i--;
		number[i+1]='\0';
		length=i+1;
	}
	free(MinFractPart);
	free(MaxFractPart);
	free(RandomFractPart);
}
inline void SetRandomUnsignedBignum(char* number,int& length,char* min,char* max,bool SignMinus)
{
	int MinLength=strlen(min),MaxLength=strlen(max);
	int i,j,MinPointPos=GetPointPosition(min,MinLength);
	int MaxPointPos=GetPointPosition(max,MaxLength);
	SetRandomIntBignum(number,length,min,max,MinPointPos,MaxPointPos);
	if(MinPointPos!=MinLength || MaxPointPos!=MaxLength)
	{
		for(i=0; i<MinPointPos && i<MaxPointPos; i++)
			if(min[i]!=max[i])
				break;
		if(i==MaxPointPos && MinPointPos==MaxPointPos)
			SetRandomFloatBignum(number,length,min,max,MinPointPos,MaxPointPos);
		else
		{
			for(i=0; i<length && i<MinPointPos; i++)
				if(number[i]!=min[i])
					break;
			if(i==MinPointPos && length==MinPointPos)
			{
				char* NewMaxWithoutSign=(char*)calloc(MaxBignumLength+MaxFractPartLength+3,sizeof(char));
				for(i=0; i<MinPointPos; i++)
					NewMaxWithoutSign[i]=number[i];
				NewMaxWithoutSign[i++]='.';
				int FractPartSize;
				int MinFractPartSize=MinLength-MinPointPos-1;
				int MaxFractPartSize=MaxLength-MaxPointPos-1;
				if(MaxFractPartSize>MinFractPartSize)
					FractPartSize=MaxFractPartSize;
				else
					FractPartSize=MinFractPartSize;
				FractPartSize+=GetRandomInt(0,MaxBignumLength-i-SignMinus-FractPartSize);
				if(i+SignMinus+FractPartSize>MaxBignumLength)
					FractPartSize=FractPartSize-(i+SignMinus+FractPartSize-MaxBignumLength);
				for(j=0; j<FractPartSize; j++,i++)
					NewMaxWithoutSign[i]='9';
				NewMaxWithoutSign[i]='\0';
				SetRandomFloatBignum(number,length,min,NewMaxWithoutSign,MinPointPos,GetPointPosition(NewMaxWithoutSign,i));
				free(NewMaxWithoutSign);
			}
			else
			{
				for(i=0; i<length && i<MaxPointPos; i++)
					if(number[i]!=max[i])
						break;
				if(i==MaxPointPos && length==MaxPointPos)
				{
					char* NewMinWithoutSign=(char*)calloc(MaxBignumLength+MaxFractPartLength+3,sizeof(char));
					for(i=0; i<MaxPointPos; i++)
						NewMinWithoutSign[i]=number[i];
					NewMinWithoutSign[i++]='.';
					int FractPartSize;
					int MinFractPartSize=MinLength-MinPointPos-1;
					int MaxFractPartSize=MaxLength-MaxPointPos-1;
					if(MaxFractPartSize>MinFractPartSize)
						FractPartSize=MaxFractPartSize;
					else
						FractPartSize=MinFractPartSize;
					FractPartSize+=GetRandomInt(0,MaxBignumLength-i-SignMinus-FractPartSize);
					if(i+SignMinus+FractPartSize>MaxBignumLength)
						FractPartSize=FractPartSize-(i+SignMinus+FractPartSize-MaxBignumLength);
					for(j=0; j<FractPartSize; j++,i++)
						NewMinWithoutSign[i]='0';
					NewMinWithoutSign[i]='\0';
					SetRandomFloatBignum(number,length,NewMinWithoutSign,max,GetPointPosition(NewMinWithoutSign,i),MaxPointPos);
					free(NewMinWithoutSign);
				}
				else
				{
					number[length++]='.';
					i=length;
					int MinFractPartSize=MinLength-MinPointPos-1;
					int MaxFractPartSize=MaxLength-MaxPointPos-1;
					if(MinFractPartSize<MaxFractPartSize)
						length+=GetRandomInt(MinFractPartSize,MaxFractPartSize+1);
					else
						length+=GetRandomInt(MaxFractPartSize,MinFractPartSize+1);
					length+=GetRandomInt(0,MaxBignumLength-length-SignMinus-1);
					while(length+SignMinus>MaxBignumLength)
						length--;
					for(; i<length-1; i++)
						number[i]=GetRandomDigit('0','9');
					number[i]=GetRandomDigit('1','9');
					number[i+1]='\0';
					length=i+1;
				}
			}
		}
	}
}
char* GetRandomBignum(char* min,char* max)
{
	int i,length=0,PointPosition;
	bool SignMinus=false;
	char* ZeroOrOne=(char*)malloc(2);
	char* number=(char*)malloc(MaxBignumLength+MaxFractPartLength+3);
	ZeroOrOne[1]='\0';
	if(min[0]=='-' && max[0]=='-')
	{
		min=&min[1];
		// MinLength--;
		max=&max[1];
		// MaxLength--;
		number[0]='-';
		number=&number[1];
		SignMinus=true;
		SetRandomUnsignedBignum(number,length,max,min,SignMinus);
		min=&min[0]-1;
		// MinLength++;
		max=&max[0]-1;
		// MaxLength++;
	}
	else
		if(min[0]=='-' && max[0]!='-')
		{
			min=&min[1];
			// MinLength--;
			if(GetRandomInt(0,10)<5)
			{
				ZeroOrOne[0]='1';
				SignMinus=true;
				number[0]='-';
				number=&number[1];
				SetRandomUnsignedBignum(number,length,ZeroOrOne,min,SignMinus);
			}
			else
			{
				ZeroOrOne[0]='0';
				SetRandomUnsignedBignum(number,length,ZeroOrOne,max,SignMinus);
			}
			min=&min[0]-1;
			// MinLength++;
		}
		else
			SetRandomUnsignedBignum(number,length,min,max,SignMinus);
	free(ZeroOrOne);
	if(SignMinus)
	{
		number=&number[0]-1;
		length++;
		if(number[1]=='0' && length==2)
		{
			number[0]='0';
			number[1]='\0';
			length=1;
		}
	}
	for(i=SignMinus,PointPosition=GetPointPosition(number,length); i<PointPosition; i++)
		if(!isdigit(number[i]))
		{
			cout<<"Random bignum contains non-digital symbol: "<<number[i]<<" ("<<(int)number[i]<<") in the position "<<i<<"; point position: "<<PointPosition<<endl
				<<"Current bignum: "<<number<<endl
			    <<"Min bignum: "<<min<<"; max bignum: "<<max;
			my_getch(); exit(0);
		}
	for(i++; i<length; i++)
		if(!isdigit(number[i]))
		{
			cout<<"Random bignum contains non-digital symbol: "<<number[i]<<" ("<<(int)number[i]<<") in the position "<<i<<"; length: "<<length<<endl
				<<"Current bignum: "<<number<<endl
			    <<"Min bignum: "<<min<<"; max bignum: "<<max;
			my_getch(); exit(0);
		}
	if(IsEqual(number,length,max,strlen(max)) || IsEqual(number,length,min,strlen(min)))
		return number;
	if((length>1 && GetPointPosition(number,length)==length && number[0]=='0') || (GetPointPosition(number,length)!=length && number[length-1]=='0' && length>1) || (number[length-1]=='.'))
	{
		cout<<"Incorrect random bignum: ";
		DisplayBignum(number,length);
		my_getch(); exit(0);
	}
	if(IsGreater(number,length,max,strlen(max)))
	{
		cout<<"Incorrect random bignum: ";
		DisplayBignum(number,length);
		cout<<" > ";
		DisplayBignum(max,strlen(max));
		my_getch(); exit(0);
	}
	else
		if(IsLess(number,length,min,strlen(min)))
		{
			cout<<"Incorrect random bignum: ";
			DisplayBignum(number,length);
			cout<<" < ";
			DisplayBignum(min,strlen(min));
			my_getch(); exit(0);
		}
	return number;
}
void SwapBignums(char*& bignum1,int& Bignum1Length,char*& bignum2,int& Bignum2Length)
{
	char* temp=bignum1;
	bignum1=bignum2;
	bignum2=temp;
	int TempLength=Bignum1Length;
	Bignum1Length=Bignum2Length;
	Bignum2Length=TempLength;
}
