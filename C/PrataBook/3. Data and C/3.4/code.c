﻿/* Напишите программу, которая считывает число с плавающей запятой и выводит его сначала в десятичном представлении, потом в экспоненциальном представлении и затем в двоично-экспоненциальном представлении, если система его поддерживает. Вывод должен быть представлен в следующем формате(фактическое количество отображаемых цифр показателя степени зависит от системы):
Введите значение с плавающей запятой: 64.25
Запись с фиксированной запятой: 64.250000
Экспоненциальная форма записи: 6.425000е+01
Двоично-экспоненциальное представление: 0*1.01p+6*/
#include <stdio.h>
int main(void)
{
    float d;
	printf("Введите значение с плавающей запятой: ");
	scanf("%e",&d);
	printf("Запись с фиксированной запятой: %f\nЭкспоненциальная форма записи: %e\nДвоично-экспоненциальное представление: %a",d,d,d);
	getchar();
	getchar();
}