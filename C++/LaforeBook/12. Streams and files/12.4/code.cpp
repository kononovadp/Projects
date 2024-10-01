//4. В цикле запрашивайте у пользователя данные, состоящие из имени, отчества, фамилии и номера работника (типа unsigned long). Затем осуществите форматированный вывод в объект ofstream с помощью оператора вставки (<<). Не забывайте, что строки данных должны оканчиваться пробелами или другими разделителями. Когда пользователь сообщит об окончании ввода, закройте объект ofstream, откройте объект ifstream, прочитайте и выведите на экран все данные из файла, после чего завершите программу.
#include "../../accessories.h"
int main(void)
{
	char ch=0,ExcludedCharacters[1];
	string name,patronymic,surname;
	unsigned long id;
	ofstream WritingFile("employees.txt",ios::app);
	ExcludedCharacters[0]=' ';
	while(ch!='0')
	{
		cout<<"Name: ";
		name=GetKeyboardInputAsString(ExcludedCharacters);
		cout<<"\nPatronymic: ";
		patronymic=GetKeyboardInputAsString(ExcludedCharacters);
		cout<<"\nSurname: ";
		surname=GetKeyboardInputAsString(ExcludedCharacters);
		cout<<"\nID: ";
		id=GetLongFromKeyboard();
		WritingFile<<name<<" "<<patronymic<<" "<<surname<<" "<<id<<endl;
		cout<<"\nPress 1 to start again or 0 to exit: ";		
		ch=getch();
		while(ch!='0' && ch!='1')		
			ch=getch();
		cout<<ch<<endl;
	}
	WritingFile.close();
	cout<<"-------------------------EMPLOYEES:-------------------------\n";
	ifstream ReadingFile("employees.txt");
	ReadingFile>>name>>patronymic>>surname>>id;
	while(!ReadingFile.eof())
	{		
		cout<<name<<" "<<patronymic<<" "<<surname<<" "<<id<<endl;
		ReadingFile>>name>>patronymic>>surname>>id;
	}
	ReadingFile.close();
	return 0;
}
