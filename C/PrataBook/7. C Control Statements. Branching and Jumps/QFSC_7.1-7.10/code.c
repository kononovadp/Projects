/*1.a false
1.б true
1.в false
2.а number>=90 && number<100
2.б ch!='q' || ch!='k'
2.в number>=1 && number<=9
2.г !(number>=1 && number<=9)
3:*/
/*#include <stdio.h>
int main(void)
{
	int weight, height;
	scanf("%d %d",&weight, &height);
	if (weight<100 && height>=72)
		printf("Ваш вес слишком мал для вашего роста");
	else
		if(weight<72 && height>64)
			printf("Ваш вес мал для вашего роста");
		else
			if(weight>=300 && height<=48)
				printf("Ваш рост мал для вашего веса");
			else
				printf("У вас идеальный вес");
	return 0;
}*/
/*
4.а true (1)
4.б false (0)
4.в true (1)
4.г 6
4.д true (1)
4.e false (0)
5: *#%*#%$#%*#%*#%$#%*#%*#%$#%*#%*#%
6: hat
cat
7:
#include <stdio.h>
int main(void)
{
	char ch;
	int lc=0;
	int uc=0;
	int oc=0;
	while((ch=getchar()) != '#')
	{
		if(ch>='a' && ch<='z')
			lc++;
		else if (ch>='A' && ch<='Z')
			uc++;
		else
			oc++;
	}
	printf("\n%d строчных, %d прописных, %d других",lc,uc,oc);
	return 0;
}
*/
/*8: 
Вам 20. Вас повысили в должности.
Вам 40. Вас повысили в должности.
Вам 60. Вас повысили в должности.
Вам 65. Получите свои золотые часы.
9: Шаг 1
Готово
10:*/
#include <stdio.h>
int main(void)
{
	char ch;
	while((ch=getchar()) != '#')
	{
		if (ch!='\n')
			printf("Шаг 1\n");
		if (ch!='c')
			if (ch=='b')
				break;
			else if (ch=='h')
				printf("Шаг 3\n");
			printf("Шаг 2\n");
	}
	printf("Готово\n");
	return 0;
}
					
