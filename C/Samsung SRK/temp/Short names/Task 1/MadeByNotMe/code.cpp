#include <iostream>
#include <string>
using namespace std;
void sort(int *a,int n)
{
	char sorted=0;
	int i,t;
	while(sorted!=1)
	{
		sorted=1;
		for(i=0; i<n-1; i++)
			if(a[i]<a[i+1])
			{
				sorted=0;
				t=a[i];
				a[i]=a[i+1];
				a[i+1]=t;
			}
	}
}
struct Z
{
	bool r;
	string otr;
};
bool NotSovp(string a, string b)
{
	bool r=1;
	int p=0,sz=a.length();
	while(r==1 && p<sz)
	{
		if (a[p]=='1' && b[p]=='1') r=0;
		p++;
	}
	return r;
}
int Poisk(int n, int *Otr)
{
	int S=0;
	/*int Otr[n];	
	for (int i=0;i<n;i++)
	{
		cin>>Otr[i];
		S+=Otr[i];
	}*/
	for(int i=0; i<n; i++)
		S+=Otr[i];
	S/=2;
	Z tab[S+1][n];
	string s="";
	for (int i=0;i<n;i++)
		s=s+'0';
	for (int j=1;j<=S;j++)
		for (int i=0;i<n;i++)
		{
			tab[j][i].otr=s;
			tab[j][i].r=0;
		}
		if (Otr[0]<=S)
		{
			tab[Otr[0]][0].r=1;
			tab[Otr[0]][0].otr[0]='1';
		}
		for (int i=1;i<n;i++)
			if (Otr[i]<=S)
			{
				tab[Otr[i]][i].r=1;
				tab[Otr[i]][i].otr[i]='1';
				for (int j=1;j<=S-Otr[i];j++)
					for (int k=0;k<i;k++)
						if (tab[j][k].r==1)
						{
							tab[j+Otr[i]][i].r=1;
							tab[j+Otr[i]][i].otr=tab[j][k].otr;
							tab[j+Otr[i]][i].otr[i]='1';
						}
			}
	/*for (int y=1;y<=S;y++)
	{
		cout<<y<<' ';
		for (int x=0;x<n;x++)
			if (tab[y][x].r)
				cout<<tab[y][x].otr<<' ';
			cout<<endl;
	}cout<<endl;*/
	int otv=0;
	int y=S;
	while(otv==0 && y>0)
	{
		for (int i=0;i<n-1;i++)
		{
			if (tab[y][i].r==1)
				for (int j=i+1;j<n;j++)
					if (tab[y][j].r==1 && NotSovp(tab[y][i].otr,tab[y][j].otr ) ) 
						otv=y;
		}
		y--;
	}
	return otv;
}

int main()
{
	FILE *f=fopen("test.txt","r");
	int i,result,StrPartsCount,PartsCount,*numbers=NULL;
	fscanf(f,"%d",&StrPartsCount);
	while(StrPartsCount-->0)
	{
		fscanf(f,"%d",&PartsCount);
		numbers=(int*)malloc(PartsCount*sizeof(int));
		for(i=0; i<PartsCount; i++)
		{
			fscanf(f,"%d ",&numbers[i]);
			printf("%d ",numbers[i]);
		}
		sort(numbers,PartsCount);
		/*printf("\n-----------------------------------------------\n");
		sort(numbers,PartsCount);
		for(i=0; i<PartsCount; i++)
			printf("%d ",numbers[i]);*/		
		result=Poisk(PartsCount,numbers);//GetBiggestLengthOfTwoEqualParts(PartsCount,numbers);
		printf("\nBiggest length of two equal parts: %d\n",result);
		
		printf("===============================================\n");
		free(numbers);
	}
	fclose(f);
	/*int n,kt;
	cin>>kt;
	for(int t=0;t<kt;t++)
	{
		cin>>n;
		if (n>=2)
			cout<<Poisk(n)<<endl;
		if (n<2)
			cout<<0<<endl;
	}*/
    return 0;
}
