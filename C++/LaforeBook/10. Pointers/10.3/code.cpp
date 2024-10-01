//*3. Используйте массив указателей на строки, представляющие собой названия дней недели, из примера PTRSORT этой главы. Напишите функции для сортировки этих строк в алфавитном порядке, используя в качестве основы функции bsort() и order() из программы PTRSORT этой главы. Сортировать необходимо указатели на строки, а не сами строки.
#include <iostream>
#include <string.h>
using namespace std;
void order(char** str1,char** str2)
{
	int i,n;
	char ch;
	char* temp;
	if(strlen(*str1)<strlen(*str2))
		n=strlen(*str1);
	else
		n=strlen(*str2);
	for(i=0; i<n && *(*str1+i)==*(*str2+i); i++);
	if((*(*str1+i))>(*(*str2+i)))
	{			
		temp=*str1;
		*str1=*str2;
		*str2=temp;			
	}	
}
void bsort(char** ptr,int n)
{
	int j,k;
	for(j=0; j<n-1; j++)
		for(k=j+1; k<n; k++)
			order(&ptr[j],&ptr[k]);		
}
int main()
{
	int i;
	char* WeekDays[7]={(char*)"Monday",(char*)"Tuesday",(char*)"Wednesday",(char*)"Thursday",(char*)"Friday",(char*)"Saturday",(char*)"Sunday"};
	for(i=0; i<6; i++)
		cout<<WeekDays[i]<<", ";
	cout<<WeekDays[i]<<endl;
	bsort(WeekDays,7);
	for(i=0; i<6; i++)
		cout<<WeekDays[i]<<", ";
	cout<<WeekDays[i];
	return 0;
}
