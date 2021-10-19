#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <fstream> 
#define _CRT_SECURE_NO_WARNINGS
#define HEAP_SIZE 100
using namespace std;
typedef struct {
	char manufacturer[127];// изготовитель
	int year;	 // год изготовления
	char model[128];// наименование модели
	float price;// цена
	int x_size;// горизонтальный размер области сканирования
	int y_size;// вертикальный размер области сканирования
	int optr; // оптическое разрешение
} SCAN_INFO;


int main ()
{SCAN_INFO sc,t; int n=0;


 //all fields
int z=1; 
ifstream in("Scaners.dba",ios::binary|ios::in);
      in.read((char*)&n,sizeof n); 
	  SCAN_INFO List[n];
	  for (int i=0; i<n; i++)
	   { in.read((char*)&t,sizeof t); List[i]=t;  cout<<t.manufacturer<<endl;    }
	in.close();

	 cout<<"enter a name of manufacturer ";      gets(sc.manufacturer);

	for (int i=0; i<n; i++)
	if (  strcmp(List[i].manufacturer , sc.manufacturer)==0  ) z=0;
	
	cout<<n<<endl;
 if (z==1)  
 {ofstream f("Scaners.dba",ios::binary|ios::out);
      n++; 
	  f.write((char*)&n,sizeof n); 
	   f.write((char*)&sc,sizeof sc); 
	 for (int i=0; i<n; i++)
 	  { t=List[i];
		  f.write((char*)&t,sizeof t); }
		  
	  
    f.close();}
 

	cin.get();
}