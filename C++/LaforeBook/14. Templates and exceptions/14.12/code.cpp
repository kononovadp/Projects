//12.Иногда проще всего бывает использовать механизм исключений, если создать новый класс, чьим компонентом является класс исключений. Попробуйте проделать такую операцию с классом, использующим исключения для обработки файловых ошибок. Создайте класс dofile, включающий в себя класс исключений и методы чтения, и записи файлов. Конструктор этого класса в качестве аргумента может брать имя файла, а действием конструктора, соответственно, может быть открытие этого файла. Можно сделать так, чтобы метод переставлял указатель позиции в начало файла. Используйте программу REWERR из главы 12 в качестве примера, напишите секцию main(), в которой сохранилась бы функциональность прежней версии, но использовались бы методы класса dofile.
//rewerr.cpp Обработка ошибок ввода/вывода
/*#include <fstream> //для файловых потоков
#include <iostream>
#include <string> //для функций strcpy,strcat
#include <string.h>
#include <random>
//#include <process.h> //для exit()
using namespace std;*/
//const int MAX=1000;
//int buff[MAX];
#include "../../accessories.h"
#include <random>
int* GetRandomIntArray(int ArraySize,default_random_engine RandomGenerator)
{
	int i,CountOfDivides,IntMax=INT_MAX/ArraySize,IntMin=IntMax/ArraySize;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		IntMin/=10;
	uniform_int_distribution<int> distribution(IntMin,IntMax);
	int* IntArray=new int[ArraySize];
	for(i=0; i<ArraySize; i++)
		IntArray[i]=distribution(RandomGenerator);
	return IntArray;
}
class dofile
{
	char* FileName;
	public:	
	dofile(char* NewFileName){FileName=NewFileName;}
	class error
	{
		string message;
		public:
		error(string NewMessage):message(NewMessage){}
		void display(){cout<<message;}
	};
	void WriteToFile(int* array,int ArraySize)
	{			
		ofstream FileWriteStream;
		ifstream infile(FileName);
		if(infile.good())
		{
			infile.close();
			FileWriteStream.open(FileName,ios::binary | ios_base::app);
		}
		else
		{
			infile.close();
			FileWriteStream.open(FileName,ios::trunc | ios::binary);
		}
		if(!FileWriteStream)
			throw(dofile::error("The file can't be opened for writing\n"));
		cout<<"Writing to file...";
		FileWriteStream.write(reinterpret_cast<char*>(array),ArraySize*sizeof(int));
		//for(int i=0; i<ArraySize; i++)
		//	FileWriteStream.write(reinterpret_cast<char*>(&array[i]),sizeof(int));
		FileWriteStream.close();
	}
	int* ReadFromFile(int& ArraySize)
	{
		ifstream FileReadStream(FileName,ios::binary | ios::ate);
		if(!FileReadStream)
			throw(dofile::error("The file can't be opened for reading\n"));
		cout<<"Reading from file...";
		int *DataFromFile=new int[(FileReadStream.tellg()/sizeof(int))+sizeof(int)*2];
		FileReadStream.close();
		ifstream NewFileReadStream(FileName,ios::binary);
		ArraySize=0;
		NewFileReadStream.read(reinterpret_cast<char*>(&DataFromFile[ArraySize]),sizeof(int));
		while(NewFileReadStream)
		{
			ArraySize++;
			NewFileReadStream.read(reinterpret_cast<char*>(&DataFromFile[ArraySize]),sizeof(int));
		}
		NewFileReadStream.close();
		return DataFromFile;
	}
};
int main()
{	
	char FileName[10],ch=0;
	strcpy(FileName,"data.dat");
	dofile file(FileName);
	srand(time(0));
	random_device RandomDevice;
	default_random_engine RandomGenerator(RandomDevice());
	int i,CountOfDivides,ArraySize,IntMax,IntMin,*IntArray;
	while(ch!='0')
	{
		cout<<"1. Write random int array to binary file\n2. Read int numbers from binary file\n0. Exit\nYour choice: ";
		ch=getch();
		while(ch<'0' || ch>'2')
			ch=getch();
		switch(ch)
		{
			case '1':
			ArraySize=GetRandomInt(10,20);
			IntArray=GetRandomIntArray(ArraySize,RandomGenerator);
			try{file.WriteToFile(IntArray,ArraySize);}
			catch(dofile::error NewError)
			{
				NewError.display();
				delete[] IntArray;
				break;
			}
			delete[] IntArray;
			cout<<" Done. "<<ArraySize<<" numbers were written.\n";
			break;
			case '2':
			try{IntArray=file.ReadFromFile(ArraySize);}
			catch(dofile::error NewError)
			{
				NewError.display();
				break;
			}
			cout<<" Count of integers in file: "<<ArraySize<<". Array: ";
			for(i=0; i<ArraySize; i++)
			{
				if(i%5==0)
					cout<<endl;
				cout<<setw(4)<<i+1<<". "<<setw(10)<<IntArray[i]<<' ';
			}
			cout<<endl;
			break;
		}
	}	
	
	/*int i;
	for(i=0; i<MAX; i++) //заполнить буфер данными
		buff[i]=i;
	ofstream os; //создать выходной поток
	os.open("data.dat",ios::trunc | ios::binary); //открыть его
	if(!os)
	{
		cerr<<"The file can't be OPENED\n";
		exit(1);
	}
	cout<<"WRITING...\n"; //записать в него содержимое буфера
	os.write(reinterpret_cast<char*>(buff),MAX*sizeof(int));
	if(!os)
	{
		cerr<<"The data can not be WRITTEN to the file\n";
		exit(1);
	}
	os.close(); //закрыть поток
	for(i=0; i<MAX; i++) //очистить буфер
		buff[i]=0;
	ifstream is; //создать входной поток
	is.open("data.dat",ios::binary);
	if(!is)
	{
		cerr<<"The input file can't be opened\n";
		exit(1);
	}
	cout<<"Reading...\n"; //чтение файла
	is.read(reinterpret_cast<char*>(buff),MAX*sizeof(int));
	if(!is)
	{
		cerr<<"The data can not be READ from the file\n";
		exit(1);
	}
	for(i=0; i<MAX; i++) //проверять данные
		if(buff[i]!=i)
		{
			cerr<<"\nThe data is incorrect\n";
			exit(1);
		}
	cout<<"The data is OK.\n";*/
	return 0;
}