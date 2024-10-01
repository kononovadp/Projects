//10. Здесь аргументами bind2nd, в свою очередь, являются equal_to<>() и Search-Name. Это выражение возвращает итератор, указывающий на первую строку в контейнере, равную SearchName. Напишите программу, в которой используется подобное выражение для поиска строки в строковом контейнере. На экран должна выводиться позиция SearchName в контейнере.
#include "../../accessories.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
char* GetRandomName(int length)
{
	int i,RandomNumber;
	char* word=new char[length+1];
	word[0]=GetRandomChar('A','Z');
	for(i=1; i<length; i++)
		word[i]=GetRandomChar('a','z');
	word[i]='\0';
	return word;
}
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	vector<char*> names;
	int i,CountOfNames=10,RandomItemNumber;
	for(i=0; i<CountOfNames; i++)
	{
		names.push_back(GetRandomName(GetRandomInt(3,10)));
		cout<<setw(2)<<i<<". "<<names[i]<<endl;
	}
	RandomItemNumber=GetRandomInt(0,CountOfNames);
	vector<char*>::iterator NamesIt1=find_if(names.begin(),names.end(),bind2nd(equal_to<char*>(),names[RandomItemNumber]));
	cout<<"Number of the required item: "<<RandomItemNumber<<endl;
	cout<<"Number of the found item: "<<NamesIt1-names.begin()<<"; Found item: "<<*NamesIt1<<endl;	
	
	for(i=0; i<CountOfNames; i++)
		delete[] names[i];
	return 0;
}
