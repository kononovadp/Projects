#include "bignum.h"
bignum::bignum(){}
char* bignum::plus(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length)
{
	char* orig1 = bignum1;
	char* orig2 = bignum2;
	if(Bignum1Length==1 && bignum1[0]=='0')
	{
		char *result=(char*)calloc(MaxBignumLength+1,sizeof(char));
		strcpy(result,bignum2);
		return result;
	}
	if(Bignum2Length==1 && bignum2[0]=='0')
	{
		char *result=(char*)calloc(MaxBignumLength+1,sizeof(char));
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
				char* result = minus(bignum2, Bignum2Length, temp1, len1);
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
				char* result = minus(bignum1, Bignum1Length, temp1, len2);
				free(temp1);
				return result;
			}		
	char SumOfDigits,*result=(char*)calloc(MaxFractPartLength+MaxFractPartLength+10,sizeof(char));
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
char* bignum::minus(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length)
{
	int i,j,k,carry=0,ResultLength;
	bool Operand1SignMinus=false,Operand2SignMinus=false,SignMinus=false;
	if(IsEqual(bignum1,Bignum1Length,bignum2,Bignum2Length))
	{
		char *result=(char*)calloc(2,sizeof(char));
		result[0]='0';
		return result;
	}
	if(IsLess(bignum1,Bignum1Length,bignum2,Bignum2Length))
	{
		SignMinus=true;
		if((bignum1[0]!='-' && bignum2[0]!='-') || (bignum1[0]=='-' && bignum2[0]!='-'))
			SwapBignums(bignum1,Bignum1Length,bignum2,Bignum2Length);
	}
	else
		if(bignum1[0]=='-' && bignum2[0]=='-')
			SwapBignums(bignum1,Bignum1Length,bignum2,Bignum2Length);
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
			char* PlusResult=plus(bignum1,Bignum1Length,bignum2,Bignum2Length);
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
	char difference,*result=(char*)calloc(strlen(bignum1)+strlen(bignum2)+10,sizeof(char));
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
	return result;
}
char* bignum::multiply(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length)
{
	if((bignum1[0]=='0' && Bignum1Length==1) || (bignum2[0]=='0' && Bignum2Length==1))
	{
		char* result=(char*)calloc(2,sizeof(char));
		result[0]='0';
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
	char MultiplicationResult,carry=0,*result=(char*)calloc(MaxBignumLength*10,sizeof(char));
	int Operand1PointPosition=GetPointPosition(bignum1,Bignum1Length);
	int Operand2PointPosition=GetPointPosition(bignum2,Bignum2Length);
	int ResultLastIndex=Bignum1Length+Bignum2Length+SignMinus;
	int ResultLength=ResultLastIndex;
	char* multiplication=(char*)calloc(MaxBignumLength*10,sizeof(char));
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
char* bignum::divide(char* bignum1_orig,int Bignum1Length,char* bignum2_orig,int Bignum2Length)
{	
	if((bignum1_orig[0]=='0' && Bignum1Length==1) || (bignum2_orig[0]=='0' && Bignum2Length==1))
	{
		char* result=new char[MaxBignumLength];
		result[0]='0';
		result[1]='\0';
		return result;
	}
	char* bignum1=(char*)calloc(MaxBignumLength*20,sizeof(char));
	char* bignum2=(char*)calloc(MaxBignumLength*20,sizeof(char));
	strcpy(bignum1,bignum1_orig);
	strcpy(bignum2,bignum2_orig);
	bool ResultWasGot=false;
	bool SignMinus=((bignum1[0]=='-' && bignum2[0]!='-')||(bignum1[0]!='-' && bignum2[0]=='-'))?true:false;
	bool Operand1SignMinus=(bignum1[0]=='-')?true:false;
	bool Operand2SignMinus=(bignum2[0]=='-')?true:false;
	int Operand1PointPosition=GetPointPosition(bignum1,Bignum1Length);
	int Operand2PointPosition=GetPointPosition(bignum2,Bignum2Length);
	int Operand1FractPartSize,Operand2FractPartSize,PrevOperand1Length,PrevOperand2Length;
	int ResultSize=MaxBignumLength*5+MaxFractPartLength;
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
	char* result=(char*)calloc(ResultSize,sizeof(char));
	MultiplicationResult[0]='0';
	MultiplicationResult[Operand2PointPosition+1]='\0';
	if(Operand1PointPosition!=Bignum1Length || Operand2PointPosition!=Bignum2Length)
	{
		Operand1FractPartSize=Bignum1Length-Operand1PointPosition-1;
		Operand2FractPartSize=Bignum2Length-Operand2PointPosition-1;
		if(Operand1FractPartSize<1)
			Operand1FractPartSize=0;
		if(Operand2FractPartSize<1)
			Operand2FractPartSize=0;
		if(Operand1PointPosition!=Bignum1Length)
		{
			Operand1Changed=true;
			PrevOperand1Length=Bignum1Length;
			PrevOperand1=new char[ResultSize];
			strcpy(PrevOperand1,bignum1);
			for(i=Operand1PointPosition; i<=Bignum1Length; i++)
				bignum1[i]=bignum1[i+1];
			Bignum1Length--;
			bignum1[Bignum1Length]='\0';
		}
		if(Operand2PointPosition!=Bignum2Length)
		{
			Operand2Changed=true;
			PrevOperand2Length=Bignum2Length;
			PrevOperand2=new char[ResultSize];
			strcpy(PrevOperand2,bignum2);
			for(i=Operand2PointPosition; i<=Bignum2Length; i++)
				bignum2[i]=bignum2[i+1];
			Bignum2Length--;
			bignum2[Bignum2Length]='\0';
		}
		if(Operand1FractPartSize>Operand2FractPartSize)
		{
			Operand2PointPosition+=Operand1FractPartSize;
			if(Operand2PointPosition>Bignum2Length)
			{
				if(!Operand2Changed)
				{
					Operand2Changed=true;
					PrevOperand2Length=Bignum2Length;
					PrevOperand2=new char[ResultSize];
					strcpy(PrevOperand2,bignum2);
				}
				CountOfZeros=Operand2PointPosition-Bignum2Length;
				/*if(Bignum2Length+CountOfZeros+SignMinus+1>MaxBignumLength)
				{
					char* NewOperand2=new char[Bignum2Length+CountOfZeros+SignMinus+1];
					strcpy(NewOperand2,bignum2);
					delete[] bignum2;
					bignum2=NewOperand2;
				}*/
				for(i=0; i<CountOfZeros; i++,Bignum2Length++)
					bignum2[Bignum2Length]='0';
				bignum2[Bignum2Length]='\0';				
			}
		}
		else
		{
			Operand1PointPosition+=Operand2FractPartSize;
			if(Operand1PointPosition>Bignum1Length)
			{
				if(!Operand1Changed)
				{
					Operand1Changed=true;
					PrevOperand1Length=Bignum1Length;
					PrevOperand1=new char[ResultSize];
					strcpy(PrevOperand1,bignum1);
				}
				CountOfZeros=Operand1PointPosition-Bignum1Length;
				/*if(Bignum1Length+CountOfZeros+SignMinus+1>MaxBignumLength)
				{
					char* NewOperand1=new char[Bignum1Length+CountOfZeros+SignMinus+1];
					strcpy(NewOperand1,bignum1);
					delete[] bignum1;
					bignum1=NewOperand1;
				}*/
				for(i=0; i<CountOfZeros; i++,Bignum1Length++)
					bignum1[Bignum1Length]='0';
				bignum1[Bignum1Length]='\0';
			}
		}
		if(bignum1[Operand1SignMinus]=='0')
		{
			for(CountOfZeros=0,j=Operand1SignMinus; bignum1[j]=='0'; CountOfZeros++,j++);
			for(i=Operand1SignMinus,j=CountOfZeros+Operand1SignMinus; j<Bignum1Length; i++,j++)
				bignum1[i]=bignum1[j];
			Bignum1Length-=CountOfZeros;
			bignum1[Bignum1Length]='\0';
		}
		if(bignum2[Operand2SignMinus]=='0')
		{
			for(CountOfZeros=0,j=Operand2SignMinus; bignum2[j]=='0'; CountOfZeros++,j++);
			for(i=Operand2SignMinus,j=CountOfZeros+Operand2SignMinus; j<Bignum2Length; i++,j++)
				bignum2[i]=bignum2[j];
			Bignum2Length-=CountOfZeros;
			bignum2[Bignum2Length]='\0';
		}
		Operand1PointPosition=Bignum1Length;
		Operand2PointPosition=Bignum2Length;
	}	
	strcpy(DividendAndRemainder,&bignum1[Operand1SignMinus]);
	DividendLength=Bignum1Length-Operand1SignMinus;
	bool Operand1IsLessThanOperand2=false;
	if(Bignum1Length-Operand1SignMinus<Bignum2Length-Operand2SignMinus)
		Operand1IsLessThanOperand2=true;
	else
		if(Bignum1Length-Operand1SignMinus==Bignum2Length-Operand2SignMinus)		
			for(i=Operand1SignMinus,j=Operand2SignMinus; i<Bignum1Length; i++,j++)
			{
				if(bignum1[i]<bignum2[j])
				{
					Operand1IsLessThanOperand2=true;
					break;
				}
				else
					if(bignum1[i]>bignum2[j])
						break;
			}
	MultiplicationResultsLengths[0]=-1;
	MultiplicationResults[1]=new char[ResultSize];
	MultiplicationResults[1][0]='0';
	for(i=1,j=Operand2SignMinus; j<Bignum2Length; i++,j++)
		MultiplicationResults[1][i]=bignum2[j];
	MultiplicationResults[1][i]='\0';
	MultiplicationResultsStartIndexes[1]=1;
	MultiplicationResultsLengths[1]=Bignum2Length-Operand2SignMinus;
	for(i=2; i<11; i++)
	{
		MultiplicationResults[i]=new char[ResultSize];
		MultiplicationResults[i][0]='0';
		MultiplicationResults[i][Operand2PointPosition+1-Operand2SignMinus]='\0';
		for(j=Operand2PointPosition-1,k=Operand2PointPosition-Operand2SignMinus,carry=0; j>=Operand2SignMinus; j--,k--)
		{
			OperationResult=(bignum2[j]-'0')*i+carry;
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
			if(bignum1[i]<bignum2[j])
			{
				DividendLength++;
				break;
			}
			else
				if(bignum1[i]>bignum2[j])
					break;
		strncpy(DividendAndRemainder,&bignum1[Operand1SignMinus],DividendLength);		
		DividendAndRemainder[DividendLength]='\0';
		while(DividendLength<Bignum1Length-Operand1SignMinus)
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
			DividendAndRemainder[DividendLength]=bignum1[DividendLength+Operand1SignMinus];
			DividendLength++;
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
		LengthsOfRemainders=new int[MaxBignumLength+1];
		remainders=new char* [MaxBignumLength+1];
		remainders[0]=new char[ResultSize];		
		strcpy(remainders[0],DividendAndRemainder);
		CountOfRemainders=1;
		for(FractPartSize=0; FractPartSize<MaxBignumLength && !ResultWasGot; FractPartSize++)
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
		strcpy(bignum1,PrevOperand1);
		Bignum1Length=PrevOperand1Length;
		delete[] PrevOperand1;		
	}
	if(Operand2Changed)
	{
		strcpy(bignum2,PrevOperand2);
		Bignum2Length=PrevOperand2Length;
		delete[] PrevOperand2;		
	}
	for(i=1; i<11; i++)
		delete[] MultiplicationResults[i];
	delete[] MultiplicationResults;
	delete[] DividendAndRemainder;
	delete[] MultiplicationResult;
	delete[] MultiplicationResultsStartIndexes;
	delete[] MultiplicationResultsLengths;
	free(bignum1);
	free(bignum2);
	return result;
}