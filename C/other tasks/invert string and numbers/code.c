#include <stdio.h>
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
double get_divide_rest_for_double(double n)
{
	double res=0;
	n-=get_fract_part(n);
	n/=10;
	return 10*(res+get_fract_part(n));
}
double cut_int_part_of_double(double n)
{
	double fract_part=get_fract_part(n);
	n-=fract_part;
	n/=10;
	n-=get_fract_part(n);
	return n+fract_part;
}
double invert_int_part_of_double(double *n)
{
	double temp, divide_rest, res=0;
	int i=0;
	temp=1;
	while(temp<*n/10)
	{
		temp*=10;		
		i++;
	}	
	for(; i>-1; i--)
	{
		divide_rest=get_divide_rest_for_double(*n);
		res=res+(temp*divide_rest);
		temp/=10;
		*n=cut_int_part_of_double(*n);
	}
	return res;
}
double invert_float(double n, int precision)
{
	double fract_part;
	fract_part=invert_int_part_of_double(&n);
	while(fract_part>1)
		fract_part/=10;
	while(precision-- >0)
		n*=10;
	n-=get_fract_part(n);
	return fract_part+invert_int_part_of_double(&n);
}
void invert_string(char *str)
{
	char t;
	for(int i=0; i<strlen(str)/2; i++)
	{
		t=str[strlen(str)-i-1];
		str[strlen(str)-i-1]=str[i];
		str[i]=t;
	}
}
int main(void)
{
	double n=987654.123456;//1237.95732;
	int int_n=453312;
	printf("Source integer number: %d\nInteger number inverted: %d\nSource float number: %lf\nFloat number inverted: %lf\n",int_n,invert_int(int_n),n,invert_float(n,6));
	char s[50]="2342dfgdrtert34534vdfg";
	printf("Source string: %s\n",s);
	invert_string(s);
	printf("String inverted: %s",s);
    return 0;
}