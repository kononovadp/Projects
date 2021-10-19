/* *1. Вернитесь к рассмотрению примера CIRCAREA главы 2 «Основы программирования на C++». Напишите функцию с именем circarea(), которая аналогичным образом вычисляет площадь круга. Функция должна принимать один аргумент типа float и возвращать значение типа float. Напишите функцию main(), которая просит пользователя ввести значение радиуса, вызывает функцию circarea(), а затем отображает результат вычисления на экране.*/
#include <iostream>
using namespace std;
float circarea(float rad)
{
	return 3.14159F*rad*rad;
}
int main(void)
{
	float rad;
	cout<<"Radius of circle: ";
	cin>>rad;
	cout<<"Area of circle: "<<circarea(rad);
	return 0;
}
