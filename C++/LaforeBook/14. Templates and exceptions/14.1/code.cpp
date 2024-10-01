//*1. Напишите шаблон функции, возвращающей среднее арифметическое всех элементов массива. Аргументами функции должны быть имя и размер массива (типа int). В main() проверьте работу функции с массивами типа int, long, double  и char.
#include "../../accessories.h"
#include <random>
template <class AnyType>
AnyType GetArithmeticalMean(AnyType* array,int ArraySize)
{
	int i;
	long long ArithmeticalMean=0;
	for(i=0; i<ArraySize; i++)
		ArithmeticalMean+=array[i];
	return ArithmeticalMean/ArraySize;
}
template <class AnyType>
void TestIntegerTypes(AnyType MinNumber,AnyType MaxNumber,int RandomSize,string TupeName,default_random_engine RandomGenerator)
{
	int i,CountOfDigits,LineWidth;
	AnyType MaxNumberInArray=MinNumber;
	AnyType* RandomArray=new AnyType[RandomSize];
	uniform_int_distribution<AnyType> distribution(MinNumber,MaxNumber);
	for(i=0; i<RandomSize; i++)
	{
		RandomArray[i]=distribution(RandomGenerator);
		if(RandomArray[i]>MaxNumberInArray)
			MaxNumberInArray=RandomArray[i];
	}
	CountOfDigits=GetCountOfDigits(MaxNumberInArray);
	LineWidth=90/(CountOfDigits+1);
	cout<<"RANDOM SIZE: "<<RandomSize<<"; MIN: "<<MinNumber<<"; MAX: "<<MaxNumber<<"; RANDOM "<<TupeName<<" ARRAY: ";
	for(i=0; i<RandomSize; i++)
	{
		if(i%LineWidth==0)
			cout<<endl;
		cout<<setw(CountOfDigits+1)<<RandomArray[i];
	}
	cout<<"\nArithmetical mean: "<<GetArithmeticalMean(RandomArray,RandomSize)<<endl;
	cout<<"-------------------------------------------------------------------------------------------";
	delete[] RandomArray;
}
template <class AnyType>
void TestCharAndDouble(AnyType MinNumber,AnyType MaxNumber,int RandomSize,string TupeName,char MaxCountOfDigits,AnyType RandomGenerator(AnyType min,AnyType max))
{
	int i,LineWidth;
	AnyType* RandomArray=new AnyType[RandomSize];
	for(i=0; i<RandomSize; i++)	
		RandomArray[i]=RandomGenerator(MinNumber,MaxNumber);
	LineWidth=90/(MaxCountOfDigits+1);
	cout<<"RANDOM SIZE: "<<RandomSize<<"; MIN: "<<MinNumber<<"; MAX: "<<MaxNumber<<"; RANDOM "<<TupeName<<" ARRAY: ";
	for(i=0; i<RandomSize; i++)
	{
		if(i%LineWidth==0)
			cout<<endl;
		cout<<setw(MaxCountOfDigits+1)<<RandomArray[i];
	}
	cout<<"\nArithmetical mean: "<<GetArithmeticalMean(RandomArray,RandomSize)<<endl;
	cout<<"-------------------------------------------------------------------------------------------";
	delete[] RandomArray;
}
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	random_device RandomDevice;
	default_random_engine RandomGenerator(RandomDevice());
	int i,CountOfDivides,RandomSize=GetRandomInt(100,200);
	
	int IntMax=INT_MAX/RandomSize,IntMin=IntMax/RandomSize;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		IntMin/=10;
	TestIntegerTypes(IntMin,IntMax,RandomSize,"INT",RandomGenerator);
	
	long LongMax=LONG_MAX/RandomSize,LongMin=LongMax/RandomSize;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		LongMin/=10;
	TestIntegerTypes(LongMin,LongMax,RandomSize,"LONG",RandomGenerator);
	
	long long LongLongMax=LLONG_MAX/RandomSize,LongLongMin=LongLongMax/RandomSize;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		LongLongMin/=10;
	TestIntegerTypes(LongLongMin,LongLongMax,RandomSize,"LONG LONG",RandomGenerator);
	
	TestCharAndDouble('A','Z',RandomSize,"CHAR",1,GetRandomChar);
	
	double DoubleMax=INT_MAX/RandomSize,DoubleMin=DoubleMax/RandomSize;
	for(i=0,CountOfDivides=GetRandomDouble(2,6); i<CountOfDivides; i++)
		DoubleMin/=10.0;
	TestCharAndDouble(DoubleMin,DoubleMax,RandomSize,"DOUBLE",GetCountOfDigits(INT_MAX)+3,GetRandomDouble);

	return 0;
}
