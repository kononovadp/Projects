/* *3. Создайте структуру с именем volume, содержащую три поля типа distance из примера englstrc, для хранения трех измерений помещения. Определите переменную volume, инициализируйте ее, вычислите объем, занимаемый помещением, и выведите результат на экран. Для подсчета объема переведите каждое из значений типа distance в значение типа float, равное соответствущей длине в футах и хранимое в отдельной переменной. Затем для вычисления объема следует перемножить три полученные вещественные переменные.*/
#include <iostream>
using namespace std;
struct distance
{
	int feet;
	float inches;
};
struct volume
{
	struct distance f1;
	struct distance f2;
	struct distance f3;
};
int main(void)
{
	struct volume v;
	float s1,s2,s3;
	v.f1.feet=10;
	v.f1.inches=v.f1.feet*12.0;
	v.f2.feet=15;
	v.f2.inches=v.f2.feet*12.0;
	v.f3.feet=12;
	v.f3.inches=v.f3.feet*12.0;
	s1=(float)v.f1.feet;
	s2=(float)v.f2.feet;
	s3=(float)v.f3.feet;
	cout<<"volume "<<s1*s2*s3<<" feets or "<<v.f1.inches*v.f2.inches*v.f3.inches<<" inches";
	return 0;
}
