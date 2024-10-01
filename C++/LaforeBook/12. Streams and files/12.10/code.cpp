/*10.	Добавьте к упражнению 9 проверку на наличие ошибок в операторе извлечения (>>). Но при этом, видимо, потребуется запрашивать сначала первую дробь, затем оператор, затем вторую дробь. Одним выражением, как в упражнении 9, уже будет не обойтись. Вывод сообщений об ошибках сделает работу с программой более понятной:
Введите первую дробь: 5/0
Знаменатель не может быть нулевым!
Введите первую дробь заново: 5/1
Введите оператор (+, -, *, /): +
Введите вторую дробь: одна треть
Ошибка ввода
Введите вторую дробь заново: 1/3
Ответ: 16/3
Продолжить (y/n)? n
Как показывает этот пример, необходимо следить за флагами ошибок ios и за тем, чтобы знаменатель не был равен нулю. Если возникает ошибка, пользователю должно быть предложено ввести данные еще раз*/
#include "../../accessories.h"
class fraction
{
	int numerator,denominator;
	public:
	fraction():numerator(0),denominator(0){}
	fraction(int num,int den):numerator(num),denominator(den){}
	void show(){cout<<numerator<<"/"<<denominator;}
	fraction lowterms(fraction fr) //сокращение дроби
	{
		long tnum,tden,temp,gcd;
		tnum=labs(fr.numerator); //используем неотрицательные
		tden=labs(fr.denominator); //значения (нужен cmath)
		if(tden == 0) //проверка знаменателя на 0	
		{	
			cout<<"\nZero fraction can't be used!";
			exit(1);
		}
		else
			if(tnum==0) //проверка числителя на 0			
				return fraction(0,1);
		while(tnum!=0) //нахождение наибольшего общего делителя
		{
			if(tnum<tden) //если числитель больше знаменателя,
			{
				temp=tnum;
				tnum=tden;
				tden=temp; //меняем их местами
			}
			tnum=tnum-tden; //вычитание
		}
		gcd=tden; //делим числитель и знаменатель на
		return fraction(fr.numerator/gcd,fr.denominator/gcd);
	}
	bool operator==(int zero)
	{
		if(numerator==zero || denominator==zero)
			return true;
		return false;
	}
	bool operator!=(int zero)
	{
		if(numerator!=zero && denominator!=zero)
			return true;
		return false;
	}
	fraction operator+(fraction fraction2)
	{
		if(*this==0 || fraction2==0)
		{
			cout<<"\nA zero fraction can't be used!";
			return fraction(0,0);
		}
		return lowterms(fraction(numerator*fraction2.denominator+denominator*fraction2.numerator,denominator*fraction2.denominator));		
	}
	fraction operator-(fraction fraction2)
	{
		if(*this==0 || fraction2==0)
		{
			cout<<"\nA zero fraction can't be used!";
			return fraction(0,0);
		}
		return lowterms(fraction(numerator*fraction2.denominator-denominator*fraction2.numerator,denominator*fraction2.denominator));
	}
	fraction operator*(fraction fraction2)
	{
		if(*this==0 || fraction2==0)
		{
			cout<<"\nA zero fraction can't be used!";
			return fraction(0,0);
		}
		return lowterms(fraction(numerator*fraction2.numerator,denominator*fraction2.denominator));
	}
	fraction operator/(fraction fraction2)
	{
		if(*this==0 || fraction2==0)
		{
			cout<<"\nA zero fraction can't be used!";
			return fraction(0,0);
		}
		return lowterms(fraction(numerator*fraction2.denominator,denominator*fraction2.numerator));
	}
	friend istream& operator>>(istream& NewStream,fraction& NewFraction);
	friend istream& operator>>(istream& NewStream,char& operation);
	friend ostream& operator<<(ostream& NewStream,fraction& NewFraction);
	friend ostream& operator<<(ostream& NewStream,char& operation);
};
istream& operator>>(istream& NewStream,fraction& NewFraction)
{
	bool CorrectInput=false;
	while(!CorrectInput)
	{
		CorrectInput=true;
		cin>>NewFraction.numerator;
		if(!cin.good())
			CorrectInput=false;
		cin.clear();
		cin.ignore(1000,'/');
		cin>>NewFraction.denominator;
		if(!cin.good())
			CorrectInput=false;
		cin.clear();
		cin.ignore(1000,'\n');
		if(!CorrectInput)
			cout<<"Incorrect fraction, try again: ";
		else
			if(NewFraction.numerator<=0 || NewFraction.denominator<=0)
			{
				CorrectInput=false;
				cout<<"Numerator or denominator mustn't be less than one, try again: ";
			}
	}
	return NewStream;
}
ostream& operator<<(ostream& NewStream,fraction& NewFraction)
{
	cout<<NewFraction.numerator<<"/"<<NewFraction.denominator;
	return NewStream;
}
istream& operator>>(istream& NewStream,char& operation)
{	
	char op=getch();	
	while(op!='+' && op!='-' && op!='*' && op!='/')
		op=getch();
	cout<<op;
	operation=op;
	return NewStream;
}
ostream& operator<<(ostream& NewStream,char& operation)
{
	cout<<"  ";
	putchar(operation);
	cout<<"  ";
	return NewStream;
}
int main(void)
{
	char op,ch=0;
	double res;
	fraction fraction1,fraction2,result;
	while(ch!='0')
	{
		cout<<"Fraction 1: ";
		cin>>fraction1;
		cout<<"Operation: ";
		cin>>op;
		cout<<"\nFraction 2: ";
		cin>>fraction2;
		switch(op)
		{
			case '+': result=fraction1+fraction2; break;
			case '-': result=fraction1-fraction2; break;
			case '*': result=fraction1*fraction2; break;
			case '/': result=fraction1/fraction2; break;
		}
		cout<<"\nYou entered: "<<fraction1<<op<<fraction2<<"  =  "<<result<<endl;
		cout<<"Press 1 to start again or 0 to exit: ";		
		ch=getch();
		while(ch!='0' && ch!='1')		
			ch=getch();
		putchar(ch);
		putchar('\n');
	}
	return 0;
}
