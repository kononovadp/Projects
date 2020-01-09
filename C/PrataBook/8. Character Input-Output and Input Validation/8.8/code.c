/*Напишите программу, которая выводит на экран меню, предполагающее выбрать сложение, вычитание, умножение или деление. После выбора программа должна запросить два числа и затем выполнить затребованную операцию. Программа должна принимать только варианты, предлагаемые в меню. Для чисел должен использоваться тип float и программа должна предоставлять пользователю возможность повторно вводить числа, если он ввел нечисловые данные. В случае деления программа должна предложить пользователю ввести другое значение, если он ввел для второго операнда значение 0. Выполнение такой программы должно иметь премерно такой вид:
Выберите желаемую операцию:
с. сложение		в. вычитание
у. умножение	д. деление
з. завершение
с
Введите первое число: 22.4
Введите второе число: один
один не является числом.
Введите число такое как 2.5, -1.78Е8 или 3: 1
22.4 + 1 = 23.4
Выберите желаемую операцию:
с. сложение		в. выитание
у. умножение	д. деление
з. завершение
д
Введите первое число: 18.4
Введите второе число: 0
Введите число, отличное от 0: 0.2
18.4 / 0.2 = 92
Выберите желаемую операцию:
с. сложение		в. выитание
у. умножение	д. деление
з. завершение
з
Программа завершена.*/
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
void menu();
int strtoint(char *s)
{
	int number=0;
	int i,ten=1;
	short sign_minus=0;
	if (s[0]=='-')
	{
		sign_minus=1;
		for (i=0; i<strlen(s)-1; i++)
			s[i]=s[i+1];
		s[strlen(s)-1]=0;
	}
	for(i=1; i<strlen(s); i++)
		ten*=10;
	for(i=0; i<strlen(s); i++)
	{
		number+=ten*(s[i]-48);
		ten/=10;
	}
	if (sign_minus==1)
		number=0-number;
	return number;
}
float strtofloat(char *s)
{	
	int i,j,temp_num,point_position=0;
	char temp_str[15]="";
	float ten,number=0;
	short sign_minus=0;	
	for(i=0; i<strlen(s); i++)
		if(s[i]=='.')
			point_position=i;
	if (point_position==0)
		return strtoint(s);
	if (s[0]=='-')
	{
		sign_minus=1;
		point_position--;
		for (i=0; i<strlen(s)-1; i++)
			s[i]=s[i+1];		
		s[strlen(s)-1]=0;
	}
	for(i=0; i<point_position; i++)
		temp_str[i]=s[i];
	number=strtoint(temp_str);
	temp_str[0]=0;	
	for(i=0; i<strlen(s); i++)
		temp_str[i]=s[i+point_position+1];
	temp_num=strtoint(temp_str);
	for(i=0,ten=1; i<strlen(temp_str); i++)
		ten*=10;
	number=number + (temp_num / ten);
	if (sign_minus==1)
		number=0-number;
	return number;
}
short check_number(char *s)
{
	int i,point_count=0;
	if ( (s[0]=='-') && ((s[1]=='.')||(s[strlen(s)-1]=='.')) ||
		((s[0]=='.') || (s[strlen(s)-1]=='.')))
		return 0;
	if(s[0]=='-')
		i=1; 
	else 
		i=0;
	for (;i<strlen(s); i++)
	{
		if (s[i]=='.')
			point_count++;
		
		if ((s[i]!='.') && (isdigit(s[i])==0))
			return 0;
		if (point_count>1)
			return 0;
	}
	return 1;
}
float get_number()
{
	float number;
	char s[30];
	short true_number=0;
	scanf("%s",s);
	while(true_number!=1)
	{
		if(strcmp("q",s)==0)
		{
			return;
		}			
		if(check_number(s)==0)
		{
			printf("Введите корректное число или q для возврата в меню: ");
			scanf("%s",s);			
		}
		else
			return strtofloat(s);
	}	
}
void calc (char ch)
{
	float number1,number2;
	printf("\nПервое число (q - возврат в меню): ");
	number1=get_number();
	if(number1!=number1)
		return;
	printf("Второе число (q - возврат в меню): ");	
	number2=get_number();
	if(number2!=number2)
		return;
	if(ch=='/')
		while(number2==0)
		{
			printf("Второе число не должно быть 0, повторите ввод: ");
			number2=get_number();
		}
	switch(ch)
		{			
			case '+': printf("%f + %f = %f",number1,number2,number1+number2); break;
			case '-': printf("%f - %f = %f",number1,number2,number1-number2); break;
			case '*': printf("%f * %f = %f",number1,number2,number1*number2); break;
			case '/': printf("%f / %f = %f",number1,number2,number1/number2); break;
		}
}
void menu()
{
	char ch;
	printf("с. сложение;		в. вычитание;\n"
	"у. умножение;		д. деление;		з. завершение.\n"
	"Желаемая операция: ");
	ch=getch();
	while(ch!='з')
	{		
		switch(ch)
		{			
			case 'с': calc('+'); break;
			case 'в': calc('-'); break;
			case 'у': calc('*'); break;
			case 'д': calc('/'); break;
			case 'з': break;
			case '\n': break;
			default: printf("\nВыберите корректное действие"); break;
		}
		if (ch!='\n')
			printf("\n**********************************************\n"
			"с. сложение;		в. вычитание;\n"
			"у. умножение;		д. деление;		з. завершение.\n"
			"Желаемая операция: ");	
		ch=getch();
		printf("%c",ch);
	}
}
int main(void)
{
	menu();
	printf("\nРабота завершена.");
	return 0;	
}