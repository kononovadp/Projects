/*10. Создайте структуру с именем sterling, хранящую денежные суммы в старой английской системе, описанной в упражнениях 8 и 11 главы 3 «Циклы и ветвления». Поля структуры могут быть названы pounds, shillings и pence и иметь тип int. Программа должна запрашивать у пользователя значение денежной суммы в новых десятичных фунтах (значение должно храниться в переменной типа double), затем переводить эту сумму в старую систему, сохранять переведенное значение в переменной типа sterling и выводить на экран полученную сумму в фунтах, шиллингах и пенсах.*/
#include <iostream>
using namespace std;
int main(void)
{
	struct sterling
	{
		int pounds,shillings,pence;
	};
	struct sterling st;
	double decpounds,decshillings,decpenny;
	cout<<"Decimal pounds count: ";
	cin>>decpounds;
	st.pounds=decpounds;
	decshillings=(decpounds-st.pounds)*20;
	st.shillings=decshillings;
	decpenny=(decshillings-st.shillings)*12;
	st.pence=decpenny;
	cout<<st.pounds<<" pounds "<<st.shillings<<" shillings "<<st.pence<<" pence";
	return 0;
}
