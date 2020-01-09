/*Цифровые изображения, особенно передаваемые по радиосигналу космическим аппаратом, могут содержать помехи. Добавьте в программу из упражнения 12 функцию подавления помех. Она должна сравнивать каждое значение с соседними значениями, расположенными слева и справа, снизу и сверху. Если значение отличается больше чем на 1 от своих соседей, оно должно быть заменено средним значением всех соседних величин. Среднее значение должно быть округлено до бижайшего целого. Обратите внимание, что точки, находящиеся на границах, имеют меньше четырех соседей, поэтому они требуют специальной обработки.*/
#include <stdio.h>
#include <string.h>
void show_numbers(int lines, int columns, int arr[][columns])
{
	int j;
	for(int i=0; i<lines; i++)
	{
		for(j=0; j<columns; j++)
			printf("%d ",arr[i][j]);
		putchar('\n');
	}
}
void show_symbols(int lines, int columns, char char_arr[][columns+1])
{
	FILE *f2=fopen("2.txt","w");
	int j;
	for(int i=0; i<lines; i++)
	{
		for(j=0; j<columns; j++)
		{
			putchar(char_arr[i][j]);
			fprintf(f2,"%c",(char)char_arr[i][j]);
		}
		putchar('\n');
		fprintf(f2,"\n");
	}
}
void create_number_matrix(int lines, int columns, int int_arr[][columns])
{
	FILE *f;
	int ch,j,i=0;
	if((f=fopen("1.txt","r"))==NULL)
		exit();
	while((ch=getc(f))!=EOF)
	{
		j=0;
		while(/*ch!='\n' && ch!=EOF && */j<columns)
		{
			if(ch!=' ')
			{
				int_arr[i][j]=ch-'0';
				j++;
			}
			ch=getc(f);
		}
		i++;
	}
	fclose(f);
}
void create_symbol_matrix(int lines, int columns, char char_arr[][columns+1],
int int_arr[][columns])
{
	int j;
	for(int i=0; i<lines; i++)
	{
		for(j=0; j<columns; j++)
			switch(int_arr[i][j])
			{
				case 0:char_arr[i][j]=' '; break;
				case 1:char_arr[i][j]='.'; break;
				case 2:char_arr[i][j]='\''; break;
				case 3:char_arr[i][j]=':'; break;
				case 4:char_arr[i][j]='~'; break;
				case 5:char_arr[i][j]='*'; break;
				case 6:char_arr[i][j]='='; break;
				case 8:char_arr[i][j]='%'; break;
				case 9:char_arr[i][j]='#'; break;
			}
	}
}
void interference_rejection(int lines, int columns, int a[][columns])
{
	int i,j;	
	if((a[1][0]>a[0][0]+1 || a[1][0]<a[0][0]-1) && 
	(a[0][1]>a[0][0]+1 || a[0][1]<a[0][0]-1))
	{
		printf("Верхний левый угол!\n");
		a[0][0]=(a[0][1]+a[1][0])/2;
	}
	if((a[lines-2][0]>a[lines-1][0]+1 || a[lines-2][0]<a[lines-1][0]-1) &&
	(a[lines-1][1]>a[lines-1][0]+1 || a[lines-1][1]<a[lines-1][0]-1))
	{
		printf("Верхний правый угол!\n");
		a[lines-1][0]=(a[lines-1][1]+a[lines-2][0])/2;
	}
	if((a[0][columns-2]>a[0][columns-1]+1 || a[0][columns-2]<a[0][columns-1]-1) &&
	(a[1][columns-1]>a[0][columns-1]+1 || a[1][columns-1]<a[0][columns-1]-1))
	{
		printf("Нижний левый угол!\n");
		a[0][columns-1]=(a[0][columns-2]+a[1][columns-1])/2;
	}
	if((a[lines-1][columns-2]>a[lines-1][columns-1]+1 ||
		a[lines-1][columns-2]<a[lines-1][columns-1]-1) &&
		(a[lines-2][columns-1]>a[lines-1][columns-1]+1 ||
		a[lines-2][columns-1]<a[lines-1][columns-1]-1))	
	{
		printf("Нижний правый угол!\n");
		a[lines-1][columns-1]=(a[lines-2][columns-1]+a[lines-1][columns-2])/2;
	}
	for(i=1; i<columns-2; i++)
		if((a[0][i+1]>a[0][i]+1 || a[0][i+1]<a[0][i]-1) &&
		   (a[0][i-1]>a[0][i]+1 || a[0][i-1]<a[0][i]-1) &&
		   (a[1][i]>a[0][i]+1 || a[1][i]<a[0][i]-1))
		{
			  printf("Первая строка: i = %d\n",i);
			  a[0][i]=(a[0][i-1]+a[0][i+1]+a[1][i])/3;
		}
	for(i=1; i<columns-2; i++)
		if((a[lines-1][i-1]>a[lines-1][i]+1 || a[lines-1][i-1]<a[lines-1][i]-1) &&
		   (a[lines-1][i+1]>a[lines-1][i]+1 || a[lines-1][i+1]<a[lines-1][i]-1) &&
		   (a[lines-2][i]>a[lines-1][i]+1 || a[lines-2][i]<a[lines-1][i]-1))
		{
			  printf("Последняя строка: i = %d\n",i);
			  a[lines-1][i]=(a[lines-1][i-1]+a[lines-1][i+1]+a[lines-2][i])/3;
		}
	for(i=1; i<lines-2; i++)
		if((a[i][1]>a[i][0]+1 || a[i][1]<a[i][0]-1) &&
		   (a[i-1][0]>a[i][0]+1 || a[i-1][0]<a[i][0]-1) &&
		   (a[i+1][0]>a[i][0]+1 || a[i+1][0]<a[i][0]-1))
		{
		      printf("Левая колонка: i = %d\n",i);
			  a[i][0]=(a[i][1]+a[i-1][0]+a[i+1][0])/3;
		}
	for(i=1; i<lines-2; i++)
		if((a[i][columns-2]>a[i][columns-1]+1 || a[i][columns-2]<a[i][columns-1]-1) && (a[i+1][columns-1]>a[i][columns-1]+1 || 
	         a[i+1][columns-1]<a[i][columns-1]-1)
		 && (a[i-1][columns-1]>a[i][columns-1]+1 ||
		     a[i-1][columns-1]<a[i][columns-1]-1))
	    {
			printf("Правая колонка: i = %d\n",i);
			a[i][columns-1]=(a[i+1][columns-1]+a[i-1][columns-1]+a[i][columns-2])/3;
		}
	for(i=1; i<lines-2; i++)
		for(j=1; j<columns-2; j++)			
			if((a[i+1][j]>a[i][j]+1 || a[i+1][j]<a[i][j]-1) &&
			   (a[i-1][j]>a[i][j]+1 || a[i-1][j]<a[i][j]-1) &&
			   (a[i][j+1]>a[i][j]+1 || a[i][j+1]<a[i][j]-1) &&
			   (a[i][j-1]>a[i][j]+1 || a[i][j-1]<a[i][j]-1))
			{
			   printf("Середина: строка i = %d; столбец j = %d\n",i,j);
			   a[i][j]=(a[i+1][j]+a[i-1][j]+a[i][j+1]+a[i][j-1])/4;
			}		   
}
int main(int argv, char *argz[])
{
	int LINES=20;
	int COLUMNS=30;
	int int_arr[LINES][COLUMNS];
	char char_arr[LINES][COLUMNS+1];
	create_number_matrix(LINES,COLUMNS,int_arr);
	/*printf("Number matrix:\n");
	show_numbers(LINES, COLUMNS, int_arr);*/
	create_symbol_matrix(LINES,COLUMNS,char_arr,int_arr);
	printf("Symbol matrix:\n");
	show_symbols(LINES, COLUMNS, char_arr);
	interference_rejection(LINES, COLUMNS, int_arr);
	/*printf("Number matrix after interference rejection:\n");
	show_numbers(LINES, COLUMNS, int_arr);*/
	create_symbol_matrix(LINES,COLUMNS,char_arr,int_arr);
	printf("Symbol matrix after interference rejection:\n");
	show_symbols(LINES, COLUMNS, char_arr);
    return 0;
}