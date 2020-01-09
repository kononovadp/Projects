/*Перепишите программу из листинга 12.4 так, чтобы в ней не использовались глобальные переменные.*/
/* global.c  -- использование внешней переменной */
#include <stdio.h>
//int units = 0;         /* внешняя переменная */
int critic(void);
int main(void)
{
    int units;  /* необязательное повторное объявление */
    printf("Сколько фунтов весит маленький бочонок масла?\n");
    scanf("%d", &units);
    while (units != 56)
        units=critic();
    printf("Вы знали это!\n");
    return 0;
}
int critic(void)
{
    int units;/* необязательное повторное объявление опущено */
    printf("Вам не повезло. Попробуйте еще раз.\n");
    scanf("%d", &units);
	return units;
}
