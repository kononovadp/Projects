//9. Начните с упражнения 7 главы 8 «Перегрузка операций» и перегрузите операторы извлечения (>>) и вставки (<<) для класса frac в нашем калькуляторе с четырьмя действиями. Имейте в виду, что операторы могут связываться в цепочки, поэтому при выполнении действий с дробями понадобится только одно выражение: cin >> frac1 >> op >> frac2;
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
	NewFraction.numerator=numerator;
	NewFraction.denominator=denominator;
	return NewStream;
}
ostream& operator<<(ostream& NewStream,fraction& NewFraction)
{
	cout<<NewFraction.numerator<<"/"<<NewFraction.denominator;
	return NewStream;
}
istream& operator>>(istream& NewStream,char& operation)
{
	cout<<"  ";
	char op=getch();	
	while(op!='+' && op!='-' && op!='*' && op!='/')
		op=getch();
	cout<<op<<"  ";
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
		cout<<"Enter expression like 55/29+35/23.\nPress ENTER after each fraction: ";
		cin>>fraction1>>op>>fraction2;
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
