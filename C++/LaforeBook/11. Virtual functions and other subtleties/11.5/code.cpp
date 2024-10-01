//5. Взяв за основу программу из упражнения 1 этой главы, добавьте метод типа bool, называющийся isOveersize(), к классам book и tape. Допустим, книга, в которой больше 800 страниц, или кассета со временем проигрывания более 90 минут, будут считаться объектами с превышением размера. К этой функции можно обращаться из main(), а результат ее работы выводить в виде строки «Превышение размера!» для соответствующих книг и кассет. Допустим, объекты классов book и tape должны быть доступны через указатели на них, хранящиеся в массиве типа publication. Что в этом случае вам нужно добавить в базовый класс publication? Вы можете привести примеры компонентов этого базового класса?
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
	virtual bool IsOversize(){return false;}
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
	bool IsOversize()
	{
		if(CountOfPages>800)
			return true;
		return false;
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
	bool IsOversize()
	{
		if(duration>90)
			return true;
		return false;
	}
};
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	int i,ArraySize=5;
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
	cout<<"==================================================\n";	
	for(ArraySize=i,i=0; i<ArraySize; i++)
	{
		publications[i]->PutData();
		if(publications[i]->IsOversize())
			cout<<"Oversize!!!\n";
		cout<<"--------------------------------------------------\n";
	}
	return 0;
}
