#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <io.h>
using namespace std;
struct SCAN_INFO
{
	char manufacturer[127];// изготовитель
	int year;	 // год изготовления
	char model[128];// наименование модели
	float price;// цена
	int x_size;// горизонтальный размер области сканирования
	int y_size;// вертикальный размер области сканирования
	int optr; // оптическое разрешение
};
struct temp
{
	char manufacturer[127];// изготовитель
	int year;	 // год изготовления
	char model[128];// наименование модели
	float price;// цена
	int x_size;// горизонтальный размер области сканирования
	int y_size;// вертикальный размер области сканирования
	int optr; // оптическое разрешение
};
int main()
{
    SCAN_INFO p;
	temp t;
	strcpy(p.manufacturer,"lkklpk");
	cout<<"1. ENTER adds data into the file"<<endl;
	cout<<"2. 1 displays contents of the file"<<endl;
	cout<<"3. ESC exit"<<endl;
	ofstream in("Scaners.dba",ios::trunc);
	in.close();	
	int menu; bool b;

	while (menu!=27)
	{
		menu=getch();
		if (menu==13)
		{	
			cout<<"Manufacturer: ";	cin>>p.manufacturer;
			cout<<"Year: ";	cin>>p.year;
			b=0;
			ifstream in("Scaners.dba",ios::binary|ios::in);
			in.seekg( 0, std::ios::end );
			int size = in.tellg();
			if (size>0)
			while(!in.eof())
			{ 
				in.read((char*)&t,sizeof t);
				//cout<<t.manufacturer<<" || "<<t.year<<endl;
				if (p.manufacturer==t.manufacturer)
				{
					b=1;
					break;
				}
			}
			in.close();
			
			if(b==0)
			{
				ofstream fw("Scaners.dba",ios_base::app|ios_base::binary);
				fw.write((char*)&p,sizeof p); //fwrite<<p.manufacturer;
				fw.close();
			}
		}
		else
			if(menu==49)
			{
				cout<<"----------FILE CONTENTS:----------"<<endl;
				int i=0;			
				ifstream in("Scaners.dba",ios::binary|ios::in);//ifstream fread("Scaners.dba",ios_base::in);
				while (!in.eof())
				{ 
				in.read((char*)&t,sizeof t);
				cout<<t.manufacturer<<" | "<<t.year<<endl;
				}
				in.close();
			}	
	}
	
	cin.get();
}