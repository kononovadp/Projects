//*1. Пусть имеется та же издательская компания, которая описана в упражнении 1 главы 9, которая продает и книги, и аудио версии печатной продукции. Как и в том упражнении, создайте класс publication, хранящий название (фактически, строку) и цену (типа float) публикации. Создайте два порожденных класса: book, в котором происходит изменение счетчика страниц (типа int), и tape, в котором происходит изменение счетчика записанных на кассету минут. Каждый из классов должен иметь метод getdata(), запрашивающий информацию у пользователя, и putdata() для вывода данных на экран.
#include "../../accessories.h"
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
	InitFloatingPointAndRandomNumbers();
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