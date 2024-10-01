/*11. Напишите программу, использующую структуру sterling, которая описана в упражнении 10 главы 4. Программа должна получать от пользователя значения двух денежных сумм, выраженных в фунтах, шиллингах и пенсах, складывать эти значения и выводить результат на экран в том же формате. Необходимо разработать три функции. Первая из них должна получать от пользователя число фунтов, шиллингов и пенсов и возвращать соответствующее значение типа sterling. Вторая функция должна принимать в качестве аргументов два значения типа sterling, складывать их и возвращать значение, также имеющее тип sterling. Третья функция должна принимать аргумент типа sterling и выводить его значение на экран.*/
#include <iostream>
using namespace std;
struct sterling
{
	int pounds,shillings,pence;
};
int GetPennyCount(sterling st)
{
	return (st.pounds*20+st.shillings)*12+st.pence;
}
sterling GetSterling()
{
	sterling st;
	cout<<"Pounds: ";
	cin>>st.pounds;
	cout<<"Shillings: ";
	cin>>st.shillings;
	cout<<"Pence: ";
	cin>>st.pence;
	return st;
}
sterling GetSterlingSum(sterling st1,sterling st2)
{
	int sum=GetPennyCount(st1)+GetPennyCount(st2);
	sterling result;
	result.pence=sum%12;
	sum=(sum-result.pence)/12;
	result.shillings=sum%20;
	sum-=result.shillings;
	result.pounds=sum/20;
	return result;
}
void ShowSterling(sterling st)
{
	cout<<st.pounds<<" pounds "<<st.shillings<<" shillings "<<st.pence<<" pence";
}
int main(void)
{
	sterling st1,st2,sum;
	cout<<"First sum:\n";
	st1=GetSterling();
	cout<<"Second sum:\n";
	st2=GetSterling();
	sum=GetSterlingSum(st1,st2);
	cout<<"Sum: ";
	ShowSterling(sum);
	return 0;
}
