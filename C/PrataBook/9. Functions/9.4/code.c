/*Среднее гармоническое значение двух чисел получается путем инвертирования этих чисел, вычисления среднего значения инверсий и получении инверсии результата. Напишите функцию, которая принимает два аргумента double и возвращает среднее гармоническое значение этих двух чисел.*/
#include <stdio.h>
#include <math.h>
#include "D:\Projects\C\my_library\user_functions.h"
double invert_number (double number)
{
	double res_double,initial_number=number;
	long long int i,temp,res_int=0;
	for(i=1; i<6; i++)
		number*=10;
	temp=(long long int)number;
	i=1;
	while (i<=temp/10)
		i*=10;
	while (temp>0)
	{
		res_int=res_int+((temp%10)*i);		
		temp/=10;		
		i/=10;
	}
	res_double=(double)res_int;	
	i=1;
	while(initial_number>1)
	{
		i*=10;
		initial_number/=10;
	}
	return res_double/i;
}
int invert_int_number(int number)
{	
	int i=1;
	int res=0;
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
double invert_number2 (double number)
{
	char temp_str[20];
	char fract_part_char[20];
	double temp,source_int_part_tens,res_double=0;
	long long int i,j,source_int_part,source_fract_part;
	source_int_part=(int)number;	
	source_int_part_tens=0;
	while(source_int_part%10==0)
	{
		source_int_part_tens++;
		source_int_part/=10;
	}	
	source_int_part=invert_int_number(source_int_part);	
	res_double=(double)source_int_part;
	i=1;
	while(i<=res_double)
		i*=10;
	res_double/=(double)i;
	while(source_int_part_tens>0)
	{
		res_double/=10;
		source_int_part_tens--;
	}	
	sprintf(temp_str,"%f",number);
	i=0;
	while(temp_str[i]!='.')
		i++;
	i++;
	for(j=0; i<strlen(temp_str); i++, j++)
		fract_part_char[j]=temp_str[i];
	return (double)invert_int_number(strtoint(fract_part_char))+res_double;
}
double harmonic_mean(char ch, double d1, double d2)
{
	printf("Инверсия числа %lf: ",d1);
	if (ch=='1')
		d1=invert_number(d1);
	else
		d1=invert_number2(d1);
	printf("%f;\nИнверсия числа %lf: ",d1,d2);
	if (ch=='1')
		d2=invert_number(d2);
	else
		d2=invert_number2(d2);
	printf("%f.\n",d2);
	d2=(d2+d1)/2;
	printf("Среднее арифметическое инвертированных чисел: %lf\n",d2);
	if (ch=='1')
		return invert_number(d2);
	else
		return invert_number2(d2);
}
int main(void)
{
	double n1=123000.456798;//998742.30124;//123.45679;
	double n2=998742.306124;
	printf("Среднее гармоническое значение %lf и %f равно %lf\n"
	"=================================================\nВторой вариант: \n",n1,n2,harmonic_mean('1',n1,n2));
	printf("Среднее гармоническое значение %lf и %f равно %lf\n",n1,n2,harmonic_mean('2',n1,n2));
	//printf("Инверсия числа %lf: %lf\n",n2,invert_number2(n2));

	return 0;
}