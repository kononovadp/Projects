/**1. Представьте себе издательскую компанию, которая торгует книгами и аудио-записями этих книг. Создайте класс publication, в котором хранятся название (строка) и цена (типа float) книги. От этого класса наследуются еще два класса: book, который содержит информацию о количестве страниц в книге (типа int), и tape, который содержит время записи книги в минутах (тип float). В каждом из этих трех классов должен быть метод getdata(), через который можно получать данные от пользователя с клавиатуры, и putdata(), предназначенный для вывода этих данных. Напишите функцию main() программы для проверки классов book и type. Создайте их объекты в программе и запросите пользователя ввести и вывести данные с использованием методов getdata() и putdata()*/
#include "../../../../accessories.h"
class publication
{
	string name;
	float price;
	public:
	publication(){}
	void GetData()
	{
		char ch=getch();
		while(ch!=13 && ch!=27)
		{
			if(ch==8 && name.length()>0)
			{
				cout<<"\b \b";
				name.pop_back();
			}
			else
				if(ch!=8)
				{
					cout<<ch;
					name+=ch;
				}
			ch=getch();
		}
		if(ch==27)
			exit(0);
		cout<<"\nPrice: ";
		price=GetFloatFromKeyboard();
	}
	void PutData()
	{
		cout<<name<<"; price: "<<price<<";\n";
	}
};
class book: private publication
{
	int CountOfPages;
	public: book(){}
	void GetData()
	{
		cout<<"Name of a book: ";
		publication::GetData();
		cout<<"\nCount of pages: ";
		CountOfPages=GetIntFromKeyboard();
	}
	void PutData()
	{
		cout<<"Name of the book: ";
		publication::PutData();
		cout<<"Count of pages: "<<CountOfPages<<endl;
	}	
};
class tape: private publication
{
	float duration;
	public: tape(){}
	void GetData()
	{
		cout<<"Name of an audiobook: ";
		publication::GetData();
		cout<<"\nDuration (minutes): ";
		duration=GetFloatFromKeyboard();
	}
	void PutData()
	{
		cout<<"Name of the audiobook: ";
		publication::PutData();
		cout<<"Duration (minutes): "<<duration<<endl;
	}
};
int main(void)
{
	InitOutputOfFloatingPointNumbers();
	book NewBook;
	tape NewAudiobook;
	NewBook.GetData();
	cout<<endl;
	NewAudiobook.GetData();
	cout<<endl<<"-----------------------------\n";
	NewBook.PutData();
	NewAudiobook.PutData();
	return 0;
}
