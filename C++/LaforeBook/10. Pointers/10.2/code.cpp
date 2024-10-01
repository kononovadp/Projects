//*2. Используйте класс String из примера NEWSTR этой главы. Добавьте к нему метод upit(), который будет переводить символы строки в верхний регистр. Вы можете использовать библиотечную функцию toupper(), которая принимает отдельный символ в качестве аргумента и возвращает символ, переведенный в верхний регистр (если это необходимо). Эта функция использует заголовочный файл Cctype. Добавьте в функцию main() необходимые строки для тестирования метода upit().
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
class String
{
	char* str; //указатель на строку
	public:
	String(char* s) //конструктор с одним параметром
	{
		int length=strlen(s); //вычисляем длину строки
		str=new char[length+1]; //выделяем необходимую память
		strcpy(str,s); //копируем строку
	}
	~String() //деструктор
	{
		delete[] str; //освобождаем память
	}
	void display() //покажем строку на экране
	{
		cout<<str<<endl;
	}
	void upit()
	{
		int i;
		for(i=0; i<strlen(str); i++)
			str[i]=toupper(str[i]);
	}
};
int main()
{
	char str[]="The more haste the less speed.";
	String s1=str;
	cout<<"s1: ";
	s1.display();
	s1.upit();
	cout<<"\nUpper case: ";
	s1.display();
	return 0;
}