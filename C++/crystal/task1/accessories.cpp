#include "accessories.h"
void InitFloatingPointAndRandomNumbers()
{
	cout.precision(FloatingPointNumberPrecision);
	cout.setf(ios::fixed);
	srand(time(0));
}
/*int GetCountOfDigits(int n)
{
	if(n==0)
		return 1;
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return i;
}*/
int GetRandomInt(int min,int max)
{
	if(min==max)
		return min;
	return min+(rand()%(max-min));
}
char GetRandomChar(char min,char max)
{
	if(min==max)
		return min;
	return min+(rand()%(max-min));
}
float GetRandomFloat(float min,float max)
{
    if(min==max)
		return min;
	float f=(float)rand()/RAND_MAX;	
    return min+f*(max-min);
}
double GetRandomDouble(double min,double max)
{
    if(min==max)
		return min;
	double f=(double)rand()/RAND_MAX;	
    return min+f*(max-min);
}
void ShuffleArrayOfCharacters(char* array)
{
	int i,j;
	char t;
	for(i=0; i<strlen(array); i++)
	{
		j=0+(rand()%(strlen(array)-0));
		t=array[i];
		array[i]=array[j];
		array[j]=t;
	}
}
void ShuffleArrayOfIntegers(int* array,int ArraySize)
{
	int i,j,t;
	for(i=0; i<ArraySize; i++)
	{
		j=0+(rand()%(ArraySize-0));
		t=array[i];
		array[i]=array[j];
		array[j]=t;
	}
}
void ShuffleString(string& str)
{
	int i,j;
	char t;
	for(i=0; i<str.length(); i++)
	{
		j=0+(rand()%(str.length()-0));
		t=str[i];
		str[i]=str[j];
		str[j]=t;
	}
}
string GetKeyboardInputAsString()
{	
	int i=0;
	string input;
	char ch=getch();
	while(ch!=13)
	{
		if(ch==8 && i>0)
		{
			cout<<"\b \b";
			input.pop_back();
		}
		else
			if(ch!=8)
			{
				input+=ch;				
				cout<<ch;
				i++;
			}
		ch=getch();
	}
	return input;	
}
string GetKeyboardInputAsString(char* ExcludedCharacters)
{
	int i=0,j;	
	string input;
	char ch=getch();
	while(ch!=13)
	{
		if(ch==8 && i>0)
		{
			cout<<"\b \b";
			input.pop_back();
		}
		else
			if(ch!=8)
			{
				for(j=0; j<strlen(ExcludedCharacters); j++)
					if(ch==ExcludedCharacters[j])
						break;
				if(j==strlen(ExcludedCharacters))
				{
					input+=ch;
					cout<<ch;
					i++;
				}
			}
		ch=getch();
	}
	return input;
}
char* GetKeyboardInputAsArrayOfChars()
{
	int i=0;	
	char* input=new char[91];
	char ch=getch();
	while(ch!=13)
	{
		if(ch==8 && i>0)
		{
			cout<<"\b \b";
			input[--i]='\0';
		}
		else
			if(ch!=8)
			{
				input[i++]=ch;
				cout<<ch;
			}
		ch=getch();
	}
	input[i]='\0';
	return input;
}
int GetIntFromKeyboard(){return GetIntFromKeyboard(0,INT_MAX);}
int GetIntFromKeyboard(int MinInt,int MaxInt)
{
	int i,result=MinInt-1;
	char ch=0;
	bool InputIsCorrect;
	string input,MaxNumber=to_string(MaxInt);	
	while(result<MinInt)
	{
		ch=getch();
		while(ch!=13)
		{
			InputIsCorrect=false;
			if(ch==27)
				exit(0);
			else
				if(ch==8 && input.length()>0)
				{
					cout<<"\b \b";
					input.pop_back();
				}
				else
					if(isdigit(ch))
					{
						if(input.length()+1<MaxNumber.length())
							InputIsCorrect=true;
						else
							if(input.length()+1==MaxNumber.length())
							{
								for(i=0; i<input.length(); i++)						
									if(input[i]<MaxNumber[i])
									{
										InputIsCorrect=true;
										break;
									}
									else
										if(input[i]>MaxNumber[i])
											break;
								if(i==input.length() && ch<=MaxNumber[MaxNumber.length()-1])
										InputIsCorrect=true;
							}
							if(input[0]=='0' && ch=='0')
								InputIsCorrect=false;
					}
					if(InputIsCorrect)
					{
						input+=ch;
						cout<<ch;
					}
					ch=getch();
		}
		if(input.length()==0)
		{
			result=0;
			cout<<result;
		}
		else
			result=stoi(input);
		if(result<MinInt)
			cout<<"\nInput number can't be less than "<<MinInt<<", try again: ";
	}
	return result;
}
long GetLongFromKeyboard(){return GetIntFromKeyboard(0,INT_MAX);}
long GetLongFromKeyboard(long MinInt,long MaxInt)
{
	int i;
	long result=MinInt-1;
	char ch=0;
	bool InputIsCorrect;
	string input,MaxNumber=to_string(MaxInt);	
	while(result<MinInt)
	{
		ch=getch();
		while(ch!=13)
		{
			InputIsCorrect=false;
			if(ch==27)
				exit(0);
			else
				if(ch==8 && input.length()>0)
				{
					cout<<"\b \b";
					input.pop_back();
				}
				else
					if(isdigit(ch))
					{
						if(input.length()+1<MaxNumber.length())
							InputIsCorrect=true;
						else
							if(input.length()+1==MaxNumber.length())
							{
								for(i=0; i<input.length(); i++)						
									if(input[i]<MaxNumber[i])
									{
										InputIsCorrect=true;
										break;
									}
									else
										if(input[i]>MaxNumber[i])
											break;
								if(i==input.length() && ch<=MaxNumber[MaxNumber.length()-1])
										InputIsCorrect=true;
							}
							if(input[0]=='0' && ch=='0')
								InputIsCorrect=false;
					}
					if(InputIsCorrect)
					{
						input+=ch;
						cout<<ch;
					}
					ch=getch();
		}
		if(input.length()==0)
		{
			result=0;
			cout<<result;
		}
		else
			result=stoi(input);
		if(result<MinInt)
			cout<<"\nInput number can't be less than "<<MinInt<<", try again: ";
	}
	return result;
}
float GetFloatFromKeyboard()
{
	float result;
	string input,MaxNumber;
	bool InputIsCorrect,PointExists=false;
	int i,FractionalPartLength=0;
	int IntegerPartLength=0;
	stringstream StringStream;
	StringStream<<fixed<<setprecision(0)<<FLT_MAX;
	StringStream>>MaxNumber;
	StringStream.clear();
	char ch=getch();
	while(ch!=13 && ch!=27)
	{
		InputIsCorrect=false;
		if(ch==8 && input.length()>0)
		{
			cout<<"\b \b";
			if(input[input.length()-1]=='.' || input[input.length()-1]==',')
			{
				PointExists=false;
				FractionalPartLength=0;
			}
			else
			{
				if(PointExists==true)				
					FractionalPartLength--;
				else
					IntegerPartLength--;
			}
			input.pop_back();			
		}
		else
			if((isdigit(ch)) && (input[0]!='0' || PointExists==true))
			{
				InputIsCorrect=true;
				if(PointExists==true)
				{					
					if(FractionalPartLength+1>FloatingPointNumberPrecision)
						InputIsCorrect=false;
					else
						FractionalPartLength++;
				}
				else
				{
					IntegerPartLength++;
					if(input.length()==MaxNumber.length()-1)
					{
						for(i=0; i<input.length(); i++)
							if(input[i]>MaxNumber[i])
							{
								InputIsCorrect=false;
								IntegerPartLength--;
								break;
							}
							else
								if(input[i]<MaxNumber[i])
									break;
						if(i==input.length() && ch>MaxNumber[MaxNumber.length()-1])
						{
							InputIsCorrect=false;
							IntegerPartLength--;
						}
					}
					else
						if(IntegerPartLength>MaxNumber.length())
						{
							InputIsCorrect=false;
							IntegerPartLength--;
						}
				}
			}
			else
				if((ch=='.' || ch==',') && (input.length()>0) && PointExists==false)
				{
					ch='.';
					PointExists=true;
					InputIsCorrect=true;
				}
		if(InputIsCorrect)
		{
			input+=ch;
			cout<<ch;
		}
		ch=getch();
	}
	if(ch==27)
		exit(0);
	StringStream<<input;
	StringStream>>fixed>>setprecision(FloatingPointNumberPrecision)>>result;
	return result;
}
long double GetLongDoubleFromKeyboard()
{
	long double result;
	string input,MaxNumber;
	bool InputIsCorrect,PointExists=false;
	int i,FractionalPartLength=0;
	int IntegerPartLength=0;
	stringstream StringStream;
	StringStream<<fixed<<setprecision(0)<<LDBL_MAX;
	StringStream>>MaxNumber;
	StringStream.clear();
	char ch=getch();
	while(ch!=13 && ch!=27)
	{
		InputIsCorrect=false;
		if(ch==8 && input.length()>0)
		{
			cout<<"\b \b";
			if(input[input.length()-1]=='.' || input[input.length()-1]==',')
			{
				PointExists=false;
				FractionalPartLength=0;
			}
			else
			{
				if(PointExists==true)				
					FractionalPartLength--;
				else
					IntegerPartLength--;
			}
			input.pop_back();
		}
		else
			if((isdigit(ch)) && (input[0]!='0' || PointExists==true))
			{
				InputIsCorrect=true;
				if(PointExists==true)
				{					
					if(FractionalPartLength+1>FloatingPointNumberPrecision)
						InputIsCorrect=false;
					else
						FractionalPartLength++;
				}
				else
				{
					IntegerPartLength++;
					if(input.length()==MaxNumber.length()-1)
					{
						for(i=0; i<input.length(); i++)
							if(input[i]>MaxNumber[i])
							{
								InputIsCorrect=false;
								IntegerPartLength--;
								break;
							}
							else
								if(input[i]<MaxNumber[i])
									break;
						if(i==input.length() && ch>MaxNumber[MaxNumber.length()-1])
						{
							InputIsCorrect=false;
							IntegerPartLength--;
						}
					}
					else
						if(IntegerPartLength>MaxNumber.length())
						{
							InputIsCorrect=false;
							IntegerPartLength--;
						}
				}
			}
			else
				if((ch=='.' || ch==',') && (input.length()>0) && PointExists==false)
				{
					ch='.';
					PointExists=true;
					InputIsCorrect=true;
				}
		if(InputIsCorrect)
		{
			input+=ch;
			cout<<ch;
		}
		ch=getch();
	}
	if(ch==27)
		exit(0);
	StringStream<<input;
	StringStream>>fixed>>setprecision(FloatingPointNumberPrecision)>>result;
	return result;
}