/*12. Рассмотрим старую Британскую платежную систему фунты-стерлинги-пенсы (см. упражнение 10 главы 4 «Структуры»). Пенни в дальнейшем делятся на фартинги и полупенни. Фартинг — это 1/4 пенни. Существовали монеты фартинг, полфартинга и пенни. Любые сочетания монет выражались через восьмые части пенни:
1/8 пенни — это полфартинга;
1/4 пенни — это фартинг;
3/8 пенни — это фартинг с половиной;
1/2 пенни — это полпенни;
5/8 пенни — это полфартинга плюс полпенни;
3/4 пенни — это полпенни  плюс фартинг;
7/8 пенни — это полпенни  плюс фартинг с половиной.
Давайте предположим, что мы хотим добавить в класс sterling возможность пользоваться этими дробными частями пенни. Формат ввода/вывода может быть похожим на £1.1.1-1/4 или £9.19.11-7/8, где дефисы отделяют дробные части от пенни. Создайте новый класс sterfrac, производный от класса sterling. В нем должна быть возможность выполнения четырех основных арифметических операций со стерлингами, включая восьмые части пенни. Поле eighths типа int определяет количество восьмых. Вам нужно будет перегрузить методы класса sterling, чтобы они могли работать с восьмыми частями. Пользователь должен иметь возможность ввести и вывести дробные части пенни. Не обязательно использовать класс fraction полностью (см. упражнение 11 главы 6), но вы можете это сделать для большей точности.*/
#include "../../../../accessories.h"
class fraction
{
	int numerator,denominator;
	public:
	fraction():numerator(0),denominator(0){}
	fraction(int num,int den):numerator(num),denominator(den){}
	fraction lowterms(fraction fr) //сокращение дроби
	{
		long tnum, tden, temp, gcd;
		tnum = labs(fr.numerator); //используем неотрицательные
		tden = labs(fr.denominator); //значения (нужен cmath)
		if(tden == 0) //проверка знаменателя на 0
		{
			cout << "Недопустимый знаменатель!";
			exit(1);
		}			
		else
			if(tnum == 0) //проверка числителя на 0			
				return fraction(0,1);			
			while(tnum != 0) //нахождение наибольшего общего делителя
			{
				if(tnum < tden) //если числитель больше знаменателя,
				{
					temp = tnum;
					tnum = tden;
					tden = temp; //меняем их местами
				}
				tnum = tnum - tden; //вычитание
			}
			gcd = tden; //делим числитель и знаменатель на
			return fraction(fr.numerator/gcd,fr.denominator/gcd);
	}
	fraction operator+(fraction fraction2)
	{
		return lowterms(fraction(numerator*fraction2.denominator+denominator*fraction2.numerator,denominator*fraction2.denominator));		
	}
	fraction operator-(fraction fraction2)
	{
		return lowterms(fraction(numerator*fraction2.denominator-denominator*fraction2.numerator,denominator*fraction2.denominator));
	}
	fraction operator*(fraction fraction2)
	{
		return lowterms(fraction(numerator*fraction2.numerator,denominator*fraction2.denominator));
	}
	fraction operator/(fraction fraction2)
	{
		return lowterms(fraction(numerator*fraction2.denominator,denominator=denominator*fraction2.numerator));
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
	bool operator<(int zero)
	{
		if(numerator<zero || denominator<zero)
			return true;
		return false;
	}
	void display(){cout<<numerator<<"/"<<denominator;}
};
class sterling
{
	protected: long pound;
	int shillings,pence;
	public:
	sterling(){}
	sterling(double DecPounds)
	{
		pound=DecPounds;
		double DecShillings=(DecPounds-pound)*20;
		shillings=DecShillings;		
		double DecPenny=(DecShillings-shillings)*12;
		pence=DecPenny;		
	}
	sterling(long NewPound,int NewShillings,int NewPence)
	{
		pound=NewPound;
		shillings=NewShillings;
		pence=NewPence;
	}
	long GetPound(){return pound;}
	int GetShillings(){return shillings;}
	int GetPence(){return pence;}
	void SetRandomSterling()
	{
		pound=GetRandomInt(0,1000000);
		shillings=GetRandomInt(0,19);
		pence=GetRandomInt(0,11);
	}
	void GetSterling()
	{
		cout<<"Pounds: ";		
		pound=GetLongFromKeyboard();
		cout<<"\nShillings: ";
		while((shillings=GetIntFromKeyboard())>19)
			cout<<"\nShillings can't be more than 19, try again: ";
		cout<<"\nPence: ";
		while((pence=GetIntFromKeyboard())>11)
			cout<<"\nPence can't be more than 11, try again: ";
	}
	void PutSterling(){cout<<"£"<<pound<<"."<<shillings<<"."<<pence;}
	operator double()
	{
		double res=pound+((shillings+(pence/12.0))/20.0f);
		while(*this!=sterling(res))
			res+=0.004;
		return res;
	}
	bool operator!=(sterling st)
	{
		if(pound!=st.pound || shillings!=st.shillings || pence!=st.pence)
			return true;
		return false;
	}
	sterling operator+(sterling st2)
	{
		return sterling((double)*this+(double)st2);
	}
	sterling operator-(sterling st2)
	{
		double operand1=(double)*this;
		double operand2=(double)st2;
		if(operand1<operand2)
			return sterling(0,0,0);
		return sterling(operand1+operand2);
	}
	sterling operator*(double DoubleNumber)
	{
		return sterling((double)*this*DoubleNumber);
	}
	sterling operator/(sterling st2)
	{
		return sterling((double)*this/(double)st2);
	}
	sterling operator/(double DoubleNumber)
	{
		return sterling((double)*this/DoubleNumber);
	}
};
class sterfrac:private sterling,private fraction
{
	fraction FractionalPartOfPenny;
	public:
	sterfrac(){}
	sterfrac(sterling NewSterling,fraction NewFraction)
	{
		pound=NewSterling.GetPound();
		shillings=NewSterling.GetShillings();
		pence=NewSterling.GetPence();
		FractionalPartOfPenny=NewFraction;
	}	
	void GetSterFrac()
	{
		sterling::GetSterling();
		cout<<"\nCount of eights:\n1. half a farthing (1/8 penny);\n2. one farthing (2/8=1/4 penny);\n3. one farthing and a half (3/8 penny);\n4. halfpenny (4/8=1/2 penny);\n5. half farthning plus halfpenny (5/8 penny);\n6. halfpenny plus farthing (6/8=3/4 penny);\n7. halfpenny plus farthing and a half (7/8 penny).\nYour choice (number 0-9): ";
		char ch=getch();
		while(ch<'0' || ch>'9')
			ch=getch();
		FractionalPartOfPenny=fraction::lowterms(fraction(ch-'0',8));
		cout<<ch<<"/8 = ";
		FractionalPartOfPenny.display();
		cout<<endl;
	}
	void PutSterFrac()
	{
		sterling::PutSterling();
		cout<<"-";
		FractionalPartOfPenny.display();		
	}
	sterfrac operator+(sterfrac st2)
	{
		sterling SterlingResult=sterling(pound,shillings,pence)+sterling(st2.pound,st2.shillings,st2.pence);
		fraction NewFraction=FractionalPartOfPenny+st2.FractionalPartOfPenny;
		return sterfrac(SterlingResult,NewFraction);
	}
	sterfrac operator-(sterfrac st2)
	{
		sterling SterlingResult=sterling(pound,shillings,pence)-sterling(st2.pound,st2.shillings,st2.pence);
		fraction NewFraction=FractionalPartOfPenny-st2.FractionalPartOfPenny;
		if(NewFraction<0)
			NewFraction=fraction(0,0);
		return sterfrac(SterlingResult,NewFraction);
	}
	sterfrac operator*(sterfrac st2)
	{
		sterling SterlingResult=sterling(pound,shillings,pence)*sterling(st2.pound,st2.shillings,st2.pence);
		fraction NewFraction=FractionalPartOfPenny*st2.FractionalPartOfPenny;
		return sterfrac(SterlingResult,NewFraction);
	}
	sterfrac operator/(sterfrac st2)
	{
		sterling SterlingResult=sterling(pound,shillings,pence)/sterling(st2.pound,st2.shillings,st2.pence);
		fraction NewFraction=FractionalPartOfPenny/st2.FractionalPartOfPenny;
		return sterfrac(SterlingResult,NewFraction);
	}	
};
int main(void)
{
	sterfrac st1,st2,result;
	char ch=0;
	while(ch!='0')
	{
		st1.GetSterFrac();
		st2.GetSterFrac();
		result=st1+st2;
		st1.PutSterFrac();
		cout<<" + ";
		st2.PutSterFrac();
		cout<<" = ";
		result.PutSterFrac();
		cout<<endl;		
		result=st1-st2;
		st1.PutSterFrac();
		cout<<" - ";
		st2.PutSterFrac();
		cout<<" = ";
		result.PutSterFrac();
		cout<<endl;		
		result=st1*st2;
		st1.PutSterFrac();
		cout<<" * ";
		st2.PutSterFrac();
		cout<<" = ";
		result.PutSterFrac();
		cout<<endl;		
		result=st1+st2;
		st1.PutSterFrac();
		cout<<" / ";
		st2.PutSterFrac();
		cout<<" = ";
		result.PutSterFrac();
		cout<<"\n---------------------------------------------\nPress 1 to continue or 0 to exit: ";
		ch=0;
		while(ch!='0' && ch!='1')		
			ch=getch();		
		cout<<ch<<endl;
	}
	return 0;
}
