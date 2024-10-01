/**3. Начните с классов book, tape и publication из упражнения 1. Добавьте базовый класс sales, в котором содержится массив, состоящий из трех значений типа float, куда можно записать общую стоимость проданных книг за последние три месяца. Включите в класс методы getdata() для получения значений стоимости от пользователя и putdata() для вывода этих цифр. Измените классы book и type так, чтобы они стали производными обоих классов: publications и sales. Объекты классов book и type должны вводить и выводить данные о продажах вместе с другими своими данными. Напишите функцию main() для создания объектов классов book и type, чтобы протестировать возможности ввода/вывода данных*/
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
