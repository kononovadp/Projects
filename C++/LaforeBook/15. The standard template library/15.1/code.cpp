//*1. Напишите программу, являющуюся примером применения алгоритма sort() к массиву типа float. Значения вводятся пользователем, результат работы выводится на экран. 
#include "../../accessories.h"
#include <algorithm>
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	int i;
	const int MaxArrSize=5;
	float* arr=new float[MaxArrSize];
	cout<<"Array:";
	for(i=0; i<MaxArrSize; i++)
	{
		cout<<"\nFloat number "<<i+1<<" / "<<MaxArrSize<<": ";
		arr[i]=GetFloatFromKeyboard();//GetRandomFloat(1,1000);
		
	}
	for(i=0; i<MaxArrSize; i++)
	{
		if(i%10==0)
			cout<<endl;
		cout<<setw(8)<<arr[i];
	}
	sort(arr,arr+MaxArrSize);
	cout<<"\nSorted array: ";
	for(i=0; i<MaxArrSize; i++)
	{
		if(i%10==0)
			cout<<endl;
		cout<<setw(8)<<arr[i];
	}
	delete[] arr;
	return 0;
}
