/*11. По умолчанию форматирование вывода производится по правому краю поля. Можно изменить форматирование текста на левостороннее путем использования манипулятора setiosflags(ios::left) (не беспокойтесь о смысле новой формы записи, встретившейся в манипуляторе). Используйте этот манипулятор вместе с setw() для того, чтобы произвести следующий вывод:
Фамилия   Имя      Адрес        Город
---------------------------------------------------
Петров    Василий  Кленовая 16  Санкт-Петербург
Иванов    Сергей   Осиновая 3   Находка
Сидоров   Иван     Березовая 21 Калининград*/
#include <iostream>
#include <iomanip>
using namespace std;
int main(void)
{
	int n=20;
	cout<<setw(9)<<setiosflags(ios::left)<<"Фамилия"<<setw(n)<<"Имя"<<setw(n)<<"Адрес"<<setw(n)<<"Город"<<endl
	<<setw(80)<<setfill('-')<<'-'
	<<setfill(' ')<<setw(9)<<setiosflags(ios::left)<<"Петров"
	<<setw(n)<<setiosflags(ios::left)<<"Василий"
	<<setw(n)<<setiosflags(ios::left)<<"Кленовая 16"
	<<setw(n)<<setiosflags(ios::left)<<"Санкт-Петербург"<<endl
	<<setw(9)<<setiosflags(ios::left)<<"Иванов"
	<<setw(n)<<setiosflags(ios::left)<<"Сергей"
	<<setw(n)<<setiosflags(ios::left)<<"Осиновая 3"
	<<setw(n)<<setiosflags(ios::left)<<"Находка"<<endl
	<<setw(9)<<setiosflags(ios::left)<<"Сидоров"
	<<setw(n)<<setiosflags(ios::left)<<"Иван"
	<<setw(n)<<setiosflags(ios::left)<<"Березовая 21"
	<<setw(n)<<setiosflags(ios::left)<<"Калининград";
	return 0;
}
