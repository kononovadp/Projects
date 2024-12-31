#include "parser.h"
using namespace ParserClasses;
bool IsIdentifierCorrect(char* identifier)
{
	if(isdigit(identifier[0]))
		return false;
	int i,length=strlen(identifier)-1;
	for(i=0; i<length; i++)
		if(!isalpha(identifier[i]) && !isdigit(identifier[i]))
			return false;
	if(!isalpha(identifier[i]) && !isdigit(identifier[i]) && identifier[i]!=';')
		return false;
	return true;
}
ProgramObject::ProgramObject(){}
ProgramObject::ProgramObject(char* NewType):type(NewType){}
void ProgramObject::display(){cout<<"TYPE: "<<type<<";\n";}
ProgramName::ProgramName(char* NewType,char* NewProgramName):ProgramObject(NewType),name(NewProgramName){}
comment::comment(char* NewType,char* NewComment):ProgramObject(NewType),text(NewComment){}
void comment::display()
{
	ProgramObject::display();
	cout<<"comment: "<<text<<endl;
}
variable::variable(char* NewType,char* NewDataType,char* NewName,char* NewValue):
ProgramObject(NewType),DataType(NewDataType),name(NewName),value(NewValue){}
void variable::display()
{
	ProgramObject::display();
	cout<<"DATA TYPE: "<<DataType<<"; NAME: "<<name<<"; VALUE: "<<value<<";\n";
}
bool IsOperator(char ch)
{
	if(isalpha(ch) || isdigit(ch) || ch=='_' || ch=='.' || ch=='/'/* || ch!='(' || ch!=')'*/)
		return false;
	return true;
}
bool OperatorConsistsOfTwoChars(char ch)
{
	if(ch=='=' || ch=='!' || ch=='/' || ch=='<' || ch=='|')
		return true;
	return false;
}
void parse()
{
	char operators[][3]={"+","-","*","/","^","=",">","<",",",";","++","==","!=","//","<<","||"};
	char DataTypes[][8]={"int","longint","float","double","bool"};
	char types[][23]={"program name","comment","initialized variable","uninitialized variable","constant","operator","condition","loop","bracket"};
	int i,j,k,LineNumber=0,WordNumber=0,WordLength;	
	int* CountsOfWords=(int*)calloc(1000,sizeof(int));
	int* CountsOfObjects=(int*)calloc(1000,sizeof(int));
	char ch,*word=(char*)calloc(50,sizeof(char));
	char*** words=new char**[1000];
	words[0]=new char*[100];	
	ifstream MyLangFile("test.mylang");
	ProgramObject*** ProgramObjects=new ProgramObject**[1000];
	MyLangFile.read(&ch,sizeof(char));
	while(!MyLangFile.eof())
	{
		WordLength=0;
		words[LineNumber][WordNumber]=(char*)calloc(50,sizeof(char));
		while((ch==' ' || ch=='\t') && (ch!='\n' && !MyLangFile.eof()))
			MyLangFile.read(&ch,sizeof(char));
		if(IsOperator(ch))
		{
			if(OperatorConsistsOfTwoChars(ch))
				while(ch!=' ' && ch!='\t' && ch!='\n' && !MyLangFile.eof() && IsOperator(ch))
				{			
					words[LineNumber][WordNumber][WordLength++]=ch;
					MyLangFile.read(&ch,sizeof(char));
				}
			else
			{
				words[LineNumber][WordNumber][WordLength++]=ch;
				MyLangFile.read(&ch,sizeof(char));
			}
			
		}
		else
			while(ch!=' ' && ch!='\t' && ch!='\n' && !MyLangFile.eof() && !IsOperator(ch))
			{			
				words[LineNumber][WordNumber][WordLength++]=ch;
				MyLangFile.read(&ch,sizeof(char));
			}
		if(strlen(words[LineNumber][WordNumber])>0)
		{
			CountsOfWords[LineNumber]++;
			// if(words[LineNumber][WordNumber][0]=='/' && words[LineNumber][WordNumber][1]=='/')
			// {
				// // words[LineNumber][WordNumber][WordLength++]=ch;
				// while(ch!='\n' && !MyLangFile.eof())
				// {
					// words[LineNumber][WordNumber][WordLength++]=ch;
					// MyLangFile.read(&ch,sizeof(char));					
				// }
			// }
			WordNumber++;
		}
		if(ch=='\n')
		{
			WordNumber=0;
			LineNumber++;
			words[LineNumber]=new char*[100];
			MyLangFile.read(&ch,sizeof(char));
		}
		
	}
	/*for(i=0; i<=LineNumber; i++)
	{
		ProgramObjects[i]=new ProgramObject*[50];
		for(j=0; j<CountsOfWords[i]; j++)
		{			
			if(strlen(words[i][j])>1 && words[i][j][0]=='/' && words[i][j][0]=='/')
			{
				char* NewComment=(char*)calloc(1000,sizeof(char));
				for(k=j; k<CountsOfWords[i]; k++)
				{
					strcat(NewComment,words[i][k]);
					NewComment[strlen(NewComment)]=' ';
				}
				ProgramObjects[i][j]=new comment(types[1],NewComment);
				CountsOfObjects[i]++;
				j=k;
				
			}
		}
	}*/
	for(i=0; i<=LineNumber; i++)
	{
		cout<<"LINE: "<<i+1<<"; COUNT OF WORDS: "<<CountsOfWords[i]<<";\n";
		for(j=0; j<CountsOfWords[i]; j++)
			cout<<words[i][j]<<endl;
		for(j=0; j<91; j++)
			cout<<'-';
	}
	for(i=0; i<=LineNumber; i++)
	{
		for(j=0; j<CountsOfWords[i]; j++)
			delete[] words[i][j];
		delete[] words[i];
	}
	delete[] word;
	delete[] words;
	delete[] CountsOfWords;
	delete[] CountsOfObjects;
}