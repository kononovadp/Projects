/*Воспользуйтесь вложенными циклами, чтобы написать программу, которая выводит следующую последовательность символов:
$
$$
$$$
$$$$
$$$$$*/
 #include <stdio.h>
 #define size 26
 int main(void)
 {
	 int i,j;
	 for(i=1; i<6; i++)
	 {
		 for (j=0; j<i; j++)
			 printf("$");
		 printf("\n");
	 }
	 getchar();
	 return 0;
 }