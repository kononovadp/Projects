//*1. Напишите программу, которая принимает группу чисел от пользователя и помещает их в массив типа float. После того как числа будут помещены в массив, программа должна подсчитать их среднее арифметическое и вывести результат на дисплей. Используйте указатели везде, где только возможно.
#include "../../accessories.h"
int main(void)
{
	int i,ArraySize=5;
	float* arr=new float[ArraySize],ArithmeticMean=0.0;
	InitFloatingPointAndRandomNumbers();
	for(i=0; i<ArraySize; i++)
	{
		cout<<"Floating point number: ";
		*(arr+i)=GetFloatFromKeyboard();
		ArithmeticMean+=*(arr+i);
		cout<<endl;
	}
	ArithmeticMean/=ArraySize;
	cout<<"Arithmetic mean: "<<ArithmeticMean;
	delete[]arr;
	return 0;
}
