/*Напишите функцию по имени transform(), которая принимает четыре аргумента: имя исходного массива, содержащего данные типа double, имя целевого массива типа double, значение int, представляющее количество элемнтов массива, и имя функции (или, что эквивалентно, указатель на функцию). Функция transform() должна применять указанную функцию к каждому элементу исходного массива и помещать возвращаемое ею значение в целевой массив. Например, вызов transform(source,target,100,sin); должен установить target[0] в sin(source[0]) и сделать то же самое для 100 элементов массива. Протестируйте функцию в программе, которая вызывает transform() четыре раза, используя в качестве аргументов две функции из библиотеки math.h и две подходящие функции, которые написаны вами специально для transform().*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double rand_double(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}
transform(double *source, double *target, int count, double (*function)(double))
{
	for(int i=0; i<count; i++)
	{
		target[i]=function(source[i]);
		printf("%lf = %lf\n",source[i],target[i]);
	}
}
double my_func1(double n)
{
	return n*n;
}
double my_func2(double n)
{
	return n+n;
}
int main(void)
{
	int i, count=10;
	double(*my_func)(double)=sin;
	double source[count],target[count];	
	srand(time(NULL));
	for(i=0; i<count; i++)
		source[i]=rand_double(10,99);
	printf("sin of %d random numbers:\n",count);
	transform(source,target,count,my_func);
	my_func=cos;
	printf("cos of %d random numbers:\n",count);
	transform(source,target,count,my_func);
	my_func=my_func1;
	printf("squares of %d random numbers:\n",count);
	transform(source,target,count,my_func);
	my_func=my_func2;
	printf("sum of %d random numbers:\n",count);
	transform(source,target,count,my_func);
    return 0;
}