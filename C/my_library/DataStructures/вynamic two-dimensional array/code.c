#include <stdio.h>
int main(void)
{
	FILE *f=fopen("pets.txt","r");
	char ch,*str,**arr;
	int words_count,symbols_count;
	words_count=0;
	arr=(char**)malloc(sizeof(arr));
	while((ch=getc(f))!=EOF)
	{
		symbols_count=0;
		str=(char*)malloc(sizeof(char));
		while(ch!='\n' && ch!=EOF)
		{
			str[symbols_count]=ch;
			symbols_count++;
			str=(char*)realloc(str,symbols_count*sizeof(char));
			str[symbols_count]=0;
			ch=getc(f);
		}
		arr[words_count]=(char*)malloc(strlen(str)*sizeof(char));
		strcpy(arr[words_count],str);
		words_count++;
		printf("!!!%s|\n",str);
		free(str);
	}
	for(symbols_count=0; symbols_count<words_count; symbols_count++)
		printf("|%s|\n",arr[symbols_count]);
	fclose(f);
	return 0;
}