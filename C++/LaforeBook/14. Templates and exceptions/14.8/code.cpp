//8. Добавьте класс исключений к программе ARROVER из главы 8, чтобы индексы, выходящие за пределы массива, вызывали генерацию исключения. Блок-ловушка может выводить пользователю сообщение об ошибке.
#include "../../accessories.h"
#include <random>
using namespace std;
const int LIMIT=10;
template <class AnyType>
class SafeArray
{
	AnyType arr[LIMIT];
	public:
	class ErrorIncorrectIndex
	{
		public:
		ErrorIncorrectIndex(int NewIncorrectIndex){}
	};
    AnyType& operator[](int n)
	{
		if(n<-1 || n>=LIMIT)
			throw ErrorIncorrectIndex(n);
		return arr[n];
	}
};
int main()
{
	InitFloatingPointAndRandomNumbers();
	random_device RandomDevice;
	default_random_engine RandomGenerator(RandomDevice());
	int i,CountOfDivides;
	
	int IntMax=INT_MAX/LIMIT,IntMin=IntMax/LIMIT;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		IntMin/=10;
	uniform_int_distribution<int> IntDistribution(IntMin,IntMax);
	SafeArray<int> SafeIntArray;
	for(i=0; i<LIMIT; i++)
		SafeIntArray[i]=IntDistribution(RandomGenerator);
	cout<<"TYPE INT:\n";
	for(i=0; i<LIMIT+3; i++)
	{
		try{cout<<"Element "<<i<<" = "<<SafeIntArray[i]<<endl;}
		catch(SafeArray<int>::ErrorIncorrectIndex){cout<<"Incorrect index\n";}
	}
	for(i=0; i<91; i++)
		cout<<'-';
	
	cout<<"TYPE LONG LONG:\n";
	long long LongLongMax=LLONG_MAX/LIMIT,LongLongMin=LongLongMax/LIMIT;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		LongLongMin/=10;
	uniform_int_distribution<long long> LongLongDistribution(LongLongMin,LongLongMax);
	SafeArray<long long> SafeLongLongArray;
	for(i=0; i<LIMIT; i++)
		SafeLongLongArray[i]=LongLongDistribution(RandomGenerator);
	for(i=0; i<LIMIT+3; i++)
	{
		try{cout<<"Element "<<i<<" = "<<SafeLongLongArray[i]<<endl;}
		catch(SafeArray<long long>::ErrorIncorrectIndex){cout<<"Incorrect index\n";}
	}
	for(i=0; i<91; i++)
		cout<<'-';
	
	cout<<"TYPE DOUBLE:\n";
	double DoubleMax=LLONG_MAX/LIMIT,DoubleMin=DoubleMax/LIMIT;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		DoubleMin/=10;
	SafeArray<double> SafeDoubleArray;
	for(i=0; i<LIMIT; i++)
		SafeDoubleArray[i]=GetRandomDouble(DoubleMin,DoubleMax);
	for(i=0; i<LIMIT+3; i++)
	{
		try{cout<<"Element "<<i<<" = "<<SafeDoubleArray[i]<<endl;}
		catch(SafeArray<double>::ErrorIncorrectIndex){cout<<"Incorrect index\n";}
	}
	
	/*SafeArray sa1(INT_MAX);
	int j;
	for(j=0; j<LIMIT; j++)
	{
		sa1[j]=j*10;
		SafeArray sa2(567);
		sa2[0]=sa1[0];
		//cout<<"sa1[j]: "<<sa1[j]<<"; GetZeroIfError(): "<<sa1.GetZeroIfError()<<endl;
	}
	cout<<"-------------------------\n";
	for(j=0; j<LIMIT+5; j++)
	{
		int temp=sa1[j]; //используем функцию справа от знака =
		cout<<"Element "<<j<<" = "<<temp<<endl;
	}*/
	return 0;
}