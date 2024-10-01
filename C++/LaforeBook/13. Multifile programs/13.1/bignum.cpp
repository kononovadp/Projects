#include "bignum.h"
bignum::bignum()
{	
	length=0;
	number=new char[MaxLength];
}
bignum::bignum(char* NewNumber)
{
	number=NewNumber;
	for(length=0; number[length]!='\0'; length++);
}
bignum::bignum(char* NewNumber,int NewLength)
{
	number=NewNumber;
	length=NewLength;
}
bignum::~bignum()
{
	delete[] number;
	length=0;	
}
void bignum::display()
{
	bool SignMinus=(number[0]=='-')?1:0;
	int i,j;
	if(length-SignMinus<11)
		cout<<number;
	else
	{
		int PointPosition=GetPointPosition();
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
int bignum::GetPointPosition()
{
	int i,position=length;
	for(i=0; i<length; i++)
		if(number[i]=='.')
			return i;
	return position;
}
void bignum::SetRandomBignum(int CountOfDigits,bool SignMinus,bool FloatingPoint)
{
	length=CountOfDigits+SignMinus+FloatingPoint;
	if(length>MaxLength)
	{
		length-=SignMinus;
		SignMinus=false;
	}
	if(length>MaxLength)
	{
		length-=FloatingPoint;
		FloatingPoint=false;
	}
	while(length>=MaxLength)
	{
		length--;
		CountOfDigits--;
	}
	int i=SignMinus,FloatingPointPosition;
	if(SignMinus)
		number[0]='-';
	if(CountOfDigits<2)
	{
		length-=FloatingPoint;
		FloatingPoint=false;
	}
	if(FloatingPoint)
	{
		number[i]=GetRandomDigit('0','9');
		if(number[i]=='0' || CountOfDigits==2)
			FloatingPointPosition=1;
		else
			FloatingPointPosition=GetRandomInt(1,length-1);
		for(i++; i<FloatingPointPosition; i++)
			number[i]=GetRandomDigit('0','9');
		number[i]='.';
		for(i++; i<length-1; i++)
			number[i]=GetRandomDigit('0','9');
		number[i++]=GetRandomDigit('1','9');
	}
	else
		for(number[i++]=GetRandomDigit('1','9'); i<length; i++)
			number[i]=GetRandomDigit('0','9');
	number[i]='\0';	
	length=i;
}
void bignum::SetRandomIntBignum(bignum* min,bignum* max,int MinPointPos,int MaxPointPos)
{
	int i;
	length=GetRandomInt(MinPointPos,MaxPointPos+1);
	for(i=0; i<length && i<MinPointPos && i<MaxPointPos && min->number[i]==max->number[i]; i++)
		number[i]=min->number[i];
	if(length==MaxPointPos)
	{		
		if(i<MinPointPos && ((min->number[i]=='0' && length==1) || (min->number[i]>'0' && length>=1)))
			number[i]=GetRandomDigit(min->number[i],max->number[i]);
		else
			number[i]=GetRandomDigit('1',max->number[i]);		
		if(number[i]==min->number[i])
		{
			for(i++; i<MinPointPos; i++)
			{
				number[i]=GetRandomDigit(min->number[i],'9');
				if(number[i]>min->number[i] && number[i]<='9')
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
			if(number[i]==max->number[i])
			{
				for(i++; i<MaxPointPos; i++)
				{
					number[i]=GetRandomDigit('0',max->number[i]);
					if(number[i]<max->number[i] && number[i]>='0')
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
				number[i]=GetRandomDigit(min->number[i],'9');
				if(number[i]>min->number[i] && number[i]<='9')
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
void bignum::SetRandomFloatBignum(bignum* min,bignum* max,int MinPointPos,int MaxPointPos)
{
	int i,j,MinFractPartLength,MaxFractPartLength,RandomFractPartLength;
	char* MinFractPart=new char[MaxLength];
	char* MaxFractPart=new char[MaxLength];
	char* RandomFractPart=new char[MaxLength+1];
	for(i=MinPointPos+1,MinFractPartLength=0; i<min->length; i++,MinFractPartLength++)
		MinFractPart[MinFractPartLength]=min->number[i];
	for(i=MaxPointPos+1,MaxFractPartLength=0; i<max->length; i++,MaxFractPartLength++)
		MaxFractPart[MaxFractPartLength]=max->number[i];
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
					RandomFractPart[i]=GetRandomDigit('0','9');	}
	while(RandomFractPart[i-1]=='0')
		i--;
	if(RandomFractPart[i-1]=='.')
		i--;
	RandomFractPart[i]='\0';
	RandomFractPartLength=i;
	if(RandomFractPartLength>0)
	{
		number[length++]='.';
		for(i=0; i<RandomFractPartLength; i++,length++)
			number[length]=RandomFractPart[i];
		number[length]='\0';
	}
	delete[] MinFractPart;
	delete[] MaxFractPart;
	delete[] RandomFractPart;
}
inline void bignum::SetRandomUnsignedBignum(bignum* min,bignum* max,bool SignMinus)
{
	int i,j,MinPointPos=min->GetPointPosition();
	int MaxPointPos=max->GetPointPosition();
	SetRandomIntBignum(min,max,MinPointPos,MaxPointPos);
	if(MinPointPos!=min->length || MaxPointPos!=max->length)
	{
		for(i=0; i<MinPointPos && i<MaxPointPos; i++)
			if(min->number[i]!=max->number[i])
				break;
		if(i==MaxPointPos && MinPointPos==MaxPointPos)		
			SetRandomFloatBignum(min,max,MinPointPos,MaxPointPos);		
		else
		{
			for(i=0; i<length && i<MinPointPos; i++)
				if(number[i]!=min->number[i])
					break;
			if(i==MinPointPos && length==MinPointPos)
			{
				bignum* NewMaxWithoutSign=new bignum();
				for(i=0; i<MinPointPos; i++)
					NewMaxWithoutSign->number[i]=number[i];
				NewMaxWithoutSign->number[i++]='.';
				int FractPartSize;
				int MinFractPartSize=min->length-MinPointPos-1;
				int MaxFractPartSize=max->length-MaxPointPos-1;
				if(MaxFractPartSize>MinFractPartSize)
					FractPartSize=MaxFractPartSize;
				else
					FractPartSize=MinFractPartSize;
				FractPartSize+=GetRandomInt(0,MaxLength-i-SignMinus-FractPartSize);
				if(i+SignMinus+FractPartSize>MaxLength)
					FractPartSize=FractPartSize-(i+SignMinus+FractPartSize-MaxLength);
				for(j=0; j<FractPartSize; j++,i++)
					NewMaxWithoutSign->number[i]='9';
				NewMaxWithoutSign->number[i]='\0';
				NewMaxWithoutSign->length=i;
				SetRandomFloatBignum(min,NewMaxWithoutSign,MinPointPos,NewMaxWithoutSign->GetPointPosition());
				delete NewMaxWithoutSign;
			}
			else
			{
				for(i=0; i<length && i<MaxPointPos; i++)
					if(number[i]!=max->number[i])
						break;
				if(i==MaxPointPos && length==MaxPointPos)
				{
					bignum* NewMinWithoutSign=new bignum();
					for(i=0; i<MaxPointPos; i++)
						NewMinWithoutSign->number[i]=number[i];
					NewMinWithoutSign->number[i++]='.';
					int FractPartSize;
					int MinFractPartSize=min->length-MinPointPos-1;
					int MaxFractPartSize=max->length-MaxPointPos-1;
					if(MaxFractPartSize>MinFractPartSize)
						FractPartSize=MaxFractPartSize;
					else
						FractPartSize=MinFractPartSize;
					FractPartSize+=GetRandomInt(0,MaxLength-i-SignMinus-FractPartSize);
					if(i+SignMinus+FractPartSize>MaxLength)
						FractPartSize=FractPartSize-(i+SignMinus+FractPartSize-MaxLength);
					for(j=0; j<FractPartSize; j++,i++)
						NewMinWithoutSign->number[i]='0';
					NewMinWithoutSign->number[i]='\0';
					NewMinWithoutSign->length=i;
					SetRandomFloatBignum(NewMinWithoutSign,max,NewMinWithoutSign->GetPointPosition(),MaxPointPos);
					delete NewMinWithoutSign;
				}
				else
				{
					number[length++]='.';
					i=length;
					int MinFractPartSize=min->length-MinPointPos-1;
					int MaxFractPartSize=max->length-MaxPointPos-1;
					if(MinFractPartSize<MaxFractPartSize)
						length+=GetRandomInt(MinFractPartSize,MaxFractPartSize+1);
					else
						length+=GetRandomInt(MaxFractPartSize,MinFractPartSize+1);
					length+=GetRandomInt(0,MaxLength-length-SignMinus-1);
					while(length+SignMinus>MaxLength)
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
void bignum::SetRandomBignum(bignum* min,bignum* max)
{
	int i,PointPosition;
	bool SignMinus=false;
	bignum *ZeroOrOne=new bignum();
	ZeroOrOne->number[1]='\0';
	ZeroOrOne->length=1;
	if(min->number[0]=='-' && max->number[0]=='-')
	{
		min->number=&min->number[1];
		min->length--;
		max->number=&max->number[1];
		max->length--;
		number[0]='-';
		number=&number[1];
		SignMinus=true;
		SetRandomUnsignedBignum(max,min,SignMinus);
		min->number=&min->number[0]-1;
		min->length++;
		max->number=&max->number[0]-1;
		max->length++;
	}
	else
		if(min->number[0]=='-' && max->number[0]!='-')
		{
			min->number=&min->number[1];
			min->length--;
			if(GetRandomInt(0,10)<5)
			{				
				ZeroOrOne->number[0]='1';
				SignMinus=true;
				number[0]='-';
				number=&number[1];
				SetRandomUnsignedBignum(ZeroOrOne,min,SignMinus);
			}
			else
			{
				ZeroOrOne->number[0]='0';
				SetRandomUnsignedBignum(ZeroOrOne,max,SignMinus);
			}
			min->number=&min->number[0]-1;
			min->length++;
		}
		else
			SetRandomUnsignedBignum(min,max,SignMinus);
	delete ZeroOrOne;
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
	for(i=SignMinus,PointPosition=GetPointPosition(); i<PointPosition; i++)
		if(!isdigit(number[i]))
		{
			cout<<"Random bignum contains non-digital symbol: "<<number[i]<<" ("<<(int)number[i]<<") in the position "<<i<<"; point position: "<<PointPosition<<endl
				<<"Current bignum: "<<number<<endl
			    <<"Min bignum: "<<min->number<<"; max bignum: "<<max->number;
			exit(0);
		}
	for(i++; i<length; i++)
		if(!isdigit(number[i]))
		{
			cout<<"Random bignum contains non-digital symbol: "<<number[i]<<" ("<<(int)number[i]<<") in the position "<<i<<"; length: "<<length<<endl
				<<"Current bignum: "<<number<<endl
			    <<"Min bignum: "<<min->number<<"; max bignum: "<<max->number;
			exit(0);
		}
	if(*this==max || *this==min)
		return;
	if((length>1 && GetPointPosition()==length && number[0]=='0') || (GetPointPosition()!=length && number[length-1]=='0' && length>1) || (number[length-1]=='.'))
	{
		cout<<"Incorrect random bignum: ";
		display();
		exit(0);
	}
	if(*this>max)
	{
		cout<<"Incorrect random bignum: ";
		display();
		cout<<" > ";
		max->display();
		exit(0);
	}
	else
		if(*this<min)
		{
			cout<<"Incorrect random bignum: ";
			display();
			cout<<" < ";
			min->display();
			exit(0);
		}
}
bool bignum::operator<(bignum* operand2)
{
	if(number[0]=='-' && operand2->number[0]!='-')
		return true;
	if(number[0]!='-' && operand2->number[0]=='-')
		return false;
	int i,Operand1PointPos=GetPointPosition();
	int Operand2PointPos=operand2->GetPointPosition();
	if(number[0]=='-' && operand2->number[0]=='-')
	{
		if(Operand1PointPos<Operand2PointPos)
			return false;
		if(Operand1PointPos>Operand2PointPos)
			return true;
		for(i=0; number[i]==operand2->number[i]; i++);
		for(; i<Operand1PointPos && i<Operand2PointPos; i++)
		{
			if(number[i]<operand2->number[i])
				return false;
			if(number[i]>operand2->number[i])
				return true;
		}
		int Operand1FractPartSize=length-Operand1PointPos-1;
		int Operand2FractPartSize=operand2->length-Operand2PointPos-1;
		if(Operand1FractPartSize<Operand2FractPartSize)
		{
			for(i=Operand1PointPos+1; i<length; i++)
			{
				if(number[i]<operand2->number[i])
					return false;
				if(number[i]>operand2->number[i])
					return true;
			}
			for(; i<operand2->length; i++)		
				if(operand2->number[i]>'0')
					return false;
		}
		else
			if(Operand1FractPartSize>Operand2FractPartSize)
			{
				for(i=Operand2PointPos+1; number[i]==operand2->number[i]; i++);
				for(; i<operand2->length; i++)
				{
					if(number[i]<operand2->number[i])
						return false;
					if(number[i]>operand2->number[i])
						return true;
				}
				for(; i<length; i++)
					if(number[i]>'0')
						return true;
			}
		for(i=Operand1PointPos+1; i<length; i++)
		{
			if(number[i]<operand2->number[i])
				return false;
			if(number[i]>operand2->number[i])
				return true;
		}
		return true;
	}
	if(Operand1PointPos<Operand2PointPos)
		return true;
	if(Operand1PointPos>Operand2PointPos)
		return false;
	for(i=0; number[i]==operand2->number[i]; i++);
	for(; i<Operand1PointPos && i<Operand2PointPos; i++)
	{
		if(number[i]<operand2->number[i])
			return true;
		if(number[i]>operand2->number[i])
			return false;
	}
	int Operand1FractPartSize=length-Operand1PointPos-1;
	int Operand2FractPartSize=operand2->length-Operand2PointPos-1;
	if(Operand1FractPartSize<Operand2FractPartSize)
	{
		for(i=Operand1PointPos+1; i<length; i++)
		{
			if(number[i]<operand2->number[i])
				return true;
			if(number[i]>operand2->number[i])
				return false;
		}
		for(; i<operand2->length; i++)		
			if(operand2->number[i]>'0')
				return true;
	}
	else
		if(Operand1FractPartSize>Operand2FractPartSize)
		{
			for(i=Operand2PointPos+1; number[i]==operand2->number[i]; i++);
			for(; i<operand2->length; i++)
			{
				if(number[i]<operand2->number[i])
					return true;
				if(number[i]>operand2->number[i])
					return false;
			}
			for(; i<length; i++)
				if(number[i]>'0')
					return false;
		}
	for(i=Operand1PointPos+1; i<length; i++)
	{
		if(number[i]<operand2->number[i])
			return true;
		if(number[i]>operand2->number[i])
			return false;
	}
	return false;
}
bool bignum::operator>(bignum* operand2)
{
	if(number[0]=='-' && operand2->number[0]!='-')
		return false;
	if(number[0]!='-' && operand2->number[0]=='-')
		return true;
	int i,Operand1PointPos=GetPointPosition();
	int Operand2PointPos=operand2->GetPointPosition();
	if(number[0]=='-' && operand2->number[0]=='-')
	{
		if(Operand1PointPos<Operand2PointPos)
			return true;
		if(Operand1PointPos>Operand2PointPos)
			return false;
		for(i=0; number[i]==operand2->number[i]; i++);
		for(; i<Operand1PointPos && i<Operand2PointPos; i++)
		{
			if(number[i]<operand2->number[i])
				return true;
			if(number[i]>operand2->number[i])
				return false;
		}
		int Operand1FractPartSize=length-Operand1PointPos-1;
		int Operand2FractPartSize=operand2->length-Operand2PointPos-1;
		if(Operand1FractPartSize<Operand2FractPartSize)
		{
			for(i=Operand1PointPos+1; i<length; i++)
			{
				if(number[i]<operand2->number[i])
					return true;
				if(number[i]>operand2->number[i])
					return false;
			}
			for(; i<operand2->length; i++)
				if(operand2->number[i]>'0')
					return true;
		}
		else
			if(Operand1FractPartSize>Operand2FractPartSize)
			{
				for(i=Operand2PointPos+1; number[i]==operand2->number[i]; i++);
				for(; i<operand2->length; i++)
				{
					if(number[i]<operand2->number[i])
						return true;
					if(number[i]>operand2->number[i])
						return false;
				}
				for(; i<length; i++)
					if(number[i]>'0')
						return false;
			}
			for(i=Operand1PointPos+1; i<length; i++)
			{
				if(number[i]<operand2->number[i])
					return true;
				if(number[i]>operand2->number[i])
					return false;
			}
			return false;
	}
	if(Operand1PointPos<Operand2PointPos)
		return false;
	if(Operand1PointPos>Operand2PointPos)
		return true;
	for(i=0; number[i]==operand2->number[i]; i++);
	for(; i<Operand1PointPos && i<Operand2PointPos; i++)
	{
		if(number[i]<operand2->number[i])
			return false;
		if(number[i]>operand2->number[i])
			return true;
	}
	int Operand1FractPartSize=length-Operand1PointPos-1;
	int Operand2FractPartSize=operand2->length-Operand2PointPos-1;
	if(Operand1FractPartSize<Operand2FractPartSize)
	{
		for(i=Operand1PointPos+1; i<length; i++)
		{
			if(number[i]<operand2->number[i])
				return false;
			if(number[i]>operand2->number[i])
				return true;
		}
		for(; i<operand2->length; i++)		
			if(operand2->number[i]>'0')
				return false;
	}
	else
		if(Operand1FractPartSize>Operand2FractPartSize)
		{
			for(i=Operand2PointPos+1; number[i]==operand2->number[i]; i++);
			for(; i<operand2->length; i++)
			{
				if(number[i]<operand2->number[i])
					return false;
				if(number[i]>operand2->number[i])
					return true;
			}
			for(; i<length; i++)
				if(number[i]>'0')
					return true;
		}
	for(i=Operand1PointPos+1; i<length; i++)
	{
		if(number[i]<operand2->number[i])
			return false;
		if(number[i]>operand2->number[i])
			return true;
	}
	return true;
}
bool bignum::operator==(bignum* operand2)
{
	if(length!=operand2->length)
		return false;
	for(int i=0; i<length; i++)
		if(number[i]!=operand2->number[i])
			return false;
	return true;
}
bool bignum::operator!=(bignum* operand2)
{
	if(length!=operand2->length)
		return true;
	for(int i=0; i<length; i++)
		if(number[i]!=operand2->number[i])
			return true;
	return false;
}
bignum* bignum::operator+(bignum* operand2)
{
	if(length==1 && number[0]=='0')
	{
		char *result=new char[MaxLength+1];
		strcpy(result,operand2->number);
		return new bignum(result);
	}
	if(operand2->length==1 && operand2->number[0]=='0')
	{
		char *result=new char[MaxLength+1];
		strcpy(result,number);
		return new bignum(result);
	}
	bool SignMinus=false;
	bool Operand1SignMinus=false,Operand2SignMinus=false;
	bignum* operand1=this;
	if(number[0]=='-' && operand2->number[0]=='-')
	{
		SignMinus=true;
		Operand1SignMinus=true;
		Operand2SignMinus=true;
		operand1->number=&operand1->number[1];
		operand1->length--;
		operand2->number=&operand2->number[1];
		operand2->length--;
	}
	else
		if(operand1->number[0]=='-' && operand2->number[0]!='-')
		{
			operand1->number=&operand1->number[1];
			operand1->length--;
			bignum* MinusResult=*operand2-operand1;
			operand1->number=&operand1->number[0]-1;
			operand1->length++;
			return MinusResult;
		}
		else
			if(operand1->number[0]!='-' && operand2->number[0]=='-')
			{
				operand2->number=&operand2->number[1];
				operand2->length--;
				bignum* MinusResult=*operand1-operand2;
				operand2->number=&operand2->number[0]-1;
				operand2->length++;
				return MinusResult;
			}		
	char SumOfDigits,*result=new char[MaxLength+MaxLength];	
	int Operand1PointPosition=operand1->GetPointPosition();
	int Operand2PointPosition=operand2->GetPointPosition();
	int i,j,k,carry=0,ResultLength;
	result[SignMinus]='A';
	if(Operand1PointPosition==operand1->length && Operand2PointPosition==operand2->length)
	{
		if(Operand1PointPosition<Operand2PointPosition)
		{			
			for(i=Operand2PointPosition+SignMinus,result[i+1]='\0',ResultLength=i,j=Operand1PointPosition-1,k=Operand2PointPosition-1; j>-1; i--,j--,k--)
			{
				SumOfDigits=(operand1->number[j]-'0')+(operand2->number[k]-'0')+carry;
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
				SumOfDigits=operand2->number[j]-'0'+carry;
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
				result[i]=operand2->number[j];
		}
		else
			if(Operand1PointPosition>Operand2PointPosition)
			{
				for(i=Operand1PointPosition+SignMinus,result[i+1]='\0',ResultLength=i,j=Operand1PointPosition-1,k=Operand2PointPosition-1; k>-1; i--,j--,k--)
				{
					SumOfDigits=(operand1->number[j]-'0')+(operand2->number[k]-'0')+carry;
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
					SumOfDigits=(operand1->number[j]-'0')+carry;
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
					result[i]=operand1->number[j];
			}
			else
			{
				for(i=Operand1PointPosition+SignMinus,result[i+1]='\0',ResultLength=i,j=Operand1PointPosition-1; j>-1; i--,j--)
				{
					SumOfDigits=(operand1->number[j]-'0')+(operand2->number[j]-'0')+carry;
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
		int Operand1FractPartSize=operand1->GetPointPosition();
		int Operand2FractPartSize=operand2->GetPointPosition();
		Operand1FractPartSize=(Operand1FractPartSize==operand1->length)?0:operand1->length-Operand1FractPartSize-1;
		Operand2FractPartSize=(Operand2FractPartSize==operand2->length)?0:operand2->length-Operand2FractPartSize-1;
		int Operand1IntPartSize=(Operand1FractPartSize==0)?operand1->length-Operand1FractPartSize:operand1->length-Operand1FractPartSize-1;
		int Operand2IntPartSize=(Operand2FractPartSize==0)?operand2->length-Operand2FractPartSize:operand2->length-Operand2FractPartSize-1;
		i=(Operand1IntPartSize>Operand2IntPartSize)?Operand1IntPartSize+SignMinus+1:Operand2IntPartSize+SignMinus+1;
		i+=(Operand1FractPartSize>Operand2FractPartSize)?Operand1FractPartSize:Operand2FractPartSize;
		ResultLength=i;
		result[i+1]='\0';
		if(Operand1FractPartSize>Operand2FractPartSize)
		{
			int DifferenceOfFractPartSizes=Operand1FractPartSize-Operand2FractPartSize;
			for(j=operand1->length-1,k=0; k<DifferenceOfFractPartSizes; i--,j--,k++)
				result[i]=operand1->number[j];
			for(k=operand2->length-1; j>Operand1PointPosition; j--,k--,i--)
			{
				SumOfDigits=(operand1->number[j]-'0')+(operand2->number[k]-'0')+carry;
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
				for(j=operand2->length-1,k=0; k<DifferenceOfFractPartSizes; i--,j--,k++)
					result[i]=operand2->number[j];
				for(k=operand1->length-1; j>Operand2PointPosition; j--,k--,i--)
				{
					SumOfDigits=(operand1->number[k]-'0')+(operand2->number[j]-'0')+carry;
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
				for(j=operand1->length-1,k=operand2->length-1; j>Operand1PointPosition; j--,k--,i--)
				{
					SumOfDigits=(operand1->number[j]-'0')+(operand2->number[k]-'0')+carry;
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
				SumOfDigits=(operand1->number[j]-'0')+(operand2->number[k]-'0')+carry;
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
				SumOfDigits=operand2->number[j]-'0'+carry;
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
				result[i]=operand2->number[j];
		}
		else
			if(Operand1PointPosition>Operand2PointPosition)
			{
				for(j=Operand1PointPosition-1,k=Operand2PointPosition-1; k>-1; i--,j--,k--)
				{
					SumOfDigits=(operand1->number[j]-'0')+(operand2->number[k]-'0')+carry;
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
					SumOfDigits=(operand1->number[j]-'0')+carry;
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
					result[i]=operand1->number[j];
			}
			else
			{
				for(j=Operand1PointPosition-1; j>-1; i--,j--)
				{
					SumOfDigits=(operand1->number[j]-'0')+(operand2->number[j]-'0')+carry;
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
	if(Operand1SignMinus)
	{
		operand1->number=&operand1->number[0]-1;
		operand1->length++;
	}
	if(Operand2SignMinus)
	{
		operand2->number=&operand2->number[0]-1;
		operand2->length++;
	}
	if(SignMinus)	
		result[0]='-';
	if(result[SignMinus]=='A')
	{
		for(i=SignMinus; i<ResultLength+1; i++)
			result[i]=result[i+1];
		result[i-1]='\0';
	}
	return new bignum(result);
}
bignum* bignum::operator-(bignum* operand2)
{
	int i,j,k,carry=0,ResultLength;
	bool Operand1SignMinus=false,Operand2SignMinus=false,SignMinus=false;
	bignum* operand1=this;
	if(*operand1==operand2)
	{
		char *result=new char[MaxLength+1];
		result[0]='0';
		result[1]='\0';
		return new bignum(result);
	}
	if(*operand1<operand2)
	{
		SignMinus=true;
		if((operand1->number[0]!='-' && operand2->number[0]!='-') || (operand1->number[0]=='-' && operand2->number[0]!='-'))		
			SwapOperands(operand1,operand2);		
	}
	else
		if(operand1->number[0]=='-' && operand2->number[0]=='-')
			SwapOperands(operand1,operand2);
	if(operand1->number[0]=='-' && operand2->number[0]=='-')
	{
		Operand1SignMinus=true;
		Operand2SignMinus=true;
		operand1->number=&operand1->number[1];
		operand1->length--;
		operand2->number=&operand2->number[1];
		operand2->length--;
	}
	else
		if(operand1->number[0]!='-' && operand2->number[0]=='-')
		{
			operand2->number=&operand2->number[1];
			operand2->length--;
			bignum* PlusResult=*operand1+operand2;
			operand2->number=&operand2->number[0]-1;
			operand2->length++;
			if(SignMinus)
			{
				for(i=PlusResult->length-1; i>-1; i--)
					PlusResult->number[i+1]=PlusResult->number[i];
				PlusResult->number[0]='-';
				PlusResult->length++;
				PlusResult->number[PlusResult->length]='\0';
			}
			return PlusResult;
		}
	char difference,*result=new char[MaxLength+MaxLength];	
	int Operand1PointPosition=operand1->GetPointPosition();
	int Operand2PointPosition=operand2->GetPointPosition();
	if(Operand1PointPosition==operand1->length && Operand2PointPosition==operand2->length)
	{
		for(i=Operand1PointPosition-1,j=Operand2PointPosition-1,k=i+SignMinus,result[k+1]='\0',ResultLength=k; j>-1; i--,j--,k--)
			if(operand1->number[i]-carry<operand2->number[j])
			{
				result[k]=((operand1->number[i]-carry+10)-operand2->number[j])+'0';
				carry=1;
			}
			else
			{
				result[k]=(operand1->number[i]-operand2->number[j]-carry)+'0';
				carry=0;
			}
		if(Operand1PointPosition>Operand2PointPosition)
			for(; i>-1; i--,k--)
			{
				difference=operand1->number[i]-carry;
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
		int Operand1FractPartSize=operand1->GetPointPosition();
		int Operand2FractPartSize=operand2->GetPointPosition();
		Operand1FractPartSize=(Operand1FractPartSize==operand1->length)?0:operand1->length-Operand1FractPartSize-1;
		Operand2FractPartSize=(Operand2FractPartSize==operand2->length)?0:operand2->length-Operand2FractPartSize-1;
		int Operand1IntPartSize=(Operand1FractPartSize==0)?operand1->length-Operand1FractPartSize:operand1->length-Operand1FractPartSize-1;
		int Operand2IntPartSize=(Operand2FractPartSize==0)?operand2->length-Operand2FractPartSize:operand2->length-Operand2FractPartSize-1;
		i=(Operand1IntPartSize>Operand2IntPartSize)?Operand1IntPartSize+SignMinus:Operand2IntPartSize+SignMinus;
		i+=(Operand1FractPartSize>Operand2FractPartSize)?Operand1FractPartSize:Operand2FractPartSize;
		ResultLength=i+1;
		result[i+1]='\0';
		if(Operand1FractPartSize>Operand2FractPartSize)
		{
			int DifferenceOfFractPartSizes=Operand1FractPartSize-Operand2FractPartSize;
			for(j=operand1->length-1,k=0; k<DifferenceOfFractPartSizes; i--,j--,k++)		
				result[i]=operand1->number[j];
			for(k=operand2->length-1; k>Operand2PointPosition; i--,j--,k--)			
				if(operand1->number[j]-carry<operand2->number[k])
				{
					result[i]=((operand1->number[j]-carry+10)-operand2->number[k])+'0';
					carry=1;
				}
				else
				{
					result[i]=(operand1->number[j]-operand2->number[k]-carry)+'0';
					carry=0;
				}			
		}
		else
			if(Operand2FractPartSize>Operand1FractPartSize)
			{
				int DifferenceOfFractPartSizes=Operand2FractPartSize-Operand1FractPartSize-1;
				j=operand2->length-1;
				result[i--]=('9'+1)-operand2->number[j--]+'0';
				for(k=0; k<DifferenceOfFractPartSizes; i--,j--,k++)				
					result[i]='9'-operand2->number[j]+'0';
				for(k=operand1->length-1,carry=1; k>Operand1PointPosition; i--,j--,k--)				
					if(operand1->number[k]-carry<operand2->number[j])
					{
						result[i]=((operand1->number[k]-carry+10)-operand2->number[j])+'0';
						carry=1;
					}
					else
					{
						result[i]=(operand1->number[k]-operand2->number[j]-carry)+'0';
						carry=0;
					}
			}
			else
			{
				for(j=operand1->length-1,k=operand2->length-1; j>Operand1PointPosition; i--,j--,k--)
					if(operand1->number[j]-carry<operand2->number[k])
					{
						result[i]=((operand1->number[j]-carry+10)-operand2->number[k])+'0';
						carry=1;
					}
					else
					{
						result[i]=(operand1->number[j]-operand2->number[k]-carry)+'0';
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
			if(operand1->number[i]-carry<operand2->number[j])
			{
				result[k]=((operand1->number[i]-carry+10)-operand2->number[j])+'0';
				carry=1;
			}
			else
			{
				result[k]=(operand1->number[i]-operand2->number[j]-carry)+'0';
				carry=0;
			}		
		if(Operand1PointPosition>Operand2PointPosition)
			for(; i>-1; i--,k--)
			{
				difference=operand1->number[i]-carry;
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
	if(Operand1SignMinus)
	{
		operand1->number=&operand1->number[0]-1;
		operand1->length++;
	}
	if(Operand2SignMinus)
	{
		operand2->number=&operand2->number[0]-1;
		operand2->length++;
	}
	return new bignum(result);	
}
bignum* bignum::operator*(bignum* operand2)
{
	if((number[0]=='0' && length==1) || (operand2->number[0]=='0' && operand2->length==1))
	{
		char* result=new char[MaxLength];
		result[0]='0';
		result[1]='\0';
		return new bignum(result,1);
	}
	bignum* operand1=this;	
	int i,j,k,l;
	bool Operand1SignMinus=false,Operand2SignMinus=false,SignMinus=false;	
	if((operand1->number[0]=='-' && operand2->number[0]!='-')||(operand1->number[0]!='-' && operand2->number[0]=='-'))
		SignMinus=true;
	if(operand1->number[0]=='-')
	{
		Operand1SignMinus=true;
		operand1->number=&operand1->number[1];
		operand1->length--;
	}
	if(operand2->number[0]=='-')
	{
		Operand2SignMinus=true;
		operand2->number=&operand2->number[1];
		operand2->length--;
	}
	char MultiplicationResult,carry=0,*result=new char[MaxLength*10];	
	int Operand1PointPosition=operand1->GetPointPosition();
	int Operand2PointPosition=operand2->GetPointPosition();
	int ResultLastIndex=operand1->length+operand2->length+SignMinus;
	int ResultLength=ResultLastIndex;
	char* multiplication=new char[MaxLength*10];
	result[ResultLastIndex+1]='\0';	
	for(i=SignMinus; i<=ResultLastIndex; i++)
		result[i]='0';
	if(Operand1PointPosition==operand1->length && Operand2PointPosition==operand2->length)
	{
		ResultLength=ResultLastIndex+1;
		for(i=Operand1PointPosition-1,j=ResultLastIndex; i>-1; i--,j--)
		{
			MultiplicationResult=(operand1->number[i]-'0')*(operand2->number[Operand2PointPosition-1]-'0')+carry;
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
				MultiplicationResult=(operand1->number[j]-'0')*(operand2->number[i]-'0')+carry;
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
		int Operand1CountOfDigits=(Operand1PointPosition==operand1->length)?operand1->length:operand1->length-1;
		int Operand2CountOfDigits=(Operand2PointPosition==operand2->length)?operand2->length:operand2->length-1;
		if(Operand1CountOfDigits<Operand2CountOfDigits)
		{
			SwapOperands(operand1,operand2);
			SwappedOperands=true;
			i=Operand1PointPosition;
			Operand1PointPosition=Operand2PointPosition;
			Operand2PointPosition=i;
		}
		int Operand1FractPartSize=operand1->length-Operand1PointPosition-1;
		int Operand2FractPartSize=operand2->length-Operand2PointPosition-1;
		if(Operand1FractPartSize<1)
			Operand1FractPartSize=0;
		if(Operand2FractPartSize<1)
			Operand2FractPartSize=0;
		if(Operand1PointPosition==operand1->length)
		{
			Operand1PointPosition=-1;
			Operand1FractPartSize=0;
		}
		else
			if(Operand2PointPosition==operand2->length)
			{
				Operand2PointPosition=-1;
				Operand2FractPartSize=0;
			}
		int ResultFractPartSize=Operand1FractPartSize+Operand2FractPartSize;
		int ResultPointPosition=ResultLastIndex-ResultFractPartSize;
		result[ResultPointPosition]='.';
		for(i=operand2->length-1,l=0; i>Operand2PointPosition; i--,l++)
		{
			for(j=operand1->length-1,k=j+1,multiplication[0]='0',multiplication[k+1]='\0',carry=0; j>Operand1PointPosition; j--,k--)
			{
				MultiplicationResult=(operand1->number[j]-'0')*(operand2->number[i]-'0')+carry;
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
				MultiplicationResult=(operand1->number[j]-'0')*(operand2->number[i]-'0')+carry;
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
			for(j=ResultLastIndex-l,k=operand1->length,carry=0; j>ResultPointPosition && k>0; k--,j--)
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
			for(j=operand1->length-1,k=j+1,multiplication[0]='0',multiplication[k+1]='\0',carry=0; j>Operand1PointPosition; j--,k--)
			{
				MultiplicationResult=(operand1->number[j]-'0')*(operand2->number[i]-'0')+carry;
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
				MultiplicationResult=(operand1->number[j]-'0')*(operand2->number[i]-'0')+carry;
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
			for(j=ResultLastIndex-l,k=operand1->length,carry=0; j>ResultPointPosition; k--,j--)
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
		if(SwappedOperands)	
			SwapOperands(operand1,operand2);
	}
	if(SignMinus)
		result[0]='-';	
	if(Operand1SignMinus)
	{
		operand1->number=&operand1->number[0]-1;
		operand1->length++;
	}
	if(Operand2SignMinus)
	{
		operand2->number=&operand2->number[0]-1;
		operand2->length++;
	}	
	delete[] multiplication;
	return new bignum(result,ResultLength);
}
bignum* bignum::operator/(bignum* operand2)
{
	if((number[0]=='0' && length==1) || (operand2->number[0]=='0' && operand2->length==1))
	{
		char* result=new char[MaxLength];
		result[0]='0';
		result[1]='\0';
		return new bignum(result,1);
	}
	bignum* operand1=this;
	bool ResultWasGot=false;
	bool SignMinus=((operand1->number[0]=='-' && operand2->number[0]!='-')||(operand1->number[0]!='-' && operand2->number[0]=='-'))?true:false;
	bool Operand1SignMinus=(operand1->number[0]=='-')?true:false;
	bool Operand2SignMinus=(operand2->number[0]=='-')?true:false;
	int Operand1PointPosition=operand1->GetPointPosition();
	int Operand2PointPosition=operand2->GetPointPosition();
	int Operand1FractPartSize,Operand2FractPartSize,PrevOperand1Length,PrevOperand2Length;
	int ResultSize=MaxLength*2+MaxFractPartLength;
	int DividendLength=SignMinus,ResultLength=SignMinus,RealDividendLength;	
	int MultiplicationResultIndex,MultiplicationResultLastIndex;
	int i,j,k,l,DividendStartIndex,MultiplicationResultLength,CountOfZeros;
	int PrevRemainderLength,CurRemainderLength,FractPartSize,CountOfRemainders;
	char OperationResult,carry=0,**remainders;
	char* DividendAndRemainder=new char[ResultSize];
	char* MultiplicationResult=new char[ResultSize];
	char** MultiplicationResults=new char*[11];
	int* MultiplicationResultsStartIndexes=new int[11],*LengthsOfRemainders;
	int* MultiplicationResultsLengths=new int[11];
	char* PrevOperand1,*PrevOperand2;
	bool Operand1Changed=false,Operand2Changed=false;
	char* result=new char[ResultSize];
	MultiplicationResult[0]='0';
	MultiplicationResult[Operand2PointPosition+1]='\0';
	if(Operand1PointPosition!=operand1->length || Operand2PointPosition!=operand2->length)
	{
		Operand1FractPartSize=operand1->length-Operand1PointPosition-1;
		Operand2FractPartSize=operand2->length-Operand2PointPosition-1;
		if(Operand1FractPartSize<1)
			Operand1FractPartSize=0;
		if(Operand2FractPartSize<1)
			Operand2FractPartSize=0;
		if(Operand1PointPosition!=operand1->length)
		{
			Operand1Changed=true;
			PrevOperand1Length=operand1->length;
			PrevOperand1=new char[ResultSize];
			strcpy(PrevOperand1,operand1->number);
			for(i=Operand1PointPosition; i<=operand1->length; i++)
				operand1->number[i]=operand1->number[i+1];
			operand1->length--;
			operand1->number[operand1->length]='\0';
		}
		if(Operand2PointPosition!=operand2->length)
		{
			Operand2Changed=true;
			PrevOperand2Length=operand2->length;
			PrevOperand2=new char[ResultSize];
			strcpy(PrevOperand2,operand2->number);
			for(i=Operand2PointPosition; i<=operand2->length; i++)
				operand2->number[i]=operand2->number[i+1];
			operand2->length--;
			operand2->number[operand2->length]='\0';
		}
		if(Operand1FractPartSize>Operand2FractPartSize)
		{
			Operand2PointPosition+=Operand1FractPartSize;
			if(Operand2PointPosition>operand2->length)
			{
				if(!Operand2Changed)
				{
					Operand2Changed=true;
					PrevOperand2Length=operand2->length;
					PrevOperand2=new char[ResultSize];
					strcpy(PrevOperand2,operand2->number);
				}
				CountOfZeros=Operand2PointPosition-operand2->length;
				if(operand2->length+CountOfZeros+SignMinus+1>MaxLength)
				{
					char* NewOperand2=new char[operand2->length+CountOfZeros+SignMinus+1];
					strcpy(NewOperand2,operand2->number);
					delete[] operand2->number;
					operand2->number=NewOperand2;
				}
				for(i=0; i<CountOfZeros; i++,operand2->length++)
					operand2->number[operand2->length]='0';
				operand2->number[operand2->length]='\0';				
			}
		}
		else
		{
			Operand1PointPosition+=Operand2FractPartSize;
			if(Operand1PointPosition>operand1->length)
			{
				if(!Operand1Changed)
				{
					Operand1Changed=true;
					PrevOperand1Length=operand1->length;
					PrevOperand1=new char[ResultSize];
					strcpy(PrevOperand1,operand1->number);
				}
				CountOfZeros=Operand1PointPosition-operand1->length;
				if(operand1->length+CountOfZeros+SignMinus+1>MaxLength)
				{
					char* NewOperand1=new char[operand1->length+CountOfZeros+SignMinus+1];
					strcpy(NewOperand1,operand1->number);
					delete[] operand1->number;
					operand1->number=NewOperand1;
				}
				for(i=0; i<CountOfZeros; i++,operand1->length++)
					operand1->number[operand1->length]='0';
				operand1->number[operand1->length]='\0';
			}
		}
		if(operand1->number[Operand1SignMinus]=='0')
		{
			for(CountOfZeros=0,j=Operand1SignMinus; operand1->number[j]=='0'; CountOfZeros++,j++);
			for(i=Operand1SignMinus,j=CountOfZeros+Operand1SignMinus; j<operand1->length; i++,j++)
				operand1->number[i]=operand1->number[j];
			operand1->length-=CountOfZeros;
			operand1->number[operand1->length]='\0';
		}
		if(operand2->number[Operand2SignMinus]=='0')
		{
			for(CountOfZeros=0,j=Operand2SignMinus; operand2->number[j]=='0'; CountOfZeros++,j++);
			for(i=Operand2SignMinus,j=CountOfZeros+Operand2SignMinus; j<operand2->length; i++,j++)
				operand2->number[i]=operand2->number[j];
			operand2->length-=CountOfZeros;
			operand2->number[operand2->length]='\0';
		}
		Operand1PointPosition=operand1->length;
		Operand2PointPosition=operand2->length;
	}	
	strcpy(DividendAndRemainder,&operand1->number[Operand1SignMinus]);
	DividendLength=operand1->length-Operand1SignMinus;
	bool Operand1IsLessThanOperand2=false;
	if(operand1->length-Operand1SignMinus<operand2->length-Operand2SignMinus)
		Operand1IsLessThanOperand2=true;
	else
		if(operand1->length-Operand1SignMinus==operand2->length-Operand2SignMinus)		
			for(i=Operand1SignMinus,j=Operand2SignMinus; i<operand1->length; i++,j++)
				if(operand1->number[i]<operand2->number[j])
				{
					Operand1IsLessThanOperand2=true;
					break;
				}
				else
					if(operand1->number[i]>operand2->number[j])
						break;
	MultiplicationResultsLengths[0]=-1;
	MultiplicationResults[1]=new char[ResultSize];
	MultiplicationResults[1][0]='0';
	for(i=1,j=Operand2SignMinus; j<operand2->length; i++,j++)
		MultiplicationResults[1][i]=operand2->number[j];
	MultiplicationResults[1][i]='\0';
	MultiplicationResultsStartIndexes[1]=1;
	MultiplicationResultsLengths[1]=operand2->length-Operand2SignMinus;
	for(i=2; i<11; i++)
	{
		MultiplicationResults[i]=new char[ResultSize];
		MultiplicationResults[i][0]='0';
		MultiplicationResults[i][Operand2PointPosition+1-Operand2SignMinus]='\0';
		for(j=Operand2PointPosition-1,k=Operand2PointPosition-Operand2SignMinus,carry=0; j>=Operand2SignMinus; j--,k--)
		{
			OperationResult=(operand2->number[j]-'0')*i+carry;
			if(OperationResult>9)
			{
				MultiplicationResults[i][k]=(OperationResult%10)+'0';
				carry=OperationResult/10;
			}
			else
			{
				MultiplicationResults[i][k]=OperationResult+'0';
				carry=0;
			}
		}
		if(carry>0)
			MultiplicationResults[i][k]=carry+'0';
		else
			MultiplicationResults[i][k]='0';
		for(MultiplicationResultsStartIndexes[i]=0; MultiplicationResults[i][MultiplicationResultsStartIndexes[i]]=='0'; MultiplicationResultsStartIndexes[i]++);
		MultiplicationResultsLengths[i]=Operand2PointPosition-MultiplicationResultsStartIndexes[i]-Operand2SignMinus+1;
	}
	MultiplicationResultLastIndex=Operand2PointPosition-Operand2SignMinus;
	if(Operand1IsLessThanOperand2)
	{
		result[ResultLength++]='0';
		result[ResultLength++]='.';
		result[ResultLength]='\0';
	}
	else
	{
		DividendLength=Operand2PointPosition-Operand2SignMinus;
		for(i=Operand1SignMinus,j=Operand2SignMinus; i<Operand1PointPosition && j<Operand2PointPosition; i++,j++)
			if(operand1->number[i]<operand2->number[j])
			{
				DividendLength++;
				break;
			}
			else
				if(operand1->number[i]>operand2->number[j])
					break;
		strncpy(DividendAndRemainder,&operand1->number[Operand1SignMinus],DividendLength);		
		DividendAndRemainder[DividendLength]='\0';
		while(DividendLength<operand1->length-Operand1SignMinus)
		{
			MultiplicationResultIndex=0;
			for(DividendStartIndex=0; DividendAndRemainder[DividendStartIndex]=='0'; DividendStartIndex++);
			RealDividendLength=DividendLength-DividendStartIndex;
			for(i=0,ResultWasGot=false; i<11 && !ResultWasGot; i++)
			{
				if(MultiplicationResultsLengths[i]>RealDividendLength)
				{
					ResultWasGot=true;
					MultiplicationResultIndex=i-1;
					break;
				}
				else
					if(MultiplicationResultsLengths[i]==RealDividendLength)
					{
						for(j=MultiplicationResultsStartIndexes[i],k=DividendStartIndex; j<Operand2PointPosition+1; j++,k++)
							if(MultiplicationResults[i][j]>DividendAndRemainder[k])
							{
								ResultWasGot=true;
								MultiplicationResultIndex=i-1;
								break;
							}
							else
								if(MultiplicationResults[i][j]<DividendAndRemainder[k])
									break;
								if(j==Operand2PointPosition+1)
								{
									MultiplicationResultIndex=i;
									ResultWasGot=true;
								}
					}
			}
			if(MultiplicationResultIndex>0)
			{
				i=DividendLength-1;
				j=MultiplicationResultLastIndex;			
				if(i<j)
					for(carry=0; i>-1; i--,j--)
					{
						if(DividendAndRemainder[i]-carry<MultiplicationResults[MultiplicationResultIndex][j])
						{
							DividendAndRemainder[i]=((DividendAndRemainder[i]-carry+10)-MultiplicationResults[MultiplicationResultIndex][j])+'0';
							carry=1;
						}
						else
						{
							DividendAndRemainder[i]=(DividendAndRemainder[i]-MultiplicationResults[MultiplicationResultIndex][j]-carry)+'0';
							carry=0;
						}
					}
				else
					for(carry=0; j>-1; i--,j--)
					{
						if(DividendAndRemainder[i]-carry<MultiplicationResults[MultiplicationResultIndex][j])
						{
							DividendAndRemainder[i]=((DividendAndRemainder[i]-carry+10)-MultiplicationResults[MultiplicationResultIndex][j])+'0';
							carry=1;
						}
						else
						{
							DividendAndRemainder[i]=(DividendAndRemainder[i]-MultiplicationResults[MultiplicationResultIndex][j]-carry)+'0';
							carry=0;
						}
					}
			}
			DividendAndRemainder[DividendLength++]=operand1->number[DividendLength+Operand1SignMinus];
			DividendAndRemainder[DividendLength]='\0';
			result[ResultLength]=MultiplicationResultIndex+'0';
			ResultLength++;
		}
		MultiplicationResultIndex=0;
		for(DividendStartIndex=0; DividendAndRemainder[DividendStartIndex]=='0'; DividendStartIndex++);
		RealDividendLength=DividendLength-DividendStartIndex;
		for(i=0,ResultWasGot=false; i<11 && !ResultWasGot; i++)
		{
			if(MultiplicationResultsLengths[i]>RealDividendLength)
			{
				ResultWasGot=true;
				MultiplicationResultIndex=i-1;
				break;
			}
			else
				if(MultiplicationResultsLengths[i]==RealDividendLength)
				{
					for(j=MultiplicationResultsStartIndexes[i],k=DividendStartIndex; j<Operand2PointPosition+1; j++,k++)
					{
						if(MultiplicationResults[i][j]>DividendAndRemainder[k])
						{
							ResultWasGot=true;
							MultiplicationResultIndex=i-1;
							break;
						}
						else
							if(MultiplicationResults[i][j]<DividendAndRemainder[k])
								break;
						if(j==Operand2PointPosition+1)
						{
							MultiplicationResultIndex=i;
							ResultWasGot=true;
						}
					}
				}
		}
		if(MultiplicationResultIndex>0)
		{
			i=DividendLength-1;
			j=MultiplicationResultLastIndex;			
			if(i<j)
				for(carry=0; i>-1; i--,j--)
				{
					if(DividendAndRemainder[i]-carry<MultiplicationResults[MultiplicationResultIndex][j])
					{
						DividendAndRemainder[i]=((DividendAndRemainder[i]-carry+10)-MultiplicationResults[MultiplicationResultIndex][j])+'0';
							carry=1;
					}
					else
					{
						DividendAndRemainder[i]=(DividendAndRemainder[i]-MultiplicationResults[MultiplicationResultIndex][j]-carry)+'0';
						carry=0;
					}
				}
			else
				for(carry=0; j>-1; i--,j--)
				{
					if(DividendAndRemainder[i]-carry<MultiplicationResults[MultiplicationResultIndex][j])
					{
						DividendAndRemainder[i]=((DividendAndRemainder[i]-carry+10)-MultiplicationResults[MultiplicationResultIndex][j])+'0';
						carry=1;
					}
					else
					{
						DividendAndRemainder[i]=(DividendAndRemainder[i]-MultiplicationResults[MultiplicationResultIndex][j]-carry)+'0';
						carry=0;
					}
				}
			}
		for(i=0,ResultWasGot=true; i<DividendLength; i++)
			if(DividendAndRemainder[i]>'0')
			{
				ResultWasGot=false;
				break;
			}
		result[ResultLength++]=MultiplicationResultIndex+'0';
		if(result[SignMinus]!='0' && !ResultWasGot)		
			result[ResultLength++]='.';
	}
	if(!ResultWasGot)
	{
		DividendAndRemainder[DividendLength++]='0';
		DividendAndRemainder[DividendLength]='\0';
		LengthsOfRemainders=new int[MaxFractPartLength+1];
		remainders=new char* [MaxFractPartLength+1];
		remainders[0]=new char[ResultSize];		
		strcpy(remainders[0],DividendAndRemainder);
		CountOfRemainders=1;
		for(FractPartSize=0; FractPartSize<MaxFractPartLength && !ResultWasGot; FractPartSize++)
		{
			MultiplicationResultIndex=0;
			for(DividendStartIndex=0; DividendAndRemainder[DividendStartIndex]=='0'; DividendStartIndex++);
			RealDividendLength=DividendLength-DividendStartIndex;
			for(i=0,ResultWasGot=false; i<11 && !ResultWasGot; i++)
			{
				if(MultiplicationResultsLengths[i]>RealDividendLength)
				{
					ResultWasGot=true;
					MultiplicationResultIndex=i-1;
					break;
				}
				else
					if(MultiplicationResultsLengths[i]==RealDividendLength)
					{
						for(j=MultiplicationResultsStartIndexes[i],k=DividendStartIndex; j<Operand2PointPosition+1; j++,k++)
						{
							if(MultiplicationResults[i][j]>DividendAndRemainder[k])
							{
								ResultWasGot=true;
								MultiplicationResultIndex=i-1;
								break;
							}
							else
								if(MultiplicationResults[i][j]<DividendAndRemainder[k])
									break;
							if(j==Operand2PointPosition+1)
							{
								MultiplicationResultIndex=i;
								ResultWasGot=true;
							}
						}
					}
			}
		if(MultiplicationResultIndex>0)
		{
			i=DividendLength-1;
			j=MultiplicationResultLastIndex;			
			if(i<j)
				for(carry=0; i>-1; i--,j--)
				{
					if(DividendAndRemainder[i]-carry<MultiplicationResults[MultiplicationResultIndex][j])
					{
						DividendAndRemainder[i]=((DividendAndRemainder[i]-carry+10)-MultiplicationResults[MultiplicationResultIndex][j])+'0';
						carry=1;
					}
					else
					{
						DividendAndRemainder[i]=(DividendAndRemainder[i]-MultiplicationResults[MultiplicationResultIndex][j]-carry)+'0';
						carry=0;
					}
				}
			else
				for(carry=0; j>-1; i--,j--)
				{
					if(DividendAndRemainder[i]-carry<MultiplicationResults[MultiplicationResultIndex][j])
					{
						DividendAndRemainder[i]=((DividendAndRemainder[i]-carry+10)-MultiplicationResults[MultiplicationResultIndex][j])+'0';
						carry=1;
					}
					else
					{
						DividendAndRemainder[i]=(DividendAndRemainder[i]-MultiplicationResults[MultiplicationResultIndex][j]-carry)+'0';
						carry=0;
					}
				}
			}
			result[ResultLength++]=MultiplicationResultIndex+'0';
			DividendAndRemainder[DividendLength++]='0';
			DividendAndRemainder[DividendLength]='\0';
			for(i=0,ResultWasGot=true; i<DividendLength; i++)
				if(DividendAndRemainder[i]!='0')
				{
					ResultWasGot=false;
					break;
				}
			if(!ResultWasGot)
			{
				for(i=0; DividendAndRemainder[i]=='0' && i<DividendLength; i++);
				CurRemainderLength=DividendLength-i;
				DividendStartIndex=i;
				for(k=i; i<DividendLength; i++)
					if(DividendAndRemainder[i]!='0')
					{
						for(j=0; j<CountOfRemainders; j++)						
							if(LengthsOfRemainders[j]==CurRemainderLength)
							{
								for(l=0; k<DividendLength; k++,l++)
									if(DividendAndRemainder[k]!=remainders[j][l])
										break;
								if(k==DividendLength)
								{
									ResultWasGot=true;
									result[ResultLength+1]=')';
									k=ResultLength-(CountOfRemainders-j);
									for(l=ResultLength,ResultLength+=2; l>k; l--)
										result[l]=result[l-1];
									result[l++]='(';
									break;
								}
								k=i;
							}						
						if(j==CountOfRemainders)
						{
							remainders[CountOfRemainders]=new char[ResultSize];
							for(i=0; DividendStartIndex<DividendLength; i++,DividendStartIndex++)
								remainders[CountOfRemainders][i]=DividendAndRemainder[DividendStartIndex];
							remainders[CountOfRemainders][i]='\0';
							LengthsOfRemainders[CountOfRemainders]=i;
							CountOfRemainders++;
						}
					break;
				}
			}
		}
		if(FractPartSize==MaxFractPartLength && !ResultWasGot)
		{
			result[ResultLength++]='.';
			result[ResultLength++]='.';
			result[ResultLength++]='.';			
		}
		for(i=0; i<CountOfRemainders; i++)
			delete[] remainders[i];
		delete[] remainders;
		delete[] LengthsOfRemainders;
	}
	result[ResultLength]='\0';
	if(SignMinus)
		result[0]='-';	
	if(Operand1Changed)
	{
		strcpy(operand1->number,PrevOperand1);
		operand1->length=PrevOperand1Length;
		delete[] PrevOperand1;		
	}
	if(Operand2Changed)
	{
		strcpy(operand2->number,PrevOperand2);
		operand2->length=PrevOperand2Length;
		delete[] PrevOperand2;		
	}
	for(i=1; i<11; i++)
		delete[] MultiplicationResults[i];
	delete[] MultiplicationResults;
	delete[] DividendAndRemainder;
	delete[] MultiplicationResult;
	delete[] MultiplicationResultsStartIndexes;
	delete[] MultiplicationResultsLengths;
	return new bignum(result,ResultLength);
}
bool bignum::CheckMultiplicationOrDivisionResult()
{
	if((length==1 && number[0]=='0') || (number[length-1]=='.' || number[length-1]==')'))
		return false;
	return true;
}
void SwapOperands(bignum*& bignum1,bignum*& bignum2)
{
	bignum* temp=bignum1;
	bignum1=bignum2;
	bignum2=temp;
}
char GetRandomDigit(char min,char max)
{
	if(min==max)
		return min;
	if(min>max)	
		return max;	
	char result=min+(rand()%(max+1-min));
	if(!isdigit(result))
		cout<<"Non-digital character: "<<result<<" ("<<(int)result<<")!\n"
			<<"Min character: "<<min<<" = "<<(int)min<<"; max character: "<<max<<" = "<<(int)max<<endl;
	return result;
}