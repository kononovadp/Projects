/*�������� ��������� ����, ��������� �� 20 ����� �� 30 ����� �����. ����� �������� ������ ������� � �������� �� 0 �� 9 � ���������� ���� �� ����� ���������. ���� �������� �������� �������������� �����������, ��� ���� �������� �� 0 �� 9 ������������� ������������ ������ �������. �������� ���������, ������� ������ ���������� ����� ����� � ������ ��������� int � �������� 20 �� 30. ��� ������ ������� � �������������� ������ ��������� ������������� � ����������� ��������� ������ ������������ �������� �� ����� ������� ��� ������������� ������� ��������� char � �������� 20 �� 31. ��� ���� 0 ������������� ������� �������, 1 - ������� ����� � �. �.; ������� �������� �������������� ��������, ���������� ������� �������. ��������, ������ # ����� �������������� ��� ������������� �������� 9. ��������� ������ (31-�) � ������ ������ ������ ���� �������, ������� � ����� ������ �� 20 �����. ��������� ������ ���������� �������������� ����������� (�. �. ������� ������) � ����� ��������� ��������� � ��������� �����. ��������, �����������, ��� ��������� ������ �������� ���: 
0 0 9 0 0 0 0 0 0 0 0 0 5 8 9 9 8 5 2 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 9 0 0 0 0 0 0 0 5 8 9 9 8 5 5 2 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 5 8 1 9 8 5 4 5 2 0 0 0 0 0 0 0 0 0
0 0 0 0 9 0 0 0 0 0 0 0 5 8 9 9 8 5 0 4 5 2 0 0 0 0 0 0 0 0
0 0 9 0 0 0 0 0 0 0 0 0 5 8 9 9 8 5 0 0 4 5 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 5 8 9 1 8 5 0 0 0 4 5 2 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 5 8 9 9 8 5 0 0 0 0 4 5 2 0 0 0 0 0
5 5 5 5 5 5 5 5 5 5 5 5 5 8 9 9 8 5 5 5 5 5 5 5 5 5 5 5 5 5
8 8 8 8 8 8 8 8 8 8 8 8 8 8 5 8 9 9 8 5 8 8 8 8 8 8 8 8 8 8
9 9 9 9 0 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 3 9 9 9 9 9 9 9
8 8 8 8 8 8 8 8 8 8 8 8 5 8 9 9 8 5 8 8 8 8 8 8 8 8 8 8 8 8
5 5 5 5 5 5 5 5 5 5 5 5 5 8 9 9 8 5 5 5 5 5 5 5 5 5 5 5 5 5
0 0 0 0 0 0 0 0 0 0 0 0 5 8 9 9 8 5 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 5 8 9 9 8 5 0 0 0 0 6 6 0 0 0 0 0 0
0 0 0 0 2 2 0 0 0 0 0 0 5 8 9 9 8 5 0 0 5 6 0 0 6 5 0 0 0 0
0 0 0 0 3 3 0 0 0 0 0 0 5 8 9 9 8 5 0 5 6 1 1 1 1 6 5 0 0 0
0 0 0 0 4 4 0 0 0 0 0 0 5 8 9 9 8 5 0 0 5 6 0 0 6 5 0 0 0 0
0 0 0 0 5 5 0 0 0 0 0 0 5 8 9 9 8 5 0 0 0 0 6 6 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 5 8 9 9 8 5 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 5 8 9 9 8 5 0 0 0 0 0 0 0 0 0 0 0 0
��� �������� ������ �������� �������� ����� ����� ����� ��������� ���:
  #         *%##%*'           
    #       *%##%**'          
            *%.#%*~*'         
    #       *%##%* ~*'        
  #         *%##%*  ~*'       
            *%#.%*   ~*'      
            *%##%*    ~*'     
*************%##%*************
%%%%%%%%%%%%%%*%##%*%%%%%%%%%%
#### #################:#######
%%%%%%%%%%%%*%##%*%%%%%%%%%%%%
*************%##%*************
            *%##%*            
            *%##%*    ==      
    ''      *%##%*  *=  =*    
    ::      *%##%* *=....=*   
    ~~      *%##%*  *=  =*    
    **      *%##%*    ==      
            *%##%*            
            *%##%*            */
#include <stdio.h>
#include <string.h>
#define LINES 20
#define COLUMNS 30
int main(int argv, char *argz[])
{
    FILE *f,*f2;
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