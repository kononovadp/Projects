/*11. Помните структуру sterling? Мы встречались с ней в упражнении 10 главы 2 «Основы программирования на C++», в упражнении 11 главы 5 и в других местах. Преобразуйте ее в класс, имеющий переменные для фунтов (типа long), шиллингов (типа int) и пенсов (типа int). Создайте в классе следующие функции:
- конструктор без аргументов;
- конструктор с одним аргументом типа double (для преобразования от десятичных фунтов);
- конструктор с тремя аргументами: фунтами, шиллингами и пенсами;
- метод getSterling() для получения от пользователя значений количества фунтов, шиллингов и пенсов в формате £9.19.11;
- метод putSterling() для вывода значений количества фунтов, шиллингов и пенсов в формате £9.19.11;
- метод для сложения (sterling + sterling), используя перегруженную операцию +;
- метод вычитания (sterling - sterling), используя перегруженную операцию -;
- метод умножения (sterling * double), используя перегруженную операцию *;
- метод деления (sterling / sterling), используя перегруженную операцию /;
- метод деления (sterling / double), используя перегруженную операцию /;
- операцию double (для преобразования к типу double)
Выполнять вычисления вы можете, например, складывая отдельно данные объекта: сложить сначала пенсы, затем шиллинги и т. д. Однако легче использовать операцию преобразования для преобразования объекта класса sterling к типу double, выполнить вычисления с типами double, а затем преобразовать обратно к типу sterling. Таким образом, операция + выглядит похожей на эту:
sterling sterling::operator+(sterling s2)
{
	return sterling(double(sterling(pounds, shillings, pense)) + double(s2));
}
Так мы создадим две временных переменных типа double, одна происходит от объекта, который вызывает функцию, а другая от аргумента s2. Эти переменные затем складываются, результат преобразовывается к типу sterling и возвращается. Заметим, что мы использовали другой подход для класса sterling, нежели для класса bMoney. В классе sterling мы используем операции преобразования, таким образом отказавшись от возможности поиска неправильных операций, но получив простоту при записи перегружаемых математических операций.*/
#include "../../../../accessories.h"
class sterling
{
	long pound;
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
int main(void)
{
	srand(time(0));
	cout.precision(2);
	cout.setf(ios::fixed);
	sterling st1,st2,result;
	double DoubleNumber,DoubleResult;
	char ch=0;
	while(ch!='0')
	{
		//cout<<"First money sum:\n";
		st1.SetRandomSterling(); //GetSterling();
		//cout<<"\nSecond money sum:\n";
		st2.SetRandomSterling(); //GetSterling();
		//cout<<endl;
		result=st1+st2;
		st1.PutSterling();
		cout<<" + ";
		st2.PutSterling();
		cout<<" = ";
		result.PutSterling();
		cout<<endl;		
		result=st1-st2;
		st1.PutSterling();
		cout<<" - ";
		st2.PutSterling();
		cout<<" = ";
		result.PutSterling();
		cout<<endl;		
		DoubleResult=st1*st2;
		st1.PutSterling();
		cout<<" * "<<(double)st2<<" = "<<DoubleResult<<endl;		
		result=st1/st2;
		st1.PutSterling();
		cout<<" / ";
		st2.PutSterling();
		cout<<" = ";
		result.PutSterling();
		cout<<endl;		
		DoubleResult=st1/st2;
		st1.PutSterling();
		cout<<" / "<<(double)st2<<" = "<<DoubleResult<<endl;		
		cout<<"Press 1 to continue or 0 to exit: ";
		ch=0;
		while(ch!='0' && ch!='1')
		{
			ch=getch();
		}
		cout<<ch<<endl;
	}
	return 0;
}
