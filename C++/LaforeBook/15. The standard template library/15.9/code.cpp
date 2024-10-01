//9. В табл. 15.10 мы привели все предопределенные функциональные объекты C++. В программе PLUSAIR показали, как применять функциональный объект plus<>() с алгоритмом accumulate(). В том примере не было необходимости в передаче каких-либо аргументов в функциональный объект, но иногда по логике работы программы это требуется. Оказывается, в данном случае нельзя просто указать аргумент в скобках, как мы привыкли делать. Вместо этого нужно использовать специальный «адаптер функции», называющийся bind1dt или bind2nd, для связывания аргумента с функциональным объектом. Пусть, например, мы ищем строку SearchName в строковом контейнере names. В этом случае необходимо писать такое выражение: ptr = find_if(names.begin(), names.end(), bind2nd(equal_to<string>(), SearchName));
#include "../../accessories.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
char* GetRandomName(int length)
{
	int i;
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
	int i,CountOfNames=10,FoundItemNumber;
	char* RandomNameToFind=GetRandomName(GetRandomInt(3,10));
	for(i=0; i<CountOfNames; i++)
	{
		names.push_back(GetRandomName(GetRandomInt(3,10)));
		cout<<setw(2)<<i<<". "<<names[i]<<endl;
	}
	FoundItemNumber=GetRandomInt(0,CountOfNames);
	vector<char*>::iterator NamesIt1=find_if(names.begin(),names.end(),bind2nd(equal_to<char*>(),names[FoundItemNumber]));
	cout<<"Number of the found item: "<<FoundItemNumber<<"; Found item: "<<*NamesIt1<<endl;	
	vector<char*>::iterator NamesIt2=find_if(names.begin(),names.end(),bind2nd(equal_to<char*>(),RandomNameToFind));
	if(NamesIt2==names.end())
		cout<<"The name "<<RandomNameToFind<<" was NOT FOUND.";
	else
		cout<<"The name "<<RandomNameToFind<<" was FOUND.";
	for(i=0; i<CountOfNames; i++)
		delete[] names[i];
	delete[] RandomNameToFind;
	return 0;
}
