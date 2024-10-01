//*3. В классе Distance, как показано в примерах FRENGL и FRISQ из этой главы, создайте перегружаемую операцию умножения *, чтобы можно было умножать два расстояния. Сделайте эту функцию дружественной, тогда можно будет использовать выражение типа Wdist = 7.5*dist2. Вам понадобится конструктор с одним аргументом для перевода величин из формата чисел с плавающей запятой в формат Distance. Напишите какой-либо main() на свое усмотрение для того, чтобы несколькими способами проверить работу этой перегружаемой операции.
#include "../../accessories.h"
class Distance
{
    int feet;
    float inches;
	public:
    Distance(){feet=0;inches=0.0;}
    Distance(float fltfeet)
	{
		feet=(int)fltfeet;
		inches=12.0*(fltfeet-feet);
	}
	Distance(int ft,float in){feet=ft;inches=in;}
    void showdist(){cout<<feet<<"\'-"<<inches<<'\"';}
    friend Distance operator+(Distance d1,Distance d2)
	{
		int f=d1.feet+d2.feet;
		float i=d1.inches+d2.inches;
		if(i>=12.0)
		{
			i-=12.0;
			f++;
		}
		return Distance(f,i);
	}
	friend Distance operator*(Distance d1,Distance d2)
	{
		int f=d1.feet*d2.feet;
		float i=d1.inches*d2.inches;
		while(i-12.0>12.0)
		{
			i-=12.0;
			f++;
		}
		return Distance(f,i);
	}
};
int main()
{
	InitFloatingPointAndRandomNumbers();
	Distance d1,d2,d3;
	float RandomFloat,RandomFloat2;
	int i;
	for(i=0; i<5; i++)
	{
		RandomFloat=GetRandomFloat(1.0,100.0);
		d1=RandomFloat;
		d2=Distance(GetRandomInt(1,100),GetRandomFloat(0.5,12.0));
		d3=d1*d2;
		cout<<RandomFloat<<" * ";
		d2.showdist();
		cout<<" = ";
		d1.showdist();
		cout<<" * ";
		d2.showdist();
		cout<<" = ";
		d3.showdist();
		cout<<endl;		
		d1=Distance(GetRandomInt(1,100),GetRandomFloat(0.5,12.0));
		d2=Distance(GetRandomInt(1,100),GetRandomFloat(0.5,12.0));
		d3=d1*d2;
		d1.showdist();
		cout<<" * ";
		d2.showdist();
		cout<<" = ";
		d3.showdist();
		cout<<endl;		
		RandomFloat=GetRandomFloat(1.0,100.0);
		RandomFloat2=GetRandomFloat(1.0,100.0);
		d1=RandomFloat;
		d2=RandomFloat2;
		d3=d1*d2;
		cout<<RandomFloat<<" * "<<RandomFloat2<<" = ";
		d1.showdist();
		cout<<" * ";
		d2.showdist();
		cout<<" = ";
		d3.showdist();
		cout<<"\n------------------------------------------------------------\n";
	}
	d3=7.5*d2;
	cout<<7.5<<" * ";
	d2.showdist();
	cout<<" = ";
	d3.showdist();
	cout<<endl;
	d3=d2*7.5;
	d2.showdist();
	cout<<" * "<<7.5<<" = ";
	d3.showdist();
	return 0;
}