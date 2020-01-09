/*Напишите программу реализации степенной зависимости, которая работает на основе командной строки. Первым аргументом командной строки должно быть число типа double, возводимое в определенную степень, а вторым аргументом целочисленный показатель степени.*/
#include <stdio.h>
#include "D:\Projects\C\my_library\user_functions.h"
int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("Некорректное количество аргументов командной строки");
		return 0;
	}
	double number=strtofloat(argv[1]);
	int power=strtoint(argv[2]);
	double res=1;
	printf("Число %lf в степени %d = ",number,power);
	while(power-- >0)
		res*=number;
	printf("%lf",res);
    return 0;
}