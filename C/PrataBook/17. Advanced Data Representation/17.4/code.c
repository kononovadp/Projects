/*Перепишите программу mall.c (листинг 17.7), чтобы она моделировала киоск с двумя окошками и двумя очередями.*/
// mall.c -- использует интерфейс Queue
// компилировать вместе с queue.c
#include <stdio.h>
#include <stdlib.h>    // для rand() и srand()
#include <time.h>      // для time()
#include "queue.c"     // измените определение типа Item
#define MIN_PER_HR 60.0
// x - среднее время между прибытием клиентов в минутах
// возвращает true, если клиент появляется в течение данной минуты
bool newcustomer(double x)
{
    if (rand() * x / RAND_MAX < 1)
        return true;
    else
        return false;
}
// when - время прибытия клиента
// функция возвращает структуру Item со временем прибытия,
// установленным в when, и временем обслуживания, 
// установленным в случайное значение из диапазона от 1 до 3
Item customertime(long when)
{
    Item cust;

    cust.processtime = rand() % 3 + 1;
    cust.arrive = when;

    return cust;
}
int main(void)
{
    Queue line1;
    Queue line2;
    long total_turnaways = 0; // количество отказов из-за переполненных очередей
    int wait_time = 0;        // время до освобождения Зигмунда
    int hours;                // количество часов моделирования
	int perhour;              // среднее количество прибывающих клиентов в час
	long cycle, cyclelimit;   // счетчик и граничное значение цикла
	double min_per_cust;      // среднее время между прибытиями клиентов
    InitializeQueue(&line1);
	InitializeQueue(&line2);
    srand((unsigned int) time(0)); // случайная инициализация rand()
    puts("Учебный пример: консультационный киоск Зигмунда Ландера");
    puts("Введите длительность моделирования в часах:");
    scanf("%d", &hours);
    cyclelimit = MIN_PER_HR * hours;
    puts("Введите среднее количество клиентов, прибывающих за час:");
    scanf("%d", &perhour);
    min_per_cust = MIN_PER_HR / perhour;
    for (cycle = 0; cycle < cyclelimit; cycle++)
    {
        if (newcustomer(min_per_cust))
        {
            if (!QueueIsFull(&line1))
			{
				line1.customers++;
				line1.temp=customertime(cycle);
				EnQueue(line1.temp, &line1);
			}
			else
				if (!QueueIsFull(&line2))
				{
					line1.turnaways++;
					line2.customers++;
					line2.temp=customertime(cycle);					
					EnQueue(line2.temp, &line2);
				}
				else
					line2.turnaways++;
        }
		if (wait_time <= 0 && !QueueIsEmpty(&line1))
        {
            DeQueue (&line1.temp, &line1);
            wait_time = line1.temp.processtime;
            line1.line_wait += cycle - line1.temp.arrive;
            line1.served++;
        }
		if (wait_time <= 0 && !QueueIsEmpty(&line2))
        {
            DeQueue (&line2.temp, &line2);
            wait_time = line2.temp.processtime;
            line2.line_wait += cycle - line2.temp.arrive;
            line2.served++;
        }
		if (wait_time > 0)
            wait_time--;
        line1.sum_line += QueueItemCount(&line1);
		line2.sum_line += QueueItemCount(&line2);	
    }
	if(line1.customers == 0 && line2.customers == 0)
	{
		puts("Клиенты отсутствуют!\nПрограмма завершена.");
		return 0;
	}
    if (line1.customers > 0)
    {
        printf("        Очередь 1:\n");
		printf("     принятых клиентов: %ld\n", line1.customers);
        printf("  обслуженных клиентов: %ld\n", line1.served);        
        printf(" средняя длина очереди: %.2f\n",
               (double) line1.sum_line / cyclelimit);
        printf("среднее время ожидания: %.2f мин\n",
               (double) line1.line_wait / line1.served);
		printf("Количество отказов в очереди: %ld\n", line1.turnaways);
    }
	if (line2.customers > 0)
    {
        printf("------------------------------------\n");
		printf("        Очередь 2:\n");
		printf("     принятых клиентов: %ld\n", line2.customers);
        printf("  обслуженных клиентов: %ld\n", line2.served);        
        printf(" средняя длина очереди: %.2f\n",
               (double) line2.sum_line / cyclelimit);
        printf("среднее время ожидания: %.2f мин\n",
               (double) line2.line_wait / line2.served);
		printf("Количество отказов в очереди: %ld\n", line2.turnaways);
    }
	printf("Количество отказов в обеих очередях: %ld\n", 
			line1.turnaways+line2.turnaways);
    EmptyTheQueue(&line1);
	EmptyTheQueue(&line2);
    puts("Программа завершена.");
    return 0;
}
