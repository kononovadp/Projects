//5. Заполните массив четными числами, а множество — нечетными. С помощью алгоритма merge() объедините эти контейнеры в вектор. Выведите его содержимое, чтобы удостовериться, что слияние прошло успешно.
#include "../../accessories.h"
#include <algorithm>
#include <set>
#include <vector>
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	int ArrSize=GetRandomInt(3,30),SetSize=GetRandomInt(3,30);
	int i,NewNumber,*IntArray=new int[ArrSize];
	set<int> IntSet;
	cout<<"Array size: "<<ArrSize<<"; INT ARRAY:";
	for(i=0; i<ArrSize; i++)
	{
		NewNumber=GetRandomInt(1,SHRT_MAX);
		if(NewNumber%2==1)
			NewNumber++;
		IntArray[i]=NewNumber;
		if(i%8==0)
			cout<<endl;
		cout<<setw(2)<<i+1<<"."<<setw(6)<<IntArray[i]<<"; ";
	}
	if(i-1%8>0)
		cout<<endl;
	cout<<"Set size: "<<SetSize<<"; INT SET:";
	for(i=0; i<SetSize; i++)
	{
		NewNumber=GetRandomInt(1,SHRT_MAX);
		if(NewNumber%2==1)
			NewNumber++;
		IntSet.insert(NewNumber);
		if(i%8==0)
			cout<<endl;
		cout<<setw(2)<<i+1<<"."<<setw(6)<<NewNumber<<"; ";
	}
	if(i-1%8>0)
		cout<<endl;
	cout<<"REAL SET SIZE: "<<IntSet.size()<<"; INT SET:";
	set<int>::iterator IntSetIterator=IntSet.begin();
	for(i=0; i<IntSet.size(); i++)
	{
		if(i%8==0)
			cout<<endl;
		cout<<setw(2)<<i+1<<"."<<setw(6)<<*IntSetIterator++<<"; ";
	}
	vector<int> ArrayAndSet;
	merge(IntArray,IntArray+ArrSize,IntSet.begin(),IntSet.end(),back_inserter(ArrayAndSet));
	if(i-1%8>0)
		cout<<endl;
	cout<<"\nSize of joined vector: "<<ArrayAndSet.size()<<"; JOINED DATA:";
	for(i=0; i<ArrayAndSet.size(); i++)
	{
		if(i%8==0)
			cout<<endl;
		cout<<setw(2)<<i+1<<"."<<setw(6)<<ArrayAndSet[i]<<"; ";
	}
	delete[] IntArray;
	return 0;
}
