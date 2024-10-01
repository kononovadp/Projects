//11. За основу возьмите программу STRPLUS из главы 8. Добавьте класс исключений, генерируйте исключения в конструкторе с одним аргументом в случае, если строка инициализации слишком длинная. Генерируйте еще одно исключение в перегруженном операторе «+», если результат конкатенации оказывается слишком длинным. Сообщайте пользователю о том, какая именно ошибка произошла.
// strplus.cpp
// перегрузка операции + для строк
#include <iostream>
#include <string> //для функций strcpy,strcat
#include <string.h>
using namespace std;
class String //наш класс для строк
{
	private:
	enum {SZ=18}; //максимальный размер строки
	char str[SZ]; //массив для строки
	public:
	class error
	{
		string message;
		public:
		error(string NewMessage):message(NewMessage){}
		void display(){cout<<message;}
	};
	String(){strcpy(str,"");} //конструктор без параметров
	String(char s[])
	{
		if(strlen(s)>SZ)
			throw(String::error("New string is too long!"));
		strcpy(str,s);
	}//конструктор с одним параметром
	void display() const {cout<<str;}
	String operator+(String ss) const //оператор сложения
	{
		String temp; //временная переменная
		if(strlen(str)+strlen(ss.str)<SZ)
		{
			strcpy(temp.str,str); //копируем содержимое первой строки
			strcat(temp.str,ss.str); //добавляем содержимое второй строки
		}
		else
		{
			throw(String::error("Concatenated string is too long!"));
			//cout<<"\nOverflow!";
			//exit(1);
		}
		return temp; //возвращаем результат
	}
};
int main()
{
	String s1,s2,s3; //используем конструктор без параметров
	char str1[32];
	strcpy(str1,"Happy New Year ");
	cout<<"s1: ";
	try{s1=str1;} //используем конструктор с параметром
	catch(String::error NewError){NewError.display();}
	s1.display();
	
	char str2[32];	
	strcpy(str2,"Happy Christmas!");
	cout<<"\ns2: ";
	try{s2=str2;} //используем конструктор с параметром
	catch(String::error NewError){NewError.display();}
	s2.display();

	cout<<"\ns1+s2=s3: ";
	try{s3=s1+s2;} //присваиваем строке s3 результат сложения строк s1 и s2
	catch(String::error NewError){NewError.display();}	
	s3.display(); //показываем результат
	return 0;
}