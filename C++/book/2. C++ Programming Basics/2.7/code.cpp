﻿/*7. Температуру, измеренную в градусах по Цельсию, можно перевести в градусы по Фаренгейту путем умножения на 9/5 и сложения с числом 32. Напишите программу, запрашивающую температуру в градусах по Цельсию и отображающую ее эквивалент по Фаренгейту.*/

#include <iostream>
using namespace std;
int main(void)
{
	float t;
	cout<<"Celsius temperature: ";
	cin>>t;
	cout<<"Fahrenheit temperature: "<<t*(9.0/5.0)+32;
	return 0;
}