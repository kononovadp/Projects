//2. Напишите main(), где создавался бы массив указателей на класс publication. Это очень похоже на то, что мы делали в текущей главе на примере VIRTPERS. В цикле запрашивайте у пользователя данные о конкретной книге или кассете, используйте new для создания нового объекта book или tape. Сопоставляйте указатель в массиве с объектом. Когда пользователь закончит ввод исходных данных, выведите результат для всех введенных книг и кассет, используя цикл for и единственное выражение pubarr[j]->putdata(); для вывода данных о каждом объекте из массива.
#include "../../accessories.h"
class publication
{
	string name;
	float price;
	public:
	publication(){}
	virtual void GetData()
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
	virtual void PutData()
	{
		cout<<name<<"; price: "<<price<<";\n";
	}
};
class book: public publication
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
class tape: public publication
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
	int i,ArraySize=3;
	char ch=0;
	publication** publications=new publication*[ArraySize];
	for(i=0; i<ArraySize && ch!='0'; i++)
	{
		cout<<"1. Add new book;\n2. Add new tape;\n3. Exit.\nYour choice: ";
		ch=getch();
		while(ch<'1' || ch>'3')
			ch=getch();
		cout<<ch<<endl;
		if(ch=='3')
			break;		
		switch(ch)
		{
			case '1': publications[i]=new book(); break;
			case '2': publications[i]=new tape(); break;
		}
		publications[i]->GetData();
		cout<<endl;
		if(i==ArraySize-1)
			continue;
		cout<<"Press 1 to add new item to the library or 0 to exit: ";
		ch=getch();
		while(ch!='0' && ch!='1')
			ch=getch();
		cout<<ch<<endl;
	}
	cout<<"----------------------------------------\n";	
	for(ArraySize=i,i=0; i<ArraySize; i++)
		publications[i]->PutData();
	return 0;
}
