﻿/*3. Операции ввода, такие как cin, должны уметь преобразовывать последовательность символов в число. Напишите программу, которая позволяет пользователю ввести шесть цифр, а затем выводит результат типа long на экране. Каждая цифра должна считываться отдельно при помощи функции getche(). Вычисления значения переменной производится путем умножения текущего ее значения на 10 и сложения с последней введенной цифрой (для того чтобы из кода символа получить цифру, вычтите из него 48 или '0'). Примером результата работы программы может служить следующий:
Введите число: 123456
Вы ввели число 123456*/
#include <iostream>
#include <conio.h>
using namespace std;
int main(void)
{
	long int r=0;
	int i,t=100000;
	char n;
	cout<<"Enter 6 digits: ";
	for(i=0; i<6; i++)
	{
		n=getche()-'0';
		r=r+(n*t);
		t/=10;
	}
	cout<<endl<<"you entered: "<<r;
	return 0;
}
