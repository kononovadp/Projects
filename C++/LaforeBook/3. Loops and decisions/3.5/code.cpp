﻿/*5. При помощи цикла for изобразите на экране пирамиду из символов 'X'. Верхняя часть пирамиды должна выглядеть следующим образом:
    X
   XXX
  XXXXX
 XXXXXXX
XXXXXXXXX
Вся пирамида должна быть высотой не 5 линий, как изображение здесь, а 20 линий. Одним из способов ее построения может служить использование двух вложенных циклов, из которых внутренний будет заниматься печатанием символов 'X' и пробелов, а другой осуществлять переход на одну строку вниз.*/
#include <iostream>
using namespace std;
int main(void)
{
	int i,j,l=19,xc=1,sc=18;
	for(i=0; i<l; i++)
		cout<<' ';
	cout<<'X';
	for(i=0; i<l; i++,xc++,sc--)
	{
		for(cout<<endl,j=0; j<sc; j++)
			cout<<' ';
		for(j=0; j<xc; j++)
			cout<<'X';
		cout<<'X';
		for(j=0; j<xc; j++)
			cout<<'X';		
	}
	return 0;
}
