#include <stdio.h>
#include <malloc.h>
/*5. 6867/7=981 - 7 нажатий вместо 9;
7. 1111-122-2=987 - 11 нажатий вместо 12;
9. 1111-122-2=987 - 11 нажатий вместо 20;
13. 1000/2=500 - 7 нажатий вместо 8;*/

//ф-я получает кол-во цифр в числе
int GetDigitsCount(long long int n)
{
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return i;
}
//ф-я возвращает максимальный предел для операций деления и умножения
long long int GetMaxForDivAndMinus(long long int RequiredNumber)
{
	long long int max=1;	
	while(RequiredNumber>1)
	{		
		max*=10;
		RequiredNumber/=10;
	}
	return max*10;
}
//ф-я проверяет, можно ли число набрать без арифметических действий
long long int CheckNumber(int *digits,int DigitsCount,long long int RequiredNumber)
{
	int i,j,mod,result;
	char found=1;
	if(RequiredNumber==0)
	{
		for(i=0; i<DigitsCount; i++)
			if(digits[i]==0)
				return 1;
		return 0;
	}
	for(i=0,result=GetDigitsCount(RequiredNumber); i<result && found==1; i++)
	{
		found=0;
		mod=RequiredNumber%10;
		RequiredNumber/=10;
		for(j=0; j<DigitsCount && found==0; j++)
			if(digits[j]==mod)
				found=1;
	}
	if(found==1)
		return result;
	return 0;
}
/*Основная рекурсивная ф-я пересчета. Список переменных:
*digits - массив чисел на клавиатуре; DigitsCount - кол-во доступных чисел
на клавиатуре; *operations - массив символов арифметических операций; 
OperationsCount - кол-во операций; CurrentPressesCount - текущее кол-во 
нажатий; MinimalPressesCount - текущее минимальное кол-во нажатий;
RequiredNumber - число, которое нужно набрать; MinimumForMinusAndDiv -
максимум для операций деления и умножения; AllResults - все результаты для 
избежания полного перебора; KeyboardNumbers - все числа, которые можно 
набрать без арифметических операций; operands - числа, с помощью которых 
получен результат; OperationsForResult - операции, с помощью которых
получен результат; OperationsCountForResult - кол-во операций.*/
long long int calc(int *digits,int DigitsCount,char *operations,int OperationsCount,int CurrentPressesCount,int MinimalPressesCount,long long int RequiredNumber,long long int MinimumForMinusAndDiv,char *AllResults,char *KeyboardNumbers,long long int *operands,char *OperationsForResult,char *OperationsCountForResult)
{
	long long int i,result,max,operand1,operand2;
	char j,operation,PreviousMinimum=MinimalPressesCount;
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает текущий минимум, то возвращаем -1
	if(AllResults[RequiredNumber]==-1 || CurrentPressesCount>MinimalPressesCount)
		return -1;
	//если результат для данного числа уже был получен, то возвращает его
	if(AllResults[RequiredNumber]>0)
	{	//если вызываем ф-ю первый раз, то знак "равно" не добавляем
		if(CurrentPressesCount==0)
			CurrentPressesCount=AllResults[RequiredNumber];
		else
			if(AllResults[RequiredNumber]>0)
				CurrentPressesCount=CurrentPressesCount+AllResults[RequiredNumber]+1;
		return CurrentPressesCount;
	}
	for(j=0; j<OperationsCount; j++)
		if(operations[j]=='+')
		{
			for(i=RequiredNumber-1; i>0; i--)
				if(AllResults[i]>0)
				{
					result=calc(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+AllResults[i]+1,MinimalPressesCount,RequiredNumber-i,MinimumForMinusAndDiv,AllResults,KeyboardNumbers,operands,OperationsForResult,OperationsCountForResult);
					if(result>0 && result<MinimalPressesCount)
					{
						MinimalPressesCount=result;
						operand1=i;
						operation='+';
						operand2=RequiredNumber-i;
					}
				}
		}
		else
			if(operations[j]=='*')
			{
				for(i=RequiredNumber-1; i>1; i--)
					if(AllResults[i]>0 && RequiredNumber%i==0)
					{
						result=calc(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+AllResults[i]+1,MinimalPressesCount,RequiredNumber/i,MinimumForMinusAndDiv,AllResults,KeyboardNumbers,operands,OperationsForResult,OperationsCountForResult);
						if(result>0 && result<MinimalPressesCount)
						{
							MinimalPressesCount=result;
							operand1=i;
							operation='*';
							operand2=RequiredNumber/i;
						}
					}
			}
			else
				if(operations[j]=='-')
				{
					for(max=MinimumForMinusAndDiv-RequiredNumber,i=max; i>0; i--)
						if(AllResults[i]>0)
						{
							result=calc(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+AllResults[i]+1,MinimalPressesCount,RequiredNumber+i,MinimumForMinusAndDiv,AllResults,KeyboardNumbers,operands,OperationsForResult,OperationsCountForResult);
							if(result>0 && result<MinimalPressesCount)
							{
								MinimalPressesCount=result;
								operand1=i;
								operation='-';
								operand2=RequiredNumber+i;
							}
						}
					}
					else
						if(operations[j]=='/')
						{
							for(max=MinimumForMinusAndDiv/RequiredNumber,i=max; i>1; i--)
								if(AllResults[i]>0)
								{
									result=calc(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+AllResults[i]+1,MinimalPressesCount,RequiredNumber*i,MinimumForMinusAndDiv,AllResults,KeyboardNumbers,operands,OperationsForResult,OperationsCountForResult);
									if(result>0 && result<MinimalPressesCount)
									{
										MinimalPressesCount=result;
										operand1=i;
										operation='/';
										operand2=RequiredNumber*i;
									}
								}
						}
	if(MinimalPressesCount==PreviousMinimum)
		return AllResults[RequiredNumber]=-1;
	//сохранение чисел, с помощью которых получен результат
	if(KeyboardNumbers[operand2]>0 && KeyboardNumbers[operand1]>0)
	{
		*OperationsCountForResult=0;
		operands[0]=operand2;
		operands[1]=operand1;
		OperationsForResult[0]=operation;
		*OperationsCountForResult=1;
	}
	else
	{
		operands[*OperationsCountForResult+1]=operand1;
		OperationsForResult[*OperationsCountForResult]=operation;
		*OperationsCountForResult=*OperationsCountForResult+1;
	}
	return AllResults[RequiredNumber]=MinimalPressesCount;
}
/*digits - числа на клавиатуре; DigitsCount - кол-во чисел на клавиатуре; operations - операции;
OperationsCount - кол-во операций; MinimalPressesCount - максимальное допустимое кол-во нажатий; RequiredNumber - 
число, которое нужно набрать.*/
char GetResult(int *digits,int DigitsCount,char *operations,int OperationsCount,int MinimalPressesCount,long long int RequiredNumber)
{
	long long int i,MinusOrDivAvailable,*operands,max=RequiredNumber+1;
	char *KeyboardNumbers,*AllResults,*OperationsForResult,result,OperationsCountForResult=0;
	for(i=0,MinusOrDivAvailable=0; i<OperationsCount; i++)
		if(operations[i]=='-' || operations[i]=='/')
		{
			MinusOrDivAvailable=1;
			break;
		}
	if(MinusOrDivAvailable==1)
		max=GetMaxForDivAndMinus(RequiredNumber);
	//формируем список чисел, которые можно набрать, не выполняя 
	//арифметические действия
	AllResults=(char*)calloc(max,sizeof(char));
	KeyboardNumbers=(char*)calloc(max,sizeof(char));	
	for(i=0; i<max; i++)
	{
		AllResults[i]=CheckNumber(digits,DigitsCount,i);
		KeyboardNumbers[i]=AllResults[i];
	}
	if(AllResults[RequiredNumber]>0)
	{
		printf("\n%lld",RequiredNumber);
		result=AllResults[RequiredNumber];
	}
	else
	{
		operands=(long long int*)malloc(MinimalPressesCount*sizeof(long long int));
		OperationsForResult=(char*)malloc(MinimalPressesCount*sizeof(char));
		result=calc(digits,DigitsCount,operations,OperationsCount,0,MinimalPressesCount+1,RequiredNumber,max-1,AllResults,KeyboardNumbers,operands,OperationsForResult,&OperationsCountForResult);
		if(result>0)
		{
			putchar('\n');
			for(i=0; i<OperationsCountForResult; i++)
				printf("%lld%c",operands[i],OperationsForResult[i]);
			printf("%lld=%lld",operands[i],RequiredNumber);
		}
		free(operands);
		free(OperationsForResult);
	}
	free(AllResults);
	free(KeyboardNumbers);		
	return result;
}
int main(void)
{
	int i,j,DigitsCount,OperationsCount,MaxPressCount,*AllResults,RightResult,TasksCount=0;
	long long int RequiredNumber;
	char result,*operations;
	FILE *f=fopen("tests-input.txt","r");
	FILE *ft=fopen("correct-output.txt","r");
	fscanf(f,"%d",&TasksCount);
	for(j=0; j<TasksCount; j++)
	{
		fscanf(f,"%d",&DigitsCount);
		AllResults=(int*)malloc(DigitsCount*sizeof(int));
		for(i=0; i<DigitsCount; i++)
			fscanf(f,"%d ",&AllResults[i]);
		fscanf(f,"%d",&OperationsCount);
		operations=(char*)malloc(OperationsCount*sizeof(char));
		for(i=0; i<OperationsCount; i++)
			fscanf(f," %c",&operations[i]);
		fscanf(f,"%d",&MaxPressCount);
		fscanf(f," %lld",&RequiredNumber);
		printf("%d. DigitsCount = %d: ",j+1,DigitsCount);
		for(i=0; i<DigitsCount; i++)
			printf("%d ",AllResults[i]);
		printf("OperationsCount = %d ",OperationsCount);
		for(i=0; i<OperationsCount; i++)
			printf("%c ",operations[i]);
		printf("\nMaxPressCount = %d; RequiredNumber = %lld; ",MaxPressCount,RequiredNumber);
		result=GetResult(AllResults,DigitsCount,operations,OperationsCount,MaxPressCount,RequiredNumber);
		fscanf(ft,"%d",&RightResult);
		printf("\n		MY RESULT = %d; REQUIRED RESULT = %d",result,RightResult);
		printf("\n=====================================================\n");
		free(AllResults);
		free(operations);
	}
	fclose(f);
	fclose(ft);
	return 0;
}
