/*1.a false
1.� true
1.� false
2.� number>=90 && number<100
2.� ch!='q' || ch!='k'
2.� number>=1 && number<=9
2.� !(number>=1 && number<=9)
3:*/
/*#include <stdio.h>
int main(void)
{
	int weight, height;
	scanf("%d %d",&weight, &height);
	if (weight<100 && height>=72)
		printf("��� ��� ������� ��� ��� ������ �����");
	else
		if(weight<72 && height>64)
			printf("��� ��� ��� ��� ������ �����");
		else
			if(weight>=300 && height<=48)
				printf("��� ���� ��� ��� ������ ����");
			else
				printf("� ��� ��������� ���");
	return 0;
}*/
/*
4.� true (1)
4.� false (0)
4.� true (1)
4.� 6
4.� true (1)
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
	printf("\n%d ��������, %d ���������, %d ������",lc,uc,oc);
	return 0;
}
*/
/*8: 
��� 20. ��� �������� � ���������.
��� 40. ��� �������� � ���������.
��� 60. ��� �������� � ���������.
��� 65. �������� ���� ������� ����.
9: ��� 1
������
10:*/
#include <stdio.h>
int main(void)
{
	char ch;
	while((ch=getchar()) != '#')
	{
		if (ch!='\n')
			printf("��� 1\n");
		if (ch!='c')
			if (ch=='b')
				break;
			else if (ch=='h')
				printf("��� 3\n");
			printf("��� 2\n");
	}
	printf("������\n");
	return 0;
}
					
