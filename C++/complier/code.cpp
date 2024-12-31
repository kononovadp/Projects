#include "parser.h"
char ArithmeticOperations[5][3]={"+","-","*","/","**"};
char DelphiComparisonOperations[4][3]={">","<","=","<>"};
char MyLangComparisonOperations[4][3]={">","<","==","!="};
char MyLangTypes[][8]={"int","longint","float","double","bool"};
void AddRandomIdentifier(int length,char* text)
{
	int TextLength=strlen(text);
	int i,choice=GetRandomInt(1,20);
		if(choice<15 && choice>10)
			text[TextLength++]=GetRandomChar('A','Z');
		else
			text[TextLength++]=GetRandomChar('a','z');
	for(i=1; i<length; i++,TextLength++)
	{
		choice=GetRandomInt(1,20);
		if(choice<15 && choice>10)
			text[TextLength]=GetRandomChar('A','Z');
		else
			if(choice<10 && choice>5)
				text[TextLength]=GetRandomChar('0','9');
			else
				text[TextLength]=GetRandomChar('a','z');
	}
}
void AddRandomInt(int length,char* text)
{
	int TextLength=strlen(text);
	text[TextLength++]=GetRandomInt(1,10)+'0';
	for(int i=1; i<length; i++)
		text[TextLength++]=GetRandomInt(0,10)+'0';
}
void AddRandomFloat(int IntPartLength,int FractPartLength,char* text)
{
	int i,TextLength=strlen(text),FloatingPointPosition;
	text[TextLength]=GetRandomDigit('0','9');
	if(text[TextLength]=='0')
	{
		i=1;
		IntPartLength=1;
	}
	else
	{
		i=0;
		FloatingPointPosition=GetRandomInt(1,9);
	}
	for(TextLength++; i<IntPartLength; i++)
		text[TextLength++]=GetRandomDigit('0','9');
	text[TextLength]='.';
	for(i=0,TextLength++; i<FractPartLength-1; i++)
		text[TextLength++]=GetRandomDigit('0','9');
	text[TextLength]=GetRandomDigit('1','9');
}
char* GetMyLangType(char* type)
{
	char* NewType;
	switch(type[0])
	{
		case 'i': NewType=MyLangTypes[0]; break;
		case 'l': NewType=MyLangTypes[1]; break;
		case 'f': NewType=MyLangTypes[2]; break;
		case 'e': NewType=MyLangTypes[3]; break;
		case 'b': NewType=MyLangTypes[4]; break;
	}
	return NewType;
}
char GetMyLangArithmeticOperation(char* operation)
{
	if(operation[1]=='*')
		return '^';
	return operation[0];
}
char* GetMyLangComparisonOperation(char* operation)
{
	if(operation[1]=='>')
		return MyLangComparisonOperations[3];
	if(operation[0]=='=')
		return MyLangComparisonOperations[2];
	return operation;
}
class variable
{
	char* type;
	char* name;
	char* value;	
	public: variable(){}
	variable(char* NewType)
	{
		type=(char*)calloc(21,sizeof(char));
		strcpy(type,NewType);
		name=(char*)calloc(12,sizeof(char));
		value=(char*)calloc(21,sizeof(char));
		AddRandomIdentifier(GetRandomInt(3,11),name);
		switch(type[0])
		{
			case 'i': AddRandomInt(GetRandomInt(1,5),value); break;
			case 'l': AddRandomInt(GetRandomInt(1,7),value); break;
			case 'f': AddRandomFloat(GetRandomInt(1,5),GetRandomInt(1,5),value); break;
			case 'e': AddRandomFloat(GetRandomInt(1,7),GetRandomInt(1,7),value); break;
			case 'b': value[0]=rand()%2; break;
		}		
	}
	variable(char* NewType,char* NewName,char* NewValue)
	{
		type=(char*)calloc(21,sizeof(char));
		strcpy(type,NewType);
		name=(char*)calloc(11,sizeof(char));
		strcpy(name,NewName);
		value=(char*)calloc(21,sizeof(char));
		strcpy(value,NewValue);		
	}
	char* GetType() {return type;}
	char* GetName() {return name;}
	char* GetValue(){return value;}	
	~variable()
	{		
		delete[] type;
		delete[] name;
		delete[] value;
	}
	void display()
	{
		cout<<"TYPE: "<<type<<"; NAME: "<<name<<"; VALUE: ";
		if(type[0]!='b')
			cout<<value<<endl;
		else
			switch(value[0])
			{
				case 1: cout<<"TRUE\n"; break;
				case 0: cout<<"FALSE\n"; break;
			}
	}
};
class operation
{	
	int NumberOfArithmeticOperation,NumberOfComparisonOperation;
	void ShuffleArrayOfOperations(char array[][3],int ArraySize)
	{
		int i,j;
			char* t=new char[3];
			for(i=0; i<5; i++)
			{
				j=0+(rand()%5);
				strcpy(t,ArithmeticOperations[i]);
				strcpy(ArithmeticOperations[i],ArithmeticOperations[j]);
				strcpy(ArithmeticOperations[j],t);
			}
			delete[] t;
	}
	public:
	operation():NumberOfArithmeticOperation(0),NumberOfComparisonOperation(0)
	{
		ShuffleArrayOfOperations(ArithmeticOperations,5);
		ShuffleArrayOfOperations(DelphiComparisonOperations,4);
	}
	char* GetArithmeticOperation()
	{
		if(NumberOfArithmeticOperation==5)
		{			
			NumberOfArithmeticOperation=0;
			ShuffleArrayOfOperations(ArithmeticOperations,5);
		}
		return ArithmeticOperations[NumberOfArithmeticOperation++];
	}
	char* GetComparisonOperation()
	{
		if(NumberOfComparisonOperation==4)
		{			
			NumberOfComparisonOperation=0;
			ShuffleArrayOfOperations(DelphiComparisonOperations,4);
		}
		return DelphiComparisonOperations[NumberOfComparisonOperation++];
	}
};
void AddRandomArithmeticExpression(char* DelphiCode,char* MyLangCode,variable*** variables,int* CountsOfVariables,operation* operations,int depth)
{
	if(depth==0)
	{
		char choice;
		if(rand()%2)
		{
			char type=GetRandomDigit(0,4);
			char number=GetRandomInt(0,CountsOfVariables[type]);
			strcat(DelphiCode,variables[type][number]->GetName());
			strcat(MyLangCode,variables[type][number]->GetName());
		}
		else
		{
			choice=GetRandomDigit(0,2);
			char* RandomNumber=(char*)calloc(20,sizeof(char));
			switch(choice)
			{
				case 0: AddRandomInt(GetRandomInt(1,5),RandomNumber); break;
				case 1: AddRandomFloat(GetRandomInt(1,5),GetRandomInt(1,5),RandomNumber); break;
			}
			strcat(DelphiCode,RandomNumber);
			strcat(MyLangCode,RandomNumber);
			delete[] RandomNumber;
		}
		return;
	}
	int DelphiCodeLength=strlen(DelphiCode);
	int MyLangCodeLength=strlen(MyLangCode);
	bool brackets=rand()%2;
	if(brackets)
	{
		DelphiCode[DelphiCodeLength++]='(';
		MyLangCode[MyLangCodeLength++]='(';
	}
	AddRandomArithmeticExpression(&DelphiCode[DelphiCodeLength],&MyLangCode[MyLangCodeLength],variables,CountsOfVariables,operations,depth-1);
	DelphiCodeLength=strlen(DelphiCode);	
	DelphiCode[DelphiCodeLength++]=' ';	
	MyLangCodeLength=strlen(MyLangCode);	
	MyLangCode[MyLangCodeLength++]=' ';	
	char* operation=operations->GetArithmeticOperation();
	strcat(DelphiCode,operation);	
	MyLangCode[strlen(MyLangCode)]=GetMyLangArithmeticOperation(operation);	
	DelphiCodeLength+=strlen(operation);
	DelphiCode[DelphiCodeLength++]=' ';
	MyLangCodeLength++;
	MyLangCode[MyLangCodeLength++]=' ';	
	if(operation[1]=='*')
	{
		if(rand()%2)
		{
			char VariableNumber=GetRandomDigit(0,CountsOfVariables[5]);
			strcat(DelphiCode,variables[5][VariableNumber]->GetName());
			strcat(MyLangCode,variables[5][VariableNumber]->GetName());
		}
		else
		{
			char RandomPower=GetRandomDigit(1,10);
			DelphiCode[DelphiCodeLength++]=RandomPower+'0';
			MyLangCode[MyLangCodeLength++]=RandomPower+'0';
		}
	}
	else	
		AddRandomArithmeticExpression(&DelphiCode[DelphiCodeLength],&MyLangCode[MyLangCodeLength],variables,CountsOfVariables,operations,depth-1);
	if(brackets)
	{
		DelphiCode[strlen(DelphiCode)]=')';
		MyLangCode[strlen(MyLangCode)]=')';
	}
}
char* GetSecondOperand(variable*** variables,int* CountsOfVariables,char type)
{
	char choice,*SecondOperand=(char*)calloc(12,sizeof(char));
	switch(type)
	{
		case 'i':
			choice=GetRandomDigit(0,3);
			switch(choice)
			{
				case 0: AddRandomInt(GetRandomInt(1,5),SecondOperand); break;
				case 1: strcpy(SecondOperand,variables[0][GetRandomDigit(0,CountsOfVariables[0])]->GetName()); break;
				case 2: strcpy(SecondOperand,variables[5][GetRandomDigit(0,CountsOfVariables[5])]->GetName()); break;
			}
		break;
		case 'l':
			choice=GetRandomDigit(0,2);
			switch(choice)
			{
				case 0: AddRandomInt(GetRandomInt(1,7),SecondOperand); break;
				case 1: strcpy(SecondOperand,variables[1][GetRandomDigit(0,CountsOfVariables[1])]->GetName()); break;
			}
		break;
		case 'f':
			choice=GetRandomDigit(0,4);
			switch(choice)
			{
				case 0: AddRandomFloat(GetRandomInt(1,5),GetRandomInt(1,5),SecondOperand); break;
				case 1: strcpy(SecondOperand,variables[2][GetRandomDigit(0,CountsOfVariables[2])]->GetName()); break;
				case 2: strcpy(SecondOperand,variables[0][GetRandomDigit(0,CountsOfVariables[0])]->GetName()); break;
				case 3: strcpy(SecondOperand,variables[5][GetRandomDigit(0,CountsOfVariables[5])]->GetName()); break;
			}
		break;
		case 'e':
			choice=GetRandomDigit(0,6);
			switch(choice)
			{
				case 0: AddRandomFloat(GetRandomInt(1,7),GetRandomInt(1,7),SecondOperand); break;
				case 1: strcpy(SecondOperand,variables[3][GetRandomDigit(0,CountsOfVariables[3])]->GetName()); break;
				case 2: strcpy(SecondOperand,variables[0][GetRandomDigit(0,CountsOfVariables[0])]->GetName()); break;
				case 3: strcpy(SecondOperand,variables[1][GetRandomDigit(0,CountsOfVariables[1])]->GetName()); break;
				case 4: strcpy(SecondOperand,variables[2][GetRandomDigit(0,CountsOfVariables[2])]->GetName()); break;
				case 5: strcpy(SecondOperand,variables[5][GetRandomDigit(0,CountsOfVariables[5])]->GetName()); break;
			}
		break;
		case 'b':
			choice=GetRandomDigit(0,3);
			switch(choice)
			{
				case 0: strcpy(SecondOperand,"false"); break;
				case 1: strcpy(SecondOperand,"true"); break;
				case 2: strcpy(SecondOperand,variables[4][GetRandomDigit(0,CountsOfVariables[4])]->GetName()); break;
			}
		break;
	}
	return SecondOperand;
}
void AddRandomCode(char* DelphiCode,char* MyLangCode,variable*** variables,int* CountsOfVariables,char* UsedLoopVariables,operation* operations,int CountOfTabs,int depth)
{
	int i,j,DelphiCodeLength=strlen(DelphiCode);
	int MyLangCodeLength=strlen(MyLangCode);
	char choice=GetRandomDigit(0,3),*SecondOperand;
	for(i=0; i<CountOfTabs; i++)
	{
		DelphiCode[DelphiCodeLength++]='	';
		MyLangCode[MyLangCodeLength++]='	';
	}
	if(depth==0)
	{		
		char* name;
		int i,CountOfWritelnVariables=GetRandomDigit(1,6);
		int TypeNumber,VariableNumber;
		switch(choice)
		{
			case 0:
				CountOfWritelnVariables=GetRandomDigit(0,5);
				strcat(DelphiCode,"writeln(");
				strcat(MyLangCode,"<< ");
				for(i=0; i<CountOfWritelnVariables-1; i++)
				{
					TypeNumber=GetRandomDigit(0,6);
					VariableNumber=GetRandomDigit(0,CountsOfVariables[TypeNumber]);
					name=variables[TypeNumber][VariableNumber]->GetName();
					DelphiCode[strlen(DelphiCode)]='\'';
					MyLangCode[strlen(MyLangCode)]='\"';
					strcat(DelphiCode,name);
					strcat(DelphiCode,": \',");
					strcat(DelphiCode,name);					
					strcat(MyLangCode,name);
					strcat(MyLangCode,": \" || ");
					strcat(MyLangCode,name);
					if(TypeNumber==2 || TypeNumber==3)
					{
						strcat(DelphiCode,":0:5");
						strcat(MyLangCode,":5");
					}
					strcat(DelphiCode,",#13#10,");
					strcat(MyLangCode," || endl || ");
				}
				TypeNumber=GetRandomDigit(0,6);
				VariableNumber=GetRandomDigit(0,CountsOfVariables[TypeNumber]);
				name=variables[TypeNumber][VariableNumber]->GetName();
				DelphiCode[strlen(DelphiCode)]='\'';
				MyLangCode[strlen(MyLangCode)]='\"';
				strcat(DelphiCode,name);
				strcat(DelphiCode,": \',");
				strcat(DelphiCode,name);					
				strcat(MyLangCode,name);
				strcat(MyLangCode,": \" || ");
				strcat(MyLangCode,name);
				if(TypeNumber==2 || TypeNumber==3)
				{
					strcat(DelphiCode,":0:5");
					strcat(MyLangCode,":5");
				}
				strcat(DelphiCode,",#13#10");
				strcat(MyLangCode," || endl || ");
				// strcat(DelphiCode,"\'-----\');\n");
				// strcat(MyLangCode,"\"-----\" || endl;\n");
				strcat(DelphiCode,");\n");
				strcat(MyLangCode," || endl;\n");
			break;
			case 1:
				TypeNumber=GetRandomDigit(0,5);
				VariableNumber=GetRandomDigit(0,CountsOfVariables[TypeNumber]);
				SecondOperand=GetSecondOperand(variables,CountsOfVariables,variables[TypeNumber][VariableNumber]->GetType()[0]);
				strcat(DelphiCode,variables[TypeNumber][VariableNumber]->GetName());
				strcat(DelphiCode," := ");				
				strcat(DelphiCode,SecondOperand);
				strcat(DelphiCode,";\n");				
				strcat(MyLangCode,variables[TypeNumber][VariableNumber]->GetName());
				strcat(MyLangCode," = ");
				strcat(MyLangCode,SecondOperand);
				strcat(MyLangCode,";\n");
				delete[] SecondOperand;
			break;
			case 2:
				strcat(DelphiCode,"result := ");
				strcat(MyLangCode,"result = ");
				AddRandomArithmeticExpression(DelphiCode,MyLangCode,variables,CountsOfVariables,operations,GetRandomDigit(2,5));
				strcat(DelphiCode,";\n");
				strcat(MyLangCode,";\n");
			break;
		}
		return;
	}
	if(choice==0)
	{		
		char* operation=operations->GetComparisonOperation();
		int TypeNumber=GetRandomDigit(0,6);
		int VariableNumber=GetRandomDigit(0,CountsOfVariables[TypeNumber]);
		strcat(DelphiCode,"if ");
		strcat(DelphiCode,variables[TypeNumber][VariableNumber]->GetName());
		DelphiCode[strlen(DelphiCode)]=' ';
		strcat(DelphiCode,operation);
		DelphiCode[strlen(DelphiCode)]=' ';
		SecondOperand=GetSecondOperand(variables,CountsOfVariables,variables[TypeNumber][VariableNumber]->GetType()[0]);
		strcat(DelphiCode,SecondOperand);
		strcat(DelphiCode," then\n");		
		strcat(MyLangCode,"if ");
		strcat(MyLangCode,variables[TypeNumber][VariableNumber]->GetName());
		MyLangCode[strlen(MyLangCode)]=' ';
		strcat(MyLangCode,GetMyLangComparisonOperation(operation));
		MyLangCode[strlen(MyLangCode)]=' ';
		strcat(MyLangCode,SecondOperand);
		MyLangCode[strlen(MyLangCode)]='\n';
		delete[] SecondOperand;
		choice=GetRandomDigit(1,5);
		if(choice>1)
		{
			MyLangCodeLength=strlen(MyLangCode);
			for(i=0,DelphiCodeLength=strlen(DelphiCode); i<CountOfTabs; i++)
			{
				DelphiCode[DelphiCodeLength++]='	';
				MyLangCode[MyLangCodeLength++]='	';
			}
			strcat(DelphiCode,"begin\n");
			strcat(MyLangCode,"{\n");
		}
		for(i=0; i<choice; i++)
			AddRandomCode(DelphiCode,MyLangCode,variables,CountsOfVariables,UsedLoopVariables,operations,CountOfTabs+1,depth-1);
		if(choice>1)
		{
			MyLangCodeLength=strlen(MyLangCode);
			for(i=0,DelphiCodeLength=strlen(DelphiCode); i<CountOfTabs; i++)
			{
				DelphiCode[DelphiCodeLength++]='	';
				MyLangCode[MyLangCodeLength++]='	';
			}
			strcat(DelphiCode,"end;\n");
			strcat(MyLangCode,"}\n");
		}
	}
	else
	{
		for(i=0; i<CountsOfVariables[6]; i++)
			if(UsedLoopVariables[variables[6][i]->GetName()[0]]==0)
			{
				UsedLoopVariables[variables[6][i]->GetName()[0]]=1;
				strcat(DelphiCode,"for ");
				DelphiCode[strlen(DelphiCode)]=variables[6][i]->GetName()[0];
				strcat(DelphiCode," := ");
				strcat(MyLangCode,"for ");
				MyLangCode[strlen(MyLangCode)]=variables[6][i]->GetName()[0];
				SecondOperand=GetSecondOperand(variables,CountsOfVariables,variables[6][i]->GetType()[0]);
				strcat(DelphiCode,SecondOperand);
				strcat(MyLangCode," = ");
				strcat(MyLangCode,SecondOperand);
				delete[] SecondOperand;
				strcat(DelphiCode," to ");
				strcat(MyLangCode,"; ");
				MyLangCode[strlen(MyLangCode)]=variables[6][i]->GetName()[0];
				strcat(MyLangCode," < ");
				SecondOperand=GetSecondOperand(variables,CountsOfVariables,variables[6][i]->GetType()[0]);
				strcat(DelphiCode,SecondOperand);
				strcat(MyLangCode,SecondOperand);
				delete[] SecondOperand;
				strcat(DelphiCode," do\n");
				strcat(MyLangCode,"; ");
				MyLangCode[strlen(MyLangCode)]=variables[6][i]->GetName()[0];
				strcat(MyLangCode,"++\n");
				choice=GetRandomDigit(1,5);
				if(choice>1)
				{
					MyLangCodeLength=strlen(MyLangCode);
					for(j=0,DelphiCodeLength=strlen(DelphiCode); j<CountOfTabs; j++)
					{
						DelphiCode[DelphiCodeLength++]='	';
						MyLangCode[MyLangCodeLength++]='	';
					}
					strcat(DelphiCode,"begin\n");
					strcat(MyLangCode,"{\n");
				}
				for(j=0; j<choice; j++)
					AddRandomCode(DelphiCode,MyLangCode,variables,CountsOfVariables,UsedLoopVariables,operations,CountOfTabs+1,depth-1);
				UsedLoopVariables[variables[6][i]->GetName()[0]]=0;
				if(choice>1)
				{
					MyLangCodeLength=strlen(MyLangCode);
					for(i=0,DelphiCodeLength=strlen(DelphiCode); i<CountOfTabs; i++)
					{
						DelphiCode[DelphiCodeLength++]='	';
						MyLangCode[MyLangCodeLength++]='	';
					}
					strcat(DelphiCode,"end;\n");
					strcat(MyLangCode,"}\n");
				}				
				break;
			}		
	}
}
void DisplayCode(char* code)
{
	int i,j,LineLength,PrevI;
	for(i=0; code[i]!='\0'; i++)
	{		
		for(LineLength=0,j=i; code[j]!='\n' && code[j]!='\0'; LineLength++,j++);
		if(LineLength<91)
		{
			for(; code[i]!='\0' && code[i]!='\n'; i++)
				if(code[i]=='	')
					cout<<' ';
				else
					cout<<code[i];
			cout<<code[i];
		}
		else
		{
			PrevI=i;
			for(j=0; j<87; j++,i++)
				if(code[i]=='	')
					cout<<' ';
				else
					cout<<code[i];
			cout<<"...\n";
			i=PrevI+LineLength;
		}
	}	
}
void GenerateDelphiAndMyLangCode()
{
	InitFloatingPointAndRandomNumbers();
	int i,j,CountsOfVariables[7],*powers=new int[21];
	char DelphiTypes[][9]={"integer","longint","float","extended","boolean"};
	char* NewName=(char*)calloc(15,sizeof(char));
	char* NewValue=(char*)calloc(6,sizeof(char));
	char* alphabet=new char[27];
	char* DelphiCode=(char*)calloc(65536,sizeof(char));
	char* MyLangCode=(char*)calloc(65536,sizeof(char));
	char* UsedLoopVariables=(char*)calloc('z'+1,sizeof(char));
	operation* operations=new operation();
	variable*** variables=new variable**[7];	
	for(i=0; i<4; i++)
	{
		variables[i]=new variable*[7];
		for(j=0,CountsOfVariables[i]=GetRandomInt(2,6); j<CountsOfVariables[i]; j++)		
			variables[i][j]=new variable(DelphiTypes[i]);		
	}
	strcpy(NewName,"IntZero");
	strcpy(NewValue,"0");
	variables[0][CountsOfVariables[0]++]=new variable(DelphiTypes[0],NewName,NewValue);
	strcpy(NewName,"FloatZero");
	strcpy(NewValue,"0.0");
	variables[2][CountsOfVariables[2]++]=new variable(DelphiTypes[2],NewName,NewValue);	
	strcpy(NewName,"result");
	strcpy(NewValue,"0.0");
	variables[3][CountsOfVariables[3]++]=new variable(DelphiTypes[3],NewName,NewValue);	
	variables[4]=new variable*[7];
	CountsOfVariables[4]=GetRandomInt(2,6);	
	for(j=0,CountsOfVariables[i]=GetRandomInt(2,6); j<CountsOfVariables[i]; j++)
	{
		strcpy(NewName,"");
		AddRandomIdentifier(GetRandomInt(3,11),NewName);
		if(rand()%2)
			strcpy(NewValue,"true");
		else
			strcpy(NewValue,"false");
		variables[4][j]=new variable(DelphiTypes[4],NewName,NewValue);
	}	
	for(i=0; i<21; i++)
		powers[i]=i;	
	ShuffleArrayOfIntegers(powers,21);
	variables[5]=new variable*[10];
	strcpy(NewName,"power");
	NewName[6]='\0';
	for(i=0,CountsOfVariables[5]=GetRandomInt(2,10); i<CountsOfVariables[5]; i++)
	{
		NewName[5]=i+1+'0';
		itoa(powers[i],NewValue,10);
		variables[5][i]=new variable(DelphiTypes[0],NewName,NewValue);
	}
	for(i=0; i<26; i++)
		alphabet[i]='a'+i;
	alphabet[i]='\0';
	ShuffleArrayOfCharacters(alphabet);
	NewName[1]='\0';
	NewValue[1]='\0';
	variables[6]=new variable*[26];
	for(i=0,CountsOfVariables[6]=GetRandomInt(10,26); i<CountsOfVariables[6]; i++)
	{
		NewName[0]=alphabet[i];
		variables[6][i]=new variable(DelphiTypes[0],NewName,NewValue);
	}
	strcpy(DelphiCode,"program ");
	AddRandomIdentifier(GetRandomInt(3,11),DelphiCode);
	strcat(DelphiCode,"; //some comment\nUses Math;\nvar\n");
	for(i=0; DelphiCode[i]!='\n'; i++)
		MyLangCode[i]=DelphiCode[i];
	strcat(MyLangCode,"\n{\n");
	for(i=0; i<7; i++)
	{
		DelphiCode[strlen(DelphiCode)]='	';
		for(j=0; j<CountsOfVariables[i]; j++)
		{
			strcat(DelphiCode,variables[i][j]->GetName());
			strcat(DelphiCode,", ");
		}
		DelphiCode[strlen(DelphiCode)-2]=':';
		strcat(DelphiCode,variables[i][0]->GetType());
		strcat(DelphiCode,";\n");
	}
	strcat(DelphiCode,"begin\n");	
	for(i=0; i<6; i++)			
		for(j=0; j<CountsOfVariables[i]; j++)
		{			
			DelphiCode[strlen(DelphiCode)]='	';
			strcat(DelphiCode,variables[i][j]->GetName());
			strcat(DelphiCode," := ");
			strcat(DelphiCode,variables[i][j]->GetValue());
			strcat(DelphiCode,";\n");
			MyLangCode[strlen(MyLangCode)]='	';
			strcat(MyLangCode,GetMyLangType(variables[i][j]->GetType()));
			MyLangCode[strlen(MyLangCode)]=' ';
			strcat(MyLangCode,variables[i][j]->GetName());
			strcat(MyLangCode," = ");
			strcat(MyLangCode,variables[i][j]->GetValue());
			strcat(MyLangCode,";\n");
		}
	MyLangCode[strlen(MyLangCode)]='	';
	strcat(MyLangCode,GetMyLangType(variables[6][0]->GetType()));
	MyLangCode[strlen(MyLangCode)]=' ';
	for(i=0; i<CountsOfVariables[6]-1; i++)
	{
		strcat(MyLangCode,variables[6][i]->GetName());
		strcat(MyLangCode,", ");
	}
	strcat(MyLangCode,variables[6][i]->GetName());
	strcat(MyLangCode,";\n");
	for(i=0,j=GetRandomDigit(1,5); i<j; i++)
	{
		strcat(DelphiCode,"\n	//----------SOME COMMENTS ");
		DelphiCode[strlen(DelphiCode)]=i+1+'0';
		strcat(DelphiCode,"----------\n");		
		strcat(MyLangCode,"\n	//----------SOME COMMENTS ");
		MyLangCode[strlen(MyLangCode)]=i+1+'0';
		strcat(MyLangCode,"----------\n");		
		AddRandomCode(DelphiCode,MyLangCode,variables,CountsOfVariables,UsedLoopVariables,operations,1,GetRandomDigit(2,5));		
	}
	strcat(DelphiCode,"end.");
	MyLangCode[strlen(MyLangCode)]='}';
	ofstream DelphiFile("CompileDelphiProgram\\program.pas");
	DelphiFile<<DelphiCode;
	DelphiFile.close();	
	ofstream MyLangFile("program.mylang");
	MyLangFile<<MyLangCode;
	MyLangFile.close();
	cout<<"----------------------------------------DELPHI CODE----------------------------------------";
	DisplayCode(DelphiCode);
	cout<<"\n----------------------------------------MYLANG CODE----------------------------------------";
	DisplayCode(MyLangCode);
	cout<<"\n-----------------------------COMPILATION OF THE DELPHI PROGRAM-----------------------------";	
	system("C:\\lazarus\\fpc\\3.2.2\\bin\\x86_64-win64\\fpc.exe CompileDelphiProgram\\program.pas && del CompileDelphiProgram\\program.o");
	cout<<"\nPress a key to start execution of the delphi program: ";
	getche();
	cout<<"\n------------------------------EXECUTION OF THE DELPHI PROGRAM------------------------------";
	system("cd CompileDelphiProgram && program.exe");	
	for(i=0; i<7; i++)
	{
		for(j=0; j<CountsOfVariables[i]; j++)		
			delete variables[i][j];		
		delete variables[i];
	}
	delete operations;
	delete[] powers;
	delete[] NewName;
	delete[] NewValue;
	delete[] alphabet;	
	delete[] variables;
	delete[] DelphiCode;
	delete[] MyLangCode;
	delete[] UsedLoopVariables;
}
int main(void)
{	
	GenerateDelphiAndMyLangCode();
	// parse();
    return 0;
}