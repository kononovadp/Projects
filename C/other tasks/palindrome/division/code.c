/*Напишите программу, которая возвращает наибольшее число палиндром, которое является произведением двух простых пятизначных чисел, а также возвращает сами сомножители.
Простое число - это натуральное число, которое делится нацело только на 1 и на себя само (2, 3, 5, 7, 11, …)
Палиндром – строка, которая читается одинаково в обоих направлениях (например ABBA).*/
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
unsigned long long int invert_int_number(unsigned long long int number)
{	
	unsigned long long int i=1;
	unsigned long long int res=0;
	while (i<=number/10)
		i*=10;
	while (number>0)
	{		
		res=res+((number%10)*i);		
		number/=10;		
		i/=10;		
	}
	return res;
}
int prime_number(int n)
{
    for(int i=2; i<=n/2; i++)
		if( (n%i)==0 ) return 0;
	return 1;
}
unsigned long long int get_palindrome(int lower_limit, unsigned long long int palindrome)
{
	if(palindrome==invert_int_number(palindrome))
		palindrome--;
	while(palindrome>lower_limit)
	{
		if(palindrome==invert_int_number(palindrome))
			return palindrome;
		palindrome--;
	}
	return 0;
}
int get_prime_number(int lower_limit, int previous_number)
{
	if(prime_number(previous_number))
		previous_number--;
	while(previous_number>lower_limit)
	{
		if(prime_number(previous_number))
			return previous_number;
		previous_number--;
	}
	return 0;
}
bool get_multipliers(int lower_limit,int upper_limit, unsigned long long int palindrome, FILE *logfile,unsigned long long int *step, int *multiplier1, int *multiplier2)
{
	int second_multiplier;
	while(upper_limit>lower_limit)
	{
		*step=*step+1;
		second_multiplier=palindrome / upper_limit;
		fprintf(logfile,"Step %lld: %lld / %d = %d\n",*step,palindrome,upper_limit,
		second_multiplier);
		if((prime_number(second_multiplier)) && 
		(upper_limit*second_multiplier==palindrome) && (second_multiplier>=
		lower_limit) && (second_multiplier<=upper_limit))
		{
			*multiplier1=upper_limit;
			*multiplier2=second_multiplier;
			return true;
		}
		upper_limit=get_prime_number(lower_limit,upper_limit);
	}
	return false;
}
void division(int lower_limit, int upper_limit, char *filename, bool optimization)
{
	time_t begin=time(&begin);
	FILE *logfile=fopen(filename,"w");
	printf("\nLooking for multipliers in the limits of %d-%d...",lower_limit,upper_limit);
	int multiplier1=0;
	int multiplier2=0;
	bool answer=false;
	unsigned long long int step=0;
	unsigned long long int palindrome;
	if(optimization==true)
		palindrome=get_palindrome(lower_limit,lower_limit*upper_limit);
	else
		palindrome=get_palindrome(lower_limit,upper_limit*upper_limit);
	upper_limit=get_prime_number(lower_limit,upper_limit);
	while((palindrome>lower_limit) && ((answer=get_multipliers (lower_limit,upper_limit,palindrome,logfile,&step,&multiplier1,&multiplier2))==false))
		palindrome=get_palindrome(lower_limit,palindrome);
	if(answer==true)
	{
		printf("\nPalindrome = %lld; multiplier 1=%d; multiplier 2=%d",palindrome,multiplier1,multiplier2);
		fprintf(logfile,"\nPalindrome = %lld; multiplier 1=%d; multiplier 2=%d",palindrome,multiplier1,multiplier2);
	}
	else
	{
		printf("No palindrome found within the limits of %d-%d",lower_limit,upper_limit);
		fprintf(logfile,"No palindrome found within the limits of %d-%d",lower_limit,upper_limit);
	}
	time_t end=time(&end);
	printf("\nTime: %d seconds. Steps count: %lld.\n",end-begin,step);
	fprintf(logfile,"\nTime: %d seconds. Steps count: %lld",end-begin,step);
	fclose(logfile);
}
void get_filename(char *name, int lower_limit, int upper_limit, char *optimization)
{
	char temp[20];
	strcpy(name,"logs\\");
	strcat(name,_itoa(lower_limit,temp,10));	
	strcat(name,"-");
	strcat(name,_itoa(upper_limit,temp,10));
	strcat(name,optimization);	
}
int main(void)
{
	int lower_limit=10;
	int upper_limit=99;
	char filename[40];
	printf("OPTIMIZATION ENABLED");
	_mkdir("logs");
	for(int i=0; i<4; i++)
	{
		get_filename(filename,lower_limit,upper_limit,"_optimized.txt");		
		division(lower_limit,upper_limit,filename,true);
		printf("-------------------------------------------------------------");
		lower_limit=upper_limit+1;
		upper_limit=lower_limit*10-1;
	}
	lower_limit=10;
	upper_limit=99;
	printf("\nOPTIMIZATION DISABLED");
	for(int i=0; i<4; i++)
	{
		get_filename(filename,lower_limit,upper_limit,"_optimized.txt");		
		division(lower_limit,upper_limit,filename,false);
		printf("-------------------------------------------------------------");
		lower_limit=upper_limit+1;
		upper_limit=lower_limit*10-1;
	}
	return 0;
}