/*8. Модифицируйте класс bMoney из упражнения 12 главы 7 «Массивы и строки», включив арифметические операции, выполненные с помощью перегруженных операций:
bMoney = bMoney + bMoney
bMoney = bMoney - bMoney
bМоnеу = bMoney * long double (цена за единицу времени, затраченного на изделие)
long double = bMoney / bMoney (общая цена, деленная на цену за изделие)
bMoney = bMoney / long double (общая цена, деленная на количество изделий)
Заметим, что операция / перегружена дважды. Компилятор может различить оба варианта, так как их аргументы разные. Помним, что легче выполнять арифметические операции с объектами класса bMoney, выполняя те же операции с его long double данными. Убедитесь, что программа main() запросит ввод пользователем двух денежных строк и числа с плавающей точкой. Затем она выполнит все пять операций и выведет результаты. Это должно происходить в цикле, так, чтобы пользователь мог ввести еще числа, если это понадобится.
Некоторые операции с деньгами не имеют смысла: bMoney*bMoney не представляет ничего реального, так как нет такой вещи, как денежный квадрат; вы не можете прибавить bMoney к long double (что же будет, если рубли сложить с изделиями?). Чтобы сделать это невозможным, скомпилируйте такие неправильные операции, не включая операции преобразования для bMoney в long double или long double в bMoney. Если вы это сделаете и запишете затем выражение типа:
bmon2 = bmon1 + widgets; // это не имеет смысла
то компилятор будет автоматически преобразовывать widgets в bMoney и выполнять сложение. Без них компилятор будет отмечать такие преобразования как ошибки, что позволит легче найти концептуальные ошибки. Также сделайте конструкторы преобразований явными. Вот некоторые другие вероятные операции с деньгами, которые мы еще не умеем выполнять с помощью перегруженных операций, так как они требуют объекта справа от знака операции, а не слева:
long double * bMoney // Пока не можем это сделать: bMoney возможен только справа
long double / bMoney // Пока не можем это сделать: bMoney возможен только справа
Мы рассмотрим выход из этой ситуации при изучении дружественных функций в главе 11.*/
#include "../../../../accessories.h"
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
	cout.precision(3);
	cout.setf(ios::fixed);
	while(ch!='0')
	{
		cout<<"Money sum 1: ";
		sum1=bMoney(GetLongDoubleFromKeyboard());
		cout<<"\nMoney sum 2: ";
		sum2=bMoney(GetLongDoubleFromKeyboard());
		cout<<"\nLong double value: ";
		LongDoubleSum=GetLongDoubleFromKeyboard();
		cout<<endl;		
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
