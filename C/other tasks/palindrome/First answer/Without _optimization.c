/*Напишите программу, которая возвращает наибольшее число палиндром, которое является произведением двух простых пятизначных чисел, а также возвращает сами сомножители.
Простое число - это натуральное число, которое делится нацело только на 1 и на себя само (2, 3, 5, 7, 11, …)
Палиндром – строка, которая читается одинаково в обоих направлениях (например ABBA).*/
#include <stdio.h>
#include <time.h>
long long int invert_int_number(long long int number)
{	
	long long int i=1;
	long long int res=0;
	while (i<=number/10)
		i*=10;
	while (number>0)
	{		
		res=res+((number%10)*i);		
		number/=10;		
		i/=10;		
	}
	return res;
}

int simple(long long int n)
{
    for(int i=2; i<=n/2; i++)
		if( (n%i)==0 ) return 0;
	return 1;
}

long long int is_the_product_palindrome(long long int multiplier1,long long int multiplier2)
{
	long long int product=multiplier1*multiplier2;
	printf("%lld multiplied by %lld makes %lld\n",multiplier1,multiplier2,product);
	if (product==invert_int_number(product))
		return product;
	else
		return 0;
}

long long int palindrome_under_different_simple_multipliers(long long int lower_limit,
long long int upper_limit,long long int *res_multiplier1,long long int *res_multiplier2)
{	
	long long int result;
	long long int second_multiplier;
	long long int palindrome;
	while(upper_limit>lower_limit)
	{
		while (simple(upper_limit)!=1)
			upper_limit--;		
		palindrome=is_the_product_palindrome(upper_limit,upper_limit);
		if (palindrome>0)
		{
			*res_multiplier1=upper_limit;
			*res_multiplier2=upper_limit;
			return palindrome;
		}
		else
		{
			second_multiplier=upper_limit-1;
			while(second_multiplier>lower_limit)
			{
				while(simple(second_multiplier)!=1)
					second_multiplier--;
				palindrome=is_the_product_palindrome(upper_limit,second_multiplier);
				if (palindrome>0)
				{
					*res_multiplier1=upper_limit;
					*res_multiplier2=second_multiplier;
					return palindrome;
				}
				second_multiplier--;
			}
		}
		upper_limit--;
	}
	return 0;
}
	
int main(void)
{
	long long int lower=1000;
	long long int upper=9999;
	long long int result_multiplier1=0;
	long long int result_multiplier2=0;
	time_t begin=time(&begin);
	long long int palindrome=palindrome_under_different_simple_multipliers(lower,upper,&result_multiplier1,&result_multiplier2);
	if (palindrome==0)
		printf("No simple multipliers in the range of %lld-%lld makes palindrome",lower,upper);
	else
		printf("Simple number %lld multiplied by the simple number %lld\nmakes palindrome %lld",result_multiplier1,result_multiplier2,palindrome);
	time_t end=time(&end);
	printf("\n\nProcess duration is %d seconds",end-begin);
	return 0;
}