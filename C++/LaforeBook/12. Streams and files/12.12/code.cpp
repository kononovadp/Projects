/*12. К программе EMPL_IO из этой главы добавьте возможность поиска работника в списке, хранящемся в файле, по номеру. При нахождении совпадения нужно вывести данные об этом работнике на экран. Пользователь должен иметь возможность запустить функцию поиска нажатием клавиши 'f'. У пользователя спрашивается номер работника. Подумайте над вопросом, какой должна быть эта функция — статической, виртуальной или какой-то еще? Поиск и вывод на экран не должны пересекаться с данными в памяти.
ПРИМЕЧАНИЕ
Не пытайтесь прочитать файл, созданный программой EMPL_IO. Классы в программах разные благодаря методу find() в новой программе, и проблемы, которые могут возникнуть в случае, если их данные смешаются, уже обсуждались в этой главе. Вам может понадобиться включить параметр RTTI в компиляторе. Чтобы не возникало вопросов, следуйте указаниям, данным в приложении В «Microsoft Visual C++» и в приложении Г «Borland C++ Builder» (выбирайте то, что для вас актуальней).*/
//empl_io.cpp
//Файловый ввод/вывод объектов employee
//Поддержка объектов неодинаковых размеров
#include "../../accessories.h"
#include <typeinfo> //для typeid()
const int LEN=32; //Максимальная длина фамилий
const int MAXEMPL=100; //максимальное число работников
enum employee_type {tmanager,tscientist,tlaborer};
class employee
{
	char name[LEN]; //фамилия работника
	unsigned long number; //номер работника
	static int n; //текущее число работников
	static employee* arrap[]; //массив указателей на класс работников
	public:
	employee(){}
	employee(char* NewName,unsigned long NewNumber): number(NewNumber)
	{
		strcpy(name,NewName);
	}
	unsigned long GetNumber(){return number;}
	virtual void getdata()
	{
		cout<<"Surname: ";cin>>name; 
		cout<<"ID: "; cin>>number;
	}
	virtual void putdata()
	{
		cout<<"Surname: "<<name<<endl<<"Number: "<<number<<endl;
	}
	virtual employee_type get_type(); //получить тип
	static void add(); //добавить работника
	static void display(); //вывести данные обо всех
	static void read(); //чтение из файла
	static void write(); //запись в файл
	static void AddRandomEmployees();
	static void FindInFile();
};
int employee::n; //статические переменные: текущее число работников
employee* employee::arrap[MAXEMPL]; //массив указателей на класс работников
class manager: public employee
{
	char title[LEN]; //титул ("вице-президент" и т. п.)
	double dues; //Налоги гольф-клуба
	public:
	manager(){}
	manager(char* NewName,unsigned long NewNumber,char* NewTitle,double NewDues):employee(NewName,NewNumber),dues(NewDues)
	{
		strcpy(title,NewTitle);
	}
	char* GetTitle(){return title;}
	double GetDues(){return dues;}
	void getdata()
	{
		employee::getdata();
		cout<<"Title: "; cin>>title;
		cout<<"Dues: "; cin>>dues;
	}
	void putdata()
	{
		employee::putdata();
		cout<<"Title: "<<title<<endl<<"Dues: "<<dues<<endl;
	}
};
class scientist: public employee
{
	int pubs; //число публикаций
	public:
	scientist(){}
	scientist(char* NewName,unsigned long NewNumber,int NewPubs):employee(NewName,NewNumber),pubs(NewPubs){}
	int GetPubs(){return pubs;}
	void getdata()
	{
		employee::getdata();
		cout<<"Count of publications: "; cin>>pubs;
	}
	void putdata()
	{
		employee::putdata();
		cout<<"Count of publications: "<<pubs<<endl;
	}
};
class laborer: public employee
{
	public: laborer(){}
	laborer(char* NewName,unsigned long NewNumber):employee(NewName,NewNumber){}
};
void employee::add()
{
	cout<<"1. Manager;\n"
		  "2. Scientist;\n"
		  "3. Laborer;\n"
		  "Your choice: ";
	char ch=getch();	
	while(ch<'1' || ch>'3')
		ch=getch();
	cout<<ch<<endl;
	switch(ch)
	{
		case '1': arrap[n]=new manager; break;
		case '2': arrap[n]=new scientist; break;
		case '3': arrap[n]=new laborer; break;
	}
	arrap[n++]->getdata();
}
void employee::display()
{
	for(int j=0; j<n; j++)
	{
		cout<<(j+1)<<". Type: ";
		switch(arrap[j]->get_type()) //вывести тип 
		{
			case tmanager: cout<<"manager\n"; break;
			case tscientist: cout<<"scientist\n"; break;
			case tlaborer:   cout<<"laborer\n"; break;
			default: cout<<"undefined type\n";
		}
		arrap[j]->putdata();
		cout<<"--------------------------------------------------\n";
	}
}
employee_type employee::get_type()
{
	if(typeid(*this)==typeid(manager))
	   return tmanager;
	if(typeid(*this)==typeid(scientist))
	   return tscientist;
	if(typeid(*this)==typeid(laborer))
	   return tlaborer;
	cerr<<"Incorrect type of employee\n"; exit(1);
	return tmanager;
}
void employee::write()
{
	int size;	
	ofstream ouf; //открыть ofstream в двоичном виде
	employee_type etype; //тип каждого объекта employee
	ouf.open("employees.dat",ios::trunc | ios::binary);
	if(!ouf)
	{
		cout<<"Unable to open file\n";
		return;
	}
	for(int j=0; j<n; j++)
	{
		etype=arrap[j]->get_type();
		ouf.write((char*)&etype,sizeof(etype));
		switch(etype)
		{
			case tmanager: size=sizeof(manager); break;
			case tscientist: size=sizeof(scientist); break;
			case tlaborer: size=sizeof(laborer); break;
		}
		ouf.write((char*)(arrap[j]),size);
		if(!ouf)
		{
			cout<<"Unable to write data\n";
			return;
		}
	}
	cout<<n<<" employees were successfully written to the file\n";
}
void employee::read()
{
	employee_type etype;
	ifstream inf;
	manager* NewManager;
	scientist* NewScientist;
	laborer* NewLaborer;
	inf.open("employees.dat",ios::binary);
	if(!inf)
	{
		cout<<"Unable to open file\n";
		return;
	}
	for(int i=0; i<n; i++)
		delete arrap[i];
	n=0; //В памяти работников нет
	while(true)
	{
		inf.read((char*)&etype,sizeof(etype));
		if(inf.eof())
		   break;
		if(!inf) //ошибка чтения типа
		{
			cout<<"Unable to read type of a record\n";
			return;
		}
		switch(etype)
		{ //создать нового работника корректного типа
			case tmanager:
				NewManager=new manager;
				inf.read((char*)NewManager,sizeof(manager));
				arrap[n++]=new manager(NewManager->name,NewManager->number,NewManager->GetTitle(),NewManager->GetDues());
				delete NewManager;
				break;
			case tscientist:
				NewScientist=new scientist;
				inf.read((char*)NewScientist,sizeof(scientist));
				arrap[n++]=new scientist(NewScientist->name,NewScientist->number,NewScientist->GetPubs());
				delete NewScientist;
				break;
			case tlaborer:
				NewLaborer=new laborer;
				inf.read((char*)NewLaborer,sizeof(laborer));
				arrap[n++]=new laborer(NewLaborer->name,NewLaborer->number);
				break;
			default: cout<<"Undefined type in file\n"; return;
		}
	}
	cout<<n<<" employees were read into the memory\n";
}
void employee::AddRandomEmployees()
{
	char* alphabet=new char[26],*NewName,*NewTitle;
	int i,j,RandomLength,RandomCountOfEmployees=GetRandomInt(5,20);
	for(i='a',j=0; i<='z'; i++,j++)
		alphabet[j]=i;
	for(i=0; i<RandomCountOfEmployees; i++)
	{
		RandomLength=GetRandomInt(5,15);
		NewName=new char[RandomLength];
		ShuffleArrayOfCharacters(alphabet);
		for(j=0; j<RandomLength; j++)
			NewName[j]=alphabet[j];
		switch(GetRandomInt(0,3))
		{
			case 0:
				RandomLength=GetRandomInt(5,15);
				NewTitle=new char[RandomLength];
				ShuffleArrayOfCharacters(alphabet);
				for(j=0; j<RandomLength; j++)
					NewTitle[j]=alphabet[j];
				arrap[n++]=new manager(NewName,GetRandomInt(1,1000),NewTitle,GetRandomDouble(100,10000));
				delete NewTitle;
				break;
			case 1:
				arrap[n++]=new scientist(NewName,GetRandomInt(1,1000),GetRandomInt(1,100));
				break;
			case 2:
				arrap[n++]=new laborer(NewName,GetRandomInt(1,1000));
				break;
			default: cout<<"Undefined choice\n"; break;
		}
		delete NewName;
	}
	delete alphabet;
	cout<<RandomCountOfEmployees<<" random employees were added to the memory\n";
}
void employee::FindInFile()
{
	ifstream inf;
	inf.open("employees.dat",ios::binary);	
	if(!inf)
	{
		cout<<"Unable to open file\n";
		return;
	}
	employee_type etype;
	manager* NewManager;
	scientist* NewScientist;
	laborer* NewLaborer;
	employee* FoundEmployee;
	cout<<"ID: ";
	int count=0,NumberFromFile,NumberFromKeyboard=GetIntFromKeyboard();
	cout<<endl;
	while(true)
	{
		inf.read((char*)&etype,sizeof(etype));
		if(inf.eof())
		   break;	
		if(!inf)
		{
			cout<<"Unable to read type of a record\n";
			return;
		}
		switch(etype)
		{
			case tmanager:
				NewManager=new manager;
				inf.read((char*)NewManager,sizeof(manager));
				NumberFromFile=NewManager->number;
				break;
			case tscientist:
				NewScientist=new scientist;
				inf.read((char*)NewScientist,sizeof(scientist));
				NumberFromFile=NewScientist->number;
				break;
			case tlaborer:
				NewLaborer=new laborer;
				inf.read((char*)NewLaborer,sizeof(laborer));
				NumberFromFile=NewLaborer->number;
				break;
			default: cout<<"undefined type\n"; NumberFromFile=-1; break;
		}		
		if(NumberFromFile==NumberFromKeyboard)
		{
			count++;
			cout<<count<<". Type: ";
			switch(etype)
			{
				case tmanager:
					FoundEmployee=new manager(NewManager->name,NewManager->number,NewManager->GetTitle(),NewManager->GetDues());
					cout<<"manager\n";
					break;
				case tscientist:
					FoundEmployee=new scientist(NewScientist->name,NewScientist->number,NewScientist->GetPubs());
					cout<<"scientist\n";
					break;
				case tlaborer:
					FoundEmployee=new laborer(NewLaborer->name,NewLaborer->number);
					cout<<"laborer\n";
					break;				
			}
			FoundEmployee->putdata();
			delete FoundEmployee;
			cout<<"--------------------------------------------------\n";			
		}
		switch(etype)
		{
			case tmanager: delete NewManager; break;
			case tscientist: delete NewScientist; break;
			case tlaborer: delete NewLaborer; break;
		}
	}
	if(count==0)
		cout<<"The employee with the number "<<NumberFromKeyboard<<" wasn't found\n";
}
int main()
{
	char ch=0;
	InitFloatingPointAndRandomNumbers();
	while(ch!='7')
	{
		cout<<"1. Add random employees\n"
			  "2. Add a new employee;\n"
			  "3. Show information about all employees;\n"
			  "4. Write all data to the file;\n"
			  "5. Read all data from the file;\n"
			  "6. Find an employee in the file by number;\n"
			  "7. Exit;\n"
			  "Your choice: ";
		ch=getch();
		while(ch<'1' || ch>'7')
			ch=getch();
		cout<<ch<<endl;
		switch(ch)
		{
			case '1': employee::AddRandomEmployees(); break;
			case '2': employee::add(); break;
			case '3': employee::display(); break;
			case '4': employee::write(); break;
			case '5': employee::read(); break;
			case '6': employee::FindInFile(); break;
		}
		cout<<"==================================================\n";
	}
	return 0;
}