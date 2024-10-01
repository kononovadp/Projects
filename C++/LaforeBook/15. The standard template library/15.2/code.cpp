//*2. Примените алгоритм sort() к массиву слов, введенных пользователем, выведите результат. Используйте push_back() для добавления слов, а оператор [] и size() — для вывода их на экран.
#include "../../accessories.h"
#include <algorithm>
#include <vector>
class SortWords
{
	public: bool operator() (char* word1,char* word2)
	{
		int i,MinLength=strlen(word1);
		char ch1,ch2;
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
char* GetRandomWord(int length)
{
	int i,RandomNumber;
	char* word=new char[length+1];
	for(i=0; i<length; i++)
	{
		RandomNumber=GetRandomInt(1,30);
		if(RandomNumber>=1 && RandomNumber<10)
			word[i]=GetRandomChar('a','z');
		else
			if(RandomNumber>=10 && RandomNumber<20)
				word[i]=GetRandomChar('A','Z');
			else
				if(RandomNumber>=20 && RandomNumber<=30)
					word[i]=GetRandomChar('0','9');
	}
	word[i]='\0';
	return word;
}
char* GetWordFromKeyboard(int WordNumber,int MaxCountOfWords)
{
	int i=0;
	char ch,*word=new char[91];
	cout<<"Word "<<WordNumber<<" / "<<MaxCountOfWords<<": ";
	for(i=0,ch=getch(); ch!=13 && i<90; ch=getch())
	{
		if(isdigit(ch) || isalpha(ch))
		{
			word[i++]=ch;
			cout<<ch;
		}
	}
	cout<<endl;
	word[i]='\0';
	return word;
}
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	int CountOfWords=GetRandomInt(10,20);
	vector<char*> words;	
	int i;
	for(i=0; i<CountOfWords; i++)
		//words.push_back(GetRandomWord(GetRandomInt(10,80)));
		words.push_back(GetWordFromKeyboard(i+1,CountOfWords));
	cout<<"Count of words: "<<words.size()<<"; ENTERED WORDS:\n";
	for(i=0; i<words.size(); i++)
		cout<<words[i]<<endl;
	sort(words.begin(),words.end(),SortWords());
	for(i=0; i<91; i++)
		cout<<'-';	
	for(i=0; i<words.size(); i++)
	{
		cout<<words[i]<<endl;
		delete[] words[i];
	}	
	return 0;
}
