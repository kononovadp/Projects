/*Разработайте структуру битовых полей, которая содержит следующую информацию:
1) идентификатор шрифта: число от 0 до 255;
2) размер шрифта: число от 0 до 127;
3) выравнивание: число от 0 до 2, представляющее опции выравнивания влево, по центру и вправо;
4) полужирный: отключен (0) или включен (1);
5) курсив: отключен (0) или включен (1);
6) подчеркнутый: отключен (0) или включен (1).
Используйте эту структуру в программе, которая отображает параметры шрифта и дает пользователю возможность менять параметры с помощью циклического меню. Ниже приведен пример выполнения программы:*//*
ИД   РАЗМЕР   ВЫРАВНИВАНИЕ     Ж     К     Ч
 1       12    влево         откл. откл. откл.
ш) изменить шрифт; р) изменить размер; в) изменить выравнивание;
ж) полужирный;     к) курсив;          п) подчеркнутый;
з) завершить.
р
Введите размер шрифта (0-127): 36
ИД   РАЗМЕР   ВЫРАВНИВАНИЕ     Ж     К     Ч
 1       36    влево         откл. откл. откл.
ш) изменить шрифт; р) изменить размер; в) изменить выравнивание;
ж) полужирный;     к) курсив;          п) подчеркнутый;
з) завершить.
в
Выберите выравнивание: л) влево; ц) по центру; п) вправо.
п
ИД   РАЗМЕР   ВЫРАВНИВАНИЕ     Ж     К     Ч
 1       36    вправо         откл. откл. откл.
ш) изменить шрифт; р) изменить размер; в) изменить выравнивание;
ж) полужирный;     к) курсив;          п) подчеркнутый;
з) завершить.
к
ИД   РАЗМЕР   ВЫРАВНИВАНИЕ     Ж     К     Ч
 1       36    вправо         откл. вкл. откл.
ш) изменить шрифт; р) изменить размер; в) изменить выравнивание;
ж) полужирный;     к) курсив;          п) подчеркнутый;
з) завершить.
з
Программа завершена.
Чтобы обеспечить преобразование вводимых значений идентификатора и размера шрифта в значения из указанного диапазона, программа должна применять операцию & и подходящие маски.*/
#include <stdio.h>
struct type
{
	unsigned int type_id: 8;
	unsigned int type_size: 7;
	unsigned int alignment: 3;
	unsigned int bold: 1;
	unsigned int italic: 1;
	unsigned int accented: 1;
};
void show_struct(struct type *format)
{
	printf("%s%10s%20s%10c%10c%10c\n","ИД","РАЗМЕР","ВЫРАВНИВАНИЕ",'Ж','К','Ч');
	printf("%d%9d",format->type_id,format->type_size);
	switch(format->alignment)
	{
		case 0: printf("%20s","влево"); break;
		case 1: printf("%20s","вправо"); break;
		case 2: printf("%20s","по центру"); break;
	}
	switch(format->bold)
	{
		case 0: printf("%14s","выкл."); break;
		case 1: printf("%14s","вкл."); break;
	}
	switch(format->italic)
	{
		case 0: printf("%10s","выкл."); break;
		case 1: printf("%10s","вкл."); break;
	}
	switch(format->accented)
	{
		case 0: printf("%10s","выкл."); break;
		case 1: printf("%10s","вкл.\n"); break;
	}
}
void change_type_id(struct type *format)
{
	unsigned int type_id;
	printf("\nНомер шрифта: ");
	scanf("%d",&type_id);
	while(type_id>255 && type_id!=0)
	{
		printf("Номер не может быть больше 255. Новый номер (0 - выход): ");
		scanf("%d",&type_id);
	}
	if(type_id>0)
		format->type_id=type_id;
}
void change_type_size(struct type *format)
{
	unsigned int type_size;
	printf("\nРазмер шрифта: ");
	scanf("%d",&type_size);
	while(type_size>127 && type_size!=0)
	{
		printf("Размер не может быть больше 127. Новый размер (0 - выход): ");
		scanf("%d",&type_size);
	}
	if(type_size>0)
		format->type_size=type_size;
}
void change_alignment(struct type *format)
{
	printf("\nВыравнивание текста (0 - влево; 1 - вправо; 2 - по центру; 3 - выход): ");
	char ch=_getche();	
	while(ch!= '0' && ch!='1' && ch!='2' && ch!='3')
	{
		switch(ch)
		{
			default: printf("\nВыберите корректное выравнивание или нажмите 3 для выхода: "); break;
		}
		ch=_getche();
	}
	if(ch>='0' && ch<='2')
		format->alignment=ch-'0';
	putchar('\n');
}
int main(void)
{
	struct type format;
	format.type_id=1;
	format.type_size=12;
	format.alignment=2;
	format.bold=0;
	format.italic=1;
	format.accented=1;
	show_struct(&format);	
	printf("1) изменить шрифт; 2) изменить размер; 3) изменить выравнивание;\n"
		   "4) полужирный; 5) курсив; 6) подчеркнутый; 7) завершить.\n"
		   "Выбранное действие (7 - выход): ");
	char ch=_getche();
	while(ch!='7')
	{
		switch(ch)
		{
			case '1': change_type_id(&format); break;
			case '2': change_type_size(&format); break;
			case '3': change_alignment(&format); break;
			case '4': if(format.bold==0) format.bold=1; else format.bold=0;
			putchar('\n'); break;
			case '5': if(format.italic==0) format.italic=1; else format.italic=0; 
			putchar('\n'); break;
			case '6': if(format.accented==0) format.accented=1; else 
			format.accented=0; putchar('\n'); break;
			default: printf("Выберите корректное действие\n"); break;
		}
		show_struct(&format);
		if (ch!='\n')
			printf("\n*****************************************************************\n"
			"1) изменить шрифт; 2) изменить размер; 3) изменить выравнивание;\n"
		    "4) полужирный; 5) курсив; 6) подчеркнутый; 7) завершить.\n"
		    "Выбранное действие (7 - выход): ");
		ch=_getche();
	}
    return 0;
}