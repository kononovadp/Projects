//4. Создайте функцию swaps(), обменивающую значения двух аргументов, посылаемых ей. (Возможно, вы догадаетесь передавать эти аргументы по ссылке.) Сделайте из функции шаблон, чтобы она могла использоваться с любыми числовыми типами данных (int, char, float и т. д.). Напишите main() для тестирования функции.
#include "../../accessories.h"
#include <random>
using namespace std;
template <class AnyType>
void swaps(AnyType& number1,AnyType& number2)
{
	AnyType temp=number1;
	number1=number2;
	number2=temp;
}
int main(void)
{
	InitFloatingPointAndRandomNumbers();	
	random_device RandomDevice;
	default_random_engine RandomGenerator(RandomDevice());
	int i,CountOfDivides,divider=GetRandomInt(5,20);
	
	int IntMax=INT_MAX/divider,IntMin=IntMax/divider;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		IntMin/=10;
	uniform_int_distribution<int> IntDistribution(IntMin,IntMax);
	int RandomInt1=IntDistribution(RandomGenerator);
	int RandomInt2=IntDistribution(RandomGenerator);	
	cout<<"RandomInt1: "<<RandomInt1<<"; RandomInt2: "<<RandomInt2<<endl;
	swaps(RandomInt1,RandomInt2);
	cout<<"RandomInt1: "<<RandomInt1<<"; RandomInt2: "<<RandomInt2<<endl;
	
	divider=GetRandomInt(5,20);
	long long LongLongMax=LLONG_MAX/divider,LongLongMin=LongLongMax/divider;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		LongLongMin/=10;
	uniform_int_distribution<long long> LongLongDistribution(LongLongMin,LongLongMax);
	long long RandomLongLong1=LongLongDistribution(RandomGenerator);
	long long RandomLongLong2=LongLongDistribution(RandomGenerator);	
	cout<<"RandomLongLong1: "<<RandomLongLong1<<"; RandomLongLong2: "<<RandomLongLong2<<endl;
	swaps(RandomLongLong1,RandomLongLong2);
	cout<<"RandomLongLong1: "<<RandomLongLong1<<"; RandomLongLong2: "<<RandomLongLong2<<endl;
	
	divider=GetRandomInt(5,20);
	double DoubleMax=LLONG_MAX/divider,DoubleMin=DoubleMax/divider;
	for(i=0,CountOfDivides=GetRandomDouble(2,6); i<CountOfDivides; i++)
		DoubleMin/=10.0;
	double RandomDouble1=GetRandomDouble(DoubleMin,DoubleMax);
	double RandomDouble2=GetRandomDouble(DoubleMin,DoubleMax);
	cout<<"RandomDouble1: "<<RandomDouble1<<"; RandomDouble2: "<<RandomDouble2<<endl;
	swaps(RandomDouble1,RandomDouble2);
	cout<<"RandomDouble1: "<<RandomDouble1<<"; RandomDouble2: "<<RandomDouble2<<endl;
	
	char RandomCharacter1=GetRandomChar('A','Z');
	char RandomCharacter2=GetRandomChar('A','Z');
	cout<<"RandomCharacter1: "<<RandomCharacter1<<"; RandomCharacter2: "<<RandomCharacter2<<endl;
	swaps(RandomCharacter1,RandomCharacter2);
	cout<<"RandomCharacter1: "<<RandomCharacter1<<"; RandomCharacter2: "<<RandomCharacter2<<endl;
	return 0;
}
