/*Напишите функцию, которая принимает в качестве аргумента имя отсортированного массива целых чисел, количество элементов в массиве и целое число, которое нужно найти. Функция возвращает значение 1, если целое число присутствует, и 0 - если отсутствует. Воспользуйтесь двоичным поиском.*/
#include <stdio.h>
#include <stdbool.h>
void SortArray(int *arr, int n)
{
	bool sorted=false;
	int i,temp;
	while(sorted==false)
	{
		sorted=true;
		for(i=0; i<n; i++)
				if(arr[i]>arr[i+1])
				{
					sorted=false;
					temp=arr[i];
					arr[i]=arr[i+1];
					arr[i+1]=temp;
				}
	}
}
void ShowArray(int *arr, int n)
{
	for(int i=0; i<n; i++)
	{
		if(i!=0 && i%10==0)
			putchar('\n');
		printf("%d ",arr[i]);
	}
}
//рекурсивная реализация:
/*bool BinarySearch(int *arr, int n, int required,int *steps) 
{	
	*steps=*steps+1;
	if(arr[n-1]==required)
		return true;
	if(n==0)
		return false;
	n/=2;
	if (arr[n]==required)
		return true;
	else
		if(required<arr[n])
			BinarySearch(arr,n,required,steps);
		else
			if(required>arr[n])
				BinarySearch(&arr[n],n,required,steps);
}*/
bool BinarySearch(int *arr, int n, int required,int *steps)
{	
	int min=0;
	int max=n;
	*steps=*steps+1;
	if(arr[0]==required)
		return true;
	while(max-min!=1)
	{
		*steps=*steps+1;
		n=(min+max)/2;
		if(required==arr[n])
			return true;
		else
			if(required<arr[n])
				max=n;
			else
				if(required>arr[n])
					min=n;		
	}
	return false;
}
					
int main(void)
{
	int n=1023;
	int arr[n];
	int steps=0;
	int required;
	srand((unsigned int) time(0));
	for(int i=0; i<n; i++)
		arr[i]=rand()%3000;
	ShowArray(arr,n);
	putchar('\n');
	SortArray(arr,n);
	printf("=========================================\n");
	ShowArray(arr,n);
	putchar('\n');
	printf("Enter a number or no number to exit: ");
	while(scanf("%d",&required))
	{
		steps=0;
		if(BinarySearch(arr,n,required,&steps)==true)
			printf("Number found; ");
		else
			printf("Number NOT found; ");
		printf("steps count: %d\n",steps);
		printf("Enter a number or no number to exit: ");
	}
    return 0;
}
