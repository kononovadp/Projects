//1. Создайте методы для вычитания и деления чисел класса verylong (см. одноименный пример). Это будут перегружаемые операции «-» и «/». Здесь потребуется некоторое напряжение интеллекта. Будем предполагать при написании функции вычитания, что числа могут быть как положительными, так и отрицательными. Это усложнит умножение и сложение, которым придется выполнять различные действия в зависимости от знака числа. Чтобы вникнуть в алгоритм, прежде всего попробуйте выполнить деление больших чисел вручную, на бумажке, записывая каждый шаг. Затем внедрите все эти шаги в новый метод класса verylong. При этом обнаружится, что приходится выполнять ряд операций сравнения, так что необходимо будет написать специальную функцию еще и для этого.
#include "verylong.h"
bool IntegerDivision;
verylong GetRandomBignum(int MinSize,int MaxSize,bool SignMinus)
{
	int i=SignMinus,length=GetRandomInt(MinSize,MaxSize);	
	char* bignum=new char[length+1];
	if(SignMinus)
		bignum[0]='-';
	bignum[i++]=GetRandomInt(1,9)+'0';
	for(; i<length; i++)
		bignum[i]=GetRandomInt(0,9)+'0';
	bignum[i]='\0';
	verylong NewBignum(bignum);
	delete[]bignum;
	return NewBignum;
}
void CalculateAnExpression(verylong& operand1,verylong& operand2,char operation)
{
	verylong result,TestResult;
	char TestOperation;
	if(operation=='*')
		IntegerDivision=true;
	operand1.display();
	cout<<" "<<operation<<" ";
	operand2.display();
	cout<<" = ";
	switch(operation)
	{
		case '+': result=operand1+operand2; TestOperation='-'; break;
		case '-': result=operand1-operand2; TestOperation='+'; break;
		case '*': result=operand1*operand2; TestOperation='/'; break;
		case '/': result=operand1/operand2; break;
	}
	result.display();
	if(operation!='/')
	{
		cout<<"; ";
		result.display();
		cout<<" "<<TestOperation<<" ";
		operand2.display();
		cout<<" = ";
		switch(TestOperation)
		{
			case '+': TestResult=result+operand2; break;
			case '-': TestResult=result-operand2; break;
			case '/': TestResult=result/operand2; break;
		}
		TestResult.display();
		verylong zero("0");
		if((operation!='*' && (operand1!=zero || operand2!=zero)) && TestResult!=operand1)
		{
			cout<<": Incorrect result! Press a key to continue.";
			getch();			
		}
	}
	cout<<endl;
}
void TestCalc(verylong& Operand1Min,verylong& Operand1Max,verylong& Operand2Min,verylong& Operand2Max)
{
	int i;
	if(Operand1Max<Operand1Min)	
		Operand1Min.SwapOperands(Operand1Min,Operand1Max);
	if(Operand2Max<Operand2Min)	
		Operand2Min.SwapOperands(Operand2Min,Operand2Max);
	verylong operand1,operand2,res;
	cout<<"==================Operand 1: ";
	Operand1Min.display();
	cout<<" - ";
	Operand1Max.display();
	cout<<"==================\n==================Operand 2: ";
	Operand2Min.display();
	cout<<" - ";
	Operand2Max.display();
	cout<<"==================\n";
	for(i=0; i<10; i++)
	{
		operand1=res.GetRandomSignedIntBignum(Operand1Min,Operand1Max);
		operand2=res.GetRandomSignedIntBignum(Operand2Min,Operand2Max);
		CalculateAnExpression(operand1,operand2,'+');
		CalculateAnExpression(operand2,operand1,'+');
		CalculateAnExpression(operand1,operand2,'-');
		CalculateAnExpression(operand2,operand1,'-');
		CalculateAnExpression(operand1,operand2,'*');
		CalculateAnExpression(operand2,operand1,'*');
		CalculateAnExpression(operand1,operand2,'/');
		CalculateAnExpression(operand2,operand1,'/');
		cout<<"--------------------------------------------------------------------\n";
	}
}
int main()
{
	InitFloatingPointAndRandomNumbers();
	int i;
	char* NewBignum;
	verylong** RandomLimits=new verylong*[5];	
	for(i=0; i<5; i++)
		RandomLimits[i]=new verylong[4];
	RandomLimits[0][0]=GetRandomBignum(1,8,false);
	RandomLimits[0][1]=GetRandomBignum(1,8,false);
	RandomLimits[0][2]=GetRandomBignum(1,8,false);
	RandomLimits[0][3]=GetRandomBignum(1,8,false);
	
	RandomLimits[1][0]=GetRandomBignum(1,8,true);
	RandomLimits[1][1]=GetRandomBignum(1,8,true);
	RandomLimits[1][2]=GetRandomBignum(1,8,true);
	RandomLimits[1][3]=GetRandomBignum(1,8,true);
	
	RandomLimits[2][0]=GetRandomBignum(1,8,true);
	RandomLimits[2][1]=GetRandomBignum(1,8,true);
	RandomLimits[2][2]=GetRandomBignum(1,8,false);
	RandomLimits[2][3]=GetRandomBignum(1,8,false);
	
	RandomLimits[3][0]=GetRandomBignum(1,8,true);
	RandomLimits[3][1]=GetRandomBignum(1,8,true);
	RandomLimits[3][2]=GetRandomBignum(1,8,true);
	RandomLimits[3][3]=GetRandomBignum(1,8,false);
	
	RandomLimits[4][0]=GetRandomBignum(1,8,true);
	RandomLimits[4][1]=GetRandomBignum(1,8,false);
	RandomLimits[4][2]=GetRandomBignum(1,8,true);
	RandomLimits[4][3]=GetRandomBignum(1,8,false);
	for(i=0; i<5; i++)
	{
		cout<<"TEST "<<i+1<<":\n";
		TestCalc(RandomLimits[i][0],RandomLimits[i][1],RandomLimits[i][2],RandomLimits[i][3]);
		delete[]RandomLimits[i];
	}
	delete[]RandomLimits;
	return 0;
}