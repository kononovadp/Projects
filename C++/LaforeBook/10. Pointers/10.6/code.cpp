//6. Создайте свою версию библиотечной функции strcmp(s1, s2), которая сравнивает две строки и возвращает -1, если s1 идет первой по алфавиту, 0, если в s1 и s2 одинаковые значения, и 1, если s2 идет первой по алфавиту. Назовите вашу функцию compstr(). Она должна принимать в качестве аргументов два указателя на строки char*, сравнивать эти строки посимвольно и возвращать число int. Напишите функцию main() для проверки работы вашей функции с разными строками. Используйте указатели во всех возможных ситуациях.
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
int LocalGetRandomInt(int min, int max)
{
	if(min==max)
		return min;
	return min+(rand()%(max-min));
}
int MyStrcmp(char* str1,char* str2)
{
	int i,size;
	if(strlen(str1)<strlen(str2))
		size=strlen(str1);
	else
		size=strlen(str2);
	for(i=0; i<size && *(str1+i)==*(str2+i); i++);
	if(*(str1+i)<*(str2+i))
		return -1;
	else
		if(*(str1+i)>*(str2+i))
			return 1;
	return 0;
}
int main(void)
{
	srand(time(0));
	char* str1,*str2;
	int i,j,Str1Size,Str2Size;
	for(i=0; i<10; i++)
	{
		Str1Size=LocalGetRandomInt(1,75);
		str1=new char[Str1Size+1];
		for(j=0; j<Str1Size; j++)
			*(str1+j)=LocalGetRandomInt('A','Z');
		*(str1+j)='\0';
		Str2Size=LocalGetRandomInt(1,75);
		char* str2=new char[Str2Size+1];
		for(j=0; j<Str2Size; j++)
			*(str2+j)=LocalGetRandomInt('A','Z');
		*(str2+j)='\0';
		cout<<"str1: "<<str1<<endl;
		cout<<"str2: "<<str2<<endl;
		cout<<"result of MyStrcmp(): "<<MyStrcmp(str1,str2);
		delete[]str1;
		delete[]str2;
		cout<<"\n--------------------------------------------------\n";
		
	}
	Str1Size=LocalGetRandomInt(1,75);
	str1=new char[Str1Size+1];
	str2=new char[Str1Size+1];
	for(j=0; j<Str1Size; j++)
	{
		str1[j]=LocalGetRandomInt('A','Z');
		str2[j]=str1[j];
	}
	str1[j]='\0';
	str2[j]='\0';
	cout<<"str1: "<<str1<<endl;
	cout<<"str2: "<<str2<<endl;
	cout<<"result of MyStrcmp(): "<<MyStrcmp(str1,str2);
	delete[]str1;
	delete[]str2;
	return 0;
}
