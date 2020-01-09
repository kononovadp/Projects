/*Напишите программу, которая возвращает наибольшее число палиндром, которое является произведением двух простых пятизначных чисел, а также возвращает сами сомножители.
Простое число - это натуральное число, которое делится нацело только на 1 и на себя само (2, 3, 5, 7, 11, …)
Палиндром – строка, которая читается одинаково в обоих направлениях (например ABBA).*/
#include <stdio.h>
#include <time.h>
//функция, инвертирующая целое число (1234 преобразовывает в 4321 и т. д.)
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
//проверка, является ли число простым
int simple(long long int n)
{
    for(int i=2; i<=n/2; i++)
		if( (n%i)==0 ) return 0;
	return 1;
}
//проверка, является ли произведение двух множителей палиндромом
long long int is_the_product_palindrome(long long int multiplier1,long long int multiplier2)
{
	long long int product=multiplier1*multiplier2;
	printf("%lld multiplied by %lld makes %lld\n",multiplier1,multiplier2,product);
	if (product==invert_int_number(product))
		return product;
	else
		return 0;
}
//поиск палиндрома в массиве простых чисел
long long int find_palindrome_in_the_array(long long int count,long long int array[count],
long long int *res_multiplier1,long long int *res_multiplier2)
{
	long long int i;
	long long int result;
	//первый элемент "сокращающегося" массива не изменяется
	const long long int first_multiplier=array[count];
	//все остальные элементы массива, на которые умножается первый элемент
	long long int second_multiplier=array[count]; 
	while(count>0)
	{
		result=is_the_product_palindrome(first_multiplier,second_multiplier);
		if(result>0)
		{
			*res_multiplier1=first_multiplier;
			*res_multiplier2=second_multiplier;
			return result;
		}
		count--;
		second_multiplier=array[count];
	}
	return 0;	
}
//главная функция, выполняющая поиск наибольшего палиндрома в заданном интервале
long long int find_palindrome(long long int lower_limit, long long int upper_limit, long long int *res_multiplier1,long long int *res_multiplier2)
{
	//в качестве размера массива взял разницу между верхним пределом и нижним
	long long int array_of_simple_numbers[upper_limit-lower_limit];
	long long int result=0;
	long long int simple_numbers_count;
	printf("looking for all simple numbers in the range of %lld-%lld...\n",lower_limit,upper_limit);
	//формирование массива всех простых чисел в заданном интервале
	for(simple_numbers_count=0; lower_limit<upper_limit; lower_limit++)
		if(simple(lower_limit)==1)
		{
			array_of_simple_numbers[simple_numbers_count]=lower_limit;			
			simple_numbers_count++;
		}
	//выполнять поиск наибольшего палиндрома, пока не будут обработаны все элементы массива
	for(simple_numbers_count--; simple_numbers_count>0; simple_numbers_count--)
	{
		result=find_palindrome_in_the_array(simple_numbers_count,array_of_simple_numbers,
											res_multiplier1, res_multiplier2);
		if(result>0)
			return result;
		//количество обрабатываемых элементов массива уменьшается на каждом шаге
	}
	//вернуть нулевой результат, если палиндром не был найден
	return result;
}
int main(void)
{
	long long int lower=1000;
	long long int upper=9999;
	long long int result_multiplier1=0;
	long long int result_multiplier2=0;
	time_t begin=time(&begin);
	long long int palindrome=find_palindrome(lower,upper,&result_multiplier1,&result_multiplier2);
	if (palindrome==0)
		printf("No simple multipliers in the range of %lld-%lld makes palindrome",lower,upper);
	else
		printf("Simple number %lld multiplied by the simple number %lld\nmakes palindrome %lld",result_multiplier1,result_multiplier2,palindrome);
	time_t end=time(&end);
	printf("\n\nProcess duration is %d seconds",end-begin);
	return 0;
}