/*6. На биржевых торгах за 1 фунт стерлингов давали $1.487, за франк - $0.172, за немецкую марку - $0.584, а за японскую йену - $0.00955. Напишите программу, которая запрашивает денежную сумму в долларах, а затем выводит эквивалентные суммы в других валютах.*/
#include<iostream>
using namespace std;
int main(void)
{
	int sum;
	cout<<"sum: ";
	cin>>sum;
	cout<<"British pound: "<<sum/1.487<<"\nfranc: "<<sum/0.172;
	cout<<"\nDeutsche Mark: "<<sum/0.584<<"\nJapanese yen: "<<sum/0.00955;
	return 0;
}
