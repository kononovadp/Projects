﻿/*Перепишите программу rain.c из листинга 10.7 так, чтобы основные задачи решались внутри функций, а не в теле main().*/
/* rain.c -- находит суммарные данные по годам, средние значения за год и средние
             значения за месяц по данным об осадках за несколько лет */
#include <stdio.h>
#define MONTHS 12   // количество месяцев в году
#define YEARS 5     // количество лет, для которых доступны данные
float year_precipitations(const float rain[YEARS][MONTHS])
{
	float subtot,total;
	int year, month;
	printf("ГОД    КОЛИЧЕСТВО ОСАДКОВ (в дюймах)\n");
    for (year = 0, total = 0; year < YEARS; year++)
    {   // для каждого года суммировать количество осадков за каждый месяц
        for (month = 0, subtot = 0; month < MONTHS; month++)
            subtot += rain[year][month];
        printf("%5d %15.1f\n", 2010 + year, subtot);
        total += subtot; // общая сумма для всех лет
    }
	return total;
}
void month_precipitations(const float rain[YEARS][MONTHS])
{
	float subtot,total;
	int year, month;
	for (month = 0; month < MONTHS; month++)
    {   // для каждого месяца суммировать количество осадков на протяжении годов
        for (year = 0, subtot =0; year < YEARS; year++)
            subtot += rain[year][month];
        printf("%4.1f ", subtot/YEARS);
    }
}
	
int main(void)
{
    // инициализация данными об осадках за период с 2010 по 2014 гг.
    const float rain[YEARS][MONTHS] =
    {
        {4.3,4.3,4.3,3.0,2.0,1.2,0.2,0.2,0.4,2.4,3.5,6.6},
        {8.5,8.2,1.2,1.6,2.4,0.0,5.2,0.9,0.3,0.9,1.4,7.3},
        {9.1,8.5,6.7,4.3,2.1,0.8,0.2,0.2,1.1,2.3,6.1,8.4},
        {7.2,9.9,8.4,3.3,1.2,0.8,0.4,0.0,0.6,1.7,4.3,6.2},
        {7.6,5.6,3.8,2.8,3.8,0.2,0.0,0.0,0.0,1.3,2.6,5.2}
    };    
    printf("\nСреднегодовое количество осадков составляет %.1f дюймов.\n\n",
            year_precipitations(rain)/YEARS);
    printf("СРЕДНЕМЕСЯЧНОЕ КОЛИЧЕСТВО ОСАДКОВ:\n\n");
    printf(" Янв  Фев  Мар  Апр  Май  Июн  Июл  Авг  Сен  Окт");
    printf("  Ноя  Дек\n");
	month_precipitations(rain);
    return 0;
}