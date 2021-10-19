﻿/*10. Напишите функцию, которая при каждом вызове будет выводить на экран количество раз, которое она вызывалась ранее. Напишите программу, которая будет вызывать данную функцию не менее 10 раз. Попробуйте реализовать данную функцию двумя различными способами: с использованием глобальной переменной и статической локальной переменной для хранения числа вызовов функции. Какой из способов предпочтительней? Почему для решения задачи нельзя использовать обычную локальную переменную?*/
#include <iostream>
using namespace std;
int CallsCount=0;
void FuncGlob()
{
	CallsCount++;
	cout<<"FuncGlob ran "<<CallsCount<<" times\n";
}
void FuncLocal(int& n)
{
	n++;
	cout<<"FuncLocal ran "<<n<<" times\n";
}
int main(void)
{
	int i;
	for(i=0; i<10; i++)
		FuncGlob();
	int n=0;
	for(i=0; i<10; i++)
		FuncLocal(n);
	return 0;
}
