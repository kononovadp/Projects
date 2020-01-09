/*Напишите программу, которая предлагает пользователю ввести день, месяц и год. Месяц может быть представлен порядковым номером, названием или аббревиатурой. Затем программа должна возвратить общее количество дней, истекших с начала года по указанный день включительно. Учитываайте высокосные годы.*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
union month_information
{
	int number;
	char name[20];
	char abbreviation[4];
};
struct month
{
	int days_count;
	union month_information data;
};
void show_struct(struct month *months,int choise)
{
	int i;
	if(choise==1)
		for(i=0; i<12; i++)
			printf("Month number: %d; days count: %d;\n",
			months[i].data.number,months[i].days_count);
	else
		if(choise==2)
			for(i=0; i<12; i++)
			printf("Month name: %s; days count: %d;\n",
			months[i].data.name,months[i].days_count);
		else
			if(choise==3)
				for(i=0; i<12; i++)
					printf("Month abbreviation: %s; days count: %d;\n",
					months[i].data.abbreviation,months[i].days_count);	
}
int get_month_inf(struct month *year, char *name)
{
	if(strlen(name)==0)
		return 0;
	if(strlen(name)<=2)
	{
		if(strlen(name)==1)
			if(!(isdigit(name[0])))
				return 0;
		if(strlen(name)==2)
			if((!(isdigit(name[0]))) || (!(isdigit(name[1]))))
				return 0;
		int number=atoi(name);
		if((number<1) || (number)>12)
			return 0;
		for (int i=1; i<13; i++)
			year[i-1].data.number=i;
		return 1;
	}
	char *temp_str=(char*)malloc(sizeof(char)*10);
	FILE *f=fopen("year.txt","r");
	bool right_month_data=false;
	if(strlen(name)==3)
	{
		for(int i=0; i<12; i++)
		{
			fscanf(f,"%s",temp_str);
			fscanf(f,"%s",year[i].data.abbreviation);
			if((strcmp(year[i].data.abbreviation,name))==0)
				right_month_data=true;
			fscanf(f,"%s",temp_str);
		}
		if(right_month_data==false)
			return 0;
		else
			return 3;
	}
	else
	{
		for(int i=0; i<12; i++)
		{			
			fscanf(f,"%s",year[i].data.name);
			if((strcmp(year[i].data.name,name))==0)
				right_month_data=true;
			fscanf(f,"%s",temp_str);
			fscanf(f,"%s",temp_str);
		}
		if(right_month_data==false)
			return 0;
		else
			return 2;
	}		
	fclose(f);
}
bool check_number_data(char *number)
{
	for(int i=0; i<strlen(number); i++)
		if(!(isdigit(number[i])))
			return false;
	return true;
}
int get_days_count(struct month *year, int choise, int day, char *month)
{
	int i;
	int res=0;
	if(choise==1)
	{
		int month_int=atoi(month);
		for(i=0; i<month_int-1; i++)
			res+=year[i].days_count;		
	}
	else
		if(choise==2)
		{
			i=0;
			while((strcmp(month,year[i].data.name))!=0)
			{
				res+=year[i].days_count;
				i++;
			}
		}
		else
			if(choise==3)
			{
				i=0;
				while((strcmp(month,year[i].data.abbreviation))!=0)
				{
					res+=year[i].days_count;
					i++;
				}
			}	
	res+=day;
	return res;
}
int main(void)
{
	int i;
	struct month year[12];
	int choise,days_count=0;
	char *my_day=(char*)malloc(sizeof(char)*10);
	char *my_month=(char*)malloc(sizeof(char)*10);
	char *my_year=(char*)malloc(sizeof(char)*10);
	FILE *f=fopen("year.txt","r");
	for(i=0; i<12; i++)
	{
		fscanf(f,"%s",my_month);
		fscanf(f,"%s",my_month);
		fscanf(f,"%s",my_month);
		year[i].days_count=atoi(my_month);
	}
	fclose(f);
	printf("Year: ");
	gets(my_year);
	if(check_number_data(my_year)==false)
	{
		printf("Incorrect year data.");
		return 0;
	}
	if((atoi(my_year))%4==0)
		year[1].days_count=29;
	printf("Month (name, number or abbreviation): ");
	gets(my_month);
	choise=get_month_inf(year,my_month);	
	if(choise==0)
	{
		printf("Incorrect month data.");
		return 0;
	}
	printf("Day: ");
	gets(my_day);
	if((check_number_data(my_day)==false) || (atoi(my_day)<1))
	{
		printf("Incorrect day data.");
		return 0;
	}
	if(choise==1)
	{
		if(atoi(my_day)>year[atoi(my_month)-1].days_count)
		{
			printf("Too big day number.");
			return 0;
		}
	}
	else
		if(choise==2)
		{
			i=0;
			while((strcmp(year[i].data.name,my_month))!=0)
				i++;
			if(atoi(my_day)>year[i].days_count)
			{
				printf("Too big day number.");
				return 0;
			}
		}
		else
			if(choise==3)
			{
				i=0;
				while((strcmp(year[i].data.abbreviation,my_month))!=0)
					i++;				
				if(atoi(my_day)>year[i].days_count)
				{
					printf("Too big day number.");
					return 0;
				}
			}
	show_struct(year,choise);
	printf("Days count: %d",
	get_days_count(year,choise,atoi(my_day),my_month));
    return 0;
}