/*1. не хватает двух точек с запятой;
2. 6 1
22 Spiffo Road
S p
3. struct year
{
	char month[20];
	char abbreviation[4];
	int days_count;
	int number;
};
4-5:
#include <stdio.h>
#include <string.h>
struct year
{
	char month[20];
	char abbreviation[4];
	int days_count;
	int number;
};
void show_struct(struct year *year2018)
{
	for (int i=0; i<12; i++)
		printf("Month: %s; abbreviation: %s; days count: %d;\n",
	year2018[i].month,year2018[i].abbreviation,year2018[i].days_count);
}
int get_days_count(char *month_name,struct year *year2018)
{
	int i=1;
	int days_count=0;
	while((i<13) && (strcmp(month_name,year2018[i-1].month)!=0))
		i++;
	if((i==13) && (strcmp(month_name,year2018[i].month)!=0))
		return 0;
	else
		for(; i>0; i--)
			days_count+=year2018[i-1].days_count;
	return days_count;
}
int main(void)
{
	struct year year2018[12];
	int i,days_count=0;
	FILE *f=fopen("year2018.txt","r");
	char *str_days_count=(char*)malloc(sizeof(char)*20);
	for (i=1; i<13; i++)
		year2018[i-1].number=i;	
	for(i=0; i<12; i++)
	{
		fscanf(f,"%s",year2018[i].month);
		fscanf(f,"%s",year2018[i].abbreviation);
		fscanf(f,"%s",str_days_count);
		year2018[i].days_count=atoi(str_days_count);
	}
	show_struct(year2018);
	printf("Month name: ");
	scanf("%s",str_days_count);
	days_count=get_days_count(str_days_count,year2018);
	if(days_count)
		printf("Days count is %d",days_count);
	else
		printf("Incorrect month name.");
	fclose(f);
    return 0;
}
6.a:
#include <stdio.h>
#include <string.h>
typedef struct lens {
	float foclen;
	float fstop;
	char brand[30];
} LENS;
int main(void)
{
	LENS my_lens[10];
	strcpy(my_lens[2].brand,"Remarkatar");
	my_lens[2].foclen=500;
	my_lens[2].fstop=2;
	printf("%s foclen=%f; fstop=%f",my_lens[2].brand,my_lens[2].foclen,my_lens[2].fstop);	
	return 0;
}
6.b:
#include <stdio.h>
#include <string.h>
typedef struct lens {
	float foclen;
	float fstop;
	char brand[30];
} LENS;
int main(void)
{
LENS my_lens[10]={[2]={500,2,"Remarkatar"}};
	printf("%s foclen=%f; fstop=%f\n",my_lens[2].brand,my_lens[2].foclen,my_lens[2].fstop);
	return 0;
}
7.a: 6
Arcturan
cturan
7.б: strcpy(deb.title.last,"Gwolkapwolk"); и strcpy(pb->title.last,"Gwolkapwolk");
7.в:
#include <stdio.h>
#include "starfolk.h"
void show(struct bem *p)
{
	printf("%s %s - это %d-конечный %s.",p->title.first,p->title.last,p->limbs,
	p->type);
}
int main(void)
{
	struct bem *pb;
	struct bem deb={6,{"Berbnazel","Gwolkapwolk"},"Arcturan"};
	pb=&deb;	
	show(pb);
	return 0;
}
8.:
#include <stdio.h>
struct fullname
{
	char fname[20];
	char lname[20];
};
struct bard
{
	struct fullname name;
	int born;
	int died;
};
int main(void)
{
	struct bard willie;
	struct bard *pt=&willie;
	willie.born=1234;
	pt->born=5678;
	scanf("%d",&willie.born);
	scanf("%d",&pt->born);
	scanf("%s",&willie.name.lname);
	scanf("%s",&pt->name.lname);
	char ch=willie.name.lname[2];
	printf("\n\n--%d--",pt->born);
	printf("%d",strlen(willie.name.fname)+strlen(willie.name.lname));
	return 0;
}
9.:
#include <stdio.h>
struct car
{
	char make[20];
	int power;
	int environmental_rating;
	int wheelbase;
	int year;
};
10.:
#include <stdio.h>
struct gas
{
	float distance;
	float gals;
	float mpg;
};
struct gas calc1(struct gas my_struct)
{
	my_struct.mpg=my_struct.distance+my_struct.gals;
	return my_struct;
}
void calc2(struct gas *my_struct)
{
	my_struct->mpg=my_struct->distance+my_struct->gals;
}
int main(void)
{
	struct gas *p,new_struct={1.23, 4.34, 0};
	printf("%f %f %f\n",new_struct.distance,new_struct.gals,new_struct.mpg);
	new_struct=calc1(new_struct);
	printf("%f %f %f\n",new_struct.distance,new_struct.gals,new_struct.mpg);
	p=&new_struct;
	calc2(p);
	printf("%f %f %f\n",new_struct.distance,new_struct.gals,new_struct.mpg);
	return 0;
}
11.:
#include <stdio.h>
int main(void)
{
	enum choises{no, yes, maybe};
	printf("%d %d %d",no,yes,maybe);
	return 0;
}
12.:
#include <stdio.h>
char *func(char *pointer,char ch)
{
	return pointer;
}
int main(void)
{
	char*(*f)(char*,char)=func;
	return 0;
}
13.:*/
#include <stdio.h>
double func1(double arg1,double arg2)
{
	return arg1+0.5;
}
double func2(double arg1,double arg2)
{
	return arg1+0.5;
}
double func3(double arg1,double arg2)
{
	return arg1+0.5;
}
double func4(double arg1,double arg2)
{
	return arg1+0.5;
}
int main(void)
{
	double (*f[4])(double,double);
	f[0]=func2;
	double (*f2)(double,double)=(double(*)(double,double))malloc(sizeof(double),5);
	f2=func1;
	printf("%f\n",f[0](10.0,2.5));
	printf("%f\n",f2(10.0,2.5));	
	return 0;
}