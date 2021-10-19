/*8. Вернитесь к упражнению 9 главы 2 «Основы программирования на C++». В этом упражнении требуется написать программу, которая хранит значения двух дробей в виде числителя и знаменателя, а затем складывает эти дроби согласно арифметическому правилу. Измените эту программу так, чтобы значения дробей хранились в структуре fraction, состоящей из двух полей типа int, предназначенных для хранения числителя и знаменателя. Все значения дробей должны храниться в переменных типа fraction.*/
#include <iostream>
using namespace std;
int main(void)
{
	struct fract
	{
		int numerator;
		int denominator;
	};
	struct fract f1,f2;
	char dummychar;
	cout<<"First fraction: ";
	cin>>f1.numerator>>dummychar>>f1.denominator;
	cout<<"Second fraction: ";
	cin>>f2.numerator>>dummychar>>f2.denominator;
	cout<<"Sum = "<<(f1.numerator*f2.denominator)+(f1.denominator*f2.numerator)<<'/'<<f1.denominator*f2.denominator;
	return 0;
}
