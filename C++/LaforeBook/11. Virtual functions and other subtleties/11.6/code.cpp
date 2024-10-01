/*6. Возьмите за основу программу из упражнения 8 главы 8, где было перегружено пять арифметических операций для работы с денежным форматом. Добавьте два оператора, которые не были перегружены в том упражнении:
long double  * bMoney //умножать число на деньги
long double  / bMoney //делить число на деньги
Эти операции требуют наличия дружественных функций, так как справа от оператора находится объект, а слева — обычное число. Убедитесь, что main() позволяет пользователю ввести две денежные строки и число с плавающей запятой, а затем корректно выполняет все семь арифметических действий с соответствующими парами значений*/
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
};
int main(void)
{	
	char ch=0;
	long double LongDoubleSum,LongDoubleRes;
	bMoney sum1,sum2,res;
	InitFloatingPointAndRandomNumbers();
	while(ch!='0')
	{
		cout<<"Money sum 1: ";
		sum1=bMoney(GetLongDoubleFromKeyboard());
		cout<<"\nMoney sum 2: ";
		sum2=bMoney(GetLongDoubleFromKeyboard());
		cout<<"\nLong double value: ";
		LongDoubleSum=GetLongDoubleFromKeyboard();
		cout<<endl;
		/*sum1=bMoney(GetRandomDouble(1.0,1000.0));
		sum2=bMoney(GetRandomDouble(1.0,1000.0));
		LongDoubleSum=GetRandomDouble(1.0,1000.0);*/
		res=sum1+sum2;		
		sum1.show();
		cout<<" + ";
		sum2.show();
		cout<<" = ";
		res.show();
		cout<<endl;		
		res=sum1-sum2;		
		sum1.show();
		cout<<" - ";
		sum2.show();
		cout<<" = ";
		res.show();
		cout<<endl;		
		res=sum1*sum2;		
		sum1.show();
		cout<<" * ";
		sum2.show();
		cout<<" = ";
		res.show();
		cout<<endl;
		LongDoubleRes=sum1/sum2;		
		sum1.show();
		cout<<" / ";
		sum2.show();
		cout<<" = "<<LongDoubleRes<<endl;		
		res=sum1/LongDoubleSum;
		sum1.show();
		cout<<" / "<<LongDoubleSum<<" = ";
		res.show();
		cout<<endl;		
		res=LongDoubleSum*sum1;
		cout<<LongDoubleSum<<" * ";
		sum1.show();
		cout<<" = ";
		res.show();
		cout<<endl;		
		res=LongDoubleSum/sum1;
		cout<<LongDoubleSum<<" / ";
		sum1.show();
		cout<<" = ";
		res.show();		
		cout<<"\n---------------WRONG OPERATIONS:---------------\n";		
		res=sum1+LongDoubleSum;		
		sum1.show();
		cout<<" + "<<LongDoubleSum<<" = ";
		res.show();
		cout<<endl;		
		res=sum1*LongDoubleSum;
		sum1.show();
		cout<<" * "<<LongDoubleSum<<" = ";
		res.show();
		cout<<"\nPress 1 to continue or 0 to exit: ";
		ch=0;
		while(ch!='0' && ch!='1')		
			ch=getch();		
		cout<<ch<<endl;
	}
	return 0;
}
