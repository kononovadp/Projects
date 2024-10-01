/*11. Вернемся к обсуждению денежных строк из упражнения 7. Напишите метод ldtoms() для преобразования числа типа long double в денежную строку, представляющую это число. Для начала вам нужно проверить, что значение long double не очень большое. Мы предполагаем, что вы не будете пытаться преобразовать число, больше чем 9 999 999 999 999 990.00. Затем преобразуем long double в строку (без знака доллара и запятых), хранящуюся в памяти, используя объект ostrstream, как рассматривалось ранее в этой главе. Получившаяся отформатированная строка может быть помещена в буфер, называющийся ustring. Затем вам нужно будет создать другую строку, начинающуюся со знака доллара, далее копируем цифру за цифрой из строки ustring, начиная слева и вставляя запятые через каждые три цифры. Также вам нужно подавлять нули в начале строки. Например, вы должны вывести $3 124.95, а не $0 000 000 000 003 124.95. Не забудьте закончить строку нулевым символом '\0'. Напишите функцию main() для тестирования этой функции путем многократного ввода пользователем чисел типа long double и вывода результата в виде денежной строки.*/
#include <iostream>
#include <strstream>
#include <string>
using namespace std;
string ldtoms(long double d)
{
	int i,j;
	string ustring,res;	
	ostrstream ostrstreamobj;
	ostrstreamobj.precision(3);
	ostrstreamobj.setf(ios::fixed);
	ostrstreamobj<<d;
	ustring=ostrstreamobj.str();
	//ustring.erase(ostrstreamobj.pcount(),ustring.length()-ostrstreamobj.pcount());
	res+='$';
	j=(/*ustring.length()*/ostrstreamobj.pcount()-1)%3;
	for(i=0; i<j; i++)
		res+=ustring[i];
	for(j=0; ustring[i]!='.'; i++,j++)
	{
		if(j%3==0)
			res+=" ";
		res+=ustring[i];
	}
	j=i+4;
	while(i<j)
	{
		res+=ustring[i];
		i++;
	}
	res+="\x00";
	return res;
}
int main(void)
{
	double d;
	char ch;
	string ustring;	
	do
	{
		cout<<"Sum (floating point number): ";
		cin>>d;
		cout<<ustring<<"Result: "<<ldtoms(d);
		cout<<endl<<"enter 1 to continue or 0 to exit: ";
		cin>>ch;
		while(ch!='0' && ch!='1')
		{
			cout<<"enter 0 or 1: ";
			cin>>ch;
		}
	}while(ch!='0');
	return 0;
}
