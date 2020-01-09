/*Гармоничное среднее двух чисел получается путем вычисления среднего от инверсий этих чисел с последующим инвертированием результата. Воспользуйтесь директивой #define для определения функционального макроса, который выполняет эту операцию. Напишите простую программу для тестирования этого макроса.*/
#include <stdio.h>
#include "invert_functions.h"
#define harmonic_mean(d1, d2, precision, func)\
	d1=func(d1,precision);\
	d2=func(d2,precision);\
	d2=(d2+d1)/2;\
	printf("Среднее арифметическое инвертированных чисел: %lf\n",d2);\
	printf("Среднее гармоническое значение: %lf\n",func(d2,precision));
int main(void)
{
	int precision=6;
	double n1=31.987654;
	double n2=23423.3425568;
	harmonic_mean(n1,n2,precision,invert_bits_of_double);
	printf("====================================================================\n");
	harmonic_mean(n1,n2,precision,invert_double);
    return 0;
}