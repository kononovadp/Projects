/* *3. Напишите программу, вычисляющую среднее значение до 100 интервалов, введенных пользователем. Создайте массив объектов класса Distance, как это было сделано в примере ENGLARAY этой главы. Для вычисления среднего значения вы можете позаимствовать метод add_dist() из примера ENGLCON главы 6. Вам также понадобится метод, который выделяет целую часть из значения Distance. Вот одна из возможностей:
void Distance::div_dist(Distance d2, int divisor)
{
	float fltfeet = d2.feet + d2.inches / 12.0;
	float temp = fltfeet /= divisor;
	feet = int(fltfeet);
	inches = (temp - feet) * 12.0;
}*/
// englaray.cpp
// объекты для английских мер
#include <iostream>
using namespace std;
///////////////////////////////////////////////////////////
class Distance
{
	private:
	int feet;
	float inches;
	public:
	Distance():feet(0),inches(0.0){}
	void getdist() // получение информации
	{
		cout << "\n Введите футы: "; cin >> feet;
		cout << " Введите дюймы: "; cin >> inches;
		if(inches>=12)
		{
			int temp=inches/12;
			feet=feet+temp;
			inches=inches/12-temp;
		}
	}
	void showdist() const // показ информации
	{ cout << feet << "\'-" << inches << '\"'; }
	Distance add_dist(Distance); // сложение
	void div_dist(Distance,int);
};
Distance Distance::add_dist(Distance d2)
{
	Distance temp; // временная переменная
	temp.inches = inches + d2.inches; // сложение дюймов
	if(temp.inches >= 12.0) // если сумма больше 12.0, то уменьшаем ее на
	{
		temp.inches -= 12.0; // 12.0 и увеличиваем
		temp.feet = 1; // число футов на 1
	}
	temp.feet += feet + d2.feet; // сложение футов
	return temp;
}
void Distance::div_dist(Distance d2, int divisor)
{
	float fltfeet = d2.feet + d2.inches / 12.0;
	float temp = fltfeet /= divisor;
	feet = int(fltfeet);
	inches = (temp - feet) * 12.0;
}
///////////////////////////////////////////////////////////
int main()
{
	Distance dist[100]; // массив переменных
	Distance AverageDistance;
	int n = 0; // счетчик данных
	char ans; // ответ пользователя (y/n)
	cout << endl;
	do
	{
		cout << "Введите длину номер " << n + 1;
		dist[n++].getdist(); // получаем и сохраняем длину
		cout << "Продолжить ввод (y/n)?: ";
		cin >> ans;
	}
	while(ans != 'n'); // продолжать, пока не будет введено 'n'
	// показываем все введенное
	for(int j = 0; j < n; j++)
	{
		cout << "\nДлина номер " << j + 1 << " : ";
		AverageDistance=AverageDistance.add_dist(dist[j]);
		dist[j].showdist();
	}
	cout << endl<<"Sum: ";
	AverageDistance.showdist();
	AverageDistance.div_dist(AverageDistance,n);
	cout<<"; average distance: ";
	AverageDistance.showdist();
	return 0;
}
