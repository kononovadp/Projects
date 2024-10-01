//7. Другим подходом к добавлению файлового потока к объекту является превращение самого этого потока в статическую компоненту объекта. Для чего это делается? Ну, часто бывает проще представить себе поток связанным с классом в целом, а не с отдельными его объектами. К тому же, гораздо правильнее открывать поток только один раз для записи и чтения всего, что нужно. Например, мы открываем файл и начинаем последовательное чтение. Функция чтения всякий раз возвращает данные для следующего объекта. Указатель файла сдвигается при этом автоматически, так как между чтениями файл мы не закрываем. Перепишите программы из упражнений 4 и 6 таким образом, чтобы использовать объект fstream в качестве статической компоненты класса name. Функционирование программы должно сохраниться. Напишите статическую функцию для открытия потока и еще одну — для сбрасывания файлового указателя и установки его на начало файла. Эту же функцию можно использовать для чтения всего файла.
#include "../../accessories.h"
class name
{
	string EmployeeName,patronymic,surname;
	unsigned long id;
	static fstream file;
	public:	
	/*name()
	{
				
	}
	~name()
	{
		//file.close();
		//cout<<"The file employees.txt was closed";
	}*/
	void WriteNameToFile()
	{
		char ch=0,ExcludedCharacters[1];
		//file.open("employees.txt",ios::in | ios::out | ios::app);
		ExcludedCharacters[0]=' ';
		cout<<"Name: ";
		EmployeeName=GetKeyboardInputAsString(ExcludedCharacters);
		cout<<"\nPatronymic: ";
		patronymic=GetKeyboardInputAsString(ExcludedCharacters);
		cout<<"\nSurname: ";
		surname=GetKeyboardInputAsString(ExcludedCharacters);
		cout<<"\nID: ";
		id=GetLongFromKeyboard();
		cout<<endl;
		file<<EmployeeName<<" "<<patronymic<<" "<<surname<<" "<<id<<endl;
		file.clear();
		file.seekg(0,ios_base::beg);
	}
	void ReadNameFromFile(unsigned long RequiredID)
	{
		file>>EmployeeName>>patronymic>>surname>>id;		
		while(!file.eof())
		{
			if(id==RequiredID)
			{
				cout<<"\nRecord found: "<<EmployeeName<<" "<<patronymic<<" "<<surname<<" "<<id<<endl;
				file.clear();
				file.seekg(0,ios_base::beg);
				return;
			}
			file>>EmployeeName>>patronymic>>surname>>id;
		}		
		cout<<"\nRecord with the ID "<<RequiredID<<" wasn't found\n";
		file.clear();
		file.seekg(0,ios_base::beg);
	}
	static void OpenFile()
	{
		file.open("employees.txt",ios::in | ios::out | ios::app);
	}
	static void CloseFile()
	{
		file.close();
	}
};
fstream name::file;
int main(void)
{	
	char ch=0;
	unsigned long RequiredID;
	name::OpenFile();
	while(ch!='0')
	{
		cout<<"Press 1 to ADD record about an employee or 0 to exit: ";
		ch=getch();
		while(ch!='0' && ch!='1')		
			ch=getch();
		cout<<ch<<endl;
		if(ch=='1')
		{
			name MyName;
			MyName.WriteNameToFile();			
		}
	}
	ch=0;
	while(ch!='0')
	{
		cout<<"Press 1 to READ record about an employee or 0 to exit: ";
		ch=getch();
		while(ch!='0' && ch!='1')		
			ch=getch();
		cout<<ch<<endl;
		if(ch=='1')
		{
			cout<<"Required ID: ";
			RequiredID=GetLongFromKeyboard();
			name MyName;
			MyName.ReadNameFromFile(RequiredID);
		}
	}
	name::CloseFile();
	return 0;
}
