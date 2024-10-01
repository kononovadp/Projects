//7. Как и в предыдущем упражнении, возьмите за основу программу из упражнения 8 главы 8. На этот раз от вас требуется добавить функцию, округляющую значение bMoney до ближайшего доллара: mo2 = round(mo1); Как известно, значения, не превышающие $0.49, округляются вниз, а числа от $0.50 и более округляются вверх. Можно использовать библиотечную функцию modfl(). Она разбивает переменную типа long double  на целую и дробную части. Если дробная часть меньше 0.50, функция просто возвращает целую часть числа. В противном случае возвращается увеличенная на 1 целая часть. В main() проверьте работоспособность функции путем передачи в нее последовательно значений, одни из которых меньше $0.49, другие - больше $0.50.
#include "../../accessories.h"
long long int StrToLongInt(char s[])
{
	int len=strlen(s)-1;
	long long int res=0,mult=1;
	while(len>-1)
	{
		res=res+((s[len]-'0')*mult);
		mult*=10;
		len--;
	}
	return res;
}
long double StringSumToLongDouble(string str)
{
	int len=str.length();
	char temp[100];
	int i,j,k,TempLen=0;
	long long int ip,dp;
	long double res;
	for(i=0; i<len && str[i]!='.'; i++)
	{
		k=str[i]-'0';
		temp[i]=0;
		if((k<=9 && k>=0)|| str[i]=='.')
			temp[TempLen++]=str[i];
	}
	temp[TempLen]=0;
	ip=StrToLongInt(temp);
	TempLen=0;
	while(i++<len)
		temp[TempLen++]=str[i];
	temp[TempLen]=0;
	if(TempLen==0)
		return (long double)ip;
	res=(long double)StrToLongInt(temp);
	for(i=1; i<TempLen; i++)
		res/=10;	
	return res+ip;
}
string LongDoubleToStringSum(long double d)
{
	int i,j;
	string ustring,res="$";
	stringstream NewStringstream;
	NewStringstream.precision(3);
	NewStringstream.setf(ios::fixed);
	NewStringstream<<d;
	ustring=NewStringstream.str();
	/*ostrstream ostrstreamobj;
	ostrstreamobj.precision(3);
	ostrstreamobj.setf(ios::fixed);
	ostrstreamobj<<d;
	ustring=ostrstreamobj.str();
	ustring.erase(ostrstreamobj.pcount(),ustring.length()-ostrstreamobj.pcount());*/
	//j=(/*ustring.length()*/ostrstreamobj.pcount()-1)%3;//ustring.length();
	j=(NewStringstream.gcount()-1)%3;
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
class bMoney
{
	long double money;
	public:
	bMoney():money(0.0){};
	bMoney(long double NewSum){money=NewSum;}
	bMoney operator+(bMoney MoneySum2)
	{
		return bMoney(money+MoneySum2.money);
	}
	bMoney operator-(bMoney MoneySum2)
	{
		return bMoney(money-MoneySum2.money);
	}
	bMoney operator*(bMoney MoneySum2)
	{
		return bMoney(money*MoneySum2.money);
	}
	bMoney operator/(long double MoneySum2)
	{
		return bMoney(money/MoneySum2);
	}
	long double operator/(bMoney MoneySum2)
	{
		return money/MoneySum2.money;
	}	
	friend bMoney operator*(long double LongDoubleSum,bMoney bMoneySum)
	{
		return bMoney(LongDoubleSum*bMoneySum.money);
	}
	friend bMoney operator/(long double LongDoubleSum,bMoney bMoneySum)
	{
		return bMoney(LongDoubleSum/bMoneySum.money);
	}
	void show()
	{
		cout<<LongDoubleToStringSum(money);
	}
	friend bMoney RoundbMoney(bMoney NewbMoney)
	{
		if((NewbMoney.money-(int)NewbMoney.money)>0.5)
			NewbMoney=NewbMoney+1.0-(NewbMoney.money-(int)NewbMoney.money);
		return NewbMoney;
	}
};
int main(void)
{	
	char ch=0;
	bMoney sum;
	InitFloatingPointAndRandomNumbers();
	while(ch!='0')
	{
		sum=GetRandomInt(1,1000)+GetRandomFloat(0.01,0.5);
		sum.show();		
		sum=RoundbMoney(sum);
		cout<<" = ";
		sum.show();
		cout<<endl;
		sum=GetRandomInt(1,1000)+GetRandomFloat(0.51,0.99);
		sum.show();		
		sum=RoundbMoney(sum);
		cout<<" = ";
		sum.show();
		cout<<"\nPress 1 to continue or 0 to exit: ";
		ch=0;
		while(ch!='0' && ch!='1')		
			ch=getch();		
		cout<<ch<<endl;
	}
	return 0;
}
