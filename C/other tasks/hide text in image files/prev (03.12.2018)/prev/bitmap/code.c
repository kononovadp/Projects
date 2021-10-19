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
int main(void)
{
	FILE *f=fopen("source.bmp","rb");
	FILE *fw=fopen("res.bmp","wb+");
	BITMAPFILEHEADER s1;
	BITMAPINFOHEADER s2;
	char ch,*picture=NULL;
	unsigned long long int i,count=0;
	fread(&s1.bfType,sizeof(s1.bfType),1,f);
	fread(&s1.bfSize,sizeof(s1.bfSize),1,f);
	fread(&s1.bfReserved1,sizeof(s1.bfReserved1),1,f);
	fread(&s1.bfReserved2,sizeof(s1.bfReserved2),1,f);
	fread(&s1.bfOffBits,sizeof(s1.bfOffBits),1,f);	
	fread(&s2.biSize,sizeof(s2.biSize),1,f);
	fread(&s2.biWidth,sizeof(s2.biWidth),1,f);
	fread(&s2.biHeight,sizeof(s2.biHeight),1,f);
	fread(&s2.biPlanes,sizeof(s2.biPlanes),1,f);
	fread(&s2.biBitCount,sizeof(s2.biBitCount),1,f);
	printf("File size  %d;\nbits count  %d;\nresolution  %d x %d;\n",
	s1.bfSize,s2.biBitCount,s2.biWidth,s2.biHeight);
	fseek(f,s1.bfOffBits,SEEK_SET);	
	while(fread(&ch,sizeof(ch),1,f))
	{
		count++;
		picture=(char*)realloc(picture,count*sizeof(char));
		picture[count-1]=ch;
	}
	printf("Bitmap bytes count  %lld",count);	
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
    return 0;
}