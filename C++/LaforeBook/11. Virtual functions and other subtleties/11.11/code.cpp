/*11. Выполните изменения в соответствии с упражнением 7, применив их к программе PARSE главы 10. То есть заставьте программу анализировать выражения, содержащие числа в формате с плавающей запятой. Совместите классы, предложенные в упражнении 7, с алгоритмами из PARSE. Вам придется работать с указателями на символы вместо работы с самими символами. Это потребует выражений, подобных следующим:
Number* ptrN=new Number(ans);
s.push(ptrN);
and
Operator* ptr0=new Operator(ch);
s.push(ptr0)*/
#include "../../accessories.h"
const int LEN=80; //максимальная длина выражения
const int MAX=400;
string GetRandomIntegerAsString(int length)
{
	string result;
	result+=(char)GetRandomInt(1,9)+'0';
	for(int i=1; i<length; i++)
		result+=(char)GetRandomInt(0,9)+'0';	
	return result;
}
char* GetRandomExpression(int MinCountOfOperations,int MaxCountOfOperations,int MinIntLength,int MaxIntLength)
{
	char ch='1',RandomOperation,*result;
	string expression;
	int i,OperationNumber;
	int CountOfOperations=GetRandomInt(MinCountOfOperations,MaxCountOfOperations);
	string operations="+-*/";	
	ShuffleString(operations);
	for(i=0,OperationNumber=0; i<CountOfOperations; i++)
	{
		if(GetRandomInt(0,10)<5)			
			expression+=GetRandomIntegerAsString(GetRandomInt(MinIntLength,MaxIntLength))+" ";			
		else			
			expression+=GetRandomIntegerAsString(GetRandomInt(MinIntLength,MaxIntLength))+'.'+GetRandomIntegerAsString(GetRandomInt(1,5))+" ";
		expression=expression+operations[OperationNumber]+" ";
		if(OperationNumber==3)
		{
			ShuffleString(operations);
			OperationNumber=0;
		}
		else
			OperationNumber++;
	}
	if(GetRandomInt(0,10)<5)
		expression+=GetRandomIntegerAsString(GetRandomInt(MinIntLength,MaxIntLength));
	else
		expression+=GetRandomIntegerAsString(GetRandomInt(MinIntLength,MaxIntLength))+'.'+GetRandomIntegerAsString(GetRandomInt(1,5));
	result=new char[expression.length()+1];
	for(i=0; i<expression.length(); i++)
		result[i]=expression[i];
	result[i]='\0';
	return result;
}
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
class Stack
{
	token** st; //массив данных
	int top; //количество сохраненных данных
	public:
	Stack()
	{
		st=new token*[MAX];
		top=0;
	}
	~Stack(){delete[]st;};
	void push(token* var)
	{		
		st[++top]=var;
	}
	void push(float var)
	{
		number* ptrN=new number(var);
		push(ptrN);
	}
	void push(char var)
	{
		operation* ptr0=new operation(var);
		push(ptr0);
	}
	float PopNumber()
	{
		float StackNumber=st[top]->GetNumber();
		delete st[top--];
		return StackNumber;
	}
	char PopOperation()
	{
		float StackOperation=st[top]->GetOperation();
		delete st[top--];
		return StackOperation;
	}
	int gettop() {return top;}//узнать количество элементов
};
class express
{
	Stack s; //стек данных
	char* pStr; //строка для ввода
	int len; //длина строки
	public:
	express(char* ptr) //конструктор
	{
		pStr=ptr; //запоминаем указатель на строку
		len=strlen(pStr); //устанавливаем длину		
	}
	void parse() //разбор выражения
	{
		char ch; //символ из строки
		float lastval,res,operand1; //последнее значение
		char lastop; //последний оператор
		string StringNumber;
		number* LastvalToken,*Operand1Token;
		operation* OperationToken;
		for(int j=0; j<len; j++) //для всех символов в строке
		{
			ch=pStr[j]; //получаем символ
			if((ch>='0' && ch<='9') || ch=='.') //если это цифра,
				StringNumber+=ch; //то сохраняем ее значение
			else
				if(ch=='+' || ch=='-' || ch=='*' || ch=='/')
				{
					s.push(stof(StringNumber));
					StringNumber="";
					if(s.gettop()==1) //если это первый оператор,
					{						
						s.push(ch); //помещаем его в стек
					}
					else //иначе
					{
						lastval=s.PopNumber(); //получаем предыдущее число
						lastop=s.PopOperation(); //получаем предыдущий оператор
						//если это * или /, а предыдущий был + или -, то
						if((ch=='*' || ch=='/') && (lastop=='+' || lastop=='-'))
						{
							s.push(lastop); //отменяем последние два взятия из стека
							s.push(lastval);
						}
						else
						{							
							//помещаем в стек результат операции
							operand1=s.PopNumber();
							switch(lastop)
							{
								case '+': res=operand1+lastval; break;
								case '-': res=operand1-lastval; break;
								case '*': res=operand1*lastval; break;
								case '/': res=operand1/lastval; break;
								default: cout << "\nUndefined operator"; exit(1);
							}
							s.push(res);
							cout<<operand1<<" "<<lastop<<" "<<lastval<<" = "<<res<<endl;
						}
						s.push(ch); //помещаем в стек текущий оператор
					}
				}
		}
		s.push(stof(StringNumber));
	}
	float solve() //получение результата
	{
		float lastval,operand1,res; //предыдущее значение
		char lastop;
		while(s.gettop()>1)
		{
			lastval=s.PopNumber();
			lastop=s.PopOperation();
			operand1=s.PopNumber();
			switch(lastop)
			{
				case '+': res=operand1+lastval; break;
				case '-': res=operand1-lastval; break;
				case '*': res=operand1*lastval; break;
				case '/': res=operand1/lastval; break;
				default: cout << "Undefined operator\n"; exit(1);
			}
			s.push(res);
			cout<<operand1<<" "<<lastop<<" "<<lastval<<" = "<<res<<endl;
		}
		return s.PopNumber(); //последний оператор в стеке - результат
	}
};
int main()
{	
	char ch,*expression;
	float result;
	int i;
	InitFloatingPointAndRandomNumbers();
	do
	{
		cout<<"Expression: ";
		expression=GetKeyboardInputAsArrayOfChars();
		//expression=GetRandomExpression(2,8,1,7);
		//cout<<expression;
		cout<<endl;
		express* eptr=new express(expression);
		eptr->parse();
		result=eptr->solve();
		cout<<"Result: "<<result<<endl;
		delete eptr;
		delete[] expression;
		cout<<"Press ENTER to continue or other key to exit: ";
		ch=getch();
		cout<<endl;
	}
	while(ch==13);
	return 0;
}