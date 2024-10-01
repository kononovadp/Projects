/**2. Напишите программу, эмулирующую команду COPY (MS DOS). То есть программа должна копировать содержимое одного файла в другой. Должно использоваться два аргумента командной строки — исходный файл и файл назначения. Например: С:\>оcopy srcfile.cpp destfile.cpp
Осуществляйте проверку числа аргументов командной строки и возможность открытия указанных пользователем файлов*/
#include "../../accessories.h"
int main(int argc, char* argv[])
{
	if(argc<3)
	{
		cout<<"Enter full names of the pats to source and destination files!\n";
		cout<<"If a path contains spaces type it using quotation marks \"";
		getchar();
		return 0;
	}
	ifstream SourceFile(argv[1],ios::binary);
	if(!SourceFile)
	{
		cout<<"The source file \""<<argv[1]<<"\" doesn't exist.";
		return 0;
	}
	ifstream IfstreamDestinationFile(argv[2]);
	ofstream DestinationFile;
	char ch;
	if(IfstreamDestinationFile.is_open())
	{
		cout<<"The file "<<argv[2]<<" already exists.\n";
		cout<<"Press 0 to create a new file or 1 to add data to existing: ";
		ch=getch();
		while(ch!='0' && ch!='1')
		{
			cout<<ch<<"\nPress 0 or 1: ";
			ch=getch();
		}
		cout<<ch;
		if(ch=='0')
			DestinationFile.open(argv[2],ios::binary);
		else
			DestinationFile.open(argv[2],ios::binary | ios_base::app);		
	}
	else	
		DestinationFile.open(argv[2],ios::binary);
	SourceFile.read(&ch,1);
	while(!SourceFile.eof())
	{
		DestinationFile<<ch;
		SourceFile.read(&ch,1);			
	}
	IfstreamDestinationFile.close();
	DestinationFile.close();
	SourceFile.close();
	return 0;
}
