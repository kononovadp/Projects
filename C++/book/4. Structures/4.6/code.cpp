/*6. Как мы говорили, стандартные средства ввода / вывода С++ вместо значений перечисляемых типов данные выводят их внутреннее представление в виде целых чисел. Для того чтобы преодолеть это ограничение, вы можете использовать конструкцию switch, с помощью которой устанавливается соответствие между значением переменной перечисляемого типа и ее внутренним представлением. Пусть, например, в программе определен перечислемый тип данных etype, отражающий должность сотрудника: enum etype {laborer,secretary,manager,accountant,executive,researcher};
Напишите программу, которая сначала по первой букве должности, введенной пользователем, определяет соответствующее значение переменной, помещает это значение в переменную типа etype, а затем выводит полностью название должности, первую букву которой ввел пользователь. Взаимодействие программы с пользователем может выглядеть так:
Введите первую букву должности (laborer, secretary, manger, accountant, executive, researcher): а
Полное название должности: accountant
Возможно вам понадобится два ветвления switch: одно - для ввода значения, другое - для вывода.*/
#include <iostream>
#include <conio.h>
using namespace std;
int main(void)
{
	enum etype {laborer,secretary,manager,accountant,executive,researcher};
	etype post;
	char ch;
	cout<<"First letter of a position (laborer, secretary, manager, accountant, executive, researcher): ";
	ch=getche();
	switch(ch)
	{
		case 'l': post=laborer; break;
		case 's': post=secretary; break;
		case 'm': post=manager; break;
		case 'a': post=accountant; break;
		case 'e': post=executive; break;
		case 'r': post=researcher; break;
	}
	cout<<"\nEntered post: ";
	switch(post)
	{
		case laborer: cout<<"laborer"; break;
		case secretary: cout<<"secretary"; break;
		case manager: cout<<"manager"; break;
		case accountant: cout<<"accountant"; break;
		case executive: cout<<"executive"; break;
		case researcher: cout<<"researcher"; break;
		default: cout<<"incorrect letter"; break;
	}
	return 0;
}
