#include "accessories.h"
#include "globals.h"
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
		exit(0);
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

