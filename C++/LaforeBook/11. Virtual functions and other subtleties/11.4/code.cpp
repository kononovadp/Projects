/**4. Как уже говорилось, классы можно заставлять вести себя как массивы. Пример CLARRAY показывает один из способов создания такого класса. Листинг 11.26. Программа CLARRAY:
#include <iostream>
using namespace std;
class Array //моделирует обычный массив C++ 
{
    int* ptr; //указатель на содержимое Array
    int size; //размер Array
	public:
    Array(int s) //конструктор с одним аргументом
	{
		size=s; //аргумент - размер Array 
		ptr=new int[s]; //выделить память под Array 
	}
    ~Array(){delete[] ptr;}
    int& operator[](int j){return *(ptr + j);} //перегружаемая операция списка индексов    
};
int main()
{
	const int ASIZE=10; //размер массива
	Array arr(ASIZE); //создать массив
	for(int j=0; j<ASIZE; j++) //заполнить его j^2
		arr[j]=j*j;
	for(int j=0; j<ASIZE; j++) //вывести его содержимое
		cout << arr[j] << ' ';
	cout<<endl;
	return 0;
}
Результат работы программы: 0 1 4 9 16 25 36 49 64 81. Взяв за основу приведенную программу, добавьте перегружаемое присваивание и перегружаемый конструктор копирования к классу Array. Затем добавьте к main() выражение Array arr2(arr1); и arr3 = arr1; для проверки того, что перегружаемые операции работают. Конструктор копирования должен создать новый объект Array со своим собственным местом в памяти, выделенным для хранения элементов массива. И конструктор копирования, и оператор присваивания должны копировать содержимое старого объекта класса Array в новый. Что будет, если вы присвоите объект Array одного размера объекту Array другого размера*/
#include "../../accessories.h"
class Array
{
    int* arr;
    int size;
	public:
    Array(int NewSize)
	{
		size=NewSize; //аргумент - размер Array 
		arr=new int[NewSize]; //выделить память под Array 
	}
	Array(Array& NewArr)
	{
		size=NewArr.size;
		arr=new int[NewArr.size];
		for(int i=0; i<size; i++)
			arr[i]=NewArr[i];
	}
	void display()
	{
		for(int i=0; i<size; i++)
			cout<<setw(3)<<arr[i];
		cout<<endl;
	}
    ~Array(){delete[] arr;}
    int& operator[](int j){return*(arr+j);} //перегружаемая операция списка индексов
	void operator=(Array& NewArray)
	{
		int i,j,NewSize=size+NewArray.size;
		Array PrevArray(NewSize);
		for(i=0; i<size; i++)
			PrevArray[i]=arr[i];		
		delete[]arr;		
		arr=new int[NewSize];		
		for(i=0; i<size; i++)
			arr[i]=PrevArray[i];		
		for(size=NewSize,j=0; i<size; i++,j++)
			arr[i]=NewArray[j];
	}
};
int main()
{
	InitFloatingPointAndRandomNumbers();
	int i,ArraySize1=GetRandomInt(5,15),ArraySize2=GetRandomInt(5,15);
	Array arr1(ArraySize1),arr2(ArraySize2);
	for(i=0; i<ArraySize1; i++)
		arr1[i]=GetRandomInt(0,100);
	for(i=0; i<ArraySize2; i++)
		arr2[i]=GetRandomInt(0,100);
	cout<<"arr1:             ";
	arr1.display();
	cout<<"arr2:             ";
	arr2.display();
	Array arr3(arr1);
	cout<<"Array arr3(arr1): ";
	arr3.display();
	arr2=arr3;	
	cout<<"arr2=arr3:        ";
	arr2.display();
	return 0;
}