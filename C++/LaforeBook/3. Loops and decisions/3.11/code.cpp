/*11. Создайте калькулятор, выполняющий действия над денежными суммами, выраженными в фунтах, шиллингах и пенсах (см. упражнение 10 и 12 главы 2). Калькулятор должен складывать и вычитать вводимые значения, а также производить умножение денежной суммы на вещественное число (операция умножения двух денежных сумм не имеет смысла, поскольку квадратных денежных единиц не существует. Деление одной денежной суммы на другую мы тоже не будем рассматривать). Организация взаимодействия с калькулятором описана в упражнении 4 этой главы.*/
#include <iostream>
#include <conio.h>
using namespace std;
int GetPennyCount(int pound,int shilling,int penny)
{
	return (pound*20+shilling)*12+penny;
}	
int main(void)
{
	char ch,op;
	double RealResult,RealOp1,RealOp2;
	int FirstPound,FirstShilling,FirstPenny,SecondPound,SecondShilling,SecondPenny,t;
	int op1,op2,ResultPound,ResultShilling,ResultPenny,res;
	do
	{
		cout<<"Press +, - or *: ";
		op=getche();
		while(op!='+' && op!='-' && op!='*')
		{
			cout<<endl<<"Press +, - or *: ";
			op=getche();
		}
		ch='.';
		cout<<endl<<"First sum: J";
		cin>>FirstPound>>ch>>FirstShilling>>ch>>FirstPenny;
		op1=GetPennyCount(FirstPound,FirstShilling,FirstPenny);
		if(op=='+' || op=='-')
		{
			cout<<"Second sum: J";
			cin>>SecondPound>>ch>>SecondShilling>>ch>>SecondPenny;
			op2=GetPennyCount(SecondPound,SecondShilling,SecondPenny);
		}
		else
		{
			cout<<"Real number: ";
			cin>>RealOp2;
		}
		switch(op)
		{
			case '+': res=op1+op2; break;
			case '-': if(op1<op2)res=0; else res=op1-op2; break;
			case '*': RealOp1=op1*1.0; RealResult=RealOp1*RealOp2; res=RealResult; if(RealResult-res>0.5)res++; break;
		}
		cout<<"Result: "<<op1<<op;
		if(op=='*')
			cout<<RealOp2<<'='<<RealResult<<'='<<res;
		else
			cout<<op2<<'='<<res;
		ResultPenny=res%12;
		res=(res-ResultPenny)/12;
		ResultShilling=res%20;
		res-=ResultShilling;
		ResultPound=res/20;
		cout<<" = "<<ResultPound<<'.'<<ResultShilling<<'.'<<ResultPenny;
		cout<<endl<<"Do you want to continue (y/n)? ";
		ch=getche();
		while(ch!='y' && ch!='n')
		{
			cout<<endl<<"press y or n: ";
			ch=getche();
		}
		cout<<endl;
	}while(ch!='n');		
	return 0;
}
