//5. Создайте функцию amax(), возвращающую значение максимального элемента массива. Аргументами функции должны быть адрес и размер массива. Сделайте из функции шаблон, чтобы она могла работать с массивом любого числового типа. Напишите секцию main(), в которой проверьте работу функции с разными типами массивов.
#include "../../accessories.h"
#include <random>
using namespace std;
template <class AnyType>
AnyType amax(AnyType* array,int size)
{
	int i;
	AnyType max=array[0];
	for(i=0; i<size; i++)
		if(array[i]>max)
			max=array[i];
	return max;
}
template <class AnyType>
AnyType* GetRandomIntOrLongLongArray(AnyType MinNumber,AnyType MaxNumber,int RandomSize,string TupeName,default_random_engine RandomGenerator)
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
	cout<<endl;
	return RandomArray;
}
template <class AnyType>
AnyType* GetRandomDoubleOrCharArray(AnyType MinNumber,AnyType MaxNumber,int RandomSize,string TupeName,int MaxCountOfDigits,AnyType RandomGenerator(AnyType min,AnyType max))
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
	cout<<endl;
	return RandomArray;
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
	int* RandomIntArray=GetRandomIntOrLongLongArray(IntMin,IntMax,RandomSize,"INT",RandomGenerator);
	cout<<"Max number in array: "<<amax(RandomIntArray,RandomSize)<<endl;	
	for(i=0; i<91; i++)
		cout<<'-';
	delete[] RandomIntArray;
	
	RandomSize=GetRandomInt(100,200);
	long long LongLongMax=LLONG_MAX/RandomSize,LongLongMin=LongLongMax/RandomSize;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		LongLongMin/=10;
	long long* RandomLongLongArray=GetRandomIntOrLongLongArray(LongLongMin,LongLongMax,RandomSize,"LONG LONG",RandomGenerator);
	cout<<"Max number in array: "<<amax(RandomLongLongArray,RandomSize)<<endl;	
	for(i=0; i<91; i++)
		cout<<'-';
	delete[] RandomLongLongArray;
	
	RandomSize=GetRandomInt(100,200);
	double DoubleMax=INT_MAX/RandomSize,DoubleMin=DoubleMax/RandomSize;
	for(i=0,CountOfDivides=GetRandomDouble(2,6); i<CountOfDivides; i++)
		DoubleMin/=10.0;
	double* RandomDoubleArray=GetRandomDoubleOrCharArray(DoubleMin,DoubleMax,RandomSize,"DOUBLE",GetCountOfDigits(INT_MAX)+3,GetRandomDouble);
	cout<<"Max number in array: "<<amax(RandomDoubleArray,RandomSize)<<endl;	
	for(i=0; i<91; i++)
		cout<<'-';
	delete[] RandomDoubleArray;
	
	RandomSize=GetRandomInt(100,200);
	char CharMax='Z'+1;
	char* RandomCharArray=GetRandomDoubleOrCharArray('A',CharMax,RandomSize,"CHAR",1,GetRandomChar);
	cout<<"Max number in array: "<<amax(RandomCharArray,RandomSize)<<endl;
	for(i=0; i<91; i++)
		cout<<'-';
	delete[] RandomCharArray;
	return 0;
}
