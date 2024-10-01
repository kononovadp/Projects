/*8. В некоторых компьютерных языках, таких, как Visual Basic, есть операции, с помощью которых можно выделить часть строки и присвоить ее другой строке. (В стандартном классе string предложены различные подходы.) Используя наследование, добавьте такую возможность в класс Pstring из упражнения 2. В новом производном классе Pstring2 разместите три новых функции:left(), mid() и right().
s2.left(s1, n) //в строку s2 помещаются n самых левых символов строки s1
s2.mid(s1, s, n) //в строку s2 помещаются n символов из строки, начиная с символа номер s
s2.right(s1, n) //в строку s2 помещаются n самых правых символов строки s1
Вы можете использовать цикл for для копирования символ за символом подходящих частей строки s1 во временный объект класса Pstring2, который затем их возвратит. Для получения лучшего результата используйте в этих функциях возврат по ссылке, чтобы они могли быть использованы с левой стороны знака «равно» для изменения части существующей строки.*/
#include "../../../../accessories.h"
class String
{
	protected:
	enum {SZ=40};
	char str[SZ+1];
	public:
	String(){str[0]='\x0';}
	String(char s[]){strcpy(str,s);}
	void display(){cout<<str;}
	operator char*(){return str;}
};
class Pstring:public String
{
	protected: bool overflow;
	public: Pstring(string NewStr)
	{
		if(NewStr.length()<SZ)
		{
			strcpy(str,NewStr.c_str());
			overflow=false;
		}
		else
		{
			int i;
			for(i=0; i<SZ; i++)
				str[i]=NewStr[i];
			str[i]='\x0';
			overflow=true;
		}
	}
	void display()
	{
		String::display();
		if(overflow)
			cout<<"...";
	}
};
class Pstring2:public Pstring
{
	public: Pstring2(string NewStr):Pstring(NewStr){}
	Pstring2 left(string s1,int n) //n самых левых символов строки s1
	{
		int i,j;
		char NewStr[SZ+1];
		strcpy(NewStr,str);
		for(i=strlen(NewStr),j=0; j<n; i++,j++)
			if(strlen(NewStr)==SZ)
			{
				NewStr[i]='\x0';
				Pstring2 NewPstring2(NewStr);
				NewPstring2.overflow=true;
				return NewPstring2;
			}
			else
				NewStr[i]=s1[j];
		NewStr[i]='\x0';
		return Pstring2(NewStr);
	}
	Pstring2 mid(string s1,int s,int n)//n символов из строки, начиная с символа s
	{
		int i,j,k;
		char NewStr[SZ+1];
		strcpy(NewStr,str);
		for(i=strlen(NewStr),j=s,k=0; k<n; i++,j++,k++)
			if(strlen(NewStr)==SZ || j==s1.length())
			{
				NewStr[i]='\x0';
				Pstring2 NewPstring2(NewStr);
				NewPstring2.overflow=true;				
				return NewPstring2;
			}
			else
				NewStr[i]=s1[j];
		NewStr[i]='\x0';
		return Pstring2(NewStr);
	}
	Pstring2 right(string s1,int n) //n самых правых символов строки s1
	{
		int i,j,k;
		char NewStr[SZ+1];
		strcpy(NewStr,str);		
		for(i=strlen(NewStr),j=s1.length()-n,k=0; k<n; i++,j++,k++)
			if(strlen(NewStr)==SZ)
			{
				NewStr[i]='\x0';
				Pstring2 NewPstring2(NewStr);
				NewPstring2.overflow=true;
				return NewPstring2;
			}
			else
				NewStr[i]=s1[j];
		NewStr[i]='\x0';
		return Pstring2(NewStr);
	}
};
int main()
{
	int CountOfAddedCharacters,StartingPosition;
	char ch=0;
	string str,str1,str2;
	srand(time(0));
	for(ch='a'; ch<'z'; ch++)
		str1+=ch;
	for(ch='A'; ch<'Z'; ch++)
		str2+=ch;
	while(ch!='0')
	{
		ShuffleString(str1);
		ShuffleString(str2);
		CountOfAddedCharacters=GetRandomInt(0,str2.length());
		StartingPosition=GetRandomInt(0,str2.length());
		Pstring2 NewPstring2(str1);
		cout<<"string 1: "<<str1<<"\nstring 2: "<<str2<<endl;
		cout<<"Count of added characters: "<<CountOfAddedCharacters<<endl;
		cout<<"Starting position for mid: "<<StartingPosition<<endl;
		cout<<"NewPstring2: ";
		NewPstring2.display();
		Pstring2 NewPstring2Result=NewPstring2.left(str2,CountOfAddedCharacters);
		cout<<"\nResult of NewPstring2.left: ";
		NewPstring2Result.display();		
		NewPstring2Result=NewPstring2.mid(str2,StartingPosition,CountOfAddedCharacters);
		cout<<"\nResult of NewPstring2.mid: ";
		NewPstring2Result.display();		
		NewPstring2Result=NewPstring2.right(str2,CountOfAddedCharacters);
		cout<<"\nResult of NewPstring2.right: ";
		NewPstring2Result.display();		
		cout<<"\n---------------------------------------------------------------------------\n";
		cout<<"Press 1 to continue or 0 to exit: ";
		ch=0;
		while(ch!='0' && ch!='1')		
			ch=getch();
		cout<<ch<<endl;		
	}	
	return 0;
}