/* Напишите программу, которая читает число с плавающей запятой и выводит его сначала в десятичной, а затем в экспоненциальной форме. Предусмотрите вывод в следующих форматах (количество цифр показателя степени в вашей системе может быть другим).
а) Вводом является 21.3 или 2.1е+001
б) Вводом является +21.290 или 2.129Е+001*/
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    float f1;
	int temp,precision;
	printf("Введите дробное число: ");	
	scanf("%f%n",&f1,&precision);
	temp=f1;	
	printf("Вводом является %f или %e\n",f1,f1);
	if (temp==0)
		precision-=2;
	else
	{
		while (temp>0)
		{
			temp /= 10;
			precision-=1;
		}
		precision-=1;
	}
	printf("Вводом является %+.*f или %.*E",precision,f1,precision,f1);
	getchar();
	getchar();
}