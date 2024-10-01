/*11. Выполните изменения в соответствии с упражнением 7, применив их к программе PARSE главы 10. То есть заставьте программу анализировать выражения, содержащие числа в формате с плавающей запятой. Совместите классы, предложенные в упражнении 7, с алгоритмами из PARSE. Вам придется работать с указателями на символы вместо работы с самими символами. Это потребует выражений, подобных следующим:
Number* ptrN=new Number(ans);
s.push(ptrN);
and
Operator* ptr0=new Operator(ch);
s.push(ptr0)*/
#include "../../accessories.h"
const int LEN=80; //максимальная длина выражения
const int MAX=40;
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
	/*token** st;//char st[MAX]; //массив данных
	int top; //количество сохраненных данных
	public:
	Stack(int size)
	{
		st=new token*[size];
		top=0;
	}
	void push(string var)
	{
		st[++top]=new number(stof(var));
	}
	void push(char var)
	{
		st[++top]=new operation(var);
	}
	token* pop()
	{
		token* res=st[top--];		
		return res;
	}
	int gettop(){ return top; }//узнать количество элементов*/
	
	char st[MAX]; //массив данных
    int top; //количество сохраненных данных
	public:
    Stack(){top=0;}
    void push(char var){st[++top]=var;}
    char pop(){return st[top--];}
    int gettop(){return top;} //узнать количество элементов      	
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
		//s=new Stack(MAX);
	}
	void parse() //разбор выражения
	{
		char ch; //символ из строки
		char lastval; //последнее значение
		char lastop; //последний оператор
		for(int j=0; j<len; j++) //для всех символов в строке
		{
			ch=pStr[j]; //получаем символ
			if(ch>='0' && ch<='9') //если это цифра,
				s.push(ch - '0'); //то сохраняем ее значение
			else
				if(ch=='+' || ch=='-' || ch=='*' || ch=='/')
				{
					if(s.gettop()==1) //если это первый оператор,
						s.push(ch); //помещаем его в стек
					else //иначе
					{
						lastval=s.pop(); //получаем предыдущее число
						lastop=s.pop(); //получаем предыдущий оператор
						//если это * или /, а предыдущий был + или -, то
						if((ch=='*' || ch=='/') && (lastop=='+' || lastop=='-'))
						{
							s.push(lastop); //отменяем последние два взятия из стека
							s.push(lastval);
						}
						else
						{
							//помещаем в стек результат операции
							switch(lastop)
							{
								case '+': s.push(s.pop() + lastval); break;
								case '-': s.push(s.pop() - lastval); break;
								case '*': s.push(s.pop() * lastval); break;
								case '/': s.push(s.pop() / lastval); break;
								default: cout << "\nUndefined operator"; exit(1);
							}
						}
						s.push(ch); //помещаем в стек текущий оператор
					}
				}
		}
	}
	float solve() //получение результата
	{
		char lastval; //предыдущее значение
		while(s.gettop()>1)
		{
			lastval=s.pop(); //получаем предыдущее значение
			switch(s.pop()) //получаем предыдущий оператор
			{
				case '+': s.push(s.pop()+lastval); break;
				case '-': s.push(s.pop()-lastval); break;
				case '*': s.push(s.pop()*lastval); break;
				case '/': s.push(s.pop()/lastval); break;
				default: cout << "\nUndefined operator"; exit(1);
			}
		}
		return int(s.pop()); //последний оператор в стеке - это результат
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
char* GetRandomExpression()
{
	char ch='1',RandomOperation,*result;
	string expression;
	int i,OperationNumber,CountOfOperations;
	string operations="+-*/";
	CountOfOperations=GetRandomInt(4,10);
	ShuffleString(operations);
	for(i=0,OperationNumber=0; i<CountOfOperations; i++)
	{
		expression+=GetRandomIntegerAsString(1);
		/*if(GetRandomInt(0,10)<5)			
			expression+=GetRandomIntegerAsString(GetRandomInt(1,2));			
		else			
			expression+=GetRandomIntegerAsString(GetRandomInt(1,2))+'.'+GetRandomIntegerAsString(GetRandomInt(1,5));*/
		expression=expression+operations[OperationNumber];
		if(OperationNumber==3)
		{
			ShuffleString(operations);
			OperationNumber=0;
		}
		else
			OperationNumber++;
	}
	expression+=GetRandomIntegerAsString(1);
	/*if(GetRandomInt(0,10)<5)
		expression+=GetRandomIntegerAsString(GetRandomInt(1,7));
	else
		expression+=GetRandomIntegerAsString(GetRandomInt(1,7))+'.'+GetRandomIntegerAsString(GetRandomInt(1,5));*/
	result=new char[expression.length()+1];
	for(i=0; i<expression.length(); i++)
		result[i]=expression[i];
	result[i]='\0';
	return result;
}
int main()
{	
	char ch,*expression=new char[10];
	InitFloatingPointAndRandomNumbers();
	do
	{
		cout<<"Expression: ";
		expression=GetRandomExpression();//cin>>expression;
		cout<<expression<<endl;
		express* eptr=new express(expression);
		eptr->parse();
		cout<<"Result: "<<eptr->solve()<<endl;
		delete eptr;
		delete expression;
		cout<<"Press ENTER to continue or other key to exit: ";
		ch=getch();
		cout<<endl;
	}
	while(ch==13);
	return 0;
}