/*Еще раз выполните упражнение 8, но на этот раз испольуйте рекурсивную функцию.*/
#include <stdio.h>
double power(double n, int p)
{	
	double pow=1;
	if ((n==0) && (p==0))
	{
		printf("ђезультат возведения числа 0 в степень 0 не определен,\n"
		"поэтому используется результат возведения 0 в степень 1.\n");
		return 0;
	}
	if (abs(p)>0)
		pow=n*power(n,abs(p)-1);
	if (p<0)
		pow=1/pow;
	return pow;
}
int main(void)
{
	double n=100;
	int p=-1;
	printf("%lf в степени %d = %lf",n,p,power(n,p));
	return 0;
}