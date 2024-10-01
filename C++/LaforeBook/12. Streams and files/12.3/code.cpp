//*3. Напишите программу, возвращающую размер файла, указанного в командной строке: C:\>filesize program.ext.
#include <Windows.h>
#include "../../accessories.h"
int main(int argc, char* argv[])
{	
	if(argc<2)
	{
		cout<<"Enter full names of the pats to source and destination files!\n";
		cout<<"If a path contains spaces type it using quotation marks \"";
		getchar();
		return 0;
	}	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);	
	ifstream SourceFile(argv[1]);
	if(!SourceFile)
	{
		cout<<"The file \""<<argv[1]<<"\" doesn't exist";
		return 0;
	}
	long long int size=0;	
	SourceFile.seekg(0,ios_base::end);
	size=SourceFile.tellg();
	cout<<"Path to file: "<<argv[1]<<endl;	
	if(size<1024)
		cout<<"Size: "<<size<<" bytes";
	else
	{
		char* SizeStr=new char[20];
		SizeStr=itoa(size,SizeStr,10);		
		int i,CharNumber=strlen(SizeStr)%3;
		cout<<"Size: ";
		for(i=0; i<CharNumber; i++)
			cout<<SizeStr[i];
		for(i=0; CharNumber<strlen(SizeStr); CharNumber++,i++)
		{
			if(i%3==0)
				cout<<" ";
			cout<<SizeStr[CharNumber];
		}
		delete[]SizeStr;
		cout<<" bytes";
		if(size>1073741824)
			cout<<" = "<<setprecision(3)<<(double)size/1073741824<<" GB";
		else
			if(size>1048576)
				cout<<" = "<<setprecision(3)<<(double)size/1048576<<" MB";
			else
				if(size>1024)
					cout<<" = "<<setprecision(3)<<(double)size/1024<<" KB";
	}
	SourceFile.close();
	return 0;
}