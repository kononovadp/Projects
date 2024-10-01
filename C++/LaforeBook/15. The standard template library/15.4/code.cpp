//*4. Начните с класса person. Создайте мультимножество для хранения указателей на объекты этого класса. Определите его с помощью функционального объекта comparePersons, чтобы сортировка производилась автоматически по именам людей. Определите с полдюжины элементов, внесите их в мультимножество. Выведите его содержимое. Задайте имена людей таким образом, чтобы некоторые из них совпадали. Тем самым можно будет удостовериться в том, что мультимножество может хранить несколько объектов с одинаковым ключом.
#include "../../accessories.h"
#include <algorithm>
#include <set>
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
class person
{
	char* name;
	public:
	person(char* NewName){name=NewName;}
	~person(){cout<<"delete "<<name<<endl; delete[] name;}
	void display(){cout<<name<<endl;}
	char* GetName()const{return name;}
};
class ComparePersons
{
	public: bool operator() (const person* person1,const person* person2)const
	{
		char *word1=person1->GetName(),*word2=person2->GetName(),ch1,ch2;
		int i,MinLength=strlen(word1);		
		if(strlen(word2)<MinLength)			
			MinLength=strlen(word2);
		for(i=0; i<MinLength; i++)
		{
			if(isdigit(word1[i]) && !isdigit(word2[i]))
				return true;
			if(!isdigit(word1[i]) && isdigit(word2[i]))
				return false;
			if(word1[i]>='0' && word1[i]<='9')
				ch1=word1[i]-'0';
			else
				if(word1[i]>='a' && word1[i]<='z')
					ch1=word1[i]-'a';
				else
					if(word1[i]>='A' && word1[i]<='Z')
						ch1=word1[i]-'A';
			if(word2[i]>='0' && word2[i]<='9')
				ch2=word2[i]-'0';
			else
				if(word2[i]>='a' && word2[i]<='z')
					ch2=word2[i]-'a';
				else
					if(word2[i]>='A' && word2[i]<='Z')
						ch2=word2[i]-'A';
			if(ch1<ch2)
				return true;
			if(ch1>ch2)
				return false;
		}
		return false;
	}
};
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	multiset<person*,ComparePersons> persons;
	int i,CountOfNames=30;
	for(i=0; i<CountOfNames; i++)
		persons.insert(new person(GetRandomName(GetRandomInt(3,10))));
	multiset<person*,ComparePersons>::iterator MultisetIterator=persons.begin();
	for(i=GetRandomInt(1,CountOfNames); i>-1; i--)
		MultisetIterator++;
	char* EqualName=new char[11];
	strcpy(EqualName,(*MultisetIterator++)->GetName());
	persons.insert(new person(EqualName));
	for(i=1,MultisetIterator=persons.begin(); MultisetIterator!=persons.end(); i++)
	{
		cout<<i<<". ";
		(*MultisetIterator++)->display();		
	}	
	for(MultisetIterator=persons.begin(); MultisetIterator!=persons.end();)
		delete (*MultisetIterator++);
	return 0;
}
