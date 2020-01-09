#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <io.h>
#include <sstream>
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

char *equsize(char s[],char t[])
{
	if (strlen(s)<strlen(t))
	{
		int n=strlen(t)-strlen(s); int i;
		for (i=0; i<n; i++)
		strcat(s," ");	
		
	}
	return(&s[50]);
}

int main()
{
    SCAN_INFO p,t;
	cout<<"Press TAB to add data"<<endl;
	cout<<"Press SPACE to display contents of the file"<<endl;
	cout<<"Press ESC to exit"<<endl;
	/*ofstream in("Scaners.dba",ios::trunc);
	in.close();*/
	int menu,k,n=0; bool b;

	while (menu!=27)
	{
		menu=getch(); 
		if (menu==9)
		{	
			cout<<"Manufacturer: ";	cin>>p.manufacturer;
			cout<<"Year: ";	cin>>p.year;
			cout<<"Model: ";	cin>>p.model;
			cout<<"Price: ";	cin>>p.price;
			cout<<"X-size: ";	cin>>p.x_size;
			cout<<"Y-size: ";	cin>>p.y_size;
			cout<<"Optr: ";	cin>>p.optr;
			b=0;
			FILE *in;
			if ((in=fopen("Scaners.dba", "rb"))!=NULL)
			{
				fread(&n, sizeof n, 1, in);
				for (int i=0;i<n;i++)
			    { 
					fread(&t, sizeof t, 1, in);
			    	if ((strcmp(p.manufacturer,t.manufacturer)==0)&&
						(p.year==t.year)&&
						(strcmp(p.model,t.model)==0)&&
						(p.price==t.price)&&
						(p.x_size==t.x_size)&&
						(p.y_size==t.y_size)&&
						(p.optr==t.optr))
			     	{
						b=1;
						break;
			    	}
			    }
		    	fclose(in);
			}
			if(b==0)
			{
				n++;
				FILE *f1;
				f1 = fopen("Scaners.dba", "r+b");
				fwrite(&n, sizeof n, 1, f1);
				fseek(f1, 0L, SEEK_END);
				fwrite(&p, sizeof p, 1, f1);
				fclose(f1);
			}
		}
		else
			if(menu==32)
			{
				cout<<"--------------------SCANNERS:--------------------"<<endl;
				cout<<"Manufacturer|Year|Model|Price|X-size|Y-size|Optr|"<<endl;
				//cout<<"-------------------------------------------------"<<endl;
				ifstream in("Scaners.dba",ios::binary|ios::in);
				in.read((char*)&n,sizeof n);
				for (int i=0;i<n;i++)
				{ 	
					in.read((char*)&t,sizeof t);
					equsize(t.manufacturer,"Manufacturer");
					cout<<t.manufacturer<<"|";
					itoa(t.year,t.manufacturer,10);
					equsize(t.manufacturer,"Year");
					cout<<t.manufacturer<<"|";
					equsize(t.model,"Model");
					cout<<t.model<<"|";
					stringstream iostr;
					iostr<<t.price;
					iostr>>t.model;
					equsize(t.model,"Price");
					cout<<t.model<<"|";
					itoa(t.x_size,t.model,10);
					equsize(t.model,"X-size");
					cout<<t.model<<"|";
					itoa(t.y_size,t.model,10);
					equsize(t.model,"Y-size");
					cout<<t.model<<"|";
					itoa(t.optr,t.model,10);
					equsize(t.model,"Optr");
					cout<<t.model<<"|"<<endl;					
				}
				in.close();
			}
	}
	
	cin.get();
}