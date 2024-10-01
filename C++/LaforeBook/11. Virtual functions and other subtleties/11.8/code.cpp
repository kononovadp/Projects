/*8. Помните программу PARSE из главы 10? Попробуйте доработать ее, чтобы она могла вычислять значения математических выражений с рациональными числами, например типа float, а не только с одноразрядными числами: 3.14159 / 2.0 + 75.25 * 3.333 + 6.02. Во-первых, нужно развить стек до такой степени, чтобы он мог хранить и операторы (типа char), и числа (типа float). Но как, спрашивается, можно хранить в стеке значения двух разных типов? Ведь стек — это, по сути дела, массив. Надо еще учесть, что типы char и float даже не совпадают по размеру! Даже указатели на разные типы данных (char* и float*) компилятор не позволит хранить в одном массиве, несмотря на то, что они одинакового размера. Единственный способ хранить в массиве два разных типа указателей — сделать эти типы наследниками одного и того же базового класса. При этом базовому классу даже нет нужды иметь какие-то собственные данные, это может быть абстрактный класс, из которого никакие объекты создаваться не будут. Конструкторы могут хранить значения в порожденных классах обычным способом, но должна иметься специальная чистая виртуальная функция для того, чтобы извлечь эти значения. Представляем возможный сценарий работы над этим вопросом:
class Token //Абстрактный базовый класс
{
	public:
	virtual float getNumber()=0; //чистая виртуальная функция
	virtual char getOperator()=0;
};
class Operator: public Token
{
	private:
	char oper; //Операторы +, -, *, /
	public:
	Operator(char);	//конструктор устанавливает значение
	char getOperator();	//получить значение
	float getNumber(); //просто некая функция
};
class Number: public Token
{
	float fnum; //число
	public:
	Number(float); //конструктор устанавливает значение
	float getNumber(); //получить значение
	char getOperator(); //просто некая функция
};
Token* atoken[100]; //содержит типы Operator* и Number*
Виртуальные функции базового класса должны быть реализованы во всех порожденных классах, в противном случае классы становятся абстрактными. Таким образом, классу Operand нужна функция getNumber(), несмотря на то, что она фиктивная. Классу Number нужна функция getOperand(), несмотря на то, что она тоже фиктивная. Поработайте над этим каркасом, сделайте его реально работающей программой, добавив класс Stack, содержащий объекты класса Token, и функцию main(), в которой бы заносились в стек и извлекались из него разные арифметические операторы и числа в формате с плавающей запятой*/
#include "../../accessories.h"
class token
{
	public:
	virtual char GetOperation()=0;
	virtual float GetNumber()=0;
	virtual bool IsNumber()=0;
};
class operation: public token
{
	char OperationCharacter;
	public: operation(char NewOperationCharacter){OperationCharacter=NewOperationCharacter;}
	char GetOperation(){return OperationCharacter;}
	float GetNumber(){return 0.0;}
	bool IsNumber(){return false;}
};
class number: public token
{
	float FloatNumber;
	public: number(float NewFloatNumber){FloatNumber=NewFloatNumber;}
	char GetOperation(){return 0;}
	float GetNumber(){return FloatNumber;}
	bool IsNumber(){return true;}
};
class stack
{
	token** tokens;
	int StackSize,CountOfTokens;
	public:
	stack(int NewCountOfTokens)
	{
		CountOfTokens=NewCountOfTokens;
		tokens=new token*[CountOfTokens];
	}
	char GetPriority(char operation)
	{
		if(operation=='*' || operation=='/')
			return 1;
		return 0;
	}
	void parse(string expression)
	{
		float result;
		int i,j,CountOfOperations=0;
		string NumberString;
		char PriorityOfNewOperation;
		token** operations=new token*[CountOfTokens];
		for(i=0,StackSize=0; i<expression.length(); i++)
		{
			if(!isdigit(expression[i]) && expression[i]!='.' && expression[i]!='+' && expression[i]!='-' && expression[i]!='*' && expression[i]!='/')
				continue;
			if(isdigit(expression[i]) || expression[i]=='.')
			{
				NumberString+=expression[i];
				if(i+1<expression.length() && expression[i+1]=='.')
					continue;
				if(i+1==expression.length() || !isdigit(expression[i+1]))
				{
					tokens[StackSize++]=new number(stof(NumberString));
					NumberString="";
				}
			}
			else
			{
				if(CountOfOperations==0)
					operations[CountOfOperations++]=new operation(expression[i]);
				else
				{
					PriorityOfNewOperation=GetPriority(expression[i]);
					while(CountOfOperations>0 && GetPriority(operations[CountOfOperations-1]->GetOperation())>=PriorityOfNewOperation)
					{
						tokens[StackSize++]=new operation(operations[CountOfOperations-1]->GetOperation());
						delete(operations[CountOfOperations-1]);
						CountOfOperations--;
					}
					operations[CountOfOperations++]=new operation(expression[i]);
				}
			}
		}
		CountOfOperations--;
		while(CountOfOperations>-1)
		{
			tokens[StackSize++]=new operation(operations[CountOfOperations]->GetOperation());
			delete(operations[CountOfOperations--]);
		}
		delete[]operations;
		cout<<"Reverse Polish notation: ";
		for(i=0; i<StackSize; i++)
			if(tokens[i]->IsNumber())
				cout<<tokens[i]->GetNumber()<<" ";
			else
				cout<<tokens[i]->GetOperation()<<" ";
		cout<<endl;
	}
	float CalculateExpression()
	{
		float op1,op2,result=0.0,*stack=new float[CountOfTokens];
		int i,FloatStackSize=0;
		char op;
		for(i=0; i<CountOfTokens; i++)
			if(tokens[i]->IsNumber())
				stack[FloatStackSize++]=tokens[i]->GetNumber();
			else
			{
				op1=stack[FloatStackSize-2];
				op2=stack[FloatStackSize-1];
				op=tokens[i]->GetOperation();
				switch(op)
				{
					case '+': result=op1+op2; break;
					case '-': result=op1-op2; break;
					case '*': result=op1*op2; break;
					case '/': result=op1/op2; break;
				}
				cout<<op1<<" "<<op<<" "<<op2<<" = "<<result<<endl;
				stack[FloatStackSize-2]=result;
				FloatStackSize-=1;
			}
		result=stack[0];
		delete[]stack;
		return result;
	}
};
string GetRandomIntegerAsString(int length)
{
	string result;
	result+=(char)GetRandomInt(1,9)+'0';
	for(int i=1; i<length; i++)
		result+=(char)GetRandomInt(0,9)+'0';	
	return result;
}
int main()
{
	char ch='1',RandomOperation;
	string expression;
	int i,OperationNumber,CountOfOperations;
	float result;
	string operations="+-*/";
	stack* NewStack;
	InitFloatingPointAndRandomNumbers();
	while(ch!='0')
	{
		CountOfOperations=GetRandomInt(4,10);
		ShuffleString(operations);
		for(i=0,OperationNumber=0; i<CountOfOperations; i++)
		{
			if(GetRandomInt(0,10)<5)			
				expression+=GetRandomIntegerAsString(GetRandomInt(1,7));			
			else			
				expression+=GetRandomIntegerAsString(GetRandomInt(1,7))+'.'+GetRandomIntegerAsString(GetRandomInt(1,5));
			expression=expression+" "+operations[OperationNumber]+" ";
			if(OperationNumber==3)
			{
				ShuffleString(operations);
				OperationNumber=0;
			}
			else
				OperationNumber++;
		}
		if(GetRandomInt(0,10)<5)			
				expression+=GetRandomIntegerAsString(GetRandomInt(1,7));			
			else			
				expression+=GetRandomIntegerAsString(GetRandomInt(1,7))+'.'+GetRandomIntegerAsString(GetRandomInt(1,5));
		cout<<expression<<endl;
		NewStack=new stack(CountOfOperations*2+1);
		NewStack->parse(expression);
		
		result=NewStack->CalculateExpression();
		cout<<"Result: "<<result;
		cout<<"\n------------------------------------------------------------\n";
		expression="";
		cout<<"Press 1 to continue or 0 to exit: ";
		ch=getch();
		while(ch!='0' && ch!='1')		
			ch=getch();		
		cout<<ch<<endl;
	}
	return 0;
}