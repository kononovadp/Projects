/*12. Создайте класс bMoney. Он должен хранить денежные значения как long double. Используйте метод mstold() для преобразования денежной строки, введенной пользователем, в long double, и метод ldtoms() для преобразования числа типа long double в денежную строку для вывода (см. упражнения 7 и 11). Вы можете вызывать для ввода и вывода методы getmoney() и putmoney(). Напишите другой метод класса для сложения двух объектов типа bMoney и назовите его madd(). Сложение этих объектов легко произвести: просто сложите переменную типа long double одного объекта с такой же переменной другого объекта. Напишите функцию main(), которая просит пользователя несколько раз ввести денежную строку, а затем выводит сумму значений этих строк. Вот как может выглядеть определение класса:
class bMoney
{
	private:
	long double money;
	public:
	bMoney();
	bMoney(char s[]);
	void madd(bMoney m1, bMoney m2);
	void getmoney();
	void putmoney();
};*/
#include <iostream>
#include <strstream>
#include <string.h>
using namespace std;
class bMoney
{
	long double money;
	public:
	bMoney():money(0.0){};
	void madd(bMoney m)
	{
		money+=m.money;
	}
	long double getmoney()
	{
		return money;
	}
	void putmoney(long double d)
	{
		money=d;
	}
};
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
long double mstold(char s[])
{
	int len=strlen(s);
	char temp[100];
	int i,j,k,TempLen=0;
	long long int ip,dp;
	long double res;
	for(i=0; i<len && s[i]!='.'; i++)
	{
		k=s[i]-'0';
		temp[i]=0;
		if((k<=9 && k>=0)|| s[i]=='.')
			temp[TempLen++]=s[i];
	}
	temp[TempLen]=0;
	ip=StrToLongInt(temp);
	TempLen=0;
	while(i++<len)
		temp[TempLen++]=s[i];
	temp[TempLen]=0;
	if(TempLen==0)
		return (long double)ip;
	res=(long double)StrToLongInt(temp);
	for(i=1; i<TempLen; i++)
		res/=10;	
	return res+ip;
}
string ldtoms(long double d)
{
	int i,j;
	string ustring,res;	
	ostrstream ostrstreamobj;
	ostrstreamobj.precision(3);
	ostrstreamobj.setf(ios::fixed);
	ostrstreamobj<<d;
	ustring=ostrstreamobj.str();
	//ustring.erase(ostrstreamobj.pcount(),ustring.length()-ostrstreamobj.pcount());
	res+='$';
	j=(/*ustring.length()*/ostrstreamobj.pcount()-1)%3;
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
int main(void)
{
	bMoney csum,bmsum;
	char sum[100];
	long double ld;
	char ch;
	do
	{
		cout<<"Sum of money: ";
		cin>>sum;
		ld=mstold(sum);
		csum.putmoney(ld);
		bmsum.madd(csum);
		cout<<"You entered "<<ldtoms(csum.getmoney());
		cout<<endl<<"enter 1 to continue or 0 to stop: ";
		cin>>ch;
		while(ch!='0' && ch!='1')
		{
			cout<<"enter 1 or 0: ";
			cin>>ch;
		}
	}
	while(ch!='0');
	cout<<"Total "<<ldtoms(bmsum.getmoney());
	return 0;
}
