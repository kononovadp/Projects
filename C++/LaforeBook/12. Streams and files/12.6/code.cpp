//6. Создайте класс name, включающий в себя данные из упражнения 4 (имя, отчество, фамилия и номер работника). Создайте методы для этого класса, осуществляющие файловый ввод/вывод данных указанного класса (с использованием ofstream и ifstream). Используйте форматирование данных (операторы << и >>). Функции чтения и записи должны быть независимыми: в них необходимо внести выражения для открытия соответствующего потока, а также чтения и записи данных. Функция записи может просто добавлять данные в конец файла. Функции чтения потребуется некоторое условие выборки конкретной записи. Можно вызывать ее с параметром, представляющим собой номер записи. Но как, даже зная, какую запись следует читать, функция найдет ее? Использование seekg() тут не поможет, так как при форматированном вводе / выводе все записи имеют разные размеры (в зависимости от количества символов в строке и разрядности числа). Поэтому придется просто считывать записи подряд, пока не будет найдена нужная. В main() вставьте вызовы описанных выше методов, чтобы пользователь мог ввести данные с их последующей записью в файл. Затем программа должна выполнить чтение и продемонстрировать результаты этого чтения на экране.
#include "../../accessories.h"
class name
{
	string name,patronymic,surname;
	unsigned long id;
	public:
	void WriteNameToFile()
	{
		char ch=0,ExcludedCharacters[1];
		ExcludedCharacters[0]=' ';
		ofstream WritingFile("employees.txt",ios::app);
		cout<<"Name: ";
		name=GetKeyboardInputAsString(ExcludedCharacters);
		cout<<"\nPatronymic: ";
		patronymic=GetKeyboardInputAsString(ExcludedCharacters);
		cout<<"\nSurname: ";
		surname=GetKeyboardInputAsString(ExcludedCharacters);
		cout<<"\nID: ";
		id=GetLongFromKeyboard();
		cout<<endl;
		WritingFile<<name<<" "<<patronymic<<" "<<surname<<" "<<id<<endl;
		WritingFile.close();
	}
	void ReadNameFromFile(unsigned long RequiredID)
	{
		ifstream ReadingFile("employees.txt");
		ReadingFile>>name>>patronymic>>surname>>id;
		while(!ReadingFile.eof())
		{
			if(id==RequiredID)
			{
				cout<<"\nRecord found: "<<name<<" "<<patronymic<<" "<<surname<<" "<<id<<endl;
				ReadingFile.close();
				return;
			}
			ReadingFile>>name>>patronymic>>surname>>id;
		}		
		cout<<"\nRecord with the ID "<<RequiredID<<" wasn't found\n";
		ReadingFile.close();
	}
};
int main(void)
{
	name MyName;
	char ch=0;
	unsigned long RequiredID;
	while(ch!='0')
	{
		cout<<"Press 1 to ADD record about an employee or 0 to exit: ";
		ch=getch();
		while(ch!='0' && ch!='1')		
			ch=getch();
		cout<<ch<<endl;
		if(ch=='1')		
			MyName.WriteNameToFile();
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
			MyName.ReadNameFromFile(RequiredID);
		}
	}
	return 0;
}
