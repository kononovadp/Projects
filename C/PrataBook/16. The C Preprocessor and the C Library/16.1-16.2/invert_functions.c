#include "D:\Projects\C\my_library\user_functions.h"
double get_fract_part(double n)
{
	return n-(int)n;
	/*double t=1;
	while(t*10<n)
		t*=10;
	while(n>t)
		n-=t;
	while(n>1)
		n--;
	if(n>=1)
		n-=1.0;
	return n;*/
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
	printf("Исходное число: %lf; точность: %d\n",n,precision);
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
	n+=fract_part;
	printf("Инвертированное число: %lf\n",n);
	return n;
}
unsigned int get_bits_count(unsigned int n)
{
	unsigned int bits_count=0;
	while(n>0)
	{
		bits_count++;
		n>>=1;
	}
	return bits_count;
}
char *convert_to_binary(unsigned int n)
{
	char ch,*res=(char*)malloc(40*sizeof(char));
	unsigned int i=0;
	unsigned int bits_count=get_bits_count(n);
	if(bits_count==0)
		return "0";
	while(bits_count>0)
	{
		res[i]=(char)'0'+((n>>bits_count-1)&1);		
		bits_count--;
		i++;
	}
	return res;
}
unsigned int invert_bits_of_int(unsigned int n)
{
	printf("%u = %s; кол-во бит: %u\n",
	n,convert_to_binary((unsigned int)n),get_bits_count((unsigned int)n));
	unsigned int bits_count,int_part=(unsigned int)n;
	bits_count=get_bits_count(n);
	n=~n;
	n<<=get_bits_count(n)-bits_count-1;
	n>>=get_bits_count(n)-bits_count-1;
	printf("%u = %s; кол-во бит: %u\n",
	n,convert_to_binary((unsigned int)n),get_bits_count((unsigned int)n));
	return n;
}
double invert_bits_of_double(double n, int precision)
{
	printf("Исходное число: %lf; точность: %d\nЦелая часть:\n",n,precision);
	unsigned int fract_part, int_part=invert_bits_of_int((unsigned int)n);
	n-=(int)n;
	while(precision-- >0)
		n*=10;
	printf("Дробная часть:\n");
	fract_part=invert_bits_of_int((unsigned int)n);
	n=(double)fract_part;
	while(n>1)
		n/=10;
	n+=int_part;
	printf("Инвертированное число: %lf\n-------------------------------------\n",n);
	return n;
}
