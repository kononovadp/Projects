/**2. Напишите программу, которая заменяет перегруженную операцию + на перегруженную операцию += в программе STRPLUS этой главы. Эта операция должна позволять записывать выражения типа: s1 += s2, где s2 прибавляется (объединяется) к строке s1, результат при этом остается в s1. Операция должна также позволять использовать результат для других вычислений, например в выражениях типа s3 = s1 += s2*/
#include <iostream>
#include <string.h> //для функций strcpy, strcat
using namespace std;
class String //наш класс для строк
{
	private:
	enum {SZ=80}; //максимальный размер строки
	char str[SZ]; //массив для строки
	public:
	String(){strcpy(str,"");}
	String(char s[]){strcpy(str,s);}
	void display()const //показ строки
	{cout<<str<<endl;}
	//оператор сложения
	String operator+(String ss)const
	{
		String temp; //временная переменная
		if(strlen(str) + strlen(ss.str) < SZ)
		{
			strcpy(temp.str,str); //копируем содержимое первой строки
			strcat(temp.str,ss.str); //добавляем содержимое второй строки
		}
		else
		{
			cout << "\nПереполнение!";
			exit(1);
		}
		return temp; //возвращаем результат
	}
	String operator+=(String SecondString)
	{
		String temp;
		if(strlen(str)+strlen(SecondString.str)<SZ)
		{
			strcpy(temp.str,str);
			strcat(temp.str,SecondString.str);
			strcpy(str,temp.str);
		}
		else
		{
			cout<<"\nПереполнение!";
			exit(1);
		}
		return temp;
	}
};
int main()
{
	char str1[]="str1 ";
	char str2[]="str2";
	String s1(str1); //используем конструктор с параметром	
	String s2(str2); //используем конструктор с параметром
	String s3; //используем конструктор без параметров	
	s1.display();
	s3=s1+=s2;
	s3.display();
	return 0;
}
