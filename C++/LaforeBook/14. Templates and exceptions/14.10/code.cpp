/*10. Есть разные мнения на тему того, когда целесообразно использовать механизм исключений. Обратимся к программе ENGLERR из главы 12 «Потоки и файлы». Надо ли в виде исключений оформлять ошибки, которые делает пользователь при вводе данных? Для этого упражнения будем считать, что надо. Добавьте класс исключений к классу Distance в указанной программе (см. также примеры XDIST и XDIST2 в этой главе). Сгенерируйте исключения во всех местах, где ENGLERR выводила сообщение об ошибке. Для выявления конкретной причины исключения (вместо дюймов введены какие-то символы, значение дюймов выходит за область допустимых значений и т. д.). Кроме того, исключения должны генерироваться в качестве реакции на ошибки, возникающие в функции isFeet() (ничего не было введено, введено слишком много разрядов значений, введен символ вместо числа, число выходит за область допустимых значений). Вопрос к вам: если функция isFeet() сгенерировала исключение, может ли она оставаться независимой?
Можно зациклить блок повторных попыток и блок-ловушку (создать цикл do), чтобы после обработки исключения программа продолжала работу, предлагая пользователю повторно ввести данные.
Если еще немного подумать, то может возникнуть желание генерировать исключение в конструкторе с двумя аргументами (в том случае, если программист инициализирует Distance значениями, выходящими за область допустимых)*/
//englerr.cpp
//контроль ввода данных для класса английских расстояний
#include <iostream>
#include <string>
#include <cstdlib> //для atoi(), atof()
#include <conio.h>
using namespace std;
int isFeet(string);
bool IsInches(string inches);
class Distance
{
	private:
	int feet;
	float inches;
	public:
	class error
	{
		string message;
		public:
		error(string NewMessage):message(NewMessage){}
		void display(){cout<<message<<endl;}
	};
	Distance()
	{
		feet=0;
		inches=0.0;
	}
	Distance(int ft,float in)
	{		
		if(ft<-999.0 || ft>999.0)
			throw(Distance::error("\nFeet must be an integer<1000!"));
		if(in<0.0 || in>=12.0)
			throw(Distance::error("\nInches must be between 0.0 and 11.99"));
		feet=ft;
		inches=in;
	}
	void showdist(){cout<<feet<<"\'-"<<inches<<'\"'<<endl; }
	void getdist(); //запросить длину у пользователя
};
void Distance::getdist() //получение длины от пользователя
{
	string instr; //для входной строки
	while(true) //цикл, пока футы не будут правильными
	{
		try
		{
			cout<<"Feet: ";
			cin.unsetf(ios::skipws); //не пропускать разделители
			cin>>instr; //получить футы как строку
			cin.clear();
			cin.ignore(10,'\n'); //съесть символы, включая разделитель строк			
			if(isFeet(instr)) //правильное значение? да
			{
				feet=atoi(instr.c_str()); //перевести значение в целочисленное
				break; //выход из цикла 'while'
			}
		}
		catch(Distance:: error NewError){NewError.display();}
		//cout<<"Feet must be an integer<1000\n";
	}
	instr="";
	while(true)
	{
		try
		{
			cout<<"Inches: ";
			cin.unsetf(ios::skipws); //не пропускать разделители
			cin>>instr;
			cin.clear();
			cin.ignore(10,'\n'); //съесть символы, включая разделитель строк
			if(IsInches(instr))
			{
				inches=stod(instr);
				if(inches>=12.0 || inches<0.0)
					throw(Distance::error("Inches must be between 0.0 and 11.99"));
				else
					break;
			}
		}
		catch(Distance:: error NewError){NewError.display();}
	}
}
int isFeet(string str) //true если введена строка
{ //с правильным значением футов
	int slen=str.size(); //получить длину
	if(slen==0 || slen>5) //не было или слишком много данных	
		throw(Distance::error("Incorrect length of input!"));		
	for(int j=0; j<slen; j++) //проверить каждый символ
		if((str[j]<'0' || str[j]>'9') && str[j]!='-') //если не цифра или минус
			throw(Distance::error("Incorrect feet!"));
	double n=atof(str.c_str()); //перевод в double 
	if(n<-999.0 || n>999.0) //вне допустимых значений?
		throw(Distance::error("Feet must be an integer<1000!"));
	return 1; //правильные футы
}
bool IsInches(string inches)
{
	if(!isdigit(inches[0]) || !isdigit(inches[inches.length()-1]) || !inches.length())
		throw(Distance::error("Incorrect inches!"));
	int i,n,PointPos=inches.find('.');
	if(!PointPos)
		PointPos=inches.length();
	if(PointPos)
		for(n=0,i=0; i<inches.length(); i++)
			if(inches[i]=='.')
				n++;
	if(n>1)
		throw(Distance::error("Incorrect inches!"));
	for(i=1; i<PointPos; i++)
		if(!isdigit(inches[i]))
			throw(Distance::error("Incorrect inches!"));
	for(i++; i<inches.length(); i++)
		if(!isdigit(inches[i]))
			throw(Distance::error("Incorrect inches!"));
	return true;
}
int main()
{
	Distance d;
	char ans;
	do
	{
		d.getdist();
		cout<<"Didtance=";
		d.showdist();
		cout<<"Press ENTER to continue or ESC to exit: ";
		ans=getch();
		while(ans!=13 && ans!=27)
			ans=getch();
		cout<<endl;
		//cout<<"\nWould you like to continue (y/n)? ";
		//cin>>ans;
		//cin.ignore(10, '\n');
	}while(ans!=27);//while(ans != 'n');
	int feet=104;
	float inches=101;
	cout<<"Trying to create a distance of "<<feet<<" feet and "<<inches<<" inches... ";
	try
	{
		Distance d(feet,inches);
	}
	catch(Distance:: error NewError){NewError.display();}
	return 0;
}