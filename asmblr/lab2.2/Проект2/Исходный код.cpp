#include <stdio.h>
int k;
int main(){
	int A[10];
	char j;
	k = 3;
	j = 0;
	while (j < 10){
		_asm{
			//if (j != 7)
			movsx eax, j;
			cmp eax, 7;
			je ln4main;
			//k += j
			movsx eax, j;
			add eax, k;
			mov k, eax;
			LN4main:
			//A[j] = k;
			movsx eax,j
			mov ecx,k
			mov A[eax * 4], ecx
			//j++;
			mov al,j
			add al,1
			mov j,al	
			}
			}
	for (j = 0; j<10; j++)
		printf("%d ", A[j]);
		printf("\n");
	getchar();
	return 0;
}