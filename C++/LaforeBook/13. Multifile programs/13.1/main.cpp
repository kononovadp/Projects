#include <ctime>
#include <chrono>
#include <algorithm>
#include "bignum.h"
int MaxLength,MaxFractPartLength;
unsigned long long CountOfCalculatedExpressions=0;
bool** CombinationsOfParameters;
void ShuffleCombinationsOfParameters()
{
	int i,j;
	bool* temp;
	for(i=0; i<16; i++)
	{
		j=0+(rand()%4);
		bool* temp=CombinationsOfParameters[i];
		CombinationsOfParameters[i]=CombinationsOfParameters[j];
		CombinationsOfParameters[j]=temp;
	}
}
void CalculateAnExpressionDetailedOutputOn(bignum* operand1,bignum* operand2,char operation)
{
	bignum* result,*TestResult=NULL;
	char TestOperation;
	cout<<endl;
	operand1->display();
	cout<<" "<<operation<<" ";
	operand2->display();
	cout<<" = ";	
	switch(operation)
	{
		case '+': result=*operand1+operand2; TestOperation='-'; break;
		case '-': result=*operand1-operand2; TestOperation='+'; break;
		case '*': result=*operand1*operand2; TestOperation='/'; break;
		case '/': result=*operand1/operand2; TestOperation='*'; break;
	}
	CountOfCalculatedExpressions++;
	result->display();
	cout<<endl;
	if(TestOperation=='+' || TestOperation=='-')
	{
		result->display();
		cout<<" "<<TestOperation<<" ";
		operand2->display();
		cout<<" = ";
	}	
	if(TestOperation=='+')
	{
		TestResult=*result+operand2;
		CountOfCalculatedExpressions++;
		TestResult->display();
	}
	else
		if(TestOperation=='-')
		{
			TestResult=*result-operand2;
			CountOfCalculatedExpressions++;
			TestResult->display();
		}
		else
			if(TestOperation=='*' && result->CheckMultiplicationOrDivisionResult())
			{
				result->display();
				cout<<" "<<TestOperation<<" ";
				operand2->display();
				cout<<" = ";				
				TestResult=*result*operand2;
				CountOfCalculatedExpressions++;
				TestResult->display();
			}
			else
				if(TestOperation=='/' && result->CheckMultiplicationOrDivisionResult())
				{
					result->display();
					cout<<" "<<TestOperation<<" ";
					operand2->display();
					cout<<" = ";					
					TestResult=*result/operand2;
					CountOfCalculatedExpressions++;
					TestResult->display();
				}
	if(TestResult)
	{
		if(*TestResult!=operand1)
		{
			cout<<endl;
			operand1->display();
			cout<<" "<<operation<<" ";
			operand2->display();
			cout<<" = ";
			result->display();
			cout<<endl;
			result->display();
			cout<<" "<<TestOperation<<" ";
			operand2->display();
			cout<<" = ";
			TestResult->display();
			cout<<"\nIncorrect result! Press a key to continue.";
			getch();
		}
		delete TestResult;
	}
	cout<<"\n------------------------------------------------------------------------------------------";
	delete result;
}
void CalculateAnExpressionDetailedOutputOff(bignum* operand1,bignum* operand2,char operation)
{
	bignum* result,*TestResult=NULL;
	char TestOperation;
	switch(operation)
	{
		case '+': result=*operand1+operand2; TestOperation='-'; break;
		case '-': result=*operand1-operand2; TestOperation='+'; break;
		case '*': result=*operand1*operand2; TestOperation='/'; break;
		case '/': result=*operand1/operand2; TestOperation='*'; break;
	}
	CountOfCalculatedExpressions++;
	if(TestOperation=='+')
	{
		TestResult=*result+operand2;	
		CountOfCalculatedExpressions++;
	}
	else
		if(TestOperation=='-')
		{
			TestResult=*result-operand2;
			CountOfCalculatedExpressions++;
		}
		else
			if(TestOperation=='*' && result->CheckMultiplicationOrDivisionResult())
			{
				TestResult=*result*operand2;
				CountOfCalculatedExpressions++;
			}
			else
				if(TestOperation=='/' && result->CheckMultiplicationOrDivisionResult())
				{
					TestResult=*result/operand2;
					CountOfCalculatedExpressions++;
				}
	if(TestResult)
	{
		if(*TestResult!=operand1)
		{
			cout<<endl;
			operand1->display();
			cout<<" "<<operation<<" ";
			operand2->display();
			cout<<" = ";
			result->display();
			cout<<endl;
			result->display();
			cout<<" "<<TestOperation<<" ";
			operand2->display();
			cout<<" = ";
			TestResult->display();
			cout<<"\nIncorrect result! Press a key to continue.";
			getch();
		}
		delete TestResult;
	}
	delete result;
}
void TestBignumArithmetic(int MinCountOfDigits,int MaxCountOfDigits,int CountOfRanges,int CountOfExpressions,void CalculateAnExpression(bignum*,bignum*,char))
{
	int i,j,k,LengthIndex,ParameterIndex,CountOfLengths=MaxCountOfDigits-MinCountOfDigits;
	int* lengths=new int[CountOfLengths];
	int* MinLengths=new int[CountOfLengths*3];
	int* MaxLengths=new int[CountOfLengths*3];
	bignum* temp,*MinBignum=new bignum(),*MaxBignum=new bignum();
	bignum* operand1=new bignum(),*operand2=new bignum();
	for(i=0,j=MinCountOfDigits; j<MaxCountOfDigits; i++,j++)
		lengths[i]=j;
	ShuffleArrayOfIntegers(lengths,CountOfLengths);
	for(i=0,j=0; i<3; i++)
		for(k=0; k<CountOfLengths; k++,j++)
		{
			MinLengths[j]=lengths[k];
			MaxLengths[j]=lengths[k];
		}
	CountOfLengths*=3;	
	ShuffleArrayOfIntegers(MinLengths,CountOfLengths);
	ShuffleArrayOfIntegers(MaxLengths,CountOfLengths);
	for(i=0,LengthIndex=0,ParameterIndex=0; i<CountOfRanges; i++)
	{
		MinBignum->SetRandomBignum(MinLengths[LengthIndex],CombinationsOfParameters[ParameterIndex][0],CombinationsOfParameters[ParameterIndex][1]);
		MaxBignum->SetRandomBignum(MaxLengths[LengthIndex],CombinationsOfParameters[ParameterIndex][2],CombinationsOfParameters[ParameterIndex][3]);
		if(*MinBignum>MaxBignum)
		{
			temp=MinBignum;
			MinBignum=MaxBignum;
			MaxBignum=temp;
		}
		cout<<setw(3)<<i+1<<" / "<<CountOfRanges<<". MIN: ";
		MinBignum->display();
		cout<<";  MAX: ";
		MaxBignum->display();
		cout<<"...";
		for(j=0; j<CountOfExpressions; j++)
		{			
			operand1->SetRandomBignum(MinBignum,MaxBignum);
			operand2->SetRandomBignum(MinBignum,MaxBignum);
			CalculateAnExpression(operand1,operand2,'+');
			CalculateAnExpression(operand2,operand1,'+');
			CalculateAnExpression(operand1,operand2,'-');
			CalculateAnExpression(operand2,operand1,'-');
			CalculateAnExpression(operand1,operand2,'*');
			CalculateAnExpression(operand2,operand1,'*');
			CalculateAnExpression(operand1,operand2,'/');
			CalculateAnExpression(operand2,operand1,'/');
		}
		cout<<endl;
		if(LengthIndex==CountOfLengths-1)
		{
			LengthIndex=0;
			ShuffleArrayOfIntegers(MaxLengths,CountOfLengths);
		}
		else
			LengthIndex++;
		if(ParameterIndex==15)
		{
			ParameterIndex=0;
			ShuffleCombinationsOfParameters();
		}
		else
			ParameterIndex++;
	}
	delete[] lengths;
	delete[] MinLengths;
	delete[] MaxLengths;
	delete MinBignum;
	delete MaxBignum;
	delete operand1;
	delete operand2;
}
bignum*** GetArraysOfRandomBignums(int MinCountOfDigits,int MaxCountOfDigits,int CountOfItems)
{
	int i,ParameterIndex=0;
	bignum*** ArrayOfRandomBignums=new bignum**[2];
	ArrayOfRandomBignums[0]=new bignum*[CountOfItems];
	ArrayOfRandomBignums[1]=new bignum*[CountOfItems];
	for(i=0; i<CountOfItems; i++)
	{
		ArrayOfRandomBignums[0][i]=new bignum();
		ArrayOfRandomBignums[0][i]->SetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),CombinationsOfParameters[ParameterIndex][0],CombinationsOfParameters[ParameterIndex][1]);
		ArrayOfRandomBignums[1][i]=new bignum();
		ArrayOfRandomBignums[1][i]->SetRandomBignum(GetRandomInt(MinCountOfDigits,MaxCountOfDigits),CombinationsOfParameters[ParameterIndex][0],CombinationsOfParameters[ParameterIndex][1]);
		if(ParameterIndex==15)
		{
			ParameterIndex=0;
			ShuffleCombinationsOfParameters();
		}
		else
			ParameterIndex++;
	}
	return ArrayOfRandomBignums;
}
void TestOneOperationWithBignums(bignum*** ArraysOfBignums,int CountOfItems,char operation)
{
	int i;
	cout<<"Testing of operation "<<operation<<"...";
	auto StartTime=chrono::system_clock::now();
	switch(operation)
	{
		case '+':
			for(i=0; i<CountOfItems; i++)
			{
				bignum* result=*ArraysOfBignums[0][i]+ArraysOfBignums[1][i];
				delete result;
			}
			break;
		case '-':
			for(i=0; i<CountOfItems; i++)
			{
				bignum* result=*ArraysOfBignums[0][i]-ArraysOfBignums[1][i];
				delete result;
			}
			break;
		case '*':
			for(i=0; i<CountOfItems; i++)
			{
				bignum* result=*ArraysOfBignums[0][i]*ArraysOfBignums[1][i];
				delete result;
			}
			break;
		case '/':
			for(i=0; i<CountOfItems; i++)
			{
				bignum* result=*ArraysOfBignums[0][i]/ArraysOfBignums[1][i];
				delete result;
			}
			break;
	}
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<" Time: "<<duration.count()<<" seconds\n";
}
int main()
{	
	InitFloatingPointAndRandomNumbers();
	int i,j,k,MinCountOfDigits=10,MaxCountOfDigits=100;
	int CountOfRanges=10,CountOfExpressions=100;
	int CountOfRandomBignums=CountOfRanges*CountOfExpressions*2;
	MaxLength=MaxCountOfDigits+10;
	MaxFractPartLength=MaxCountOfDigits*2;
	CountOfCalculatedExpressions=0;
	CombinationsOfParameters=new bool*[16];
	bool source[]={0,0,0,0};
	for(j=3,i=0; j>-1; j--)
	{
		source[j]=1;
		do
		{
			CombinationsOfParameters[i]=new bool[4];
			for(k=0; k<4; k++)
				CombinationsOfParameters[i][k]=source[k];
			i++;
		}
		while(next_permutation(&source[0],&source[4]));
	}	
	CombinationsOfParameters[i]=new bool[4];
	for(j=0; j<4; j++)
		CombinationsOfParameters[i][j]=0;
	ShuffleCombinationsOfParameters();	
	cout<<"Min. count of digits: "<<MinCountOfDigits<<"; Max. count of digits: "<<MaxCountOfDigits<<";\nMax. length of a bignum: "<<MaxLength<<"; Max. fractional part length: "<<MaxFractPartLength<<";\nCount of ranges: "<<CountOfRanges<<"; Count of expressions: "<<CountOfExpressions<<endl;
	if(MaxFractPartLength<MaxCountOfDigits*2)
		cout<<"WARNING!!! Devision or multiplication results may be incorrect\nbecause of low maximum fractional part length!\n";
	auto StartTime=chrono::system_clock::now();
	TestBignumArithmetic(MinCountOfDigits,MaxCountOfDigits,CountOfRanges,CountOfExpressions,CalculateAnExpressionDetailedOutputOff);
	auto EndTime=chrono::system_clock::now();
	chrono::duration<double> duration=EndTime-StartTime;
	cout<<"Count of calculated expressions: "<<CountOfCalculatedExpressions<<";\nTime: "<<duration.count()<<" seconds\n";	
	bignum*** ArraysOfRandomBignums=GetArraysOfRandomBignums(MinCountOfDigits,MaxCountOfDigits,CountOfRandomBignums);
	cout<<"Count of random bignums: "<<CountOfRandomBignums<<endl;
	TestOneOperationWithBignums(ArraysOfRandomBignums,CountOfRandomBignums,'+');
	TestOneOperationWithBignums(ArraysOfRandomBignums,CountOfRandomBignums,'-');
	TestOneOperationWithBignums(ArraysOfRandomBignums,CountOfRandomBignums,'*');
	TestOneOperationWithBignums(ArraysOfRandomBignums,CountOfRandomBignums,'/');	
	for(i=0; i<CountOfRandomBignums; i++)
	{
		delete ArraysOfRandomBignums[0][i];
		delete ArraysOfRandomBignums[1][i];
	}
	delete[] ArraysOfRandomBignums[0];
	delete[] ArraysOfRandomBignums[1];
	delete[] ArraysOfRandomBignums;
	for(i=0; i<16; i++)
		delete[] CombinationsOfParameters[i];
	delete[] CombinationsOfParameters;
	
	/*MaxLength=100;
	MaxFractPartLength=100;
	string StrOp1="1056",StrOp2="5123";
	char* op1=new char[StrOp1.length()+2];
	char* op2=new char[StrOp2.length()+2];
	int j,k,Op1PointPos=StrOp1.length(),Op2PointPos=StrOp2.length();
	for(j=0; j<Op1PointPos; j++)
		op1[j]=StrOp1[j];
	op1[j]='\0';
	for(j=0; j<Op2PointPos; j++)
		op2[j]=StrOp2[j];
	op2[j]='\0';
	CalculateAnExpressionDetailedOutputOn(new bignum(op1),new bignum(op2),'/');
	CalculateAnExpressionDetailedOutputOn(new bignum(op2),new bignum(op1),'/');
	for(Op2PointPos--; Op2PointPos>0; Op2PointPos--)
	{
		for(j=0; j<Op2PointPos; j++)
			op2[j]=StrOp2[j];
		op2[j]='.';
		for(; j<StrOp2.length(); j++)
			op2[j+1]=StrOp2[j];
		op2[j+1]='\0';
		CalculateAnExpressionDetailedOutputOn(new bignum(op1),new bignum(op2),'/');
		CalculateAnExpressionDetailedOutputOn(new bignum(op2),new bignum(op1),'/');
	}
	for(Op1PointPos--; Op1PointPos>0; Op1PointPos--)
	{
		for(j=0; j<Op1PointPos; j++)
			op1[j]=StrOp1[j];
		op1[j]='.';
		for(; j<StrOp1.length(); j++)
			op1[j+1]=StrOp1[j];
		op1[j+1]='\0';
		Op2PointPos=StrOp2.length();
		for(j=0; j<Op2PointPos; j++)
			op2[j]=StrOp2[j];
		op2[j]='\0';
		CalculateAnExpressionDetailedOutputOn(new bignum(op1),new bignum(op2),'/');
		CalculateAnExpressionDetailedOutputOn(new bignum(op2),new bignum(op1),'/');
		for(Op2PointPos--; Op2PointPos>0; Op2PointPos--)
		{
			for(j=0; j<Op2PointPos; j++)
				op2[j]=StrOp2[j];
			op2[j]='.';
			for(; j<StrOp2.length(); j++)
				op2[j+1]=StrOp2[j];
			op2[j+1]='\0';
			CalculateAnExpressionDetailedOutputOn(new bignum(op1),new bignum(op2),'/');
			CalculateAnExpressionDetailedOutputOn(new bignum(op2),new bignum(op1),'/');
		}
	}*/
	/*MaxLength=100;
	MaxFractPartLength=100;
	char* number1=new char[MaxLength],*number2=new char[MaxLength];
	strcpy(number1,"9.85");
	strcpy(number2,"12.4");
	bignum* bignum1=new bignum(number1),*bignum2=new bignum(number2);
	CalculateAnExpressionDetailedOutputOn(bignum1,bignum2,'-');
	delete bignum1;
	delete bignum2;*/
	
	/*for(MaxLength=80,MaxFractPartLength=10,i=0; i<100; i++)
	{
		bignum* bignum1=new bignum(),*bignum2=new bignum();
		bignum1->SetRandomBignum(GetRandomInt(1,5),GetRandomInt(0,0),GetRandomInt(0,2));
		bignum2->SetRandomBignum(GetRandomInt(1,5),GetRandomInt(0,0),GetRandomInt(0,2));
		CalculateAnExpressionDetailedOutputOn(bignum1,bignum2,'-');
		CalculateAnExpressionDetailedOutputOn(bignum2,bignum1,'-');
		delete bignum1;
		delete bignum2;
	}*/
	return 0;
}