/*3.: Разработайте шаблон структуры, которая будет содержать название месяца, его трехбуквенную аббревиатуру, количество дней в месяце и его номер.
5.: Напишите функцию, которая после получения номера месяца возвращает общее количество дней с начала года до конца указанного месяца. Предположите, что шаблон структуры, описанный в вопросе 3, и подходящий массив таких структур объявлены внешне.
Переделайте задание из вопроса 5 таким образом, чтобы аргумент был представлен названием месяца, а не его номером. (Не забывайте о функции strcmp().) Протестируйте готовую функцию в простой программе.*/
#include <stdio.h>
#include <string.h>
struct year
{
	char month[20];
	char abbreviation[4];
	int days_count;
	int number;
};
void show_struct(struct year *year2018)
{
	for (int i=0; i<12; i++)
		printf("Month: %s; abbreviation: %s; days count: %d;\n",
	year2018[i].month,year2018[i].abbreviation,year2018[i].days_count);
}
int get_days_count(char *month_name,struct year *year2018)
{
	int i=1;
	int days_count=0;
	while((i<13) && (strcmp(month_name,year2018[i-1].month)!=0))
		i++;
	if((i==13) && (strcmp(month_name,year2018[i].month)!=0))
		return 0;
	else
		for(; i>0; i--)
			days_count+=year2018[i-1].days_count;
	return days_count;
}
int main(void)
{
	struct year year2018[12];
	int i,days_count=0;
	FILE *f=fopen("year2018.txt","r");
	char *str_days_count=(char*)malloc(sizeof(char)*20);
	for (i=1; i<13; i++)
		year2018[i-1].number=i;	
	for(i=0; i<12; i++)
	{
		fscanf(f,"%s",year2018[i].month);
		fscanf(f,"%s",year2018[i].abbreviation);
		fscanf(f,"%s",str_days_count);
		year2018[i].days_count=atoi(str_days_count);
	}
	show_struct(year2018);
	printf("Month name: ");
	scanf("%s",str_days_count);
	days_count=get_days_count(str_days_count,year2018);
	if(days_count)
		printf("Days count is %d",days_count);
	else
		printf("Incorrect month name.");
	fclose(f);
    return 0;
}