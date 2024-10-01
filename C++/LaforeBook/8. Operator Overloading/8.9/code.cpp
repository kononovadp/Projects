/*9. Дополните класс safearay из программы ARROVER3 этой главы так, чтобы пользователь мог определять и верхнюю, и нижнюю границы массива (например, индексы, начинающиеся с 100 и заканчивающиеся 200). Имеем перегруженную операцию доступа к членам массива, проверяющую индексы каждый раз, когда к массиву нужен доступ, для проверки того, что мы не вышли за пределы массива. Вам понадобится конструктор с двумя аргументами, который определяет верхнюю и нижнюю границы. Так как мы еще не изучили, как выделять память динамически, то данные класса все еще будут размещаться в массиве, состоящем из 100 элементов, но вообще вы можете преобразовывать индексы массива safearay в индексы реального массива целых чисел произвольным образом. Например, если пользователь определил диапазон от 100 до 175, то вы можете преобразовать его в диапазон от arr[0] до arr[75]*/
//arrover3.cpp
//демонстрация создания безопасного массива, проверяющего
//свои индексы при использовании
//используется перегрузка операции []
#include <iostream>
using namespace std;
const int limit=20; //размер массива
int zero=100000;
class SafeArray
{
	bool overflow;
	int LowerIndex,UpperIndex,*arr;
	public:
	SafeArray(){overflow=false; arr=new int[limit];}
	SafeArray(int NewLowerIndex,int NewUpperIndex)
	{
		overflow=false;
		arr=new int[limit];
		LowerIndex=NewLowerIndex;
		UpperIndex=NewUpperIndex;
	}
	//~SafeArray(){delete(arr);}
	bool GetOverflowState(){return overflow;}
	int& operator[](int n)
	{
		if(n<LowerIndex || n>LowerIndex+limit || n>UpperIndex)
		{
			overflow=true;
			return zero;
		}
		overflow=false;
		return arr[n-LowerIndex];		
	}
};
int main()
{	
	int LowerIndex=5,UpperIndex=30,j,item;
	SafeArray SafeArray1(LowerIndex,UpperIndex);
	for(j=0; j<UpperIndex; j++)
	{
		item=j*10;
		SafeArray1[j]=item;
		cout<<"item "<<SafeArray1[j]<<" with index "<<j;
		if(!SafeArray1.GetOverflowState())
			cout<<" was added\n";
		else
			cout<<" was NOT ADDED\n";
	}
	cout<<"---------------------------\n";
	for(j=0; j<UpperIndex; j++)
	{
		item=SafeArray1[j];
		cout<<"item with index "<<j<<": ";
		if(!SafeArray1.GetOverflowState())
			cout<<item<<endl;
		else
			cout<<"not found\n";
	}
	return 0;
}
