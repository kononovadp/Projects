// Program lab4.cpp
#include <stdio.h>
#define n 255 // кількість байтів у надвеликому числі
typedef unsigned char byte; // для роботи з байтами використовується тип char
extern "C" void BigShowN(byte* p1, int p2); //функція реалізована мовою Асемблера
int main()
{
	byte x[n], y[n]; //надвеликі числа
	for (int i = 0; i<n; i++)
	{
		x[i] = i;
		y[i] = 0;
	}
	printf("x=");
	BigShowN(x, n);
	printf("y=");
	BigShowN(y, n);
	return 0;
}