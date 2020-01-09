 #include <stdio.h>
int main()
{
    float cost=12.99;
	float percent=80.0;
	printf ("Данный экземпляр книги \"Война и мир\" стоит $%.2f.\nЭто %.0f%% от цены в прайс-листе.\n",cost,percent);
	int a1=5678;
	int b1=0x8A;
	float c1=232.346;
	float d1=2.33e+002;
	char e1[40]="My string123456";
	printf ("%d|\n%4x|\n%10.3f|\n%12.2e|\n%-30s|\n========================\n",a1,b1,c1,d1,e1);
	unsigned long a2=1234567890;
	int b2=0x8A;
	float c2=2.33e+02;
	float d2=232.346;
	char e2[40]="12345678910";
	printf ("%15lu|\n%#4x|\n%#-12.2e|\n%+10.3f|\n%8.8s|\n========================\n",a2,b2,c2,d2,e2);
	int a3=12345;
	int b3=024;
	char c3='Y';
	float d3=321.13;
	char e3[40]="My string1234567890";
	printf ("%6.4d|\n%*o|\n%2c|\n%+.2f|\n%-7.5s|\n========================\n",a3,5,b3,c3,d3,e3);
	int a4;
	scanf("%d",&a4);
	printf("input: %d\n",a4);
	float b5,b6;
	scanf("%f %f",&b5,&b6);
	printf("input: %f %e\n",b5,b6);
	char c4[20];
	scanf("%s",c4);
	printf("input: %s\n",c4);
	char d4[20];
	int d5;
	scanf("%s %d",d4,&d5);
	printf("input: %s %d\n",d4,d5);
	char e4[20];
	int e5;
	scanf("%*s %d",e4,&e5);
	printf("input: %d\n",e5);
	getchar();
	getchar();
	return 0;
}