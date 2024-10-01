//11. Создайте класс, который позволит вам использовать 10 отдельных массивов из упражнения 10 как один одномерный массив, допуская применение операций массива. То есть мы можем получить доступ к элементам массива, записав в функции main() выражение типа a[j], а методы класса могут получить доступ к полям класса, используя двухшаговый подход. Перегрузим операцию [] (см. главу 9 «Наследование»), чтобы получить нужный нам результат. Заполним массив данными и выведем их. Хотя для интерфейса класса использованы операции индексации массива, вам следует использовать указатели внутри методов класса.
#include "../../accessories.h"
class TwoDimensionalArray
{
	int** arr,MaxSize;
	public:
	TwoDimensionalArray(int** NewArr,int NewMaxSize)
	{
		arr=NewArr;
		MaxSize=NewMaxSize;
	}
	int operator[](int index)
	{
		return *(*(arr+index/MaxSize)+index%MaxSize);
	}
};
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	int i,j,MaxSize=10,**arr=new int*[MaxSize];
	for(i=0; i<MaxSize; i++)
	{
		*(arr+i)=new int[MaxSize];
		for(j=0; j<MaxSize; j++)
			*(*(arr+i)+j)=GetRandomInt(10,1000);
	}
	TwoDimensionalArray MyArray(arr,MaxSize);
	for(i=0; i<MaxSize; i++)
	{
		for(j=0; j<MaxSize; j++)
			cout<<setw(4)<<*(*(arr+i)+j);
		cout<<endl;
	}
	cout<<"-------------------------------------------------------------------------------------";
	for(i=0; i<MaxSize*MaxSize; i++)
	{		
		if(i%5==0)
			cout<<endl;
		cout<<"arr["<<setw(3)<<i<<"] = "<<setw(4)<<MyArray[i]<<"; ";		
	}	
	for(i=0; i<MaxSize; i++)
		delete[]*(arr+i);
	delete[]arr;
	return 0;
}
