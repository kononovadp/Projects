#include "parser.h"
#include <stack>
#include <vector>
#include <unordered_map>
#include <memory>
using namespace ParserClasses;
char delimiters[7][2][20]=
{
	{"(","open bracket"},{")","close bracket"},{"{","open block bracket"},
	{"}","close block bracket"},{",","comma"},{":","colon"},{";","semicolon"}
};
char operators[14][2][17]=
{
	{"+","arithmetic"},{"-","arithmetic"},{"*","arithmetic"},{"/","arithmetic"},
	{"^","arithmetic"},{"=","assignment"},{"<","comparison"},{">","comparison"},
	{"==","comparison"},{"!=","comparison"},{"++","increment"},{"<<","output"},
	{"||","output delimiter"},{"//","comment"}
};
char keywords[9][2][20]=
{
	{"program","program definition"},{"int","data type"},{"longint","data type"},
	{"float","data type"},{"double","data type"},{"bool","data type"},
	{"if","condition"},{"for","loop"},{"endl","end of line"}
};
char operand[3][7]={"string","int","float"};
char TokenTypes[7][11]={"keyword","identifier","number","operator","delimiter","string","comment"};
char IsNumber(char* number)
{
	int NumberLength=strlen(number);
	if(number[0]=='.' || number[NumberLength-1]=='.')
		return 0;
	bool DecimalNumber=0;	
	for(int i=0; i<NumberLength; i++)
	{
        if(number[i]=='.')
		{
			if(DecimalNumber)
				return 0;
			DecimalNumber=true;
		}
		else
			if(!isdigit(number[i]))
				return 0;
	}
    return 1+DecimalNumber;
}
bool IsOperator(char ch)
{
	if(isspace(ch))
		return true;
	int i,j;
	for(i=0; i<14; i++)
		for(j=0; j<strlen(operators[i][0]); j++)
			if(ch==operators[i][0][j])			
				return true;
	return false;
}
struct token*** LexicalAnalyzer(char* code)
{
	char ch,*buffer,*word,ConstNumber;
	int i,j,CountOfErrors=0,LineNumber=0,TokenNumber=0,CodeLength=strlen(code),BufferLength;
	struct token*** tokens=(token***)calloc(1000,sizeof(token**));
	tokens[0]=(token**)calloc(100,sizeof(token*));
	for(i=0; i<35; i++)
		cout<<'=';
	cout<<"LEXICAL ANALYZER:";
	for(i=0; i<35; i++)
		cout<<'=';
	cout<<endl;
	for(i=0; i<CodeLength; i++)
	{
		ch=code[i];
		if(isspace(ch))			
		{
			if(ch=='\n')
			{
				LineNumber++;
				TokenNumber=0;
				tokens[LineNumber]=(token**)calloc(100,sizeof(token*));
			}
			continue;
		}
		for(ConstNumber=0; ConstNumber<7; ConstNumber++)
			if(ch==delimiters[ConstNumber][0][0])
				break;
		if(ConstNumber<7)
		{
			tokens[LineNumber][TokenNumber]=(token*)calloc(1,sizeof(token));
			tokens[LineNumber][TokenNumber]->TokenType=TokenTypes[4];
			tokens[LineNumber][TokenNumber]->type=delimiters[ConstNumber][1];
			tokens[LineNumber][TokenNumber]->value=(char*)calloc(3,sizeof(char));
			tokens[LineNumber][TokenNumber++]->value[0]=ch;
			continue;
		}
		BufferLength=0;
		buffer=(char*)calloc(100,sizeof(char));		
		if(isalpha(ch))
		{
			while(isalnum(ch) || ch=='_')
			{
				buffer[BufferLength++]=ch;
				ch=code[++i];
            }
            --i;
			tokens[LineNumber][TokenNumber]=(token*)calloc(1,sizeof(token));
			for(ConstNumber=0; ConstNumber<9; ConstNumber++)
				if(!memcmp(keywords[ConstNumber][0],buffer,BufferLength))
					break;
			if(ConstNumber<9)
			{
				tokens[LineNumber][TokenNumber]->TokenType=TokenTypes[0];
				tokens[LineNumber][TokenNumber]->type=keywords[ConstNumber][1];
			}
			else
			{
				tokens[LineNumber][TokenNumber]->TokenType=TokenTypes[1];
				tokens[LineNumber][TokenNumber]->type=operand[0];
			}
			tokens[LineNumber][TokenNumber]->value=(char*)calloc(100,sizeof(char));
			strcpy(tokens[LineNumber][TokenNumber++]->value,buffer);
		}
		else
			if(isdigit(ch))
			{
				while(isdigit(ch) || ch=='.')
				{
					buffer[BufferLength++]=ch;
					ch=code[++i];
				}
				--i;
				ConstNumber=IsNumber(buffer);
				if(ConstNumber)
				{
					tokens[LineNumber][TokenNumber]=(token*)calloc(1,sizeof(token));
					tokens[LineNumber][TokenNumber]->TokenType=TokenTypes[2];
					if(ConstNumber==1)
						tokens[LineNumber][TokenNumber]->type=operand[1];
					else
						tokens[LineNumber][TokenNumber]->type=operand[2];
					tokens[LineNumber][TokenNumber]->value=(char*)calloc(100,sizeof(char));
					strcpy(tokens[LineNumber][TokenNumber++]->value,buffer);
				}
				else
				{
					cerr<<"ERROR in the line "<<LineNumber+1<<": incorrect number: "<<buffer<<endl;
					CountOfErrors++;
				}
			}
			else
			{
				if(ch=='"')
				{
					while(code[++i]!='"' && code[i]!='\n' && i<CodeLength)
						buffer[BufferLength++]=code[i];					
					if(code[i]=='"')
					{
						tokens[LineNumber][TokenNumber]=(token*)calloc(1,sizeof(token));
						tokens[LineNumber][TokenNumber]->TokenType=TokenTypes[5];
						tokens[LineNumber][TokenNumber]->type=operand[0];
						tokens[LineNumber][TokenNumber]->value=(char*)calloc(100,sizeof(char));
						strcpy(tokens[LineNumber][TokenNumber++]->value,buffer);
						i++;
					}
					else
					{						
						cerr<<"ERROR in the line "<<LineNumber+1<<": unterminated string literal: "<<buffer<<endl;
						CountOfErrors++;
					}
				}
				else
				{
					buffer[BufferLength++]=ch;
					i++;
					while(i<CodeLength && code[i]!='\n' && IsOperator(code[i]))
					{
						if(isspace(code[i]))
						{
							i++;
							continue;
						}
						buffer[BufferLength++]=code[i++];
					}
					i--;
					for(ConstNumber=0; ConstNumber<14; ConstNumber++)
						if(!memcmp(operators[ConstNumber][0],buffer,BufferLength))
							break;
					if(ConstNumber<14)
					{
						tokens[LineNumber][TokenNumber]=(token*)calloc(1,sizeof(token));
						tokens[LineNumber][TokenNumber]->TokenType=TokenTypes[3];
						tokens[LineNumber][TokenNumber]->type=operators[ConstNumber][1];
						tokens[LineNumber][TokenNumber]->value=(char*)calloc(3,sizeof(char));
						strcpy(tokens[LineNumber][TokenNumber++]->value,buffer);
						if(buffer[0]=='/' && buffer[1]=='/')
						{
							tokens[LineNumber][TokenNumber]=(token*)calloc(1,sizeof(token));
							tokens[LineNumber][TokenNumber]->TokenType=TokenTypes[6];
							tokens[LineNumber][TokenNumber]->type=operand[0];
							tokens[LineNumber][TokenNumber]->value=(char*)calloc(100,sizeof(char));
							for(j=0,i++; i<CodeLength && code[i]!='\n'; i++,j++)
								tokens[LineNumber][TokenNumber]->value[j]=code[i];
							TokenNumber++;
							i--;
						}
					}
					else
					{
						cerr<<"ERROR in the line "<<LineNumber+1<<": undeclared operator: "<<buffer<<endl;
						CountOfErrors++;
					}
				}
			}
		delete[] buffer;
	}
	for(i=0; tokens[i]; i++)
	{
		cout<<"All tokens in the line "<<i+1<<":\n";
		for(j=0; tokens[i][j]; j++)
			cout<<"Token type: "<<setw(10)<<tokens[i][j]->TokenType<<"; type: "<<setw(18)<<tokens[i][j]->type<<"; value: "<<tokens[i][j]->value<<endl;
		for(j=0; j<90; j++)
			cout<<'-';
		cout<<endl;
	}
	if(CountOfErrors)
	{
		cout<<"There are "<<CountOfErrors<<" lexical errors, compilation terminated!";
		exit(1);
	}
	return tokens;
}
void SyntaxAnalyzer(struct token*** tokens)
{
	int i,j,CountOfErrors=0;
	for(i=0; tokens[i]; i++)
		if(tokens[i][0] && memcmp(tokens[i][0]->type,TokenTypes[6],7))
			break;	
	if(!tokens[i] || memcmp(tokens[i][0]->type,keywords[0][0],7))
	{		
		cerr<<"ERROR in the line "<<i+1<<": the directive \"program\" doesn't exist!\n";
		exit(1);
	}
	if(!tokens[i][1] || memcmp(tokens[i][1]->TokenType,TokenTypes[1],10))
	{
		cerr<<"ERROR in the line "<<i+1<<": the program name isn't identifier!\n";
		exit(1);
	}
	if(!tokens[i][2] || memcmp(tokens[i][2]->type,delimiters[6][1],9))
	{
		cerr<<"ERROR in the line "<<i+1<<": semicolon expected";
		exit(1);
	}
	/*int k=0;
	char* t=(char*)calloc(1000,1);
	unordered_map<char,char> MatchingBrackets ={{'}','{'}};
	stack<char> BracketStack;
    // unordered_map<char,char> MatchingBrackets ={{'}','{'}};
	for(i++; tokens[i]; i++)
	{
		for(j=0; tokens[i][j]; j++)
		{
			if(!memcmp(tokens[i][j]->type,delimiters[2][1],18) || !memcmp(tokens[i][j]->type,delimiters[3][1],19))
			{
				char bracket=tokens[i][j]->value[0];
				if(bracket=='{')
					t[k++]=bracket;//BracketStack.push(bracket);
				else
					if(bracket=='}')
					{
						if(k==0 || t[k-1] != MatchingBrackets[bracket])
							cout<<"ERROR in the line "<<i+1<<": mismatched or unbalanced bracket\n";
						// BracketStack.pop();
						k--;
					}
			}
		}
	}
	if(k>-1)
		cout<<"ERROR: mismatched or unbalanced brackets\n";*/
	stack<char> BracketStack;
    unordered_map<char,char> MatchingBrackets ={{'}','{'}};
	for(i++; tokens[i]; i++)
	{
		for(j=0; tokens[i][j]; j++)
		{
			if(!memcmp(tokens[i][j]->type,delimiters[2][1],18) || !memcmp(tokens[i][j]->type,delimiters[3][1],19))
			{
				char bracket=tokens[i][j]->value[0];
				if(bracket=='{')
					BracketStack.push(bracket);
				else
					if(bracket=='}')
					{
						if(BracketStack.empty() || BracketStack.top() != MatchingBrackets[bracket])
							cout<<"ERROR in the line "<<i+1<<": mismatched or unbalanced bracket\n";
						if(!BracketStack.empty())
							BracketStack.pop();
					}
			}
		}
	}
	if(!BracketStack.empty())
		cout<<"ERROR: mismatched or unbalanced brackets\n";
	
	// MatchingBrackets.clear();
	// BracketStack=stack<char>();
	// return;
	
}
void PolishNotation(struct token*** tokens)
{
	struct ASTNode
	{
		struct token* MainToken;
		vector<std::shared_ptr<ASTNode>> children;
	};
	std::stack<std::shared_ptr<ASTNode>> operators;
    std::stack<std::shared_ptr<ASTNode>> operands;
	int i,j;
	for(i=0; tokens[i]; i++)	
		for(j=0; tokens[i][j]; j++)
			if(memcmp(tokens[i][j]->TokenType,TokenTypes[4],9) && memcmp(tokens[i][j]->TokenType,TokenTypes[3],8))
				operands.push(std::make_shared<ASTNode>(ASTNode{tokens[i][j],{}}));
			else
				if(!memcmp(tokens[i][j]->TokenType,TokenTypes[3],8))
					operators.push(std::make_shared<ASTNode>(ASTNode{tokens[i][j],{}}));
				else
					if(!memcmp(tokens[i][j]->type,delimiters[2][1],18))
						operators.push(std::make_shared<ASTNode>(ASTNode{NULL,{}}));
					else
						if(!memcmp(tokens[i][j]->type,delimiters[3][1],19))
						{
							while (!operators.empty() && operators.top()->MainToken!=NULL)
							{
								auto opNode = operators.top();
								operators.pop();
								if (!operands.empty())
								{
									auto right = operands.top(); operands.pop();
									opNode->children.push_back(right);
								}
								if (!operands.empty())
								{
									auto left = operands.top(); operands.pop();
									opNode->children.insert(opNode->children.begin(), left);
								}
								operands.push(opNode);
							}
							if (!operators.empty() && operators.top()->MainToken == NULL)
								operators.pop();            
						}
				
			
}