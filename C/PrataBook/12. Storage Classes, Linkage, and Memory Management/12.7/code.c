/*Напишите программу, которая ведет себя подобно модификации листинга 12.13, которая обсуждалась после представления вывода из программы, показанной в листинге 12.13 То есть программа должна давать вывод следующего вида:
Введите количество бросаний или q для завершения: 18
Сколько граней и сколько костей: 6 3
Имеем 18 бросаний 3 костей с 6 гранями.
12 10 6 9 8 14 8 15 9 14 12 17 11 7 10 13 8 14
Введите количество бросаний или q для завершения: q*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000
int roll_a_die(int sides)
{
	return rand()%sides+1;
}
void play_dise(int rolls,int dies,int sides)
{
	while(rolls-- > 0)
	{
		int total=0;
		for(int i=0; i<dies; i++)
			total+=roll_a_die(sides);
		printf("%d ",total);
	}	
}
int main(void)
{
    signed int rolls,dies,sides;
	printf("Введите количество бросаний или q для завершения: ");
	while(scanf("%d",&rolls)==1)
	{
		printf("Сколько граней и сколько костей: ");
		scanf("%d %d",&sides, &dies);
		printf("Имеем %d бросаний %d костей с %d гранями\n",rolls,dies,sides);
		play_dise(rolls,dies,sides);
		printf("\nВведите количество бросаний или q для завершения: ");		
	}
	
	return 0;
}
