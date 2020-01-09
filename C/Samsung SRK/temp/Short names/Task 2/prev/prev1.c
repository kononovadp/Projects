#include <stdio.h>
#include <malloc.h>
/*void CreateTests(void)
{
	char i,j,*filename;
	unsigned char ch;
	FILE *fr,*fw=fopen("tests-output.txt","w");
	fprintf(fw,"20\n");
	for(i=0; i<2; i++)
		for(j=1; j<10+i; j++)
		{
			filename=(char*)malloc(5*sizeof(char));
			itoa(i,filename,10);
			filename[1]='\0';
			filename[1]=j+'0'-i;
			filename[2]='\0';
			strcat(filename,".out");
			printf("%s\n",filename);
			fr=fopen(filename,"rb");
			while(fread(&ch,sizeof(char),1,fr))
				fprintf(fw,"%c",ch);
			fclose(fr);
			free(filename);
		}
	fr=fopen("20.out","rb");
	while(fread(&ch,sizeof(char),1,fr))
		fprintf(fw,"%c",ch);
	fclose(fr);
	fclose(fw);
}*/
void sort(int *a,int n)
{
	char sorted=0;
	int i,t;
	while(sorted!=1)
	{
		sorted=1;
		for(i=0; i<n-1; i++)
			if(a[i]>a[i+1])
			{
				sorted=0;
				t=a[i];
				a[i]=a[i+1];
				a[i+1]=t;
			}
	}
}
int GetDigitsCount(int n)
{
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return i;
}
int CheckNumber(int *numbers,int NumbersCount,int RequiredNumber)
{
	int i,j,mod,nc=GetDigitsCount(RequiredNumber);
	char found=1;
	if(RequiredNumber==0)
	{
		for(i=0; i<NumbersCount; i++)
			if(numbers[i]==0)
				return 1;
		return -1;
	}
	for(i=0; i<nc && found==1; i++)
	{
		found=0;
		mod=RequiredNumber%10;
		RequiredNumber/=10;
		for(j=0; j<NumbersCount && found==0; j++)
			if(numbers[j]==mod)
				found=1;
	}
	if(found==1)
		return nc;
	return -1;
}
int plus(int *keys,int kc,int rn,int mpc)
{
	struct part
	{
		int n;
		int c;
		int *it;
	};
	int i,k,t,pn,cn,min,minind,ind,anc,kn=0;
	int *an=(int*)malloc(sizeof(int)*rn);
	struct part **p=(struct part**)malloc(sizeof(struct part*)*(rn+1));
	if(rn<keys[0])
		return -1;
	if(an[0]==0)
		kn++;
	for(i=kn,anc=0; i<rn; i++)
		if(CheckNumber(keys,kc,i)>-1)
		{
			an[anc]=i;
			anc++;
		}
	for(cn=an[kn],pn=0; cn<=rn; cn++,pn++)
	{
		if(cn==an[kn+1] && kn<anc)
			kn++;
		p[pn]=(struct part*)malloc(sizeof(struct part)*1);
		if(cn==an[kn])
		{
			p[pn]->n=cn;
			p[pn]->c=1;
			p[pn]->it=(int*)malloc(sizeof(int));
			p[pn]->it[0]=cn;
			continue;
		}		
		min=cn+1;
		minind=cn+1;
		p[pn]->n=0;
		p[pn]->c=0;
		p[pn]->it=(int*)malloc(sizeof(int));
		for(i=0; i<=kn; i++)
		{
			t=cn-an[i];
			ind=t-p[0]->n;
			if(t>=p[0]->n && ind>=0 && p[ind]->c>0 && p[ind]->c<min)
			{
				min=p[ind]->c;
				minind=ind;
			}
		}
		if(min<cn+1)
		{
			p[pn]->n=cn;
			p[pn]->c=min+1;
			p[pn]->it=(int*)malloc(sizeof(int)*(min+1));
			for(i=0,t=cn; i<min; i++)
			{
				p[pn]->it[i]=p[minind]->it[i];
				t=t-p[minind]->it[i];
			}
			p[pn]->it[i]=t;
		}
	}
	t=0;
	if(p[pn-1]->c>0)
		for(i=0,pn=pn-1; i<p[pn]->c; i++)
			t=t+GetDigitsCount(p[pn]->it[i])+1;
	printf("\n%d  : ",p[pn]->n);
	for(i=0; i<p[pn]->c; i++)
		printf("%d ",p[pn]->it[i]);
	
	for(i=0; i<pn; i++)
	{		
		free(p[i]->it);
		free(p[i]);
	}
	free(p);
	free(an);
	if(t==0 || t>mpc)
		return -1;
	return t;
}
int mult(int *n,int nc,int rn,int mpc)
{
	int mod=1;
	int cpc=0;
	int cn=rn-1;
	while(cn>0 && rn>0 && mod>0)
	{
		while(CheckNumber(n,nc,cn)==-1 && cn>0)
			cn--;
		mod=rn%cn;		
		cpc=cpc+GetDigitsCount(cn)+GetDigitsCount(rn)+1;
		rn/=cn;
	}
	if(mod>0 || cpc>mpc)
		return -1;
	return cpc+1;
}
int minus(int *n,int nc,int rn,int mpc)
{
	int cpc,cn=rn;
	while(CheckNumber(n,nc,cn)==-1)
		cn++;
	rn=cn-rn;
	cpc=GetDigitsCount(cn)+1;
	printf("\ncn=%d; rn=%d; cpc=%d",cn,rn,cpc);
	while(rn>0 && cn>0 && cpc<mpc)
	{
		cn=rn;
		while(CheckNumber(n,nc,cn)==-1)
			cn--;
		rn=rn-cn;
		cpc=cpc+GetDigitsCount(cn)+1;
		printf("\ncn=%d; rn=%d; cpc=%d",cn,rn,cpc);
	}
	if(rn!=0 || cpc>mpc)
		return -1;
	return cpc;
}
int divide(int *n,int nc,int rn,int mpc)
{
	int res,cpc=0;
	int i,cn=rn*2;
	//FILE *f=fopen("wr.txt","w");
	while(CheckNumber(n,nc,cn)==-1)
		cn++;
	res=cn/rn;
	cpc=GetDigitsCount(cn)+GetDigitsCount(res);
	while(CheckNumber(n,nc,res)==-1 || (cn/res!=rn && cpc<mpc))
	{
		cn++;
		while(CheckNumber(n,nc,cn)==-1 && cn/res!=rn)
			cn++;
		res=cn/rn;
		cpc=GetDigitsCount(cn)+GetDigitsCount(res);		
	}	
	if(cpc>mpc)
		return -1;
	cpc+=2;
	printf("\n%d/%d=%d; cpc = %d",cn,res,rn,cpc);
	return cpc;
}
int GetRes(int *numbers,int NumbersCount,char *operations,int OperationsCount,int MaxPressCount,int rn)
{
	int i,min,res=CheckNumber(numbers,NumbersCount,rn);
	char *results=(char*)malloc(sizeof(char)*MaxPressCount);
	char rescount=0;
	if(res>-1)
		return res;	
	//return res=minus(numbers,NumbersCount,rn,MaxPressCount);
	return plus(numbers,NumbersCount,rn,MaxPressCount);
	for(i=0; i<OperationsCount; i++)
	{
		if(operations[i]=='/')
			res=divide(numbers,NumbersCount,rn,MaxPressCount-2);
		else
			if(operations[i]=='*')
				res=mult(numbers,NumbersCount,rn,MaxPressCount);
			else
				if(operations[i]=='-')
					res=minus(numbers,NumbersCount,rn,MaxPressCount);
				else
					if(operations[i]=='-')
						res=plus(numbers,NumbersCount,rn,MaxPressCount);
		if(res>-1)
		{
			results[rescount]=res;
			rescount++;
		}
		printf("\n%c = %d",operations[i],res);
	}
	if(rescount==0)
		return -1;
	for(i=0,min=results[0]; i<rescount; i++)
		if(results[i]<min)
			min=results[i];
	return min;
}
int main(void)
{
	int res,i,j,NumbersCount,OperationsCount,MaxPressCount,RequiredNumber,*numbers,TasksCount=0;
	char *operations;
	FILE *f=fopen("test.txt","r");
	fscanf(f,"%d",&TasksCount);
	for(j=0; j<TasksCount; j++)
	{
		fscanf(f,"%d",&NumbersCount);
		numbers=(int*)malloc(NumbersCount*sizeof(int));
		for(i=0; i<NumbersCount; i++)
			fscanf(f,"%d ",&numbers[i]);
		sort(numbers,NumbersCount);
		fscanf(f,"%d",&OperationsCount);
		operations=(char*)malloc(OperationsCount*sizeof(char));
		for(i=0; i<OperationsCount; i++)
			fscanf(f," %c",&operations[i]);
		fscanf(f,"%d",&MaxPressCount);
		fscanf(f," %d",&RequiredNumber);
		printf("%d. NumbersCount = %d: ",j+1,NumbersCount);
		for(i=0; i<NumbersCount; i++)
			printf("%d ",numbers[i]);
		printf("OperationsCount = %d ",OperationsCount);
		for(i=0; i<OperationsCount; i++)
			printf("%c ",operations[i]);
		printf("\nMaxPressCount = %d; RequiredNumber = %d; ",MaxPressCount,RequiredNumber);
		res=GetRes(numbers,NumbersCount,operations,OperationsCount,MaxPressCount,RequiredNumber);
		printf("\n		RES = %d",res);
		printf("\n=====================================================\n");
		free(numbers);
		free(operations);
	}
	fclose(f);
	return 0;
}