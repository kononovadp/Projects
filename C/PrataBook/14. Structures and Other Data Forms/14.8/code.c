/*Самолетный парк авиакомпании Colossus Airlines включает один самолет с количеством мест 12. Он выполняет один рейс ежедневно. Напишите программу бронирования авиабилетов со следующими характеристиками:
а. Программа использует массив из 12 структур. Каждая структура содержит идентификационный номер места, специальный маркер, который показывает, забронировано ли место, а также фамилию и имя пассажира, занявшего место;
б. Программа отображает следующее меню:
Для выбора функции введите ее буквенную метку:
а) показать количество свободных мест;
b) показать список свободных мест;
c) показать список забронированных мест в алфавитном порядке;
d) забронировать место для пассажира;
e) снять броню с места;
f) выйти из программы.
в. Программа выполняет действия, соответствующие пунктам менюю Позиции d и e требуют ввода дополнительных данных, и каждая из них должна позволять приреывать ввод.
г. По завершении выполнения отдельной функции программа отображает меню снова; исключением является позиция f.
д. Между запусками программы данные сохраняются в файле. При очередном запуске программа сначала загружает данные из файла, если они есть.*/
#include<io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXIMUM_SEATS_COUNT 12
struct ticket
{
	int seat_number;
	bool booked_seat;
	char name[20];
	char surname[20];
};
void write_inf_to_file(struct ticket *tickets)
{
	FILE *f=fopen("tickets.dat", "wb");
	size_t size = sizeof(struct ticket);
	for(int i=0; i<MAXIMUM_SEATS_COUNT; i++)
		fwrite(&tickets[i],size,1,f);
	fclose(f);
}
void show_booked_seats_count(struct ticket *tickets)
{
	int free_seats_count=0;
	for(int i=0; i<MAXIMUM_SEATS_COUNT; i++)
		if(tickets[i].booked_seat==true)
			free_seats_count++;
	printf("Количество свободных мест: %d\n",free_seats_count);
}
void show_free_seats_count(struct ticket *tickets)
{
	int free_seats_count=0;
	for(int i=0; i<MAXIMUM_SEATS_COUNT; i++)
		if(tickets[i].booked_seat==false)
			free_seats_count++;
	printf("Количество свободных мест: %d\n",free_seats_count);
}
void show_free_seats_list(struct ticket *tickets)
{
	int free_seats_count=0;
	printf("Список свободных мест:\n");
	for(int i=0; i<MAXIMUM_SEATS_COUNT; i++)
		if(tickets[i].booked_seat==false)
			printf("Место %d\n",tickets[i].seat_number);
}
void book_seat(struct ticket *tickets)
{
	int seat_number;
	printf("Номер места: ");
	scanf("%d",&seat_number);
	while((seat_number<1) || (seat_number>12) || (tickets[seat_number-1].booked_seat!=false))
	{
		if(tickets[seat_number-1].booked_seat==true)
			printf("Это место уже забронировано. ");
		else
			printf("В самолете всего 12 мест. ");
		printf("Новый номер места: ");
		scanf("%d",&seat_number);
	}
	tickets[seat_number-1].booked_seat=true;
	printf("Имя пассажира ");
	scanf("%s",&tickets[seat_number-1].name);
	printf("Фамилия пассажира ");
	scanf("%s",&tickets[seat_number-1].surname);
	write_inf_to_file(tickets);
}
void free_seat(struct ticket *tickets)
{
	int seat_number;
	printf("Номер места: ");
	scanf("%d",&seat_number);
	while(seat_number<1 && seat_number>12)
	{
		printf("В самолете всего 12 мест. Новый номер места: ");
		scanf("%d",&seat_number);
	}
	tickets[seat_number-1].booked_seat=false;
	strcpy(tickets[seat_number-1].name,"\0");
	strcpy(tickets[seat_number-1].surname,"\0");
	write_inf_to_file(tickets);
}
void show_booked_seats(struct ticket *tickets)
{
	struct ticket temp,sorted_tickets[MAXIMUM_SEATS_COUNT];
	bool b;
	int i,j,k,min_length,booked_seats_count=0;
	char ch;
	
	for(i=0; i<MAXIMUM_SEATS_COUNT; i++)
		if(tickets[i].booked_seat==true)
		{
			sorted_tickets[booked_seats_count]=tickets[i];			
			booked_seats_count++;
		}
	printf("%d|Исходный список забронированных мест:\n",booked_seats_count);
	for(i=0; i<booked_seats_count; i++)
		printf("Место %d; имя: %s; фамилия: %s\n",sorted_tickets[i].seat_number,
		sorted_tickets[i].name,sorted_tickets[i].surname);
	b=false;
	while(b==false)
	{
		b=true;
		for(i=0; i<booked_seats_count; i++)		
			for(j=i; j<booked_seats_count; j++)
			{
				if(strlen(sorted_tickets[i].name)<strlen(sorted_tickets[j].name))
					min_length=strlen(sorted_tickets[i].name);
				else
					min_length=strlen(sorted_tickets[j].name);
				for(k=0; k<min_length; k++)
					if(sorted_tickets[j].name[k]<sorted_tickets[i].name[k])
					{
						temp=sorted_tickets[j];
						sorted_tickets[j]=sorted_tickets[i];
						sorted_tickets[i]=temp;
						b=false;
						break;
					}
					else
						if(sorted_tickets[j].name[k]>sorted_tickets[i].name[k])
							break;
			}
	}
	printf("Список отсортирован по именам:\n");
	for(i=0; i<booked_seats_count; i++)
		printf("Место %d; имя: %s; фамилия: %s\n",sorted_tickets[i].seat_number,
		sorted_tickets[i].name,sorted_tickets[i].surname);
}
int main(void)
{
    int i,count=0;
	struct ticket tickets[MAXIMUM_SEATS_COUNT];
	size_t size = sizeof(struct ticket);
	char ch;
	FILE *f;
	if ((f=fopen("tickets.dat", "rb")) == NULL)
	{
		f=fopen("tickets.dat", "wb");
		for(i=0; i<MAXIMUM_SEATS_COUNT; i++)
		{
			tickets[i].seat_number=i+1;
			tickets[i].booked_seat=false;
			fwrite(&tickets[i],size,1,f);
		}
		fclose(f);
	}
	f=fopen("tickets.dat", "rb");
	rewind(f);
	while(fread(&tickets[count],size,1,f)==1)
		count++;
	fclose(f);
	printf(
	"1) показать количество свободных мест; 2) показать список свободных мест;\n"
	"3) показать список забронированных мест в алфавитном порядке;\n"
	"4) забронировать место для пассажира; 5) снять броню с места;\n"
	"6) выйти из программы. Для выбора функции введите ее числовую метку: ");
	ch=_getche();
	while(ch!='6')
	{		
		putchar('\n');
		switch(ch)
		{			
			case '1': show_free_seats_count(tickets); break;
			case '2': show_free_seats_list(tickets); break;
			case '3': show_booked_seats(tickets); break;
			case '4': book_seat(tickets); break;	
			case '5': free_seat(tickets); break;
			case '6': break;
			default: printf("Выберите корректное действие\n"); break;
		}
		if (ch!='\n')
			printf("*******************************************************************************\n"
			"1) показать количество свободных мест; 2) показать список свободных мест;\n"
			"3) показать список забронированных мест в алфавитном порядке;\n"
			"4) забронировать место для пассажира; 5) снять броню с места;\n"
			"6) выйти из программы. Для выбора функции введите ее числовую метку: ");	
		ch=_getche();
	}
    return 0;
}