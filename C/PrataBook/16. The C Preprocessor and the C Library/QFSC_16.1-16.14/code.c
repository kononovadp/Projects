/*1.а переводит мили в футы
1. б plort = 32;
1.в nex=6;
1.г NEW увеличивает указанную переменную на 5;
2. #define NEW(X) ((X)+(5))
3. #define LESS(x,y) x>y?x:y
4. #define EVEN_GT(x,y) x%2==0&&x>y?1:0
5. #define OPERATION(X) printf(""#X" = %d\n",X) Вызов: OPERATION(4*12);
6. const int n=25;
#define SPACE ' '
#define PS() printf("%c|",SPACE);
#define BIG(X) X+3
#define SUMSQ(X,Y) ((X*X)+(Y*Y))
7. #define NVA(x) printf("name: "#x"; value: %d; adr: %p",x,x,&x)
8. Использование директив условной компиляции #if, #ifdef, #ifndef, #elif и т. д.
9.#include <stdio.h>
#define PR_DATE() printf("%s",__DATE__)
int main(void)
{
	#ifdef PR_DATE
		PR_DATE();
	#endif
    return 0;
}
10. Функция square из первого файла видна только в пределах первого файла. Та же функция из второго файла видна в пределах трех файлах, но первый файл использует свое определение этой фунции. Второй файл использует только square из второго файла. Третий файл выбирает: либо задействовать определение функции square из третьего файла либо из второго.
11. #define IS_TYPE_BOOLEAN(X) _Generic((X),\
bool: "boolean",\
default: "not boolean")
12. Неправильный спецификатор формата для вывода на экран (%f нельзя использовать, так как тип входящего параметра - массив символов); функция sqrt не определена в stdio.h, нужно включить файл math.h; вместо char argv[] следует использовать char **argv; последняя команда должна быть "return 0;".
13. #include <stdio.h>
int comp (const void *el1, const void *el2)
{
	const int *n1=(const int*)el1;
	const int *n2=(const int*)el2;
	if(*n1<*n2)
		return -1;
	else
		if(*n1==*n2)
			return 0;
		else
			return 1;
}
void showarr(int *arr, int n)
{
	for(int i=0; i<n; i++)
	{
		if(i!=0 && i%10==0)
			putchar('\n');
		printf("%4d ",arr[i]);		
	}
}
int main(void)
{
	int n=1000;
	int scores[n];
	srand("time");
	for(int i=0; i<n; i++)
		scores[i]=rand()%1000;
	showarr(scores,n);
	qsort(scores,n,sizeof(int),comp);
	printf("\n\nSORTED ARRAY\n\n");
	showarr(scores,n);
    return 0;
}
14. #include <stdio.h>
void showarr(double *arr, int n)
{
	for(int i=0; i<n; i++)
	{
		if(i!=0 && i%10==0)
			putchar('\n');
		printf("%5.2lf ",arr[i]);		
	}
}
int main(void)
{
	int n1=100;
	int n2=300;
	double data1[n1];
	double data2[n2];
	srand("time");
	for(int i=0; i<n2; i++)
		data2[i]=rand()%100;
	printf("DATA2:\n");
	showarr(data2,n2);
	memcpy(data1,data2,n1*sizeof(double));
	printf("\n\nFIRST 10 ELEMENTS OF DATA2 IN DATA1:\n");
	showarr(data1,n1);	
	memcpy(data1,data2+200,n1*sizeof(double));
	printf("\n\nLAST 10 ELEMENTS OF DATA2 IN DATA1:\n");
	showarr(data1,n1);
    return 0;
}*/

