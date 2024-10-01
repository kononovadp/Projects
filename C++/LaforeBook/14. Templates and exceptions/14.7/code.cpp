//7. За основу возьмите класс frac и калькулятор с четырьмя функциями из упражнения 7 главы 8. Сделайте этот класс шаблоном, чтобы его можно было реализовывать с использованием различных типов данных в качестве делимого и делителя. Конечно, это должны быть целочисленные типы, что строго ограничивает вас в их выборе (char, short, int и long). Можно, впрочем, определить и свой целочисленный класс, никто не запрещает. В main() реализуйте класс frac<char> и используйте его при разработке калькулятора с четырьмя функциями. Этому классу требуется меньше памяти, чем frac<int>, но с его помощью невозможно выполнять деление больших чисел.
#include "../../accessories.h"
#include <random>
template <class AnyType>
class fraction
{
	AnyType numerator,denominator;
	public:
	fraction():numerator(0),denominator(0){}
	fraction(AnyType num,AnyType den):numerator(num),denominator(den){}
	void show(){cout<<numerator<<"/"<<denominator;}
	void ShowFraction()
	{
		if(numerator==10)
			cout<<' ';
		else
			cout<<numerator;
		cout<<'('<<(int)numerator<<')'<<"/";
		if(denominator==10)
			cout<<' ';
		else
			cout<<denominator;
		cout<<'('<<(int)denominator<<')';
	}
	char GetNumerator(){return numerator;}
	char GetDenominator(){return denominator;}
	fraction lowterms(fraction fr) //сокращение дроби
	{
		AnyType tnum,tden,temp,gcd;
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
template <class AnyType>
fraction<AnyType> GetFraction()
{
	char ch;
	string input;
	char* FractionPart;
	bool CorrectCharacter;
	int i,j,CharacterCount;
	AnyType numerator,denominator=0;
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
	return fraction<AnyType>(numerator,denominator);
}
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	int i,j;
	char operations[4]={'+','-','*','/'};
	cout<<"FRACTIONS OF TYPE CHAR:\n";
	for(i=0; i<4; i++)
	{
		fraction<char> fraction1(GetRandomChar('A','Z'),GetRandomChar('A','Z'));
		fraction<char> fraction2(GetRandomChar('A','Z'),GetRandomChar('A','Z'));
		for(j=0; j<4; j++)
		{
			fraction<char> result;
			switch(operations[j])
			{
				case'+': result=fraction1+fraction2; break;
				case'-': result=fraction1-fraction2; break;
				case'*': result=fraction1*fraction2; break;
				case'/': result=fraction1/fraction2; break;
			}
			fraction1.ShowFraction();
			cout<<" "<<operations[j]<<" ";
			fraction2.ShowFraction();
			cout<<" = ";
			result.ShowFraction();
			cout<<endl;
		}
		for(j=0; j<91; j++)
			cout<<'-';
	}
	
	cout<<"FRACTIONS OF TYPE INT:\n";
	random_device RandomDevice;
	default_random_engine RandomGenerator(RandomDevice());
	int IntMax=SHRT_MAX/100,IntMin=IntMax/100;
	for(i=0,j=GetRandomInt(2,6); i<j; i++)
		IntMin/=10;
	uniform_int_distribution<int> IntDistribution(IntMin,IntMax);
	for(i=0; i<4; i++)
	{
		fraction<int> fraction1(IntDistribution(RandomGenerator),IntDistribution(RandomGenerator));
		fraction<int> fraction2(IntDistribution(RandomGenerator),IntDistribution(RandomGenerator));
		for(j=0; j<4; j++)
		{
			fraction<int> result;
			switch(operations[j])
			{
				case'+': result=fraction1+fraction2; break;
				case'-': result=fraction1-fraction2; break;
				case'*': result=fraction1*fraction2; break;
				case'/': result=fraction1/fraction2; break;
			}
			fraction1.show();
			cout<<" "<<operations[j]<<" ";
			fraction2.show();
			cout<<" = ";
			result.show();
			cout<<endl;
		}
		for(j=0; j<91; j++)
			cout<<'-';
	}
	return 0;
}