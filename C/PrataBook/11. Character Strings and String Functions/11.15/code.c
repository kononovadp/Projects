/*Для подготовки реализации функции atoi() используйте функции классификации символов. Эта версия должна возвращать значение 0, если строка ввода не является полностью числовой.*/
#include <stdio.h>
#include<ctype.h>
int my_atoi(char *s)
{
	int number=0;
	int i,ten=1;
	short sign_minus=0;
	for(i=0; i<strlen(s); i++)
		if(s[i]!='.' && s[i]!=',' && s[i]!='-' && (!isdigit(s[i])))
			return 0;
	if (s[0]=='-')
	{
		sign_minus=1;
		for (i=0; i<strlen(s)-1; i++)
			s[i]=s[i+1];
		s[strlen(s)-1]=0;
	}	
	for(i=0; isdigit(s[i+1]); i++)
		ten*=10;
	for(i=0; ten>0; i++,ten/=10)		
		number+=ten*(s[i]-'0');
	if (sign_minus==1)
		number=0-number;
	return number;
}
int main(void)
{
    char s[10]="12,34509";
	printf("%d",my_atoi(s));
	return 0;
}
