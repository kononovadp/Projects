/*Среднее гармоническое значение двух чисел получается путем инвертирования этих чисел, вычисления среднего значения инверсий и получении инверсии результата. Напишите функцию, которая принимает два аргумента double и возвращает среднее гармоническое значение этих двух чисел.*/
#include <stdio.h>
double get_fract_part(double n)
{
	double t=1;
	while(t*10<n)
		t*=10;
	while(n>t)
		n-=t;
	while(n>1)
		n--;
	if(n>=1)
		n-=1.0;
	return n;
}
int invert_int(int n)
{
	int temp, res;
	temp=1;
	while((temp*=10)<n/10);
	res=0;
	while(n>0)
	{
		res+=(n%10)*temp;
		temp/=10;
		n/=10;
	}
	return res;		
}
double invert_double(double n,int precision)
{
	double fract_part=(double)((int)invert_int(n));
	double int_part=1;
	while(fract_part>1)
		fract_part/=10;
	n=get_fract_part(n);
	while(precision>0)
	{
		n*=10;
		precision--;
	}
	n-=get_fract_part(n);
	n=(double)((int)invert_int(n));
	n-=get_fract_part(n);
	return n+fract_part;
}
double harmonic_mean(double d1, double d2, int precision)
{
	printf("Инверсия числа %.7lf: ",d1);
	d1=invert_double(d1,precision);
	printf("%.7lf;\nИнверсия числа %.7lf: ",d1,d2);
	d2=invert_double(d2,precision);
	printf("%.7lf.\n",d2);
	d2=(d2+d1)/2;
	printf("Среднее арифметическое инвертированных чисел: %.7lf\n",d2);
	return invert_double(d2,precision);
}
int main(void)
{
	int precision=7;
	double n1=9876512.9876543;
	double n2=23423.3425568;
	printf("Source number: %.7lf\n",n1);
	printf("Среднее гармоническое значение: %.7lf\n",
	harmonic_mean(n1,n2,precision));
	return 0;
}