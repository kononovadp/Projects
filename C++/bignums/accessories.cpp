#include "accessories.h"
#ifndef _WIN32
char my_getch(void)
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
char my_kbhit(void)
{
    struct termios oldt, newt;
    char ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
#else
char my_getch(void){return getch();}
char my_kbhit(void){return kbhit();}
#endif
void InitFloatingPointAndRandomNumbers()
{
	cout.precision(FloatingPointNumberPrecision);
	cout.setf(ios::fixed);
	cout.setf(ios::unitbuf);
	srand(time(0));
}
int GetCountOfDigits(int n)
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
}
char GetRandomDigit(char min,char max)
{
	if(min==max)
		return min;
	if(min>max)	
		return max;	
	char result=min+(rand()%(max+1-min));
	if(!isdigit(result))
	{
		cout<<"Non-digital character: "<<result<<" ("<<(int)result<<")!\n"
			<<"Min character: "<<min<<" = "<<(int)min<<"; max character: "<<max<<" = "<<(int)max<<endl;
		// exit(0);
	}
	return result;
}
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
	float f=rand()/RAND_MAX;
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
	int i,j,ArraySize=strlen(array);
	char t;
	for(i=0; i<ArraySize; i++)
	{
		j=0+(rand()%ArraySize);
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
	int i,j,StringLength=str.length();
	char t;
	for(i=0; i<StringLength; i++)
	{
		j=0+(rand()%StringLength);
		t=str[i];
		str[i]=str[j];
		str[j]=t;
	}
}
string GetKeyboardInputAsString()
{	
	int i=0;
	string input;
	char ch=my_getch();
	while(ch!='\n' && ch!='\r')
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
		ch=my_getch();
	}
	return input;	
}
string GetKeyboardInputAsString(char* ExcludedCharacters)
{
	int i=0,j,StringLength=strlen(ExcludedCharacters);
	string input;
	char ch=my_getch();
	while(ch!='\n' && ch!='\r')
	{
		if(ch==8 && i>0)
		{
			cout<<"\b \b";
			input.pop_back();
		}
		else
			if(ch!=8)
			{
				for(j=0; j<StringLength; j++)
					if(ch==ExcludedCharacters[j])
						break;
				if(j==StringLength)
				{
					input+=ch;
					cout<<ch;
					i++;
				}
			}
		ch=my_getch();
	}
	return input;
}
char* GetKeyboardInputAsArrayOfChars()
{
	int i=0;	
	char* input=(char*)malloc(91);
	char ch=my_getch();
	while(ch!='\n' && ch!='\r')
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
		ch=my_getch();
	}
	input[i]='\0';
	return input;
}
int GetIntFromKeyboard(){return GetIntFromKeyboard(0,INT_MAX);}
int GetIntFromKeyboard(int MinInt,int MaxInt)
{
	int result=MinInt-1;
	size_t i;
	char ch=0;
	bool InputIsCorrect;
	string input,MaxNumber=to_string(MaxInt);	
	while(result<MinInt)
	{
		ch=my_getch();
		while(ch!='\n' && ch!='\r')
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
				{
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
					ch=my_getch();
				}
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
	size_t i;
	long result=MinInt-1;
	char ch=0;
	bool InputIsCorrect;
	string input,MaxNumber=to_string(MaxInt);	
	while(result<MinInt)
	{
		ch=my_getch();
		while(ch!='\n' && ch!='\r')
		{
			InputIsCorrect=false;
			if(ch==27)
				exit(0);
			else
			{
				if(ch==8 && input.length()>0)
				{
					cout<<"\b \b";
					input.pop_back();
				}
				else
				{
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
				}
			}
			ch=my_getch();
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
	int FractionalPartLength=0;
	size_t i,IntegerPartLength=0;
	stringstream StringStream;
	StringStream<<fixed<<setprecision(0)<<FLT_MAX;
	StringStream>>MaxNumber;
	StringStream.clear();
	char ch=my_getch();
	while(ch!='\n' && ch!='\r' && ch!='\r' && ch!=27)
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
		ch=my_getch();
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
	int FractionalPartLength=0;
	size_t i,IntegerPartLength=0;
	stringstream StringStream;
	StringStream<<fixed<<setprecision(0)<<LDBL_MAX;
	StringStream>>MaxNumber;
	StringStream.clear();
	char ch=my_getch();
	while(ch!='\n' && ch!='\r' && ch!='\r' && ch!=27)
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
		ch=my_getch();
	}
	if(ch==27)
		exit(0);
	StringStream<<input;
	StringStream>>fixed>>setprecision(FloatingPointNumberPrecision)>>result;
	return result;
}
void FillArrayWithZeros(char* arr, int size)
{
	for(int i=0; i<size; i++)
		arr[i]=0;
}
