/*Напишите программу, которая создает шаблон структуры с двумя членами в соответствии со следующими критериями:
а. Первым членом является номер карточки социального страхования. Второй член - это структура, состоящая из трех членов. Ее первый член содержит имя, второй член - отчество и третий член - фамилию. Создайте и инициализируйте массив из пяти таких структур. Программа должна выводить данные в следующем формате:
Dribble, Flossie M. -- 302039823
Выводиться должна только начальная буква отчества, за которой следует точка. Разумеется, если этот член пуст, не должен выводиться ни инициал, ни точка. Напишите функцию, которая выполняет такой вывод, передайте рассматриваемую структуру этой функции.
б. Модифицируйте часть а) так, чтобы вместо адреса передавалась сама структура.*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
struct insured
{
	char name[20];
	char patronymic[20];
	char surname[20];
};	
struct insurance
{
	long long int insurance_card;
	struct insured person;
};
void show_struct_pointer(struct insurance *mystruct)
{
	printf("%s, %s ",mystruct->person.surname,mystruct->person.name);
	if(strlen(mystruct->person.patronymic)>0)
		printf("%c.",mystruct->person.patronymic[0]);
	printf(" -- %lld\n",mystruct->insurance_card);
}
void show_struct(struct insurance mystruct)
{
	printf("%s, %s ",mystruct.person.surname,mystruct.person.name);
	if(strlen(mystruct.person.patronymic)>0)
		printf("%c.",mystruct.person.patronymic[0]);
	printf(" -- %lld\n",mystruct.insurance_card);
}
int main(void)
{
    struct insurance insured_persons[5];
	strcpy(insured_persons[0].person.surname,"Dribble");
	strcpy(insured_persons[0].person.name,"Flossie");	
	strcpy(insured_persons[0].person.patronymic,"Matt");
	insured_persons[0].insurance_card=302039823;	
	strcpy(insured_persons[1].person.surname,"Kononov");
	strcpy(insured_persons[1].person.name,"Maxim");	
	strcpy(insured_persons[1].person.patronymic,"Anatolievitch");
	insured_persons[1].insurance_card=3020398;	
	strcpy(insured_persons[2].person.surname,"Kokareva");
	strcpy(insured_persons[2].person.name,"Ludmila");	
	strcpy(insured_persons[2].person.patronymic,"Ivanovna");
	insured_persons[2].insurance_card=30203823;	
	strcpy(insured_persons[3].person.surname,"Ivanov");
	strcpy(insured_persons[3].person.name,"Alexander");	
	strcpy(insured_persons[3].person.patronymic,"");
	insured_persons[3].insurance_card=3039823;	
	strcpy(insured_persons[4].person.surname,"Petrov");
	strcpy(insured_persons[4].person.name,"Vasiliy");	
	strcpy(insured_persons[4].person.patronymic,"Alexandrovych");
	insured_persons[4].insurance_card=3020393;
	for(int i=0; i<5; i++)
		show_struct_pointer(&insured_persons[i]);
	printf("--------------------------------\n");
	for(int i=0; i<5; i++)
		show_struct(insured_persons[i]);
    return 0;
}