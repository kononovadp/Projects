/*10. Только для любителей математики: создайте класс Polar, который предназначен для хранения полярных координат (радиуса и угла). Перегрузите операцию + для выполнения сложения для объектов класса Polar. Сложение двух объектов выполняется путем сложения координат X объектов, а затем координат Y. Результат будет координатами новой точки. Таким образом, вам нужно будет преобразовать полярные координаты к прямоугольным, сложить их, а затем обратно преобразовать прямоугольные координаты результата к полярным*/
#include <iostream>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;
class polar
{
	bool IncorrectData;
	double radius,angle;
	struct cartesian{double x; double y;};
	struct cartesian PolarToCartesian(polar point)
	{
		struct cartesian NewCartesian;
		point.angle=point.angle*3.14/180.0;
		NewCartesian.x=point.radius*cos(point.angle);
		NewCartesian.y=point.radius*sin(point.angle);
		return NewCartesian;
	}
	polar CartesianToPolar(cartesian point)
	{
		double NewRadius=sqrt(point.x*point.x+point.y*point.y);
		double NewAngle=atan(point.y/point.x);
		if(point.x<0)
			NewAngle+=M_PI;
		else
			if(point.x>0 && point.y<0)
				NewAngle=NewAngle+2*M_PI;
		return polar(NewRadius,NewAngle*180/3.14);
	}
	public:
	polar(){IncorrectData=false;}
	polar(double NewRadius,double NewAngle)
	{
		radius=NewRadius;
		angle=NewAngle;
		IncorrectData=false;
	}
	polar(double NewRadius,double NewAngle,bool IncorrectDataFlag)
	{
		IncorrectData=IncorrectDataFlag;
		radius=NewRadius;
		angle=NewAngle;		
	}
	void output()
	{
		if(IncorrectData)
			cout<<"incorrect data!";
		else
			cout<<"("<<radius<<", "<<angle<<"°)";
	}
	bool operator!=(cartesian CartesianPoint)
	{		
		polar PolarPoint=CartesianToPolar(CartesianPoint);
		if(PolarPoint.radius==radius && PolarPoint.angle==angle)
			return false;
		double difference;
		if(angle>PolarPoint.angle)
			difference=angle-PolarPoint.angle;
		else
			difference=PolarPoint.angle-angle;
		if(difference>0.0001)
			return true;		
		if(radius>PolarPoint.radius)
			difference=radius-PolarPoint.radius;
		else
			difference=PolarPoint.radius-radius;
		if(difference>0.0001)
			return true;
		return false;
	}
	polar operator+(polar PolarPoint2)
	{		
		struct cartesian CartesianPoint1=PolarToCartesian(*this);
		if(*this!=CartesianPoint1)
			return polar(0,0,true);
		struct cartesian CartesianPoint2=PolarToCartesian(PolarPoint2);
		if(PolarPoint2!=CartesianPoint2)
			return polar(0,0,true);
		struct cartesian CartesianResult;
		CartesianResult.x=CartesianPoint1.x+CartesianPoint2.x;
		CartesianResult.y=CartesianPoint1.y+CartesianPoint2.y;
		cout<<"\n["<<CartesianPoint1.x<<", "<<CartesianPoint1.y<<"] + "<<"["<<CartesianPoint2.x<<", "<<CartesianPoint2.y<<"] = ["<<CartesianResult.x<<", "<<CartesianResult.y<<"]";
		polar PolarResult=CartesianToPolar(CartesianResult);
		if(PolarResult!=CartesianResult)
			return polar(0,0,true);
		cout<<" = ";
		return PolarResult;
	}
};
double GetRandomDouble(double min, double max)
{
    if(min==max)
		return min;
	double f=(double)rand()/RAND_MAX;	
    return min+f*(max - min);
}
int main(void)
{
	srand(time(0));
	cout.precision(3);
	cout.setf(ios::fixed);
	polar result;
	double radius,angle=0,RandomAngle1,RandomAngle2;
	for(int i=0; i<4; i++,angle+=90.0)
	{
		RandomAngle1=GetRandomDouble(angle+5,angle+90);
		RandomAngle2=GetRandomDouble(0,(angle+90)-RandomAngle1);
		polar point1(GetRandomDouble(0,100.0),RandomAngle1);
		polar point2(GetRandomDouble(0,100.0),RandomAngle2);		
		point1.output();
		cout<<" + ";
		point2.output();
		cout<<" = ";
		result=point1+point2;
		result.output();		
		cout<<"\n--------------------------------------------------------------------------------\n";
	}
	return 0;
}
