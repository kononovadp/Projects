/**2. Вспомните пример STRCONV из главы 8. Класс String в этом примере имеет дефект: у него нет защиты на тот случай, если его объекты будут инициализированы слишком длинной строкой (константа SZ имеет значение 80). Например, определение String s = "Эта строка имеет очень большую длину и мы можем быть уверены, что она не уместится в отведенный буфер, что приведет к непредсказуемым последствиям."; будет причиной переполнения массива str строкой s с непредсказуемыми последствиями вплоть до краха системы. Создадим класс Pstring, производный от класса String, в котором предотвратим возможность переполнения буфера при определении слишком длинной строковой константы. Новый конструктор производного класса будет копировать в str только SZ-1 символов, если строка окажется слишком длинной, и будет копировать строку полностью, если она будет иметь длину меньшую, чем SZ. Напишите функцию main() программы для проверки ее работы со строками разной длины*/
#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;
class String
{
	protected:
	enum {SZ=5}; //размер массива
	char str[SZ+1]; //массив для хранения строки
	public:
	//конструктор без параметров
	String(){str[0]='\x0';}
	// конструктор с одним параметром
	String(char s[]){strcpy(str,s);}// сохраняем строку в массиве
	void display(){cout<<str;}
	// перевод строки к обычному типу
	operator char*(){return str;}
};
class Pstring:public String
{
	public: Pstring(string NewStr)
	{
		if(NewStr.length()<SZ)
		{
			strcpy(str,NewStr.c_str());
		}
		else
		{
			int i;
			for(i=0; i<SZ; i++)
				str[i]=NewStr[i];
			str[i]='\x0';
			//strncpy(str,NewStr.c_str(),SZ);
			//strcat(str,"\0");
		}
	}
	void display(){String::display();}
};
int main()
{
	/*String s1; //используем конструктор без параметров
	char xstr[] = "Ура, товарищи! "; //создаем обычную строку
	s1=xstr; // неявно используем конструктор с одним параметром
	s1.display();
	String s2;
	strcpy(s2,"Мы победим!"); //снова используем конструктор с параметром
	cout<<static_cast<char*>(s2);	//используем оператор перевода типа
	cout<<endl;*/
	char ch=0;
	string str;
	while(ch!='0')
	{
		cout<<"Your string: ";
		cin>>str;
		Pstring NewPstring(str);
		cout<<"You entered: ";
		NewPstring.display();
		cout<<"\nPress 1 to continue or 0 to exit: ";
		ch=0;
		while(ch!='0' && ch!='1')		
			ch=getch();		
		cout<<ch<<endl;
	}	
	return 0;
}
