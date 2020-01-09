/*Компания ABC Mail Grocery продает артишоки по цене $2.05 за фунт, свеклу по $1.15 за фунт и морковь по $1.09 за фунт. До добавления затрат на доставку компания предоставляет скидку 5% на заказы на сумму $100 и выше. Затраты составляют $6.50 за доставку и обработку заказа весом в 5 фунтов или менее, $14.00 за обработку и доставку заказа весом от 5 до 20 фунтов и $14.00 плюс $0.50 за каждый фунт для доставки заказа с весом, превышающем 20 фунтов. Напишите программу, которая использует оператор switch в цикле так, что в ответ на ввод а пользователь получает возможность указать желаемый вес артишоков в фунтах; в ответ на ввод b - вес свеклы в фунтах; в ответ на ввод с - вес моркови в фунтах; а в ответ на ввод q - завершить процесс заказа. Программа должна вести учет сумм нарастающим итогом. То есть если пользователь вводит 4 фунта свеклы и позже вводит еще 5 фунтов свеклы, программа должна сообщать о заказе 9 фунтов свеклы. Затем программа должна вычислить общие затраты, скидку, если есть, расходы на доставку и полную сумму заказа. Далее программа должна отобразить всю информацию о покупке: стоимость фунта товара, количество заказанных фунтов, стоимость каждого заказанного вида овощей, общую стоимость заказа, скидку (если есть), затраты на доставку и итоговую сумму заказа с учетом всех затрат.*/
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
	printf("Вес %s: ",good_name);
	scanf("%f",&temp);
	*good_weight+=temp;
	*weight_total+=temp;
	if (strcmp(good_name,"артишоков")==0)
		temp=temp*artichoke_1pound_price;
	else
		if (strcmp(good_name,"свеклы")==0)
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
		printf("Нет заказа.");
	else
	{
		float discount,delivery;
		printf("|         Имя|         Вес|Цена 1 фунта|        Цена|\n");
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
			printf("%1c%12s%1c%12.2f%1c%12.2f%1c%12.2f|\n",'|',"Артишоки",'|',
			artichoke_weight,'|',artichoke_1pound_price,'|',artichoke_price);
		if (beet_weight>0.0)
			printf("%1c%12s%1c%12.2f%1c%12.2f%1c%12.2f|\n",'|',"Свекла",'|',
			beet_weight,'|',beet_1pound_price,'|',beet_price);
		if (carrot_weight>0.0)
			printf("%1c%12s%1c%12.2f%1c%12.2f%1c%12.2f|\n",'|',"Морковь",'|',
			carrot_weight,'|',carrot_1pound_price,'|',carrot_price);
			printf("Полная информация о заказе:\nОбщий вес заказанных овощей (в фунтах): %0.2f;\nСкидка: %0.2f;\nДоставка и обработка: %0.2f;\nИтого: %0.2f;",
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
	printf("a) Артишоки; b) Свекла; c) Морковь; q) Завершить заказ и выйти.\n"
	"Выберите товар или действие: ");
	ch=getchar();
	while(ch!='q')
	{		
		boolean=0;
		switch(ch)
		{			
			case 'a': add_good(&artichoke_weight,&weight_total,&artichoke_price,
			&price_total,"артишоков"); break;			
			case 'b': add_good(&beet_weight,&weight_total,&beet_price,&price_total,
			"свеклы"); break;			
			case 'c': add_good(&carrot_weight,&weight_total,&carrot_price,&price_total,"моркови"); break;			
			case 'q': break;
			case '\n': break;
			default: printf("Выберите корректное действие"); boolean=1; break;
		}
		if (ch!='\n')
		{
			if (boolean==1)
				printf("\n");
			printf("***************************************************************\n"
			"a) Артишоки; b) Свекла; c) Морковь; q) Завершить заказ и выйти.\n"
			"Выберите товар или действие: ");
		}
		ch=getchar();
	}
	complete_order(artichoke_weight,beet_weight,carrot_weight,artichoke_price,
	beet_price,carrot_price,weight_total,price_total);
	return 0;	
}