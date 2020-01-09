/*Напишите программу с таким же поведением как в упражнении 6, но используйте для хранения информации о шрифте переменную типа unsigned long, а для манипулирования этой информацией - побитовые операции вместо членов структуры с битовыми полями.*/
#include <stdio.h>
struct type
{
	unsigned long type_inf;
	unsigned int alignment: 3;
	unsigned int bold: 1;
	unsigned int italic: 1;
	unsigned int accented: 1;
};
int get_bits_count(unsigned int n)
{
	int bits_count=0;
	while(n>0)
	{
		bits_count++;
		n>>=1;
	}
	return bits_count;
}
char *convert_to_binary(int n)
{
	char ch,*res=(char*)malloc(40*sizeof(char));
	int i=0;
	int bits_count=get_bits_count(n);
	if(bits_count==0)
		return "0";
	while(bits_count>0)
	{
		res[i]=(char)'0'+((n>>bits_count-1)&1);		
		bits_count--;
		i++;
	}
	return res;
}
unsigned long read_type_size(unsigned long n)
{
	int bit_number=16;
	unsigned int res=0;
	while(bit_number>9)
	{
		res<<=1;
		res+=(n>>bit_number-1)&1;		
		bit_number--;
	}
	return res;
}
unsigned long write_type_id(unsigned long n,unsigned long type_id)
{
	return 65536|read_type_size(n)<<9|type_id;
}
unsigned long read_type_id(unsigned long n)
{
	int bit_number=8;
	unsigned int res=0;
	while(bit_number>0)
	{
		res<<=1;
		res+=(n>>bit_number-1)&1;		
		bit_number--;
	}
	return res;
}
unsigned long write_type_size(unsigned long n,int type_size)
{
	return 65536|(type_size<<9)|read_type_id(n);
}
//----------------------------------------------------------------------------------
void show_struct(struct type *format)
{
	printf("%s%10s%20s%10c%10c%10c\n","ИД","РАЗМЕР","ВЫРАВНИВАНИЕ",'Ж','К','Ч');
	printf("%d%9d",read_type_id(format->type_inf),read_type_size(format->type_inf));
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
	unsigned long int type_id;
	printf("\nНомер шрифта: ");
	scanf("%d",&type_id);
	while(type_id>255 && type_id!=0)
	{
		printf("Номер не может быть больше 255. Новый номер (0 - выход): ");
		scanf("%d",&type_id);
	}
	if(type_id>0)
		format->type_inf=write_type_id(format->type_inf,type_id);}
void change_type_size(struct type *format)
{
	unsigned long int type_size;
	printf("\nРазмер шрифта: ");
	scanf("%d",&type_size);
	while(type_size>127 && type_size!=0)
	{
		printf("Размер не может быть больше 127. Новый размер (0 - выход): ");
		scanf("%d",&type_size);
	}
	if(type_size>0)
		format->type_inf=write_type_size(format->type_inf,type_size);
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
	format.type_inf=65536;
	format.type_inf=write_type_id(format.type_inf,1);
	format.type_inf=write_type_size(format.type_inf,12);
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