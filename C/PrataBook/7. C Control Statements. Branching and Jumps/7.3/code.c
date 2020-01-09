/*Напишите программу, которая читает целые числа до тех пор, пока не встретится число 0. После прекращения ввода программа должна сообщить общее количество введенных четных целых чисел (за исключением 0), среднее значение четных целых чисел, общее количество введенных нечетных целых чисел и среднее значение нечетных чисел.*/
#include <stdio.h>
int main(void)
{
	int n,even_numbers,odd_numbers,even_numbers_sum,odd_numbers_sum;
	scanf("%d",&n);
	for(even_numbers=0,odd_numbers=0,even_numbers_sum=0,odd_numbers_sum=0;
	n!=0; scanf("%d",&n))
	{
		if(n!=0 && n%2==0)
		{
			even_numbers++;
			even_numbers_sum+=n;
		}
		else
		{
			odd_numbers++;
			odd_numbers_sum+=n;
		}
	}
	printf("Общее количество четных чисел: %d\n"
	"Среднее значение четных чисел: %d\n"
	"Общее количество нечетных чисел: %d\n"
	"Среднее значение нечетных чисел: %d\n",even_numbers,even_numbers_sum/even_numbers,
	odd_numbers,odd_numbers_sum/odd_numbers);	
	return 0;
}
					
