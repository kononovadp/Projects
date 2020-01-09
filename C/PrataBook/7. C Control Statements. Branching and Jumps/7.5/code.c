/*Выполните упражнение 4, но с применением оператора switch.*/
#include <stdio.h>
int main(void)
{
	char ch,char_array[100];
	int j,i=0;
	int changes=0;
	while((ch=getchar())!='#')
	{
		char_array[i]=ch;
		i++;
	}
	
	printf("Output: ");
	for(j=0; j<i; j++)
		switch (char_array[j])
		{
			case '.': printf("!"); changes++; break;
			case '!': printf("!!"); changes++; break;
			default: printf("%c",char_array[j]);
		}
	printf("\n Количество произведенных замен: %d",changes);
	return 0;
}
					
