//5. Предположим, что в функции main() определены три локальных массива одинакового размера и типа (скажем, float). Первые два уже инициализированы значениями. Напишите функцию addarrays(), которая принимает в качестве аргументов адреса трех массивов, складывает соответствующие элементы двух массивов и помещает результат в третий массив. Четвертым аргументом этой функции может быть размерность массивов. На всем протяжении программы используйте указатели.
#include "../../accessories.h"
void addarrays(double* arr1,double* arr2,double* arr3,int size)
{	
	for(int i=0; i<size; i++)
		*(arr3+i)=*(arr1+i)+*(arr2+i);
}
void display(double* arr,int size)
{	
	for(int i=0; i<size; i++)
		cout<<setw(8)<<arr[i];
	cout<<endl;
}
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	int i,size=10;
	double* arr1=new double[size];
	double* arr2=new double[size];
	double* arr3=new double[size];
	for(i=0; i<size; i++)
	{
		arr1[i]=GetRandomDouble(1,100);
		arr2[i]=GetRandomDouble(1,100);
	}
	addarrays(arr1,arr2,arr3,size);
	display(arr1,size);
	display(arr2,size);
	display(arr3,size);
	delete[]arr1;
	delete[]arr2;
	delete[]arr3;
	return 0;
}
