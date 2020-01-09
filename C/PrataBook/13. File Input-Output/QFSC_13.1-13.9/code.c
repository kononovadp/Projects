/*1. Неправильно fopen, fputs, fclose;
2. Выводит только числовые символы;
3. ch=getc(fp1); fprintf(fp2,"%c\n",ch); putc(ch,fp2); fclose(fp1);
4:
#include <stdio.h>
int main(int argz, char *argv[])
{
	float n,sum=0;
	int i=0;
	if(argz==2)
	{
		FILE *f;
		if((f=fopen(argv[1],"r"))==NULL)
		{
			printf("File %s not found",argv[1]);
			exit();
		}
		while(((int)fscanf(f,"%f",&n))!=EOF)
		{
			sum+=n;
			printf("%f\n",n);
			i++;
		}
		fclose(f);
	}
	else
	{
		printf("Количество чисел с плавающей запятой: ");
		scanf("%d",&i);
		for(int j=0; j<i; j++)
		{
			printf("Число %d: ",j+1);
			scanf("%f",&n);
			sum+=n;
		}		
	}
	printf("Среднее арифметическое введенных чисел: %f",sum/i);
	return 0;
}
5:
#include <stdio.h>
#include <string.h>
int main(int argz, char *argv[])
{
	FILE *f;
	char s[256];
	int i;
	if((f=fopen(argv[2],"r"))==NULL)
		exit();
	printf("Строки, содержащие символ %c:\n",argv[1][0]);
	while((fgets(s,256,f))!=NULL)	
		for(i=0; i<strlen(s); i++)
			if(s[i]==argv[1][0])
			{
				printf("%s",s);
				break;
			}
	fclose(f);
	return 0;
}
6. В двоичном режиме доступен каждый байт файла, содержимое текстового файла может отличаться от того что реально хранится в файле.
7.а. fprintf сохраняет число как последовательность символов, возможно, изменяя значения, fwrite записывает двоичный код, выделяя память для определенного типа данных.
7.б=7.а. fprintf принимает указатель на файл в первом, а не в последнем аргументе.
8. printf и fprintf(stdout...) означают вывод на экран. fprintf(stderr...) выводит сообщение только в случае ошибки.
9. r+.*/