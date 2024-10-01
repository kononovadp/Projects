/*7. Взяв в качестве основы функцию power() из упражнения 2, работающую только со значением типа double, создайте перегруженные функции с этим же именем, принимающими в качестве аргумента значения типа char, int, long и float. Напишите программу, вызывающую функцию power() со всеми возможными типами аргументов.*/
#include <iostream>
using namespace std;
float power(float n, int p)
{
	float r=1.0;
	if(p>0)
		r=n*power(n,p-1);	
	return r;
}
double power(double n, int p)
{
	double r=1.0;
	if(p>0)
		r=n*power(n,p-1);	
	return r;
}
char power(char n, int p)
{
	char r=1;
	if(p>0)
		r=n*power(n,p-1);	
	return r;
}
int power(int n, int p)
{
	int r=1;
	if(p>0)
		r=n*power(n,p-1);	
	return r;
}
long power(long n, int p)
{
	long r=1;
	if(p>0)
		r=n*power(n,p-1);
	return r;
}
int main(void)
{
	char ch=5;
	int in=876;
	long lo=7686;
	float fl=56.1;
	double db=5.34;
	cout<<ch<<" in the power of "<<3<<" equals "<<power(ch,3)<<endl;
	
	cout<<in<<" in the power of "<<2<<" equals "<<power(in,2)<<endl;
	cout<<lo<<" in the power of "<<2<<" equals "<<power(lo,2)<<endl;
	//cout<<fl<<" in the power of "<<3<<" equals "<<power(fl,3)<<endl;
	printf("%f in the power of %d = %f\n",fl,3,power(fl,3));	
	//cout<<db<<" in the power of "<<3<<" equals "<<power(db,5)<<endl;
	printf("%f in the power of %d = %f",db,5,power(db,5));
	return 0;
}
