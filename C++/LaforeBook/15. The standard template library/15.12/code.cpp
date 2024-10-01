//12. Напишите программу, копирующую один файл с целочисленными данными в другой. Используйте для этого потоковые итераторы. Пользователь должен ввести имена обоих файлов. Можно использовать цикл while. В этом цикле, наверное, будут читаться последовательно значения из входного итератора и сразу записываться в выходной, после чего будет производиться инкремент обоих итераторов. В качестве исходного можно взять файл ITER.DAT, созданный программой FOUTITER.
//foutiter.cpp
//Демонстрация работы ostream_iterator с файлами
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <list>
using namespace std;
int main()
{
	/*int arr[]={11,21,31,41,51};
	list<int> theList;
	for(int j=0; j<5; j++) //Передача данных 
		theList.push_back(arr[j]); //из массива в список
	ofstream outfile("ITER.DAT"); //создание файлового объекта
	ostream_iterator<int> ositer(outfile," "); //итератор                                   
	copy(theList.begin(),theList.end(),ositer); //записать список в файл*/ 
	int n;
	ifstream InputFile("ITER.DAT");
	ofstream OutputFile("output.dat");
	InputFile>>n;
	while(!InputFile.eof())
	{
		cout<<n<<endl;
		OutputFile<<n<<" ";
		InputFile>>n;
	}
	InputFile.close();
	OutputFile.close();
	return 0;
}