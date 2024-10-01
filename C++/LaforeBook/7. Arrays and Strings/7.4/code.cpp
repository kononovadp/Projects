/*4. Начните с программы, которая позволяет пользователю вводить целые числа, а затем сохранять их в массиве типа int. Напишите функцию maxint(), которая, обрабатывая элементы массива один за другим, находит наибольший. Функция должна принимать в качестве аргумента адрес массива и количество элементов в нем, а возвращать индекс наибольшего элемента. Программа должна вызвать эту функцию, а затем вывести наибольший элемент и его индекс. (Смотрите программу SALES этой главы.)*/
#include <iostream>
using namespace std;
int maxint(int arr[],int n)
{
	int i,max=0;
	for(i=0; i<n; i++)
		if(arr[i]>arr[max])
			max=i;
	return max;
}
int main(void)
{
	int i,max,arr[10];
	cout<<"Enter 10 integers:"<<endl;
	for(i=0; i<10; i++)
	{
		cout<<"Number "<<i+1<<": ";
		cin>>arr[i];
	}
	max=maxint(arr,10);
	cout<<endl<<"Maximum integer: "<<arr[max]<<"; index: "<<max;
	return 0;
}
