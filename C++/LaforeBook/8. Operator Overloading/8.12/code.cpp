/*12. Напишите программу, объединяющую в себе классы bMoney из упражнения 8 и sterling из упражнения 11. Напишите операцию преобразования для преобразования между классами bMoney и sterling, предполагая, что один фунт (£1.0.0) равен пятидесяти долларам ($50.00). Это приблизительный курс обмена для XIX века, когда Британская империя еще использовала меру фунты-шиллинги-пенсы. Напишите программу main(), которая позволит пользователю вводить суммы в каждой из валют и преобразовывать их в другую валюту с выводом результата. Минимизируйте количество изменений в существующих классах bMoney и sterling*/
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
long double MoneySumToLongDouble(string str)
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
string LongDoubleToMoneySum(long double d)
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
	void SetSum(long double NewSum){money=NewSum;}
	double GetSum(){return money;}
	void SetRandomSum(){money=GetRandomDouble(0.1,1000000.0);}	
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
		cout<<LongDoubleToMoneySum(money);
	}
};
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
	operator bMoney()
	{
		return bMoney((double)*this*50.0);
	}
	sterling(bMoney bm)
	{
		*this=sterling(bm.GetSum()/50.0);
	}
};
int main(void)
{
	srand(time(0));
	cout.precision(3);
	cout.setf(ios::fixed);
	sterling SterlingSum;
	bMoney bMoneySum;
	char ch=0;
	while(ch!='0')
	{
		cout<<"Sterling sum:\n";
		SterlingSum.GetSterling();
		bMoneySum=SterlingSum;
		cout<<endl;
		SterlingSum.PutSterling();
		cout<<" = ";
		bMoneySum.show();		
		cout<<"\nbMoney sum: ";
		bMoneySum.SetSum(GetLongDoubleFromKeyboard());
		SterlingSum=bMoneySum;
		cout<<endl;
		bMoneySum.show();
		cout<<" = ";
		SterlingSum.PutSterling();		
		/*SterlingSum.SetRandomSterling();		
		cout<<"Sterling sum: ";
		SterlingSum.PutSterling();
		cout<<" = ";
		bMoneySum=SterlingSum;
		bMoneySum.show();		
		bMoneySum.SetRandomSum();
		cout<<"\nbMoney sum: ";
		bMoneySum.show();
		cout<<" = ";
		SterlingSum=bMoneySum;
		SterlingSum.PutSterling();*/
		cout<<"\nPress 1 to continue or 0 to exit: ";
		ch=0;
		while(ch!='0' && ch!='1')		
			ch=getch();		
		cout<<ch<<endl;
	}
	return 0;
}
