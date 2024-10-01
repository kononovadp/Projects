/*9. Вспомним классы publication, book и tape из упражнения 1. Предположим, что мы хотим добавить в классы book и tape дату выхода книги. Создайте новый производный класс publication2, который является производным класса publication и включает в себя поле, хранящее эту дату. Затем измените классы book и tape так, чтобы они стали производными класса publication2 вместо publication. Сделайте необходимые изменения функций классов так, чтобы пользователь мог вводить и выводить дату выхода книги. Для даты можно использовать класс data из упражнения 5 главы 6, который хранит дату в виде трех целых: для месяца, для дня и для года*/
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
		cout<<name<<";\nPrice: "<<price<<";\n";
	}
};
class date
{	
	int day;
	int month;
	int year;
	public:
	void GetDate()
	{
		cout<<"Day: ";
		day=GetIntFromKeyboard(1,31);
		cout<<"\nMonth: ";
		month=GetIntFromKeyboard(1,12);
		cout<<"\nYear: ";
		year=GetIntFromKeyboard(1,2023);
	}	
	void display()
	{
		cout<<"Date: "<<day<<"."<<month<<"."<<year<<";\n";
	}
};
class publication2: public publication
{
	date PublicationDate;
	public:
	void GetData()
	{
		publication::GetData();
		cout<<"\nDate of publication:\n";
		PublicationDate.GetDate();
	}
	void PutData()
	{
		publication::PutData();
		PublicationDate.display();
	}
};
class book: private publication2
{
	int CountOfPages;
	public: book(){}
	void GetData()
	{
		cout<<"Name of a book: ";
		publication2::GetData();
		cout<<"\nCount of pages: ";
		CountOfPages=GetIntFromKeyboard();
	}
	void PutData()
	{
		cout<<"Name of the book: ";
		publication2::PutData();
		cout<<"Count of pages: "<<CountOfPages<<endl;
	}	
};
class tape: private publication2
{
	float duration;
	public: tape(){}
	void GetData()
	{
		cout<<"Name of an audiobook: ";
		publication2::GetData();
		cout<<"\nDuration (minutes): ";
		duration=GetFloatFromKeyboard();
	}
	void PutData()
	{
		cout<<"Name of the audiobook: ";
		publication2::PutData();
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
	cout<<endl<<"--------------------------------------------------\n";
	NewBook.PutData();
	NewAudiobook.PutData();
	return 0;
}
