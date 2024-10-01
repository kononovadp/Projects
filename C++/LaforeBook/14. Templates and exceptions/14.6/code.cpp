//6. Начните работу с класса safearay из программы ARROVER3 (глава 8). Сделайте класс шаблоном, чтобы массив мог хранить любые типы данных. В секции main() создайте, по крайней мере, два массива разных типов.
#include "../../accessories.h"
#include <random>
using namespace std;
const int LIMIT=10;
template <class AnyType>
class SafeArray
{
	AnyType ZeroIfError;
	AnyType arr[LIMIT];
	public:	
	SafeArray(AnyType NewZeroIfError)
	{
		ZeroIfError=NewZeroIfError;
	}
    AnyType& operator[](int n)
	{
		/*if(n<0 || n>=LIMIT)
		{
			cout<<"Incorrect index!";			
			//exit(1);
		}
		return arr[n];*/
		if(n>-1 && n<LIMIT)
			return arr[n];
		return ZeroIfError;
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
	SafeArray<int> SafeIntArray(INT_MIN);
	for(i=0; i<LIMIT; i++)
		SafeIntArray[i]=IntDistribution(RandomGenerator);
	cout<<"TYPE INT:\n";
	for(i=0; i<LIMIT+5; i++)
	{
		if(SafeIntArray[i]==INT_MIN)
			cout<<"ERROR! "<<i<<" is an incorrect index!"<<endl;
		else
			cout<<"Element "<<i<<" = "<<SafeIntArray[i]<<endl;
	}
	for(i=0; i<91; i++)
		cout<<'-';
	
	cout<<"TYPE LONG LONG:\n";
	long long LongLongMax=LLONG_MAX/LIMIT,LongLongMin=LongLongMax/LIMIT;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		LongLongMin/=10;
	uniform_int_distribution<long long> LongLongDistribution(LongLongMin,LongLongMax);
	SafeArray<long long> SafeLongLongArray(LLONG_MIN);
	for(i=0; i<LIMIT; i++)
		SafeLongLongArray[i]=LongLongDistribution(RandomGenerator);
	for(i=0; i<LIMIT+5; i++)
	{
		if(SafeLongLongArray[i]==LLONG_MIN)
			cout<<"ERROR! "<<i<<" is an incorrect index!"<<endl;
		else
			cout<<"Element "<<i<<" = "<<SafeLongLongArray[i]<<endl;
	}
	for(i=0; i<91; i++)
		cout<<'-';
	
	cout<<"TYPE DOUBLE:\n";
	double DoubleMax=LLONG_MAX/LIMIT,DoubleMin=DoubleMax/LIMIT;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		DoubleMin/=10;
	SafeArray<double> SafeDoubleArray(DBL_MIN);
	for(i=0; i<LIMIT; i++)
		SafeDoubleArray[i]=GetRandomDouble(DoubleMin,DoubleMax);
	for(i=0; i<LIMIT+5; i++)
	{
		if(SafeDoubleArray[i]==DBL_MIN)
			cout<<"ERROR! "<<i<<" is an incorrect index!"<<endl;
		else
			cout<<"Element "<<i<<" = "<<SafeDoubleArray[i]<<endl;
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
