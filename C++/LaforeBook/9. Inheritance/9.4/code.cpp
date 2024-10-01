/*4. Предположим, что издатель из упражнений 1 и 3 решил добавить к своей продукции версии книг на компьютерных дисках для тех, кто любит читать книги на своих компьютерах. Добавьте класс disk, который, как book и type, является производным класса publication. Класс disk должен включать в себя те же функции, что и в других классах. Полем только этого класса будет тип диска: CD или DVD. Для хранения этих данных вы можете ввести тип enum. Пользователь должен выбрать подходящий тип, набрав на клавиаtype с или d*/
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
class sales
{
	float prices[3];
	public: sales(){}
	void GetData()
	{		
		for(int i=0; i<3; i++)
		{
			cout<<"\nPrice for month "<<i+1<<": ";
			prices[i]=GetFloatFromKeyboard();
		}
	}
	void PutData()
	{
		for(int i=0; i<3; i++)
			cout<<"Price for month "<<i+1<<": "<<prices[i]<<";\n";
	}
};
class book: private publication,private sales
{
	int CountOfPages;
	public: book(){}
	void GetData()
	{
		cout<<"Name of a book: ";
		publication::GetData();
		sales::GetData();
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
class tape: private publication,private sales
{
	float duration;
	public: tape(){}
	void GetData()
	{
		cout<<"Name of an audiobook: ";
		publication::GetData();
		sales::GetData();
		cout<<"\nDuration (minutes): ";
		duration=GetFloatFromKeyboard();
	}
	void PutData()
	{
		cout<<"Name of the audiobook: ";
		publication::PutData();
		sales::PutData();
		cout<<"Duration (minutes): "<<duration<<endl;
	}
};
class DiscBook:private publication
{
	enum DiscTypes{CD='c',DVD='d'};
	char DiscType;
	public:
	DiscBook(){}
	void GetData()
	{
		cout<<"Name of an compact disc book: ";
		publication::GetData();
		cout<<"\nDisk type (press \"c\" to choose CD or \"d\" to choose DVD: ";
		char ch=getch();
		while(ch!=27 && ch!=CD && ch!=DVD)
			ch=getch();
		if(ch==27)
			exit(0);
		if(ch==CD)
			cout<<"CD";
		else
			cout<<"DVD";
		DiscType=ch;
	}
	void PutData()
	{
		cout<<"Disc type: ";
		if(DiscType==CD)
			cout<<"CD";
		else
			cout<<"DVD";
	}
};
int main(void)
{
	InitOutputOfFloatingPointNumbers();
	book NewBook;
	tape NewAudiobook;
	DiscBook NewDiscBook;
	NewBook.GetData();
	cout<<endl;
	NewAudiobook.GetData();	
	cout<<endl;
	NewDiscBook.GetData();
	cout<<endl<<"-----------------------------\n";
	NewBook.PutData();
	NewAudiobook.PutData();
	NewDiscBook.PutData();
	return 0;
}
