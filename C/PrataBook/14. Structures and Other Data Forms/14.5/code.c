/*Напишите программу, которая соответствует следующим требованиям:
а) программа внешне определяет шаблон структуры name с двумя членами: строкой для хранения имени и строкой для хранения фамилии;
б) программа внешне определяет шаблон структуры student с тремя членами: структурой name, массивом grade для хранения трех оценок в виде числа с плавающей запятой и переменной для хранения среднего значения этих трех оценок;
в) программа содержит функцию main(), где объявляется массив из CSIZE (с CSIZE=4) структур student, в которых инициализируются члены name именами по вашему выбору. Для выполнения задач, описанных в частях г), д), е) и ж), используйте функции;
г) программа интерактивнно вводит оценки для каждого студента, запрашивая у пользователя ввод имени студента и его оценок. Поместите оценки в массив grade соответствующей структуры. Требуемый цикл можно реализовать в main() или в специальной функции по вашему усмотрению;
д) программа вычисляет среднюю оценку для каждой структуры и присваивает ее соответствующему члену;
е) программа выводит информацию из каждой структуры;
ж) программа выводит среднее значение по курсу для каждого числового члена структуры.*/
#include <stdio.h>
struct name
{
	char name[20];
	char last_name[20];
};
struct student
{
	struct name full_name;
	float grade[3];
	float average_grade;
};
void add_grades(struct student *CSIZE)
{
	int i,j;
	for(i=0; i<4; i++)
	{
		printf("Enter 3 grades of the student %s %s\n",CSIZE[i].full_name.name,
		CSIZE[i].full_name.last_name);
		for(j=0; j<3; j++)
		{
			printf("Grade %d: ",j+1);
			scanf("%f",&CSIZE[i].grade[j]);
		}
	}
}
void calk_average_grade(struct student *CSIZE)
{
	float average;
	int i,j;
	for(i=0; i<4; i++)
	{
		for(j=0; j<3; j++)
			average+=CSIZE[i].grade[j];
		CSIZE[i].average_grade=average/3;
		average=0;
	}
}
void show_struct(struct student *CSIZE)
{
	int i,j;
	for(i=0; i<4; i++)
	{
		printf("Grades of the strudent %s %s: ",CSIZE[i].full_name.name,
		CSIZE[i].full_name.last_name);
		for(j=0; j<2; j++)
			printf("%f, ",CSIZE[i].grade[j]);
		printf("%f;\n",CSIZE[i].grade[j]);
		printf("Average grade: %f\n-------------------\n",CSIZE[i].average_grade);
		
	}
}
void total_average(struct student *CSIZE)
{
	float average=0;
	for(int i=0; i<4; i++)
		average+=CSIZE[i].average_grade;
	printf("Average grade of all students: %f",average/4);
}
int main(void)
{
    struct student CSIZE[4];
	int i,j;
	strcpy(CSIZE[0].full_name.name,"Ivan");
	strcpy(CSIZE[0].full_name.last_name,"Ivanov");
	strcpy(CSIZE[1].full_name.name,"Petr");
	strcpy(CSIZE[1].full_name.last_name,"Petrov");
	strcpy(CSIZE[2].full_name.name,"Fedor");
	strcpy(CSIZE[2].full_name.last_name,"Fedorov");
	strcpy(CSIZE[3].full_name.name,"My name");
	strcpy(CSIZE[3].full_name.last_name,"My last name");
	add_grades(CSIZE);
	calk_average_grade(CSIZE);
	show_struct(CSIZE);
	total_average(CSIZE);
    return 0;
}