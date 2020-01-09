/*1.: 8 8
4 4
0 0
2 2
2. 4
3. Первый элемент.
4.а 12 и 16
4.б 12 и 14
5.а 12 и 14
5.б 12 и 0
6.а *(*(grid+22)+56) / &grid[22][56]
6.б *(*(grid+22)+0), *(grid+22) / &grid[22][0], &grid[22]
6.в *(*(grid+0)+0), *(grid+0), *grid / &grid[0][0], &grid[0], &grid
7.а int digits[10]
7.б float rates[6]
7.в int mat[3][5] или short mat[3][5]
7.г char *psa[20]
7.д char (*pstr)[20]
8:*/
/*#include <stdio.h>
int main(void)
{
	int arr1[6]={1,2,4,8,16,32 };
	printf("%d\n",arr1[4]);
	int arr2[100]={[99]=-1};
	int i;
	for(i=0; i<100; i++)
		printf("%d\n",arr2[i]);
	int arr3[100]={[5]=101,[10]=101,101,101,[3]=101};
	printf("======================\n");
	for(i=0; i<100; i++)
		printf("%d\n",arr3[i]);
}*/
/*9. 0-9
10.а true; 10.б true; 10.в false; 10.г false; 10.д true; 10.е false; 10.ж false; 10.з true;
11. int arr[800][600]*/
#include <stdio.h>
void functrots1(double arr[], int n);
void functrots2(int n, double arr[n]);
void funcclops1(short arr[][30], int n1);
void funcclops2(int n1, int n2, short arr[n1][n2]);
void funcshots1(long arr[][10][15], int n1);
void funcshots2(int n1, int n2, int n3, long arr[n1][n2][n3]);
void show(const double ar[], int n);
void show2(const double ar[2][3], int n);

int main(void)
{
	double trots[20];	
	short clops[10][30];
	long shots[5][10][15];
	functrots1(trots, 20);
	functrots2(20, trots);
	funcclops1(clops, 10);
	funcclops2(10, 30, clops);
	funcshots1(shots, 5);
	funcshots2(5, 10, 15, shots);
	show((const double []){8,3,9,2},4);
	show2((const double [][3]){{8,3,9},{5,4,1}},2);
}
void functrots1(double arr[], int n) {}
void functrots2(int n, double arr[n]) {}
void funcclops1(short arr[][30], int n1) {}
void funcclops2(int n1, int n2, short arr[n1][n2]) {}
void funcshots1(long arr[][10][15], int n1) {}
void funcshots2(int n1, int n2, int n3, long arr[n1][n2][n3]) {}
void show(const double ar[], int n) {}
void show2(const double ar[2][3], int n) {}