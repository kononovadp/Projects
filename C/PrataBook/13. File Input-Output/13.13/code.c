/*Выполните упражнение 12, используя массивы переменной длины вместо стандартных массивов.*/
#include <stdio.h>
#include <string.h>

int main(int argv, char *argz[])
{
    FILE *f,*f2;
	int LINES=20;
	int COLUMNS=30;
	int int_arr[LINES][COLUMNS],ch,j,i=0;
	char char_arr[LINES][COLUMNS+1];
	if((f=fopen("1.txt","r"))==NULL)
		exit();
	while((ch=getc(f))!=EOF)
	{
		j=0;
		while(/*ch!='\n' && ch!=EOF && */j<COLUMNS)
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
	for(i=0; i<LINES; i++)
	{
		for(j=0; j<COLUMNS; j++)
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
	f2=fopen("2.txt","w");
	for(i=0; i<LINES; i++)
	{
		for(j=0; j<COLUMNS; j++)
		{
			putchar(char_arr[i][j]);
			fprintf(f2,"%c",(char)char_arr[i][j]);
		}
		putchar('\n');
		fprintf(f2,"\n");
	}
	fclose(f2);
    return 0;
}