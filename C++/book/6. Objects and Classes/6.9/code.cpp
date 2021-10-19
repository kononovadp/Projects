/*9. На основе структуры fraction из упражнения 8 главы 4 создайте класс fraction. Данные класса должны быть представлены двумя полями: числителем и знаменателем. Методы класса должны получать от пользователя значения числителя и знаменателя дроби в форме 3/5 и выводить значение дроби в этом же формате. Кроме того, должен быть разработан метод, складывающий значения двух дробей. Напишите функцию main(), которая циклически запрашивает у пользователя ввод пары дробей, затем складывает их и выводит результат на экран. После каждой такой операции программа должна спрашивать пользователя, следует ли продолжать цикл.*/
#include <iostream>
#include <conio.h>
using namespace std;
class fraction
{
	int numerator;
	int denominator;
	public:
	void SetData(int n,int d)
	{
		numerator=n;
		denominator=d;
	}
	void ShowData()
	{
		cout<<numerator<<'/'<<denominator;
	}
	double GetSum(fraction f1,fraction f2)
	{
		double res=(f1.numerator*f2.denominator)+(f1.denominator*f2.numerator);
		return res/(f1.denominator*f2.denominator);
	}
};
int main(void)
{
	fraction f1,f2;
	int n1,n2,d1,d2;
	char ch;
	do
	{
		cout<<"First fraction in the format N/N: ";
		scanf("%d/%d",&n1,&d1);
		f1.SetData(n1,d1);
		cout<<"Second fraction in the format N/N: ";
		scanf("%d/%d",&n2,&d2);
		f2.SetData(n2,d2);
		f1.ShowData();
		cout<<" + ";
		f2.ShowData();
		cout<<" = "<<f1.GetSum(f1,f2)<<endl<<"press 1 to continue or 0 to stop: ";
		ch=getche();
		while(ch!='0' && ch!='1')
		{
			cout<<endl<<"press 0 or 1: ";
			ch=getche();
		}
		cout<<endl;
	}while(ch!='0');		
	return 0;
}
