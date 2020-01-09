/*Напишите функцию, которая циклически сдвигает биты значение типа unsigned int на указанное количество позиций влево. Например, функция rotate_l(x,4) перемещает биты значения x на четыре позиции влево, при этом утраченные слева биты воспроизводятся в правой части комбинации. Другими словами, вытесненный старший бит помещается в позицию младшего бита. Протестируйте функцию в какой-нибудь программе.*/
#include <stdio.h>
int get_bits_count(unsigned int n)
{
	int bits_count=0;
	while(n>0)
	{
		bits_count++;
		n>>=1;
	}
	return bits_count;
}
unsigned int rotate_left(unsigned int n, short bits_count)
{
	int total_bits_count=get_bits_count(n);
	if(bits_count>total_bits_count)
	{
		printf("не содержит такого количества битов.\n");
		return (unsigned int)0;
	}
	int bit,original_n=n;
	for(int i=0; i<bits_count; i++)
	{
		bit=(original_n>>total_bits_count-1)&1;
		total_bits_count--;
		n<<=1;
		n|=bit;
	}
	return n;
}
char *convert_to_binary(int n)
{
	char ch,*res=(char*)malloc(40*sizeof(char));
	int i=0;
	int bits_count=get_bits_count(n);
	if(bits_count==0)
		return "0";
	while(bits_count>0)
	{
		res[i]=(char)'0'+((n>>bits_count-1)&1);		
		bits_count--;
		i++;
	}
	return res;
}
int main(void)
{
	unsigned int n=28;
	short bits_count=5;
	char *s=convert_to_binary(n);	
	printf("Исходное число %d (в двоичной системе %s)\n",n,s);
	n=rotate_left(n,bits_count);
	if(n>0)
		printf("сдвинуто на %d позиций влево: %s.\n",
				bits_count,convert_to_binary(n));
    return 0;
}