/*Авиакомпания Colossus Airlines (из упражнения 8) приобрела второй самолет (с тем же количеством мест) и расширила обслуживание до четырех рейсов ежедневно (рейсы с номерами 102, 311, 444 и 519). Модифицируйте программу для обработки четырех рейсов. Она должна предлагать меню верхнего уровня, которое позволяет выбирать интересующий рейс и выходить из программы. После выбора рейса должно отобразиться меню, подобное показанному в упражнении 8. Однако в него должен быть добавлен новый элемент - подтверждение брони места. Кроме того, вариант выхода из программы потребуется заменить вариантом возвращения в меню верхнего уровня. При каждом отображении должен указываться номер рейса, обрабатываемого в текущий момент. Вдобавок при отображении брони мест должно выводиться состояние подтверждения.*/
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
	bool confirmation_status;
	char name[20];
	char surname[20];
};
void write_inf_to_file(struct ticket *tickets, char *filename)
{
	FILE *f=fopen(filename, "wb");
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
	printf("Список свободных мест:\n");
	for(int i=0; i<MAXIMUM_SEATS_COUNT; i++)
		if(tickets[i].booked_seat==false)
			printf("Место %d\n",tickets[i].seat_number);
}
void book_seat(struct ticket *tickets, char *filename)
{
	int seat_number;
	char name[20],surname[20];
	bool b=true;
	while(b==true)
	{
		printf("Номер места (введите 0 для прерывания ввода): ");
		scanf("%d",&seat_number);
		while((seat_number<0) || (seat_number>12) || (tickets[seat_number-1].booked_seat!=false))
		{
			if(seat_number==0)
				break;
			if(tickets[seat_number-1].booked_seat==true)
				printf("Это место уже забронировано. ");
			else
				printf("В самолете всего 12 мест. ");
			printf("Новый номер места (0 - прерывание ввода): ");
			scanf("%d",&seat_number);
		}
		if(seat_number>0)
		{
			printf("Имя пассажира (пустая строка для отмены): ");
			getchar();
			gets(tickets[seat_number-1].name);
			if(strlen(tickets[seat_number-1].name)>0)
			{
				printf("Фамилия пассажира (пустая строка для отмены): ");
				gets(tickets[seat_number-1].surname);
			}
			else
				b=false;
			if(strlen(tickets[seat_number-1].surname)>0)
			{
				tickets[seat_number-1].booked_seat=true;
				write_inf_to_file(tickets,filename);
			}
			else
				b=false;
		}
		else b=false;
	}
}
void free_seat(struct ticket *tickets, char *filename)
{
	int seat_number;
	printf("Номер места (введите 0 для прерывания ввода): ");
	scanf("%d",&seat_number);
	while(seat_number<0 && seat_number>12)
	{
		if(seat_number==0)
			break;
		printf("В самолете всего 12 мест. Новый номер места: ");
		scanf("%d",&seat_number);
	}
	if(seat_number>0)
	{
		tickets[seat_number-1].booked_seat=false;
		strcpy(tickets[seat_number-1].name,"\0");
		strcpy(tickets[seat_number-1].surname,"\0");
		write_inf_to_file(tickets,filename);
	}
}
void confirm_flight_reservation(struct ticket *tickets, char *filename)
{
	int seat_number;
	printf("Номер места (введите 0 для прерывания ввода): ");
	scanf("%d",&seat_number);
	while((seat_number<0) || (seat_number>12) || (tickets[seat_number-1].booked_seat==false))
	{
		if(seat_number==0)
			break;
		if(tickets[seat_number-1].booked_seat==false)
			printf("Перед подтверждением это место нужно забронировать. ");
		else
			printf("В самолете всего 12 мест. ");
		printf("Новый номер места: ");
		scanf("%d",&seat_number);
	}
	tickets[seat_number-1].confirmation_status=true;
	write_inf_to_file(tickets,filename);
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
	{
		printf("Место %d; имя: %s; фамилия: %s; броня подтвержена: ",
		sorted_tickets[i].seat_number,sorted_tickets[i].name,sorted_tickets[i].surname);
		if(sorted_tickets[i].confirmation_status==true)
			printf("да\n");
		else
			printf("нет\n");
	}
}
void menu(int flight_number)
{
	int i,count=0;
	struct ticket tickets[MAXIMUM_SEATS_COUNT];
	size_t size = sizeof(struct ticket);
	char ch,filename[15],temp[15];
	FILE *f;
	strcpy(filename,"flight_");
	_itoa(flight_number,temp,10);
	strcat(filename,temp);
	strcat(filename,".dat");
	if ((f=fopen(filename, "rb")) == NULL)
	{
		f=fopen(filename, "wb");
		for(i=0; i<MAXIMUM_SEATS_COUNT; i++)
		{
			tickets[i].seat_number=i+1;
			tickets[i].booked_seat=false;
			tickets[i].confirmation_status=false;
			fwrite(&tickets[i],size,1,f);
		}
		fclose(f);
	}
	f=fopen(filename, "rb");
	rewind(f);
	while(fread(&tickets[count],size,1,f)==1)
		count++;
	fclose(f);
	printf("Обработка рейса %d\n"
	"1) показать количество свободных мест; 2) показать список свободных мест;\n"
	"3) показать список забронированных мест в алфавитном порядке;\n"
	"4) забронировать место для пассажира; 5) снять броню с места;\n"
	"6) подтвердить броню места; 7) вернуться в меню выбора рейса.\n"
	"Для выбора функции введите ее числовую метку: ",flight_number);
	ch=_getche();
	while(ch!='7')
	{		
		putchar('\n');
		switch(ch)
		{			
			case '1': show_free_seats_count(tickets); break;
			case '2': show_free_seats_list(tickets); break;
			case '3': show_booked_seats(tickets); break;
			case '4': book_seat(tickets,filename); break;	
			case '5': free_seat(tickets,filename); break;
			case '6': confirm_flight_reservation(tickets,filename); break;
			default: printf("Выберите корректное действие\n"); break;
		}
		if (ch!='\n')
			printf("*******************************************************************************\n"
			"1) показать количество свободных мест; 2) показать список свободных мест;\n"
			"3) показать список забронированных мест в алфавитном порядке;\n"
			"4) забронировать место для пассажира; 5) снять броню с места;\n"
			"6) подтвердить броню места; 7) вернуться в меню выбора рейса.\n"
			"Для выбора функции введите ее числовую метку: ");	
		ch=_getche();
	}
}
int main(void)
{
	printf("1) 102; 2) 311; 3) 444; 4) 519.\nНомер рейса или цифра 5 для выхода из программы: ");
	char ch=_getche();
	while(ch!='5')
	{		
		putchar('\n');
		switch(ch)
		{
			case '1': menu(102); break;
			case '2': menu(311); break;
			case '3': menu(444); break;
			case '4': menu(519); break;
			case '5': break;
			default: printf("Выберите корректное действие\n"); break;
		}
		if (ch!='\n')
			printf("\n*******************************************************************************\n1) 102; 2) 311; 3) 444; 4) 519.\n"
			"Номер рейса или 5 для выхода из программы: ");
		ch=_getche();
	}
    return 0;
}