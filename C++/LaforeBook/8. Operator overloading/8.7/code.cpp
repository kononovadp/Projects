/*7. Модифицируйте класс fraction в четырехфункциональном дробном калькуляторе из упражнения 11 главы 6 так, чтобы он использовал перегруженные операции сложения, вычитания, умножения и деления. (Вспомните правила арифметики с дробями в упражнении 12 главы 3 «Циклы и ветвления».) Также перегрузите операции сравнения == и != и используйте их для выхода из цикла, когда пользователь вводит 0/1, 0 и 1 значения двух частей дроби. Вы можете модифицировать и функцию lowterms() так, чтобы она возвращала значение ее аргумента, уменьшенное до несократимой дроби. Это будет полезным в арифметических функциях, которые могут быть выполнены сразу после получения ответа*/
#include <iostream>
#include <ctype.h>
#include <conio.h>
#include <cmath>
#include <cstring>
using namespace std;
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
};
fraction GetFraction()
{
	char ch;
	string input;
	char* FractionPart;
	bool CorrectCharacter;
	int i,j,numerator,denominator=0,CharacterCount;
	while(true)
	{
		CorrectCharacter=false;
		ch=getch();
		if(ch==13)
		{
			if(input.length()==0)			
				input="0/0";
			else
				if(input[input.length()-1]=='/')				
					input+='0';				
				else
				{
					for(i=0,CharacterCount=0; i<input.length(); i++)
						if(input[i]=='/')
							CharacterCount++;
					if(CharacterCount==0)
						input+="/0";
				}
			break;
		}
		else
			if(ch==8 && input.length()>0)
			{
				cout<<"\b \b";
				input.pop_back();
			}
			else
				if(ch=='/')
				{
					if(input.length()==0)
						continue;
					for(i=0,CharacterCount=0; i<input.length(); i++)
						if(input[i]=='/')
							CharacterCount++;
					if(CharacterCount==0)
						CorrectCharacter=true;
				}
				else
					if(isdigit(ch))
					{
						if(ch=='0')
						{
							if((input.length()==1 && input[0]=='0') || (input.length()>3 && input[input.length()-2]=='/' && input[input.length()-1]=='0'))
								CorrectCharacter=false;
							else
								CorrectCharacter=true;
						}
						else
						{
							if((input.length()==1 && input[0]=='0') || (input.length()>=3 && input[input.length()-2]=='/' && input[input.length()-1]=='0'))
								CorrectCharacter=false;
							else
								CorrectCharacter=true;
						}
					}
		if(CorrectCharacter==true)
		{
			input+=ch;
			putchar(ch);
		}
	}
	FractionPart=new char[input.length()];
	for(i=0; input[i]!='/'; i++)
		if(input[i]!='/')
			FractionPart[i]=input[i];
	numerator=atoi(FractionPart);
	FractionPart[0]='\0';
	memset(FractionPart,0,sizeof(FractionPart));
	for(i++,j=0; i<input.length(); i++,j++)
		FractionPart[j]=input[i];
	denominator=atoi(FractionPart);
	delete(FractionPart);
	return fraction(numerator,denominator);
}
int main(void)
{
	char op,ch=0;
	double res;
	fraction fraction1,fraction2,result;
	while(ch!=27)
	{
		cout<<"Fraction 1: ";
		fraction1=GetFraction();
		while(fraction1==0)
		{
			cout<<"\nFraction can not be zero! Try again: ";
			fraction1=GetFraction();
		}
		cout<<"\nFraction 2: ";
		fraction2=GetFraction();
		while(fraction2==0)
		{
			cout<<"\nFraction can not be zero! Try again: ";
			fraction2=GetFraction();
		}
		cout<<"\nOperation: ";
		op=getche();
		while(op!='+' && op!='-' && op!='*' && op!='/' && op!=27)
		{
			cout<<endl<<"press correct operation: ";
			op=getche();
		}
		switch(op)
		{
			case '+': result=fraction1+fraction2; break;
			case '-': result=fraction1-fraction2; break;
			case '*': result=fraction1*fraction2; break;
			case '/': result=fraction1/fraction2; break;
		}
		if(ch!=27)
		{
			cout<<endl;
			fraction1.show();
			cout<<" "<<op<<" ";
			fraction2.show();
			cout<<" = ";
			result.show();
			cout<<"\nPress ENTER to continue or ESC to exit: ";
			ch=getche();
			while(ch!=13 && ch!=27)
			{
				cout<<endl<<"press ENTER or EXIT: ";
				ch=getche();
			}
			cout<<endl;
		}
	}
	return 0;
}
