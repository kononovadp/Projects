#include <stdio.h>
typedef unsigned short WORD;
typedef unsigned long int DWORD;
typedef signed long LONG;
typedef struct tagBITMAPFILEHEADER
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;
typedef struct tagBITMAPINFOHEADER
{
	DWORD  biSize;
	LONG   biWidth;
	LONG   biHeight;
	WORD   biPlanes;
	WORD   biBitCount;
	DWORD  biCompression;
	DWORD  biSizeImage;
	LONG   biXPelsPerMeter;
	LONG   biYPelsPerMeter;
	DWORD  biClrUsed;
	DWORD  biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
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
char *dec_to_bin(int n)
{
	char *res=(char*)malloc(9*sizeof(char));
	while(strlen(res)>0)
		for(int i=0; i<strlen(res); i++)
			res[i]=res[i+1];
	int i=0;
	int bits_count=get_bits_count(n);
	if(bits_count==0)
		return "00000000";
	while(bits_count>0)
	{
		res[i]=(char)'0'+((n>>bits_count-1)&1);		
		bits_count--;
		i++;
	}
	if(strlen(res)<8)
	{
		i=0;
		while(strlen(res)<8)
		{
			for(int j=strlen(res); j>0; j--)
				res[j]=res[j-1];
			res[i]='0';
			i++;
		}
	}
	return res;
}
int bin_to_dec(char *s)
{
	int i=0;
	int shift,res=0;	
	while(s[i]=='0')
		i++;
	for(shift=strlen(s)-i-1; i<strlen(s); i++,shift--)
		res=res+((s[i]-'0')<<shift);
	return res;
}
char change_last_bit(char ch,char bit)
{
	ch>>=1;
	if(bit=='0')
		ch<<=1;
	else
	{
		ch<<=1;
		ch++;
	}
	return ch;
}
char get_last_bit(char ch)
{
	if(ch%2==0)
		return '0';
	else
		return '1';
}
void read_header_data(FILE *f, BITMAPFILEHEADER *s1, BITMAPINFOHEADER *s2)
{
	fread(&s1->bfType,sizeof(s1->bfType),1,f);
	fread(&s1->bfSize,sizeof(s1->bfSize),1,f);
	fread(&s1->bfReserved1,sizeof(s1->bfReserved1),1,f);
	fread(&s1->bfReserved2,sizeof(s1->bfReserved2),1,f);
	fread(&s1->bfOffBits,sizeof(s1->bfOffBits),1,f);	
	fread(&s2->biSize,sizeof(s2->biSize),1,f);
	fread(&s2->biWidth,sizeof(s2->biWidth),1,f);
	fread(&s2->biHeight,sizeof(s2->biHeight),1,f);
	fread(&s2->biPlanes,sizeof(s2->biPlanes),1,f);
	fread(&s2->biBitCount,sizeof(s2->biBitCount),1,f);
}
void write_message(char *text)
{
	FILE *f=fopen("source.bmp","rb");
	FILE *fw=fopen("res.bmp","wb+");
	BITMAPFILEHEADER s1;
	BITMAPINFOHEADER s2;
	char ch,*s,*picture=NULL;
	unsigned long long int i,j,count=0;
	read_header_data(f,&s1,&s2);
	printf("File size  %d;\nbits count  %d;\nresolution  %d x %d;\n",
	s1.bfSize,s2.biBitCount,s2.biWidth,s2.biHeight);
	fseek(f,s1.bfOffBits,SEEK_SET);	
	while(fread(&ch,sizeof(ch),1,f))
	{
		count++;
		picture=(char*)realloc(picture,count*sizeof(char));
		picture[count-1]=ch;
	}
	s=NULL;
	j=0;
	for(int i=0; i<strlen(text); i++)
	{
		s=dec_to_bin(text[i]);
		printf("%c = %d = %s\n",text[i],text[i],s);
		for(int k=0; k<strlen(s); k++,j++)
			picture[j]=change_last_bit(picture[j],s[k]);
	}
	fseek(f,0,SEEK_SET);
	fread(&s1,sizeof(s1)-1,1,f);
	fread(&s2,sizeof(s2)-1,1,f);
	fwrite(&s1,sizeof(s1)-1,1,fw);
	fwrite(&s2,sizeof(s2)-1,1,fw);
	for(i=0; i<count; i++)
		fwrite(&picture[i],sizeof(picture[i]),1,fw);
	free(picture);
	fclose(f);
	fclose(fw);	
}
void read_message(int n)
{
	FILE *f=fopen("res.bmp","rb");
	BITMAPFILEHEADER s1;
	BITMAPINFOHEADER s2;
	char ch,message[n],*picture=NULL;
	unsigned long long int i,j,count=0;
	read_header_data(f,&s1,&s2);
	printf("File size  %d;\nbits count  %d;\nresolution  %d x %d;\n",
	s1.bfSize,s2.biBitCount,s2.biWidth,s2.biHeight);
	fseek(f,s1.bfOffBits,SEEK_SET);	
	while(fread(&ch,sizeof(ch),1,f))
	{
		count++;
		picture=(char*)realloc(picture,count*sizeof(char));
		picture[count-1]=ch;
	}
	char num[9];
	j=0;
	for(i=0; i<n; i++)
	{
		for(int k=0; k<8; k++,j++)
			num[k]=get_last_bit(picture[j]);
		message[i]=bin_to_dec(num);
	}
	printf("\n\nmessage:|%s|",message);
	free(picture);
	fclose(f);
}		
int main(void)
{	
	char *message="*MESSAGE_BEGIN*";
	write_message(message);
	printf("-------------------------------------\n");
	read_message(strlen(message));
	/*int n=165;
	char *s=dec_to_bin(n);
	printf("%d = %s\n%s = %d",n,s,s,bin_to_dec(s));*/
	/*char ch=20;
	char ch2=change_last_bit(ch,'1');
	printf("%c = %d = %s\n",ch,ch,dec_to_bin(ch));
	printf("%c = %d = %s\n",ch2,ch2,dec_to_bin(ch2));*/
    return 0;
}