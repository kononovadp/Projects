/*Напишите программу, которая принимает в качестве ввода положительное целое число и отображает все простые числа, которые меньше или равны введенному числу.*/
#include <stdio.h>
int main(void)
{
	int n,i,j,divisors;
	short b;
	printf("Положительное целое число: ");
	scanf("%d",&n);
	printf("Все простые числа от 1 до %d:\n",n);
	while(--n >1)
	{
		divisors=0;
		for(i=1; i<n; i++)
			if(n%i==0)
				divisors++;
		if(divisors<2)
			printf("%d\n",n);
	}
	printf("Программа выполнена");
	return 0;	
}