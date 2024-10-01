//11. Начните с класса bMoney, который мы последний раз видели в упражнении 6 главы 11. Перегрузите операторы извлечения и вставки, чтобы можно было осуществлять ввод/вывод объектов этого класса. Выполните какой-нибудь ввод/вывод в main().
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
	friend istream& operator>>(istream& NewStream,bMoney& sum);
	friend ostream& operator<<(ostream& NewStream,bMoney& sum);
};
istream& operator>>(istream& NewStream,bMoney& sum)
{
	sum.money=GetLongDoubleFromKeyboard();
	return NewStream;
}
ostream& operator<<(ostream& NewStream,bMoney& sum)
{
	cout<<LongDoubleToStringSum(sum.money);
	return NewStream;
}
int main(void)
{
	char ch=0;
	long double LongDoubleSum,LongDoubleRes;
	bMoney sum1;
	InitFloatingPointAndRandomNumbers();
	while(ch!='0')
	{
		cout<<"Money sum: ";
		cin>>sum1;
		cout<<"\nYou entered: "<<sum1<<endl;
		cout<<"Press 1 to continue or 0 to exit: ";
		ch=getch();
		while(ch!='0' && ch!='1')
			ch=getch();		
		cout<<ch<<endl;
	}
	return 0;
}
