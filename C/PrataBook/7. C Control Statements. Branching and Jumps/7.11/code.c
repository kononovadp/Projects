/*�������� ABC Mail Grocery ������� �������� �� ���� $2.05 �� ����, ������ �� $1.15 �� ���� � ������� �� $1.09 �� ����. �� ���������� ������ �� �������� �������� ������������� ������ 5% �� ������ �� ����� $100 � ����. ������� ���������� $6.50 �� �������� � ��������� ������ ����� � 5 ������ ��� �����, $14.00 �� ��������� � �������� ������ ����� �� 5 �� 20 ������ � $14.00 ���� $0.50 �� ������ ���� ��� �������� ������ � �����, ����������� 20 ������. �������� ���������, ������� ���������� �������� switch � ����� ���, ��� � ����� �� ���� � ������������ �������� ����������� ������� �������� ��� ��������� � ������; � ����� �� ���� b - ��� ������ � ������; � ����� �� ���� � - ��� ������� � ������; � � ����� �� ���� q - ��������� ������� ������. ��������� ������ ����� ���� ���� ����������� ������. �� ���� ���� ������������ ������ 4 ����� ������ � ����� ������ ��� 5 ������ ������, ��������� ������ �������� � ������ 9 ������ ������. ����� ��������� ������ ��������� ����� �������, ������, ���� ����, ������� �� �������� � ������ ����� ������. ����� ��������� ������ ���������� ��� ���������� � �������: ��������� ����� ������, ���������� ���������� ������, ��������� ������� ����������� ���� ������, ����� ��������� ������, ������ (���� ����), ������� �� �������� � �������� ����� ������ � ������ ���� ������.*/
#define artichoke_1pound_price 2.05
#define beet_1pound_price 1.15
#define carrot_1pound_price 1.09
#define discount_size 5.0
#define deliver_5pound 6.50
#define deliver_5_20pound 14.00
#define deliver_more20pound 0.50
#include <string.h>
#include <stdio.h>
void add_good(float*good_weight,float*weight_total,float*good_price,float*price_total,char good_name[10])
{	
	float temp;
	printf("��� %s: ",good_name);
	scanf("%f",&temp);
	*good_weight+=temp;
	*weight_total+=temp;
	if (strcmp(good_name,"���������")==0)
		temp=temp*artichoke_1pound_price;
	else
		if (strcmp(good_name,"������")==0)
			temp=temp*beet_1pound_price;
		else
			temp=temp*carrot_1pound_price;
	*good_price+=temp;
	*price_total+=temp;		
}
void complete_order(float artichoke_weight,float beet_weight,float carrot_weight,
				float artichoke_price,float beet_price,float carrot_price,					
				float weight_total,float price_total)
{	
	if(artichoke_weight==0.0&&beet_weight==0.0&&carrot_weight==0.0)
		printf("��� ������.");
	else
	{
		float discount,delivery;
		printf("|         ���|         ���|���� 1 �����|        ����|\n");
		if(price_total>=100.0)
		{
			discount=price_total*discount_size/100;
			price_total-=discount;
		}
		if (weight_total<=5)
			delivery=deliver_5pound;
		else
			if (weight_total>5 && weight_total<=20)
				delivery=deliver_5_20pound;
			else
				delivery=deliver_5_20pound+deliver_more20pound*(weight_total-20);
		price_total+=delivery;
		if (artichoke_weight>0.0)
			printf("%1c%12s%1c%12.2f%1c%12.2f%1c%12.2f|\n",'|',"��������",'|',
			artichoke_weight,'|',artichoke_1pound_price,'|',artichoke_price);
		if (beet_weight>0.0)
			printf("%1c%12s%1c%12.2f%1c%12.2f%1c%12.2f|\n",'|',"������",'|',
			beet_weight,'|',beet_1pound_price,'|',beet_price);
		if (carrot_weight>0.0)
			printf("%1c%12s%1c%12.2f%1c%12.2f%1c%12.2f|\n",'|',"�������",'|',
			carrot_weight,'|',carrot_1pound_price,'|',carrot_price);
			printf("������ ���������� � ������:\n����� ��� ���������� ������ (� ������): %0.2f;\n������: %0.2f;\n�������� � ���������: %0.2f;\n�����: %0.2f;",
			weight_total,discount,delivery,price_total);
	}			
}
int main(void)
{
	int i=0;
	short boolean;
	char ch;
	float artichoke_weight=0.0; float beet_weight=0.0; float carrot_weight=0.0;
	float weight_total=0.0;	float price_total=0.0; float artichoke_price=0.0;
	float beet_price=0.0; float carrot_price=0.0;
	printf("a) ��������; b) ������; c) �������; q) ��������� ����� � �����.\n"
	"�������� ����� ��� ��������: ");
	ch=getchar();
	while(ch!='q')
	{		
		boolean=0;
		switch(ch)
		{			
			case 'a': add_good(&artichoke_weight,&weight_total,&artichoke_price,
			&price_total,"���������"); break;			
			case 'b': add_good(&beet_weight,&weight_total,&beet_price,&price_total,
			"������"); break;			
			case 'c': add_good(&carrot_weight,&weight_total,&carrot_price,&price_total,"�������"); break;			
			case 'q': break;
			case '\n': break;
			default: printf("�������� ���������� ��������"); boolean=1; break;
		}
		if (ch!='\n')
		{
			if (boolean==1)
				printf("\n");
			printf("***************************************************************\n"
			"a) ��������; b) ������; c) �������; q) ��������� ����� � �����.\n"
			"�������� ����� ��� ��������: ");
		}
		ch=getchar();
	}
	complete_order(artichoke_weight,beet_weight,carrot_weight,artichoke_price,
	beet_price,carrot_price,weight_total,price_total);
	return 0;	
}