#include "BignumAccessories.h"
void AddZerosAndNumber(char* recipient, int ZeroPosition, int ZeroCount,char* source,int SourceLength)
{
	int i,j;
	if(ZeroPosition==0)
	{		
		for(i=0; i<ZeroCount; i++)
			recipient[i]='0';
		for(j=0; j<SourceLength; j++,i++)		
			recipient[i]=source[j];
		recipient[i]='\0';
	}
	else
	{
		for(i=ZeroPosition,j=0; j<SourceLength; i++,j++)
			recipient[i]=source[j];
		for(j=0; j<ZeroCount; j++,i++)
			recipient[i]='0';
		recipient[i]='\0';
	}
}
int GetCharacterPosition(char* array,int size,char ch)
{
	int i,pos=-1;
	for(i=0; i<size; i++)
		if(array[i]==ch)
		{
			pos=i;
			break;
		}
	return pos;
}
void SwapOperands(bignum*& bignum1,bignum*& bignum2)
{
	bignum* temp=bignum1;
	bignum1=bignum2;
	bignum2=temp;
}
int JustifyNumbers(char*& bignum1,char*& bignum2,char* source1,char* source2,int& Source1Length,int& Source2Length,bool& DeleteOperand1,bool& DeleteOperand2)
{
	int i,ResultPointPos=-1;
	int Operand1PointPos=GetCharacterPosition(source1,Source1Length,'.');
	int Operand2PointPos=GetCharacterPosition(source2,Source2Length,'.');
	if(Operand1PointPos==-1 && Operand2PointPos==-1)
	{
		if(Source1Length<Source2Length)
		{
			bignum2=source2;
			DeleteOperand1=true;
			bignum1=new char[MaxLength+MaxLength];
			AddZerosAndNumber(bignum1,0,Source2Length-Source1Length,source1,Source1Length);
		}
		else
			if(Source1Length>Source2Length)
			{
				bignum1=source1;
				DeleteOperand2=true;
				bignum2=new char[MaxLength+MaxLength];
				AddZerosAndNumber(bignum2,0,Source1Length-Source2Length,source2,Source2Length);
			}
			else
			{
				bignum1=source1;
				bignum2=source2;
			}
	}
	else
	{
		bignum1=new char[MaxLength+MaxLength];
		bignum2=new char[MaxLength+MaxLength];
		DeleteOperand1=true;
		DeleteOperand2=true;
		if(Operand1PointPos==-1)
			Operand1PointPos=Source1Length;
		else
			if(Operand2PointPos==-1)
				Operand2PointPos=Source2Length;
		int Operand1CountOfDecimalDigits=0,Operand2CountOfDecimalDigits=0;
		for(i=Operand1PointPos; i<Source1Length; i++,Operand1CountOfDecimalDigits++);
		for(i=Operand2PointPos; i<Source2Length; i++,Operand2CountOfDecimalDigits++);
		if(Operand1PointPos!=Operand2PointPos || Operand1CountOfDecimalDigits!=Operand2CountOfDecimalDigits)
		{
			if(Operand1PointPos<Operand2PointPos)
			{
				AddZerosAndNumber(bignum1,0,Operand2PointPos-Operand1PointPos,source1,Operand1PointPos);
				AddZerosAndNumber(bignum2,0,0,source2,Source2Length-(Source2Length-Operand2PointPos));
				ResultPointPos=Operand2PointPos;
			}
			else
				if(Operand1PointPos>Operand2PointPos)
				{
					AddZerosAndNumber(bignum2,0,Operand1PointPos-Operand2PointPos,source2,Operand2PointPos);
					AddZerosAndNumber(bignum1,0,0,source1,Source1Length-(Source1Length-Operand1PointPos));
					ResultPointPos=Operand1PointPos;
				}
				else
				{
					AddZerosAndNumber(bignum1,0,0,source1,Source1Length-(Source1Length-Operand1PointPos));
					AddZerosAndNumber(bignum2,0,0,source2,Source2Length-(Source2Length-Operand2PointPos));
					ResultPointPos=Operand1PointPos;
				}
			if(Operand1CountOfDecimalDigits<Operand2CountOfDecimalDigits)
			{
				AddZerosAndNumber(bignum1,ResultPointPos,Operand2CountOfDecimalDigits-Operand1CountOfDecimalDigits,&source1[Operand1PointPos],Source1Length-Operand1PointPos);
				AddZerosAndNumber(&bignum2[strlen(bignum2)],0,0,&source2[Operand2PointPos],Source2Length-Operand2PointPos);
			}
			else
				if(Operand1CountOfDecimalDigits>Operand2CountOfDecimalDigits)
				{
					AddZerosAndNumber(bignum2,ResultPointPos,Operand1CountOfDecimalDigits-Operand2CountOfDecimalDigits,&source2[Operand2PointPos],Source2Length-Operand2PointPos);
					AddZerosAndNumber(&bignum1[strlen(bignum1)],0,0,&source1[Operand1PointPos],Source1Length-Operand1PointPos);
				}
				else
				{
					AddZerosAndNumber(&bignum1[strlen(bignum1)],0,0,&source1[Operand1PointPos],Source1Length-Operand1PointPos);
					AddZerosAndNumber(&bignum2[strlen(bignum2)],0,0,&source2[Operand2PointPos],Source2Length-Operand2PointPos);
				}
		}
		else
		{
			for(i=0; i<Operand1PointPos; i++)
				bignum1[i]=source1[i];
			for(; i<Source1Length; i++)
				bignum1[i]=source1[i];
			bignum1[i]='\0';
			for(i=0; i<Operand2PointPos; i++)
				bignum2[i]=source2[i];
			for(; i<Source2Length; i++)
				bignum2[i]=source2[i];
			bignum2[i]='\0';
			ResultPointPos=Operand1PointPos;
		}
	}
	return ResultPointPos;
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