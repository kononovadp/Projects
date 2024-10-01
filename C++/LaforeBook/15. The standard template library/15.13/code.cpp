//13. Частотная таблица представляет собой список слов и количество их вхождений в данном тексте. Напишите программу, создающую частотную таблицу для файла, имя которого введет пользователь. Для решения этой задачи хорошо подходит отображение, содержащее пары значений string-int. Можно использовать библиотечную функцию C под названием ispunct() (см. заголовочный файл CTYPE.H) для проверки правильности пунктуации, чтобы знать, где кончается каждое слово, и выделять его в подстроку методом substr(). Кроме того, функцией tolower() можно сделать все буквы слов строчными.
#include "../../accessories.h"
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>
#include <functional>
char* GetRandomWord()
{
	int i,length=GetRandomInt(3,10);
	char* word=new char[length+1];
	word[0]=GetRandomChar('A','Z');
	for(i=1; i<length; i++)
		word[i]=GetRandomChar('a','z');
	word[i]='\0';
	return word;
}
void ShuffleVector(vector<char*>& words)
{
	char* temp;
	int i,RandomPos;
	for(i=0; i<words.size(); i++)
	{
		RandomPos=0+(rand()%(words.size()-0));
		temp=words[i];
		words[i]=words[RandomPos];
		words[RandomPos]=temp;
	}
}
void WriteRandomTextToFile()
{
	InitFloatingPointAndRandomNumbers();
	vector<char*> words;
	vector<char*> text;
	int i,j,CountOfWords=GetRandomInt(10,30),CountOfRepetitions;
	for(i=0; i<CountOfWords; i++)
	{
		words.push_back(GetRandomWord());
		CountOfRepetitions=GetRandomInt(1,5);
		for(j=0; j<CountOfRepetitions; j++)
			text.push_back(words[i]);
	}
	ShuffleVector(text);
	ofstream OutputFile("text.txt");
	for(i=0; i<text.size(); i++)
	{
		OutputFile<<text[i];
		for(j=0,CountOfRepetitions=GetRandomInt(1,5); j<CountOfRepetitions; j++)
			OutputFile<<" ";
	}
	OutputFile.close();
	for(i=0; i<words.size(); i++)
		delete[] words[i];
}
class CompareArraysOfChars
{
	public: bool operator() (const char* str1,const char* str2)const
	{
		return strcmp(str1,str2)<0;		
	}
};
int main(void)
{
	//WriteRandomTextToFile();
	int i=0;
	char ch=0,*word=new char[10];
	map<char*,int,CompareArraysOfChars> words;
	map<char*,int>::iterator WordsIterator;
	ifstream  InputFile("text.txt",ios::binary);
	InputFile.read((char*)&ch,sizeof(ch));
	while(true)
	{
		if(ch!=' ')
		{
			if(InputFile.eof())
				break;
			word[i++]=ch;
			InputFile.read((char*)&ch,sizeof(ch));
		}
		else
		{
			word[i]=0;
			char* NewWord=new char[11];
			strcpy(NewWord,word);
			words[NewWord]++;
			i=0;			
			while(!InputFile.eof() && ch==' ')			
				InputFile.read((char*)&ch,sizeof(ch));			
			if(InputFile.eof())
				break;
		}		
	}
	for(WordsIterator=words.begin(); WordsIterator!=words.end(); WordsIterator++)
	{
		cout<<"The word \""<<(*WordsIterator).first<<"\" appears "<<(*WordsIterator).second<<" times\n";
		delete[] (*WordsIterator).first;
	}	
	InputFile.close();
	return 0;
}
