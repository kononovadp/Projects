﻿/*9. Представьте, что вы собираетесь пригласить к себе шестерых гостей, но за вашим столом могут разместиться всего лишь 4 человека. Сколькими способами можно разместить четырех из шести гостей за обеденным столом? Каждый из шести гостей может разместиться на первом стуле. Каждый из оставшихся пяти гостей может занять второй стул. На третьем стуле может разместиться один из четырех гостей, и на четвертом - один из трех оставшихся гостей. Двоим из гостей не достанется ни одного места. Таким образом, число возможных рассадок гостей за столом равно 6*5*4*3=360. Напишите программу, которая будет производить аналогичные вычисления для любого числа гостей и любого числа мест за столом (при этом предполагается, что число гостей не меньше числа мест). Программа не должна быть сложной, и вычисления можно организовать с помощью простого цикла for.*/
#include <iostream>
using namespace std;
int main(void)
{
	int gc,sc,cc,i;
	cout<<"Count of guests: ";
	cin>>gc;
	cout<<"Count of seats: ";
	cin>>sc;
	for(cc=1,i=gc-sc; gc>i; gc--)
		cc*=gc;
	cout<<"Combinations count: "<<cc;
	return 0;
}