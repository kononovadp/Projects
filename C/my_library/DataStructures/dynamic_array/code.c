#include <stdio.h>
int main(void)
{
	char ch,*a=NULL;
	int count=0;
	printf("Input: ");
	while((ch=getchar())!='\n')
	{
		count++;
		a=(char*)realloc(a,count*sizeof(char));
		a[count-1]=ch;
	}
	if(a!=NULL)
	{
		printf("Count = %d; strlen = %d\n",count,strlen(a));
		for(count=0; count<strlen(a); count++)
			printf("|%c|\n",a[count]);
	}
	free(a);
    return 0;
}