/*Напишите программу, которая читает входные данные до тех пор, пока не встретится символ #, а затем отображает количество прочитанных пробелов, количество символов новой строки и количество всех остальных символов.*/
#include <stdio.h>
int main(void)
{
	char ch;
	int spaces,new_lines,other_symbols;
	for(spaces=0,new_lines=0,other_symbols=0; ch!='#'; ch=getchar())
	{
		if (ch==' ')
			spaces++;
		else if (ch=='\n')
			new_lines++;
		else
			other_symbols++;
	}
	printf("Пробелов: %d; Символов новой строки: %d; Других символов: %d",
	spaces,new_lines,other_symbols);
	return 0;
}
					
