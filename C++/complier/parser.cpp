#include "parser.h"
using namespace ParserClasses;
char operators[21][3]={"-","*","^",">",",",";","\"","(",")","{","}","+","/","=","<","++","==","!=","//","<<","||"};
// char OneCharOperators[15]={'-','*','^','>','<',',',';','\"','(',')','{','}','+','/','='};
char KeyWords[][8]={"int","longint","float","double","bool","program","if","for","endl"};
char types[][23]={"program name","comment","initialized variable","uninitialized variable","constant","operator","condition","loop","bracket"};
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
	if(isalpha(ch) || isdigit(ch) || ch=='_' || ch=='.')
		return false;
	return true;
}
void parse()
{
	int i,j,k,l,CountOfLines=0,LineLength,CountOfWords;
	int* LengthsOfLines=(int*)calloc(1000,sizeof(int));
	int* CountsOfWords=(int*)calloc(1000,sizeof(int));
	int* CountsOfObjects=(int*)calloc(1000,sizeof(int));
	char ch,CharType,***chars=new char**[1000];
	char*** words=new char**[1000];	
	ifstream MyLangFile("test.mylang");
	ProgramObject*** ProgramObjects=new ProgramObject**[1000];
	MyLangFile.read(&ch,sizeof(char));
	while(!MyLangFile.eof())
	{		
		LineLength=0;
		chars[CountOfLines]=new char*[1000];
		while((ch==' ' || ch=='\t') && (ch!='\n' && !MyLangFile.eof()))
			MyLangFile.read(&ch,sizeof(char));
		while(ch!='\n' && !MyLangFile.eof())
		{			
			while(ch!=' ' && ch!='\t' && ch!='\n' && !MyLangFile.eof())
			{
				chars[CountOfLines][LineLength]=(char*)calloc(2,sizeof(char));
				chars[CountOfLines][LineLength][0]=ch;
				chars[CountOfLines][LineLength++][1]=IsOperator(ch);
				MyLangFile.read(&ch,sizeof(char));
				if(LineLength>0 && chars[CountOfLines][LineLength-1][0]=='/' && ch=='/')
				{
					chars[CountOfLines][LineLength]=(char*)calloc(2,sizeof(char));
					chars[CountOfLines][LineLength][0]=ch;
					chars[CountOfLines][LineLength++][1]=1;
					MyLangFile.read(&ch,sizeof(char));
					while(ch!='\n' && !MyLangFile.eof())
					{
						chars[CountOfLines][LineLength]=(char*)calloc(2,sizeof(char));
						chars[CountOfLines][LineLength][0]=ch;
						chars[CountOfLines][LineLength++][1]=0;
						MyLangFile.read(&ch,sizeof(char));
					}
				}
				if(ch=='\"')
				{
					chars[CountOfLines][LineLength]=(char*)calloc(2,sizeof(char));
					chars[CountOfLines][LineLength][0]=ch;
					chars[CountOfLines][LineLength++][1]=1;
					MyLangFile.read(&ch,sizeof(char));
					while(ch!='\"' && ch!='\n' && !MyLangFile.eof())
					{
						chars[CountOfLines][LineLength]=(char*)calloc(2,sizeof(char));
						chars[CountOfLines][LineLength][0]=ch;
						chars[CountOfLines][LineLength++][1]=0;
						MyLangFile.read(&ch,sizeof(char));
					}
				}					
			}
			if(ch==' ' || ch=='\t')
			{
				chars[CountOfLines][LineLength]=(char*)calloc(2,sizeof(char));
				chars[CountOfLines][LineLength][0]=ch;
				chars[CountOfLines][LineLength++][1]=2;
				MyLangFile.read(&ch,sizeof(char));
			}
		}
		LengthsOfLines[CountOfLines]=LineLength;
		CountOfLines++;
		MyLangFile.read(&ch,sizeof(char));
	}
	for(i=0; i<CountOfLines; i++)
	{
		words[i]=new char*[200];
		j=0;
		CountOfWords=0;
		while(j<LengthsOfLines[i])
		{
			// while(j<LengthsOfLines[i] && chars[i][j][1]==2)
				// j++;
			CharType=chars[i][j][1];
			k=0;
			words[i][CountOfWords]=(char*)calloc(500,sizeof(char));
			while(j<LengthsOfLines[i] && CharType==chars[i][j][1])
			{				
				if(chars[i][j][1]==1)
				{
					CharType=0;
					for(k=0; k<21; k++)
						if(chars[i][j][0]==operators[k][0])
						{
							CharType=1;
							if(/*j+1<LengthsOfLines[i] &&*/ k>10)
							{
								l=j+1;
								while(l<LengthsOfLines[i] && chars[i][l][1]==2)
									l++;
								if(l<LengthsOfLines[i] && chars[i][l][1]==1)
									for(k=15; k<21; k++)
										if(chars[i][l][0]==operators[k][1])
										{
											CharType=2;
											break;
										}
							}
							break;
						}
					if(CharType==1)
					{
						words[i][CountOfWords][0]=chars[i][j][0];
						j++;
					}
					else
						if(CharType==2)
						{
							words[i][CountOfWords][0]=chars[i][j][0];
							words[i][CountOfWords][1]=chars[i][l][0];
							j+=2;
						}
					break;
				}
				words[i][CountOfWords][k]=chars[i][j][0];
				k++;
				j++;
			}
			CountOfWords++;
			while(j<LengthsOfLines[i] && chars[i][j][1]==2)
				j++;
		}
		CountsOfWords[i]=CountOfWords;
	}
	for(i=0; i<CountOfLines; i++)
	{
		cout<<"Line "<<i+1<<"; LengthsOfLines[i]: "<<LengthsOfLines[i]<<"; CountsOfWords: "<<CountsOfWords[i]<<":\n";
		for(j=0; j<LengthsOfLines[i]; j++)		
		{
			// cout<<(int)chars[i][j][1]<<"|";
			delete[] chars[i][j];
		}
		for(j=0; j<CountsOfWords[i]; j++)
		{
			cout<<words[i][j]<<"|\n";
			delete[] words[i][j];
		}
		delete[] chars[i];
		delete[] words[i];
		cout<<"---------------------------------------------\n";
	}
	delete[] chars;
	delete[] words;
	delete[] CountsOfWords;
	delete[] LengthsOfLines;
	delete[] CountsOfObjects;
}