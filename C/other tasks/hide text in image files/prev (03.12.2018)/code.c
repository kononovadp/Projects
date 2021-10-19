#define WIN32_DEFAULT_LIBS
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#define TextMarker "text begin"
#define ChangedFileMarker "_sgte"
typedef unsigned short WORD;
typedef unsigned long int DWORD;
typedef signed long LONG;
struct information_about_text *GetTextData(void);
struct information_about_text
{
	char *text;
	unsigned long long int TextLength;
	char encryption;
};
struct JpgData
{
	WORD marker;
	unsigned long long int length;
	unsigned char *data;
};
struct FFDB
{
	unsigned char DataSize;
	unsigned char TableIdentifier;
	unsigned char **matrix;
};
struct FFC0Component
{
	unsigned char Identifier;
	unsigned char HorizontalDecimation;
	unsigned char VerticalDecimation;
	unsigned char QuantizationTableIdentifier;
};
struct FFC0
{
	unsigned char ChannelWidth;
	WORD ImageHigh;
	WORD ImageWidth;
	unsigned char ComponentsCount;
	struct FFC0Component **components;
};
struct InformationAboutHuffmanCodes
{
	unsigned char CodeLength;
	unsigned char CodeQuantity;
};
struct HuffmanCode
{
	char HuffmanCodeLength;
	char HuffmanCodeInFile;
	int HuffmanCode;
};
struct HuffmanTreeNode
{
	int value;
	struct HuffmanTreeNode *left;
	struct HuffmanTreeNode *right;
};
struct HuffmanTree
{
	struct HuffmanTreeNode *TreeRoot;
	struct HuffmanTreeNode **TreeNodes;
};
struct FFC4
{
	unsigned char class;
	unsigned char TableIdentifier;
	WORD HuffmanCodesCount;
	struct InformationAboutHuffmanCodes **HuffmanCodesInf;
	struct HuffmanCode **HuffmanCodes;
	struct HuffmanTree *tree;
};
struct ScanComponent
{
	char ImageComponentNumber;
	char HuffmanTableIdentifierForDCCoefficient;
	char HuffmanTableIdentifierForACCoefficient;
};
struct FFDA
{
	WORD HeadlineLength;
	unsigned char ScanComponentsCount;
	struct ScanComponent **ScanComponents;
	char *UnknownBytes;
};
typedef struct BitmapInfo
{
	WORD  FileType;
	DWORD FileSize;
	WORD  Reserved1;
	WORD  Reserved2;
	DWORD BitmapBeginning;
	DWORD SecondStructureSize;
	LONG  ImageWidth;
	LONG  ImageHeight;
	WORD  Planes;
	WORD  BitCount;
	DWORD Compression;
	DWORD ImageSize;
	LONG  HorizontalResolution;
	LONG  VerticalResolution;
	DWORD ColorsUsed;
	DWORD ColorsImportant;
}bitmapinfo;
char GetDigitChar(char ch)
{
	if(ch<10)
		return ch+'0';
	else
		return 'A'+(ch-10);
}
char *DecToHex(int n, size_t type_size)
{
	char ch,*res=(char*)malloc(sizeof(char)*(type_size*2));
	int i=0;
	for(unsigned int i=0; i<type_size*2; i++)
	{		
		res[i]='0';
		res[i+1]=0;
	}
	while(n>0)
	{
		ch=GetDigitChar(n%16);
		res[2*type_size-i-1]=ch;
		n=n/16;
		i++;
	}
	res[type_size*2]=0;
	return res;
}
int GetBitsCount(unsigned int n)
{
	if(n==0)
		return 1;
	int bits_count=0;
	while(n>0)
	{
		bits_count++;
		n>>=1;
	}
	return bits_count;
}
char *DecToBin(int n)
{
	char *res=(char*)malloc(sizeof(char));
	int j,i=0;
	int bits_count=GetBitsCount(n);
	strcpy(res,"");
	if(bits_count==0)
		return "0";
	while(bits_count>0)
	{
		res=(char*)realloc(res,(i+1)*sizeof(char));
		res[i]=(char)'0'+((n>>bits_count-1)&1);
		res[i+1]=0;
		bits_count--;
		i++;
	}
	/*if(strlen(res)<8)
	{
		i=0;
		while(strlen(res)<8)
		{
			for(j=strlen(res); j>0; j--)
				res[j]=res[j-1];
			res[i]='0';
			i++;			
		}
	}*/
	return res;
}
int BinToDec(char *s)
{
	unsigned int i=0;
	unsigned int shift,res=0;
	while(s[i]=='0')
		i++;
	for(shift=strlen(s)-i-1; i<strlen(s); i++,shift--)
		res=res+((s[i]-'0')<<shift);
	return res;
}
char *GenerateRandomText(int n)
{
	char *text=(char*)malloc(n*sizeof(char));
	srand(time(NULL));
	int space;
	int spaces_count=rand()%n;
	for(int i=0; i<n; i++)
		if(rand()%2==0)
			text[i]='a'+rand()%('z' - 'a');
		else
			text[i]='A'+rand()%('Z' - 'A');
	while(spaces_count>0)
	{
		space=2+rand()%(strlen(text)-2);
		if(text[space]!=' ')
		{
			text[space]=' ';
			spaces_count--;
		}
		else
			continue;
	}
	return text;
}
void EncryptText(char *output, char *input, unsigned long long int CharsCount)
{
	unsigned long long int j=0;
	unsigned long long int WordCharNumber,PrevWordBegin=0;
	unsigned long long int InputCharNumber=0;
	unsigned long long int WordEnd=0;
	while(WordEnd<CharsCount)
	{
		InputCharNumber=WordEnd;
		PrevWordBegin=InputCharNumber;
		while(WordEnd<CharsCount && input[WordEnd]!=' ')
			WordEnd++;
		for(WordCharNumber=0,j=0; InputCharNumber<WordEnd; InputCharNumber++,WordCharNumber++)
		{
			if(WordCharNumber%2==0)
			{
				output[InputCharNumber]=input[InputCharNumber-j];
				output[InputCharNumber+1]=0;
			}
			else
			{				
				output[InputCharNumber]=input[WordEnd-InputCharNumber+j+PrevWordBegin];
				output[InputCharNumber+1]=0;
				j++;
			}
			output[InputCharNumber+1]=0;			
		}
		if(WordEnd!=CharsCount)
			while(input[WordEnd]!=' ' && input[WordEnd]!='\n')
			{
				output[WordEnd]=input[WordEnd];
				output[WordEnd+1]=0;
				WordEnd++;
			}
		while(input[WordEnd]==' ')
		{
			output[WordEnd]=' ';
			output[WordEnd+1]=0;
			WordEnd++;
		}
	}
}
void DecryptText(char *output, char *input, unsigned long long int CharsCount)
{
	unsigned long long int i=0;
	unsigned long long int j=0;
	unsigned long long int beg=0;
	unsigned long long int end=0;
	while(end<CharsCount)
	{
		end=beg;
		while(input[end]!=' '&& end<CharsCount)
			end++;
		for(i=beg; i<end; i+=2,j++)
		{
			output[j]=input[i];
			output[j+1]=0;
		}
		for(i=i-1-(2*((end-beg)%2)); i>beg; i-=2,j++)
		{
			output[j]=input[i];
			output[j+1]=0;
		}
		while(input[end]==' ')
		{
			output[j]=input[end];
			output[j+1]=0;
			end++;
			j++;
		}
		beg=end;
	}
}
unsigned char GetMask(int bits_count)
{
	unsigned char res=1;
	for(int i=0; i<bits_count-1; i++)
	{
		res<<=1;
		res|=1;
	}
	return res;
}
unsigned char CopyBits(unsigned char count, unsigned char result, unsigned char source)
{ 
	result&=GetMask(GetBitsCount(result))<<count;
	source&=GetMask(count);
	return result|source;
}
unsigned long long int GetBitmapSize(char *FileName)
{
	FILE *f=fopen(FileName,"rb");
	char filechar;
	unsigned long long int FileSize=0;
	bitmapinfo inf;
	fseek(f,0,SEEK_SET);
	fread(&inf,sizeof(inf)-1,1,f);
	while(fread(&filechar,sizeof(filechar),1,f))
		FileSize++;
	fclose(f);
	return FileSize;
}
int InvertInt(int n)
{
	int ten=1;
	int res=0;
	while(ten<n/16)
		ten=ten*16;
	while(ten>0)
	{
		res=res+(ten*(n%16));
		n/=16;
		ten/=16;
	}
	return res;
}
char GetImageFileType(char *filename)
{
	FILE *f=fopen(filename,"rb");
	WORD first_bytes;
	fread(&first_bytes,sizeof(first_bytes),1,f);
	fclose(f);
	if(first_bytes==55551)
		return 'j';
	else
		if(first_bytes==19778)
			return 'b';
		else
			printf("Unknown file format.\n");		
		return '0';
}
void ChangeFileExtension(char *FileName, char *NewExtension)
{
	unsigned int i,j;
	for(i=strlen(FileName)-1, j=0; i>strlen(FileName)-4; i--,j++)
		FileName[i]=NewExtension[strlen(NewExtension)-j-1];	
}
WORD ReplaceHexBits(WORD n)
{
	WORD coefficient_for_digit,coefficient_for_number=1;
	WORD digit,number=0;
	coefficient_for_number=256;
	if(n<256)
		return n;
	while(coefficient_for_number>0)
	{
		coefficient_for_digit=1;
		digit=0;
		for(int i=0; i<2; i++,coefficient_for_digit*=16)
		{
			digit=digit+(coefficient_for_digit*(n%16));
			n/=16;
		}
		number=number+(digit*coefficient_for_number);		
		coefficient_for_number/=256;
	}
	return number;
}
struct information_about_text *GetTextFromJpgComment(char *FileName)
{
	struct information_about_text *text_info=(struct information_about_text*)malloc(sizeof(struct information_about_text)*1);
	char *text=(char*)malloc(sizeof(char));
	FILE *f=fopen(FileName,"rb");
	unsigned int textchar;
	unsigned long long int i;
	unsigned long long int previous_part_length=0;
	WORD marker,block_length;	
	fread(&marker,sizeof(marker),1,f);
	fread(&marker,sizeof(marker),1,f);
	while(marker!=65279 && marker!=56063)
	{
		fread(&block_length,sizeof(block_length),1,f);
		block_length=ReplaceHexBits(block_length);
		for(WORD i=0; i<block_length-2; i++)
			textchar=getc(f);
		fread(&marker,sizeof(marker),1,f);
	}
	if(marker!=65279)
	{
		printf("\nThe comment field of this file doesn't contain a text.\n");
		return NULL;
	}
	i=0;
	fread(&block_length,sizeof(block_length),1,f);
	fread(&text_info->encryption,sizeof(char),1,f);
	block_length=ReplaceHexBits(block_length);
	block_length-=1;
	while(marker==65279 /*&& textchar!=EOF*/)
	{		
		text=(char*)realloc(text,sizeof(char)*(block_length+previous_part_length+1));
		while(i<block_length+previous_part_length-2/* && textchar!=EOF*/)
		{
			textchar=getc(f);
			text[i]=textchar;
			text[i+1]=0;
			i++;
		}
		previous_part_length=previous_part_length+block_length-2;
		fread(&marker,sizeof(marker),1,f);
		fread(&block_length,sizeof(block_length),1,f);
		block_length=ReplaceHexBits(block_length);
	}
	text_info->text=text;
	text_info->TextLength=i;
	fclose(f);
	return text_info;
}
char *ReadTextFromBmp(int TextBitsCountPerFileByte,int TextLength,int offset,char *FileName)
{
	FILE *f=fopen(FileName,"rb");
	char *text=(char*)malloc(TextLength*sizeof(char)+1);
	int MaxBitsCount,TextChar,lastbits,shiftscount=0;
	int PreviousTextBitsCountPerFileByte;
	unsigned char filechar;
	fseek(f,sizeof(bitmapinfo)+offset-1,SEEK_SET);
	PreviousTextBitsCountPerFileByte=TextBitsCountPerFileByte;
	for(int i=0; i<TextLength; i++)
	{
		TextBitsCountPerFileByte=PreviousTextBitsCountPerFileByte;
		MaxBitsCount=8;
		TextChar=0;
		shiftscount=0;
		while(MaxBitsCount>0)
		{
			TextBitsCountPerFileByte=MaxBitsCount-(MaxBitsCount-TextBitsCountPerFileByte);
			if(MaxBitsCount<TextBitsCountPerFileByte)
				TextBitsCountPerFileByte=MaxBitsCount;
			fread(&filechar,sizeof(filechar),1,f);
			lastbits=1<<TextBitsCountPerFileByte;
			lastbits=CopyBits(TextBitsCountPerFileByte,lastbits,filechar);
			lastbits<<=shiftscount;
			lastbits=CopyBits(GetBitsCount(TextChar)-1,lastbits,TextChar);
			TextChar=lastbits;
			shiftscount+=TextBitsCountPerFileByte;
			MaxBitsCount-=TextBitsCountPerFileByte;
		}
		TextChar&=GetMask(8);
		text[i]=TextChar;
		text[i+1]=0;
	}
	fclose(f);
	return text;
}
struct information_about_text *GetTextFromBmp(char *fn)
{
	struct information_about_text *text_info=(struct information_about_text*)malloc(sizeof(struct information_about_text)*1);
	char *text=(char*)calloc(strlen(TextMarker)+1,sizeof(char));
	char *temp_str=(char*)calloc(strlen(TextMarker),sizeof(char));
	char *untangle_result=(char*)calloc(strlen(TextMarker),sizeof(char));
	short encryption,TextLengthCharsCount,TextBitsCount=1;
	unsigned int i,j;
	unsigned long long int TextLength,PrevioustextLength;
	text=ReadTextFromBmp(TextBitsCount,strlen(TextMarker)+1,0,fn);
	strcpy(temp_str,"");
	strncpy(temp_str,text,strlen(text)-1);
	DecryptText(untangle_result,temp_str,strlen(TextMarker));
//	printf("mes: %s\n",temp_str);
	while(strcmp(untangle_result,TextMarker)!=0 && ++TextBitsCount<9)
	{		
		text=ReadTextFromBmp(TextBitsCount,strlen(TextMarker)+1,0,fn);
		strncpy(temp_str,text,strlen(text)-1);
//		printf("mes: %s\n",temp_str);
		DecryptText(untangle_result,temp_str,strlen(TextMarker));
	}
	if(TextBitsCount==9)
	{
		printf("\nThis file doesn't contain a text added by this program.\n");
		return NULL;
	}	
	TextLengthCharsCount=text[strlen(text)-1]-'0';
	/*text=(char*)*/realloc(text,strlen(TextMarker)+2+TextLengthCharsCount);
	text=ReadTextFromBmp(TextBitsCount,strlen(TextMarker)+2+TextLengthCharsCount,0,fn);
	strcpy(temp_str,"");
	for(j=0,i=strlen(TextMarker)+1; i<strlen(text)-1; i++,j++)
	{
		temp_str[j]=text[i];
		temp_str[j+1]=0;
	}
	TextLength=atoi(temp_str);	
	encryption=text[strlen(text)-1]-'0';
	PrevioustextLength=strlen(text);
	/*text=(char*)*/realloc(text,strlen(TextMarker)+2+TextLengthCharsCount+TextLength);
	text=ReadTextFromBmp(TextBitsCount,TextLength,
	8/TextBitsCount*PrevioustextLength,fn);
	if(encryption=='1')
	{
		untangle_result=(char*)realloc(untangle_result,sizeof(char)*TextLength);
		DecryptText(untangle_result,text,TextLength);
		free(temp_str);
		free(text);
		text=untangle_result;//return untangle_result;
	}
	free(temp_str);
	text_info->TextLength=TextLength;
	text_info->text=text;
	text_info->encryption=encryption;
	return text_info;
}
void ChangeBmpData(char *FileData,char *text,unsigned long long int TextLength,short TextBitsCountPerFileByte,int offset)
{
	int MaxBitsCount,textchar,PreviousTextBitsCountPerFileByte;
	unsigned long long  int TextCharNumber,FileCharNumber=0;
	unsigned char filechar;
	FileCharNumber=offset;
	PreviousTextBitsCountPerFileByte=TextBitsCountPerFileByte;	
	for(TextCharNumber=0; TextCharNumber<TextLength; TextCharNumber++)
	{
		TextBitsCountPerFileByte=PreviousTextBitsCountPerFileByte;
		textchar=text[TextCharNumber]|1<<8;
		MaxBitsCount=8;
		while(MaxBitsCount>0)
		{	
			TextBitsCountPerFileByte=MaxBitsCount-(MaxBitsCount-TextBitsCountPerFileByte);
			if(MaxBitsCount<TextBitsCountPerFileByte)
				TextBitsCountPerFileByte=MaxBitsCount;
			filechar=FileData[FileCharNumber];
			filechar=CopyBits(TextBitsCountPerFileByte,filechar,textchar);
			FileData[FileCharNumber]=filechar;
			FileCharNumber++;
			MaxBitsCount-=TextBitsCountPerFileByte;
			textchar>>=TextBitsCountPerFileByte;
		}
	}
}
short GetTextBitsCount(unsigned long long int ImageSize,unsigned long long int TextLength)
{
	int BitsPerByte=0;
	short BytesCountForOneSymbol;
	unsigned long long int TextBytesCount=ImageSize;
	while(TextBytesCount>=ImageSize && ++BitsPerByte<8)
	{
		BytesCountForOneSymbol=8/BitsPerByte;
		if(BitsPerByte!=1 && BitsPerByte%2==1)
			BytesCountForOneSymbol++;
		TextBytesCount=BytesCountForOneSymbol*TextLength;
	}
	BytesCountForOneSymbol=8/BitsPerByte;
	if(BytesCountForOneSymbol==1 && BytesCountForOneSymbol%2==1)
		BytesCountForOneSymbol++;
	TextBytesCount=BytesCountForOneSymbol*TextLength;
	if(TextBytesCount-1>=ImageSize)
		return 0;
	return BitsPerByte;
}
bool WriteTextToBmp(struct information_about_text *text_info,char *result,char *source)
{
	char *ready_text=NULL;
	short TextBitsCount,TextLengthCharsCount=0;
	unsigned long long int TextLength=text_info->TextLength;
	unsigned long long int ImageBytesCount=TextLength;
	char *temp_str=(char*)malloc(strlen(TextMarker)*sizeof(char));
	unsigned char filechar;
	unsigned long long  int BitmapSize=GetBitmapSize(source);
	unsigned long long  int FileCharNumber=0;
	FILE *f=fopen(source,"rb");
	FILE *fw=NULL;
	char *FileData=(char*)malloc(BitmapSize*sizeof(char));
	bitmapinfo inf;
	EncryptText(temp_str,TextMarker,strlen(TextMarker));	
	while(TextLength>0)
	{
		TextLengthCharsCount++;
		TextLength/=10;
	}
	TextLength=ImageBytesCount;
	ImageBytesCount=GetBitmapSize(source);	
	ready_text=(char*)malloc(sizeof(char)*(strlen(TextMarker)+TextLengthCharsCount)+2+1);
	strcpy(ready_text,temp_str);
	strcat(ready_text,_itoa(TextLengthCharsCount,temp_str,10));
	strcat(ready_text,_itoa(TextLength,temp_str,10));
	strcpy(temp_str,"");
	_itoa(text_info->encryption-'0',temp_str,10);
	strcat(ready_text,temp_str);
	fread(&inf,sizeof(inf)-1,1,f);
	while(fread(&filechar,sizeof(filechar),1,f))
	{
		FileData[FileCharNumber]=filechar;
		FileCharNumber++;
	}
	fclose(f);
	if((TextBitsCount=GetTextBitsCount(ImageBytesCount,TextLength+strlen(ready_text)))==0)
	{
		printf("\nThis text is too big for this bitmap and can damage the image!\n");
		free(ready_text);
		free(temp_str);
		free(FileData);
		return false;
	}
	ChangeBmpData(FileData,ready_text,strlen(ready_text),
	TextBitsCount,0);
	ChangeBmpData(FileData,text_info->text,text_info->TextLength,TextBitsCount,(8/TextBitsCount)*strlen(ready_text));
	free(ready_text);
	free(temp_str);
	fw=fopen(result,"wb");
	fwrite(&inf,sizeof(inf)-1,1,fw);
	for(FileCharNumber=0; FileCharNumber<BitmapSize; FileCharNumber++)
		fwrite(&FileData[FileCharNumber],sizeof(char),1,fw);
	fclose(fw);	
	free(FileData);
	return true;
}
void WriteTextToJpgComment(struct information_about_text *text_info,char *resultFileName,char *SourceFileName)
{
	FILE *f=fopen(SourceFileName,"rb");
	FILE *fw=fopen(resultFileName,"wb");
	unsigned long long int i=0;
	unsigned long long int previous_part_length=0;
	unsigned int textchar;
	unsigned char filechar;
	char *text=text_info->text;
	unsigned long long int TextCharsCount=text_info->TextLength;
	/*WORD */unsigned long long int MaximumTextLength=65533;
	WORD marker,block_length,CurrentTextCharsCount,comment_marker=65279;
	 
	fread(&marker,sizeof(marker),1,f);
	fwrite(&marker,sizeof(marker),1,fw);
	fread(&marker,sizeof(marker),1,f);	
	while(marker!=65279 && marker!=56063)
	{
		fwrite(&marker,sizeof(marker),1,fw);
		fread(&block_length,sizeof(block_length),1,f);
		fwrite(&block_length,sizeof(block_length),1,fw);
		block_length=ReplaceHexBits(block_length);
		for(WORD i=0; i<block_length-2; i++)
		{
			textchar=getc(f);
			fwrite(&textchar,sizeof(char),1,fw);
		}
		fread(&marker,sizeof(marker),1,f);
	}
	if(marker==65279)
	{
		while (marker==65279)
		{
			fread(&block_length,sizeof(block_length),1,f);
			block_length=ReplaceHexBits(block_length);
			fseek(f,block_length-2,SEEK_CUR);
			fread(&marker,sizeof(marker),1,f);
		}
	}
	i=0;
	MaximumTextLength--;
	fwrite(&comment_marker,sizeof(comment_marker),1,fw);
	if(TextCharsCount<MaximumTextLength)
		CurrentTextCharsCount=(WORD)TextCharsCount;
	else
	{
		if(i<TextCharsCount-MaximumTextLength)
			CurrentTextCharsCount=MaximumTextLength;
		else
			CurrentTextCharsCount=TextCharsCount-i;
	}
	if(CurrentTextCharsCount<=253)
	{
		filechar=0;
		fwrite(&filechar,sizeof(filechar),1,fw);
		filechar=(char)CurrentTextCharsCount+3;
		fwrite(&filechar,sizeof(filechar),1,fw);
	}
	else
	{
		block_length=ReplaceHexBits(CurrentTextCharsCount+3);
		fwrite(&block_length,sizeof(block_length),1,fw);
	}
	fwrite(&text_info->encryption,sizeof(char),1,fw);
	MaximumTextLength++;
	while(i<TextCharsCount)
	{		
		while(i<CurrentTextCharsCount+previous_part_length)
		{
			filechar=text[i];
			fwrite(&filechar,sizeof(char),1,fw);
			i++;
		}
		if(i==TextCharsCount)
			break;
		previous_part_length=previous_part_length+CurrentTextCharsCount;
		fwrite(&comment_marker,sizeof(comment_marker),1,fw);
		if(i<TextCharsCount-MaximumTextLength)
			CurrentTextCharsCount=MaximumTextLength;
		else
			CurrentTextCharsCount=TextCharsCount-i;
		if(CurrentTextCharsCount<=253)
		{
			filechar=0;
			fwrite(&filechar,sizeof(filechar),1,fw);
			filechar=(char)CurrentTextCharsCount+2;
			fwrite(&filechar,sizeof(filechar),1,fw);
		}
		else
		{
			block_length=ReplaceHexBits(CurrentTextCharsCount+2);
			fwrite(&block_length,sizeof(block_length),1,fw);
		}
	}
	if(marker!=65279)
		fwrite(&marker,sizeof(marker),1,fw);
	fread(&block_length,sizeof(block_length),1,f);
	fwrite(&block_length,sizeof(block_length),1,fw);
	textchar=getc(f);
	while(textchar!=EOF)
	{
		fprintf(fw,"%c",textchar);
		textchar=getc(f);
	}
	fclose(f);
	fclose(fw);
}
/*char *GetImageFileName(void)
{	
	unsigned long long int CharsCount=0;
	char ch,*filename=NULL;
	FILE *f;
	printf("\nImage file name: (extension will be added automatically): ");
	filename=GetKeyboardData(&CharsCount);
	bool BmpExists=false;
	bool JpgExists=false;
	if((f=fopen(filename,"rb"))!=NULL)
	{
		fclose(f);
		return filename;
	}
	if((f=fopen(filename,"rb"))==NULL)
	{
		filename=(char*)realloc(filename,sizeof(char)*
		(strlen(filename)+4));
		strcat(filename,".bmp");
		if((f=fopen(filename,"rb"))!=NULL)
		{
			fclose(f);
			BmpExists=true;
		}
		ChangeFileExtension(filename,"jpg");
		if((f=fopen(filename,"rb"))!=NULL)
		{
			fclose(f);
			JpgExists=true;
		}
		if(BmpExists==false && JpgExists==true)
			return filename;
		if(BmpExists==true && JpgExists==false)
		{
			ChangeFileExtension(filename,"bmp");
			return filename;
		}
		if(BmpExists==false && JpgExists==false)
		{
			printf("This file does not exist\n");
			return NULL;
		}
		printf("Press 1 to choose bmp-file, 2 to choose jpg-file or other key to exit: ");
		ch=_getche();
		switch(ch)
		{
			case '1': ChangeFileExtension(filename,"bmp");
			return filename;
			case '2': ChangeFileExtension(filename,"jpg");
			return filename;
			default: printf("\nThe file was not chosen.\n");
			return NULL;
		}
	}
}*/
char *AddMarkerToFileName(char *source)
{
	unsigned int i,n,k;
	int j=strlen(source)-1;
	char *NewName=(char*)malloc(strlen(source)*sizeof(char));
	strcpy(NewName,source);
	n=strlen(NewName)+strlen(ChangedFileMarker);
	i=strlen(NewName);
	while(i<n)
	{
		NewName[i]='0';
		NewName[i+1]=0;		
		i++;
	}	
	i=strlen(NewName)-1;	
	while(NewName[j]!='.')
	{
		NewName[i]=NewName[j];
		i--;
		j--;
	}
	NewName[i]='.';
	j=strlen(ChangedFileMarker)-1;
	for(k=0,i--; k<strlen(ChangedFileMarker); j--,k++,i--)
		NewName[i]=ChangedFileMarker[j];
	return NewName;
}
char **GetFilesList_Windows(char **FileTypes,int FileTypesCount,int *FilesCount)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	int FileNumber=0;	 
	int FileTypeNumber=0;
	char **files=(char**)malloc(sizeof(char*));
	for(FileTypeNumber=0; FileTypeNumber<FileTypesCount; FileTypeNumber++)
	{
		hf=FindFirstFile(FileTypes[FileTypeNumber],&FindFileData);
		if(hf!=INVALID_HANDLE_VALUE)
			do
			{		
				files=(char**)realloc(files,(FileNumber+1)*sizeof(char*));
				*(files+FileNumber)=(char*)malloc(strlen(FindFileData.cFileName)*sizeof(char));
				strcpy(*(files+FileNumber),FindFileData.cFileName);
				FileNumber++;
			}while(FindNextFile(hf,&FindFileData)!=0);
		FindClose(hf);
	}
	if(FileNumber==0)
	{
		printf("No BMP or JPG files found!\nPut suitable image files into the directory with this program and run it again.");
		return NULL;
	}
	*FilesCount=FileNumber;
	return files;
}
char *ChooseFile(char **FileTypes, int FileTypesCount)
{
	int i,choice,FilesCount=0;
	char *FileName=NULL;
	char **files=GetFilesList_Windows(FileTypes,FileTypesCount,&FilesCount);
	if(files==NULL)
		return NULL;
	if(FileTypesCount==1)
		printf("\nText files list:\n");
	else
		printf("\nImage files list:\n");
	for(i=0; i<FilesCount; i++)
		printf("%d. %s\n",i+1,*(files+i));
	if(FilesCount<10)
	{
		printf("Press a number key to choose the file or 0 to exit: ");
		choice=_getche();
		while(choice)
		{
			if(choice=='0')
			{
				if(FilesCount>1)
					for(i=1; i<FilesCount; i++)
						free(files[i]);
				free(files);
				return NULL;
			}
			if(choice<'0' || choice>FilesCount+'0')
				printf("\nIncorrect choice.\n");
			else
			{
				FileName=(char*)malloc(strlen(files[choice-'0'-1])*sizeof(char));
				strcpy(FileName,files[choice-'0'-1]);
				break;
			}
			printf("Press a number key to choose the file or 0 to exit: ");
			choice=_getche();
		}
	}
	else
	{
		printf("Enter a number of file or 0 to exit and press ENTER: ");
			while(scanf("%d",&choice))
			{
				if(choice==0)
				{
					for(i=1; i<FilesCount; i++)
						free(files[i]);
					free(files);
					return NULL;
				}
				if(choice>FilesCount)
					printf("Incorrect choice.\n");
				else
				{
					FileName=(char*)malloc(strlen(files[choice-1])*sizeof(char));
					strcpy(FileName,files[choice-1]);
					break;
				}
			}
	}
	if(FilesCount>1)
		for(i=1; i<FilesCount; i++)
			free(files[i]);
	free(files);
	return FileName;
}
char *GetImageFileName(void)
{
	char *FileName=NULL;
	char **FileTypes=(char**)malloc(2*sizeof(char*));
	*FileTypes=(char*)malloc(8*sizeof(char));
	strcpy(*FileTypes,".\\*.jpg");
	*(FileTypes+1)=(char*)malloc(8*sizeof(char));
	strcpy(*(FileTypes+1),".\\*.bmp");
	FileName=ChooseFile(FileTypes,2);
	free(*FileTypes);
	free(*(FileTypes+1));
	free(FileTypes);
	if(FileName==NULL)
	{
		printf("\nThe file not chosen or chosen incorrect.\n");
		return NULL;
	}	
	return FileName;
}
char *GetKeyboardData(unsigned long long int *CharsCount)
{	
	char ch,*input=(char*)calloc(2,sizeof(char));	
	while((ch=getchar())!='\n')
	{
		input[*CharsCount]=ch;
		input[*CharsCount+1]=0;
		*CharsCount=*CharsCount+1;
		input=realloc(input,*CharsCount+2);
	}
	return input;
}
struct information_about_text *GetTextData(void)
{
	FILE *f=NULL;
	char ch,*EncryptedText=NULL;
	char *FileName=NULL;
	char **FileTypes=NULL;
	struct information_about_text *text_info=(struct information_about_text*)malloc(sizeof(struct information_about_text)*1);
	char keyboard_or_file;		
	printf("Press 0 to input text from keyboard or 1 from file or other key to exit: ");
	keyboard_or_file=_getche();
	text_info->TextLength=0;
	if(keyboard_or_file=='0')
	{		
		printf("\nText: ");
		text_info->text=GetKeyboardData(&text_info->TextLength);
	}
	else
		if(keyboard_or_file=='1')
		{
			FileTypes=(char**)malloc(sizeof(char*));
			*FileTypes=(char*)malloc(8*sizeof(char));
			strcpy(*FileTypes,".\\*.txt");
			FileName=ChooseFile(FileTypes,1);
			free(*FileTypes);
			free(FileTypes);
			if(FileName==NULL)
			{
				printf("\nThe file not chosen or chosen incorrect.\n");
				return NULL;
			}
			f=fopen(FileName,"rb");
			text_info->text=(char*)malloc(2*sizeof(char));
			while(fread(&ch,sizeof(char),1,f))
			{
				text_info->text[text_info->TextLength]=ch;
				text_info->text[text_info->TextLength+1]=0;
				text_info->TextLength++;
				text_info->text=realloc(text_info->text,text_info->TextLength+2);
			}
			fclose(f);
			free(FileName);
			putchar('\n');
		}
		else
		{
			printf("\nIncorrect choice.\n");
			return NULL;
		}
	if(text_info->TextLength==0)
	{
		printf("No symbols inputted\n");
		return NULL;
	}	
	printf("Press 1 to enable encryption text, 0 to disable it or other key to exit: ");
	text_info->encryption=_getche();
	if(text_info->encryption=='1')
	{
		EncryptedText=(char*)calloc(text_info->TextLength,sizeof(char));
		EncryptText(EncryptedText,text_info->text,text_info->TextLength);
		free(text_info->text);
		text_info->text=EncryptedText;
	}
	else
		if(text_info->encryption!='0')
		{
			printf("\nIncorrect information about encryption.\n");
			return NULL;
		}
	return text_info;
}
void WriteText(void)
{
	char *ResultFileName=NULL;
	char *SourceFileName=NULL;
	char FileType;
	struct information_about_text *text_info=GetTextData();
	if(text_info==NULL)
		return;
	SourceFileName=GetImageFileName();
	if(SourceFileName==NULL)
		return;
	FileType=GetImageFileType(SourceFileName);
	ResultFileName=AddMarkerToFileName(SourceFileName);
	if(FileType=='b')
	{
		if((WriteTextToBmp(text_info,ResultFileName,SourceFileName))==false)
			return;
	}
	else
	{
		if(FileType=='j')
		{
			WriteTextToJpgComment(text_info,ResultFileName,SourceFileName);
		}
		else
		{
			printf("\nIncorrect file type.\n");
			return;
		}
	}
	printf("\nData written successfully to the file %s.\n",ResultFileName);
	free(text_info->text);
	free(text_info);
	free(ResultFileName);
	free(SourceFileName);
	
}
void ReadText(void)
{
	char ch,*FileName=GetImageFileName();
	unsigned long long int i;
	struct information_about_text *TextData=NULL;
	FILE *TextFile=NULL;	
	if(FileName==NULL)
		return;
	ch=GetImageFileType(FileName);
	if(ch=='b')
		TextData=GetTextFromBmp(FileName);
	else
		if(ch=='j')
			TextData=GetTextFromJpgComment(FileName);
		else
		{
			free(FileName);
			return;
		}
	if(TextData==NULL)
		return;
	printf("\nPress 0 to display text or 1 to load it to file (other key - exit): ");
	ch=_getche();
	if(ch=='0')
	{
		putchar('\n');
		for(i=0; i<TextData->TextLength; i++)
			putchar(TextData->text[i]);
		putchar('\n');
	}
		else
		{
			strcat(FileName,".txt");
			//ChangeFileExtension(FileName,"txt");
			TextFile=fopen(FileName,"wb");
			for(i=0; i<TextData->TextLength; i++)
				fprintf(TextFile,"%c",TextData->text[i]);
			printf("\nThe file %s created\n",FileName);
		}
	free(FileName);
	free(TextData->text);
	free(TextData);
}
struct JpgData **ReadJpgData(char *FileName,int *MarkersCount,
unsigned long long int *ImageDataSize)
{
	unsigned long long int ImageByteNumber=0;
	unsigned int textchar,MarkerNumber=0;	
	struct JpgData **jpgdata=(struct JpgData**)malloc(sizeof(struct JpgData*));
	FILE *f=(FILE*)malloc(sizeof(FILE));
	f=fopen(FileName,"rb");
	WORD marker,block_length,i;
	fread(&marker,sizeof(marker),1,f);	
	fread(&marker,sizeof(marker),1,f);
	while(marker!=56063)
	{
		jpgdata[MarkerNumber]=(struct JpgData*)malloc(sizeof(struct JpgData));
		jpgdata[MarkerNumber]->marker=marker;
		fread(&block_length,sizeof(block_length),1,f);
		jpgdata[MarkerNumber]->length=block_length;
		block_length=ReplaceHexBits(block_length);
		jpgdata[MarkerNumber]->data=(unsigned char*)malloc((block_length-2)*sizeof(char));
		for(i=0; i<block_length-2; i++)
		{
			textchar=getc(f);
			jpgdata[MarkerNumber]->data[i]=textchar;
		}
		MarkerNumber++;
		fread(&marker,sizeof(marker),1,f);		
	}
	jpgdata[MarkerNumber]=(struct JpgData*)malloc(sizeof(struct JpgData));
	jpgdata[MarkerNumber]->marker=marker;
	jpgdata[MarkerNumber]->data=(unsigned char*)malloc(sizeof(char));
	textchar=getc(f);
	while(textchar!=EOF)
	{
		jpgdata[MarkerNumber]->data[ImageByteNumber]=textchar;		
		ImageByteNumber++;
		jpgdata[MarkerNumber]->data=(unsigned char*)realloc(jpgdata[MarkerNumber]->data,ImageByteNumber+1);
		textchar=getc(f);		
	}
	jpgdata[MarkerNumber]->length=ImageByteNumber-2;
	jpgdata[MarkerNumber]->data=(unsigned char*)realloc(jpgdata[MarkerNumber]->data,jpgdata[MarkerNumber]->length);
	*MarkersCount=MarkerNumber;
	*ImageDataSize=ImageByteNumber;
	fclose(f);	
	free(f);
	return jpgdata;
}
void WriteJpgData(struct JpgData **jpgdata,char *FileName,
int *MarkersCount,unsigned long long int *ImageDataSize)
{
	WORD block_length,j,marker=55551;
	FILE *fw=fopen(FileName,"wb");
	unsigned long long int i;
	fwrite(&marker,sizeof(marker),1,fw);
	for(int i=0; i<*MarkersCount; i++)
	{
		fwrite(&jpgdata[i]->marker,sizeof(WORD),1,fw);
		fwrite(&jpgdata[i]->length,sizeof(WORD),1,fw);
		block_length=ReplaceHexBits(jpgdata[i]->length);
		for(j=0; j<block_length-2; j++)
			fwrite(&jpgdata[i]->data[j],sizeof(char),1,fw);		
	}	
	fwrite(&jpgdata[*MarkersCount]->marker,sizeof(WORD),1,fw);
	for(i=0; i<*ImageDataSize; i++)
		fwrite(&jpgdata[*MarkersCount]->data[i],sizeof(char),1,fw);
	fclose(fw);
}
char GetFirstHexBit(int n)
{
	return n/16;
}
char GetLastHexBit(int n)
{
	return n%16;
}
unsigned char **GetZigzagMatrix(unsigned char *SourceMatrix)
{
	int rows,columns,i,DataIndex;
	unsigned char **ResultMatrix=(unsigned char**)malloc(8*sizeof(unsigned char*));
	for(i=0; i<8; i++)
		ResultMatrix[i]=(unsigned char*)malloc(8*sizeof(unsigned char));
	rows=0;
	columns=0;
	DataIndex=0;
	i=0;
	ResultMatrix[rows][columns]=SourceMatrix[DataIndex];
	for(i=0; i<7; i++)
	{
		if(columns<7)
			columns++;
		else
			rows++;
		DataIndex++;
		ResultMatrix[rows][columns]=SourceMatrix[DataIndex];
		while(columns>0 && rows<7)
		{
			columns--;
			rows++;
			DataIndex++;
			ResultMatrix[rows][columns]=SourceMatrix[DataIndex];
		}
		if(rows<7)
			rows++;
		else
			columns++;
		DataIndex++;
		ResultMatrix[rows][columns]=SourceMatrix[DataIndex];
		while(rows>0 && columns<7)
		{
			columns++;
			rows--;
			DataIndex++;
			ResultMatrix[rows][columns]=SourceMatrix[DataIndex];
		}
	}
	return ResultMatrix;
}
WORD GetWORDSizeNumber(unsigned char *n)
{	
	return n[0]*256+n[1];
}
char CompareChars(char ch1, char ch2)
{
	if(ch1==ch2)
		return '=';
	else
		if(ch1>ch2)
			return '>';
		else
			if(ch1<ch2)
				return '<';
}
void ShowChar(char ch)
{
	printf("%s ",DecToHex(ch,1));//putchar(ch);
}
/*void GetSumsOfNeighbouringElements(char *source, int SourceElementsCount)
{
	int SumNumber,SourceElementNumber,i,t;
	int LastElementNumber=0;
	int *sums=(int*)malloc(sizeof(int)*(SourceElementsCount-1));
	int *LastElements=(int*)malloc(sizeof(int));
	printf("source: ");
	for(SumNumber=0; SumNumber<SourceElementsCount; SumNumber++)
		printf("%d ",source[SumNumber]);
	for(SumNumber=0,SourceElementNumber=SourceElementsCount-1; SumNumber<SourceElementsCount/2; SumNumber++,SourceElementNumber-=2)
		sums[SumNumber]=source[SourceElementNumber]+source[SourceElementNumber-1];
	if(SourceElementsCount%2==1)
	{
		LastElements[0]=source[0];
		LastElementNumber=1;
	}
	SourceElementsCount/=2;
	SourceElementNumber=0;
	while(SourceElementsCount>1)
	{
		t=SourceElementsCount/2;
		for(i=0; i<t; SumNumber++,SourceElementNumber+=2,i++)
			sums[SumNumber]=sums[SourceElementNumber]+sums[SourceElementNumber+1];
		if(SourceElementsCount%2==1)
		{
			LastElements=(int*)realloc(LastElements,sizeof(int)*(LastElementNumber+1));
			LastElements[LastElementNumber]=sums[SourceElementNumber];
			LastElementNumber++;
			SourceElementNumber++;
		}
		SourceElementsCount/=2;
	}
	for(SumNumber--,LastElementNumber--; LastElementNumber>-1; LastElementNumber--,SumNumber++)
		sums[SumNumber+1]=sums[SumNumber]+LastElements[LastElementNumber];
	printf("\nres: ");
	for(i=0; i<SumNumber+1; i++)
		printf("%d ",sums[i]);
	putchar('\n');
}*/
char ChangeBit(unsigned char source, unsigned char bit, unsigned char BitNumber)
{
	if(bit==1)
		return source|(1<<(BitNumber-1));
	else
	{
		if((source>>BitNumber-1)%2==1)
			return source^(1<<(BitNumber-1));
		else
			return source;
	}
}
/*char *GetHuffmanCodes(int count,char *source)
{
	int multiplier,StepsNumber=count/2;
	int i,j,StepsCount=0;	
	int StepsLength=1;
	int CharNumber;	
	char ChangedBitNumber=1;
	char NumberLength=0;
	char ShiftsCountAndZeroPosition=1;
	char *res=(char*)malloc(sizeof(char)*count);
	printf("Source: ");
	for(i=0; i<count; i++)
		printf("%d ",source[i]);
	for(i=0; i<count; i++)
		res[i]=1;
	StepsCount+=StepsNumber;
	while(StepsNumber>0)
	{		
		CharNumber=count-1;
		for(i=0; i<StepsNumber; i++)
		{
			for(j=0; j<StepsLength; j++,CharNumber--)
				res[CharNumber]=(1<<ShiftsCountAndZeroPosition)|res[CharNumber];
			for(j=0; j<StepsLength; j++,CharNumber--)
				res[CharNumber]=ChangeBit((1<<ShiftsCountAndZeroPosition)|res[CharNumber],0,ShiftsCountAndZeroPosition);
		}	printf("\nStepsLength=%d|StepsNumber=%d|CharNumber=%d\n",StepsLength,StepsNumber,CharNumber);
		ShiftsCountAndZeroPosition++;
		StepsNumber/=2;
		StepsLength*=2;
		StepsCount+=StepsNumber;
	}
	CharNumber=count-1;
	count/=2;
	for(i=0; i<count; i++)
		res[i]=res[i]^(1<<(GetBitsCount(res[i])-1));
	return res;
}*/
int GetNearestPowerOfTwo(int n)
{
	int res=1;
	while(res*2<n)
		res=res*2;
	return res;
}
int *GetAllPowersOfTwo(int source)
{
	int sum=GetNearestPowerOfTwo(source);
	int i,number;	
	int *res=(int*)malloc(2*sizeof(int));
	res[0]=2;
	if(sum*2==source)
		sum*=2;
	res[1]=sum;
	while(sum<source)
	{		
		number=sum;		
		while(sum+number>source)
			number=GetNearestPowerOfTwo(number);
		res=(int*)realloc(res,sizeof(int)*(res[0]+2));
		res[res[0]]=number;
		sum+=number;
		res[0]++;
	}
	return res;
}
int *GetHuffmanCodesFromIntArray(int SourceElementsCount,int *source)
{
	struct HuffmanTreeNode
	{
		int value;
		struct HuffmanTreeNode *left;
		struct HuffmanTreeNode *right;
	};
	struct HuffmanTree
	{
		struct HuffmanTreeNode *root;
	};	
	int i,SumNumber,SourceElementNumber,PreviousSourceElementsCount,SourceSymbolNumber,CurrentStep,PowerNumber,MinIndex,MaxIndex,AsymmetricalStep,AsymmetricalPowerNumber,AsymmetricalMaxIndex,prevmin,prevmax;
	int BitNumber=SourceElementsCount;
	int *powers=NULL;
	int *res=(int*)malloc(SourceElementsCount*sizeof(int));
	int LastElementNumber=0;
	struct HuffmanTree *tree=(struct HuffmanTree*)malloc(sizeof(struct HuffmanTree));
	struct HuffmanTreeNode *node=NULL;	
	struct HuffmanTreeNode **nodes=(struct HuffmanTreeNode**)malloc((SourceElementsCount-1)*sizeof(struct HuffmanTreeNode*));
	struct HuffmanTreeNode **LastElements=(struct HuffmanTreeNode**)malloc(sizeof(struct HuffmanTreeNode*));
	if(SourceElementsCount<=1)
	{
		tree->root=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		tree->root->value=0;
		tree->root->left=NULL;
		tree->root->right=NULL;
		res[0]=0;
		return res;
	}
	for(SumNumber=0,SourceElementNumber=SourceElementsCount-1; SumNumber<SourceElementsCount/2; SumNumber++,SourceElementNumber-=2)
	{
		nodes[SumNumber]=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		nodes[SumNumber]->left=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		nodes[SumNumber]->left->value=source[SourceElementNumber-1];
		nodes[SumNumber]->left->left=NULL;
		nodes[SumNumber]->left->right=NULL;		
		nodes[SumNumber]->right=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		nodes[SumNumber]->right->value=source[SourceElementNumber];
		nodes[SumNumber]->right->left=NULL;
		nodes[SumNumber]->right->right=NULL;
		nodes[SumNumber]->value=source[SourceElementNumber-1]+source[SourceElementNumber];
	}	
	if(SourceElementsCount%2==1)
	{
		LastElements[0]=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		LastElements[0]->value=source[0];
		LastElements[0]->left=NULL;
		LastElements[0]->right=NULL;
		LastElementNumber=1;
	}
	SourceElementsCount/=2;
	SourceElementNumber=0;
	while(SourceElementsCount>1)
	{
		PreviousSourceElementsCount=SourceElementsCount/2;
		for(i=0; i<PreviousSourceElementsCount; SumNumber++,SourceElementNumber+=2,i++)
		{
			nodes[SumNumber]=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));			
			nodes[SumNumber]->left=nodes[SourceElementNumber+1];
			nodes[SumNumber]->right=nodes[SourceElementNumber];
			nodes[SumNumber]->value=nodes[SumNumber]->left->value+nodes[SumNumber]->right->value;
		}
		if(SourceElementsCount%2==1)
		{
			LastElements=(struct HuffmanTreeNode**)realloc(LastElements,sizeof(struct HuffmanTreeNode)*(LastElementNumber+1));
			LastElements[LastElementNumber]=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
			LastElements[LastElementNumber]->value=nodes[SourceElementNumber]->value;
			LastElements[LastElementNumber]->left=nodes[SourceElementNumber]->left;
			LastElements[LastElementNumber]->right=nodes[SourceElementNumber]->right;
			LastElementNumber++;
			SourceElementNumber++;
		}
		SourceElementsCount/=2;
	}
	for(SumNumber--,LastElementNumber--; LastElementNumber>-1; LastElementNumber--,SumNumber++)
	{
		nodes[SumNumber+1]=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		nodes[SumNumber+1]->left=LastElements[LastElementNumber];
		nodes[SumNumber+1]->right=nodes[SumNumber];
		nodes[SumNumber+1]->value=LastElements[LastElementNumber]->value+nodes[SumNumber]->value;
	}	
	/*for(i=powers[0]-1; i>0; i--)
		printf("powers[i] = %d\n",powers[i]);
	printf("powers[i] = %d\n",powers[0]-2);*/
	tree->root=nodes[SumNumber];
	SourceElementsCount=BitNumber;
	powers=GetAllPowersOfTwo(SourceElementsCount);
	AsymmetricalStep=0;
	PowerNumber=powers[0]-1;
	MinIndex=0;
	MaxIndex=0;
	free(nodes);
	free(LastElements);
	for(SourceSymbolNumber=0; SourceSymbolNumber<SourceElementsCount; SourceSymbolNumber++)
	{
		res[SourceSymbolNumber]=0;		
		AsymmetricalMaxIndex=0;
		node=tree->root;		
		if(AsymmetricalStep<powers[0]-2 && SourceSymbolNumber==MaxIndex)
			AsymmetricalStep++;		
		for(CurrentStep=0,AsymmetricalPowerNumber=powers[0]-1; CurrentStep<AsymmetricalStep; CurrentStep++,AsymmetricalPowerNumber--)
		{			
			AsymmetricalMaxIndex+=powers[AsymmetricalPowerNumber];
			if(SourceSymbolNumber<AsymmetricalMaxIndex)
			{
				node=node->left;
				res[SourceSymbolNumber]<<=1;
			}
			else
			{
				node=node->right;
				res[SourceSymbolNumber]=ChangeBit(res[SourceSymbolNumber]<<1,1,1);
			}
		}
		if(SourceSymbolNumber==MaxIndex)
		{
			MinIndex=MaxIndex;
			MaxIndex+=powers[PowerNumber];
			PowerNumber--;
			prevmin=MinIndex;
			prevmax=MaxIndex;
		}
		while(node->left!=NULL && node->right!=NULL)
		{
			if(SourceSymbolNumber<(MinIndex+MaxIndex)/2)
			{
				MaxIndex=(MinIndex+MaxIndex)/2;
				node=node->left;
				res[SourceSymbolNumber]=res[SourceSymbolNumber]<<1;
			}
			else
			{
				MinIndex=(MinIndex+MaxIndex)/2;
				node=node->right;
				res[SourceSymbolNumber]=ChangeBit(res[SourceSymbolNumber]<<1,1,1);
			}
		}
		MaxIndex=prevmax;
		MinIndex=prevmin;
	}
	free(powers);
	free(tree);
	return res;
}
void GetHuffmanCodes(struct FFC4 *source)
{	
	int i,SumNumber,SourceElementsCount,PreviousSourceElementsCount,SourceElementNumber,SourceSymbolNumber,CurrentStep,PowerNumber,MinIndex,MaxIndex,AsymmetricalStep,AsymmetricalPowerNumber,AsymmetricalMaxIndex,prevmin,prevmax;
	int *powers=NULL;
	int LastElementNumber=0;
	struct HuffmanTreeNode *node=NULL;	
	source->tree=(struct HuffmanTree*)malloc(sizeof(struct HuffmanTree*));
	source->tree->TreeNodes=(struct HuffmanTreeNode **)malloc((source->HuffmanCodesCount-1)*sizeof(struct HuffmanTreeNode*));
	struct HuffmanTreeNode **LastElements=(struct HuffmanTreeNode**)malloc(sizeof(struct HuffmanTreeNode*));
	if(source->HuffmanCodesCount<=1)
	{		
		source->tree->TreeRoot=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		source->tree->TreeRoot->value=0;
		source->tree->TreeRoot->right=NULL;
		source->tree->TreeRoot->left=NULL;
		source->HuffmanCodes[0]->HuffmanCode=0;
		source->HuffmanCodesCount=1;
		return;
	}
	for(SumNumber=0,SourceElementNumber=source->HuffmanCodesCount-1; SumNumber<source->HuffmanCodesCount/2; SumNumber++,SourceElementNumber-=2)
	{
		source->tree->TreeNodes[SumNumber]=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		source->tree->TreeNodes[SumNumber]->left=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		source->tree->TreeNodes[SumNumber]->left->value=source->HuffmanCodes[SourceElementNumber-1]->HuffmanCodeInFile;
		source->tree->TreeNodes[SumNumber]->left->left=NULL;
		source->tree->TreeNodes[SumNumber]->left->right=NULL;		
		source->tree->TreeNodes[SumNumber]->right=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		source->tree->TreeNodes[SumNumber]->right->value=source->HuffmanCodes[SourceElementNumber]->HuffmanCodeInFile;
		source->tree->TreeNodes[SumNumber]->right->left=NULL;
		source->tree->TreeNodes[SumNumber]->right->right=NULL;
		source->tree->TreeNodes[SumNumber]->value=source->HuffmanCodes[SourceElementNumber-1]->HuffmanCodeInFile+source->HuffmanCodes[SourceElementNumber]->HuffmanCodeInFile;
	}
	if(source->HuffmanCodesCount%2==1)
	{
		LastElements[0]=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		LastElements[0]->value=source->HuffmanCodes[0]->HuffmanCodeInFile;
		LastElements[0]->left=NULL;
		LastElements[0]->right=NULL;
		LastElementNumber=1;
	}
	SourceElementsCount=source->HuffmanCodesCount/2;	
	SourceElementNumber=0;
	while(SourceElementsCount>1)
	{
		PreviousSourceElementsCount=SourceElementsCount/2;
		for(i=0; i<PreviousSourceElementsCount; SumNumber++,SourceElementNumber+=2,i++)
		{
			source->tree->TreeNodes[SumNumber]=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));			
			source->tree->TreeNodes[SumNumber]->left=source->tree->TreeNodes[SourceElementNumber+1];
			source->tree->TreeNodes[SumNumber]->right=source->tree->TreeNodes[SourceElementNumber];
			source->tree->TreeNodes[SumNumber]->value=source->tree->TreeNodes[SumNumber]->left->value+source->tree->TreeNodes[SumNumber]->right->value;
		}
		if(SourceElementsCount%2==1)
		{
			LastElements=(struct HuffmanTreeNode**)realloc(LastElements,sizeof(struct HuffmanTreeNode)*(LastElementNumber+1));
			LastElements[LastElementNumber]=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
			LastElements[LastElementNumber]->value=source->tree->TreeNodes[SourceElementNumber]->value;
			LastElements[LastElementNumber]->left=source->tree->TreeNodes[SourceElementNumber]->left;
			LastElements[LastElementNumber]->right=source->tree->TreeNodes[SourceElementNumber]->right;
			LastElementNumber++;
			SourceElementNumber++;
		}
		SourceElementsCount/=2;
	}
	for(SumNumber--,LastElementNumber--; LastElementNumber>-1; LastElementNumber--,SumNumber++)
	{
		source->tree->TreeNodes[SumNumber+1]=(struct HuffmanTreeNode*)malloc(sizeof(struct HuffmanTreeNode));
		source->tree->TreeNodes[SumNumber+1]->left=LastElements[LastElementNumber];
		source->tree->TreeNodes[SumNumber+1]->right=source->tree->TreeNodes[SumNumber];
		source->tree->TreeNodes[SumNumber+1]->value=LastElements[LastElementNumber]->value+source->tree->TreeNodes[SumNumber]->value;
	}
	source->tree->TreeRoot=source->tree->TreeNodes[SumNumber];
	//for(i=0; i<source->HuffmanCodesCount-1; i++)
	//	printf("sum: %d\n",source->tree->TreeNodes[i]->value);	
	powers=GetAllPowersOfTwo(source->HuffmanCodesCount);
	AsymmetricalStep=0;
	PowerNumber=powers[0]-1;
	MinIndex=0;
	MaxIndex=0;
	free(LastElements);
	for(SourceSymbolNumber=0; SourceSymbolNumber<source->HuffmanCodesCount; SourceSymbolNumber++)
	{
		source->HuffmanCodes[SourceSymbolNumber]->HuffmanCode=0;		
		AsymmetricalMaxIndex=0;
		node=source->tree->TreeRoot;
		if(AsymmetricalStep<powers[0]-2 && SourceSymbolNumber==MaxIndex)
			AsymmetricalStep++;		
		for(CurrentStep=0,AsymmetricalPowerNumber=powers[0]-1; CurrentStep<AsymmetricalStep; CurrentStep++,AsymmetricalPowerNumber--)
		{			
			AsymmetricalMaxIndex+=powers[AsymmetricalPowerNumber];
			if(SourceSymbolNumber<AsymmetricalMaxIndex)
			{
				node=node->left;
				source->HuffmanCodes[SourceSymbolNumber]->HuffmanCode<<=1;
			}
			else
			{
				node=node->right;
				source->HuffmanCodes[SourceSymbolNumber]->HuffmanCode=ChangeBit(source->HuffmanCodes[SourceSymbolNumber]->HuffmanCode<<1,1,1);
			}
		}
		if(SourceSymbolNumber==MaxIndex)
		{
			MinIndex=MaxIndex;
			MaxIndex+=powers[PowerNumber];
			PowerNumber--;
			prevmin=MinIndex;
			prevmax=MaxIndex;
		}
		while(node->left!=NULL && node->right!=NULL)
		{
			if(SourceSymbolNumber<(MinIndex+MaxIndex)/2)
			{
				MaxIndex=(MinIndex+MaxIndex)/2;
				node=node->left;
				source->HuffmanCodes[SourceSymbolNumber]->HuffmanCode=source->HuffmanCodes[SourceSymbolNumber]->HuffmanCode<<1;
			}
			else
			{
				MinIndex=(MinIndex+MaxIndex)/2;
				node=node->right;
				source->HuffmanCodes[SourceSymbolNumber]->HuffmanCode=ChangeBit(source->HuffmanCodes[SourceSymbolNumber]->HuffmanCode<<1,1,1);
			}
		}
		SumNumber=GetBitsCount(source->HuffmanCodes[SourceSymbolNumber]->HuffmanCode);
		if(SumNumber<source->HuffmanCodes[SourceSymbolNumber]->HuffmanCodeLength)
			for(i=0,SumNumber=source->HuffmanCodes[SourceSymbolNumber]->HuffmanCodeLength-SumNumber; i<SumNumber; i++)
				source->HuffmanCodes[SourceSymbolNumber]->HuffmanCode<<=1;
		MaxIndex=prevmax;
		MinIndex=prevmin;
	}
	free(powers);
	//free(tree);
}
char GetBitUnderNumberN(int SourceNumber, int BitNumber, int BitsCountOfNumber)
{	
	if((SourceNumber&(1<<(BitsCountOfNumber-BitNumber)))>0)
		return 1;
	else
		return 0;
}
int main(void)
{
	//стеганография BMP и добавление текста в поле комментария JPG-файла
	int i,FilesCount=0;
	char **FileNames,**FileTypes=(char**)malloc(2*sizeof(char*));
	*FileTypes=(char*)malloc(8*sizeof(char));
	strcpy(*FileTypes,".\\*.jpg");
	*(FileTypes+1)=(char*)malloc(8*sizeof(char));
	strcpy(*(FileTypes+1),".\\*.bmp");
	FileNames=GetFilesList_Windows(FileTypes,2,&FilesCount);
	if(FileNames==NULL)
	{		
		for(i=0; i<2; i++)
			free(FileTypes[i]);
		free(FileTypes);
		return 0;
	}
	for(i=0; i<2; i++)
		free(FileTypes[i]);	
	free(FileTypes);
	for(i=0; i<2; i++)
		free(FileNames[i]);
	free(FileNames);
	char ch;
	printf("1. Write text; 2. Read text; 3. Exit.\nYour choice: ");
	while((ch=_getche())!='3')
	{
		putchar('\n');
		switch(ch)
		{
			case '1': WriteText(); break;
			case '2': ReadText(); break;
			case '3': break;
			default: printf("Incorrect choice!\n"); break;
		}
		printf("1. Write text; 2. Read text; 3. Exit.\nYour choice: ");
	}
	//Тест функции получения кодов Хаффмана
	/*int i,n=10;
	int *source=NULL;
	int *result=NULL;
	source=(int*)malloc(sizeof(int)*n);
		for(int i=0; i<n; i++)
			source[i]=i+1;
	result=GetHuffmanCodesFromIntArray(n,source);
	printf("Code:\n");
	for(i=0; i<n; i++)
		printf("%d = %s\n",source[i],DecToBin(result[i]));
	free(source);
	free(result);*/
	//Декодирование JPG-файла для последующей стеганографии
	/*WORD HuffmanCodesCount;
	char *SourceFileName="1.jpg";
	char *ResultFileName="res.jpg";
	int JpgDataIndex,DataIndex,HuffmanCodeNumber,i,j,j2,temp,DQTCount,MarkersCount=0;
	unsigned long long int ImageDataSize=0;
	struct JpgData **jpgdata=NULL;
	struct FFDB **DQT=NULL;
	struct FFC0 *DCT=NULL;
	struct FFC4 **DHT=NULL;
	struct FFDA *SOS=NULL;
	jpgdata=ReadJpgData(SourceFileName,&MarkersCount,&ImageDataSize);
	JpgDataIndex=0;
	while(jpgdata[JpgDataIndex]->marker!=56319)
		JpgDataIndex++;
	DataIndex=0;
	DQT=(struct FFDB**)malloc(sizeof(struct FFDB*));
	DQTCount=0;
	while(jpgdata[JpgDataIndex]->marker==56319)
	{
		DQT=(struct FFDB**)realloc(DQT,(DQTCount+1)*sizeof(struct FFDB*));
		DQT[DataIndex]=(struct FFDB*)malloc(sizeof(struct FFDB));
		DQT[DataIndex]->DataSize=GetFirstHexBit(jpgdata[JpgDataIndex]->data[0]);
		DQT[DataIndex]->TableIdentifier=GetLastHexBit(jpgdata[JpgDataIndex]->data[0]);
		DQT[DataIndex]->matrix=GetZigzagMatrix(&jpgdata[JpgDataIndex]->data[1]);
		JpgDataIndex++;
		DataIndex++;
		DQTCount++;
	}
	JpgDataIndex=0;
	while(jpgdata[JpgDataIndex]->marker!=49407)
		JpgDataIndex++;
	DCT=(struct FFC0*)malloc(sizeof(struct FFC0));
	DCT->ChannelWidth=jpgdata[JpgDataIndex]->data[0];
	DCT->ImageHigh=GetWORDSizeNumber(&jpgdata[JpgDataIndex]->data[1]);
	DCT->ImageWidth=GetWORDSizeNumber(&jpgdata[JpgDataIndex]->data[3]);
	DCT->ComponentsCount=jpgdata[JpgDataIndex]->data[5];
	DCT->components=(struct FFC0Component**)malloc(3*sizeof(struct FFC0Component*));
	for(i=0,DataIndex=6; i<3; i++)
	{
		DCT->components[i]=(struct FFC0Component*)malloc(sizeof(struct FFC0Component));
		DCT->components[i]->Identifier=jpgdata[JpgDataIndex]->data[DataIndex];
		DataIndex++;
		DCT->components[i]->HorizontalDecimation=GetFirstHexBit(jpgdata[JpgDataIndex]->data[DataIndex]);
		DCT->components[i]->VerticalDecimation=GetLastHexBit(jpgdata[JpgDataIndex]->data[DataIndex]);
		DataIndex++;
		DCT->components[i]->QuantizationTableIdentifier=jpgdata[JpgDataIndex]->data[DataIndex];
		DataIndex++;
	}
	JpgDataIndex=0;
	DataIndex=0;
	while(jpgdata[JpgDataIndex]->marker!=50431)
		JpgDataIndex++;
	DHT=(struct FFC4**)malloc(sizeof(struct FFC4*));
	while(jpgdata[JpgDataIndex]->marker==50431)
	{
		DHT=(struct FFC4**)realloc(DHT,(DataIndex+1)*sizeof(struct FFC4*));
		DHT[DataIndex]=(struct FFC4*)malloc(sizeof(struct FFC4));
		DHT[DataIndex]->class=GetFirstHexBit(jpgdata[JpgDataIndex]->data[0]);
		DHT[DataIndex]->TableIdentifier=GetLastHexBit(jpgdata[JpgDataIndex]->data[0]);
		HuffmanCodesCount=0;
		DHT[DataIndex]->HuffmanCodesInf=(struct InformationAboutHuffmanCodes**)malloc(sizeof(struct InformationAboutHuffmanCodes*));
		for(i=1; i<17; i++)
			if(jpgdata[JpgDataIndex]->data[i]!=0)
			{
				DHT[DataIndex]->HuffmanCodesInf=(struct InformationAboutHuffmanCodes**)realloc(DHT[DataIndex]->HuffmanCodesInf,(HuffmanCodesCount+1)*sizeof(struct InformationAboutHuffmanCodes*));
				DHT[DataIndex]->HuffmanCodesInf[HuffmanCodesCount]=(struct InformationAboutHuffmanCodes*)malloc(sizeof(struct InformationAboutHuffmanCodes));
				DHT[DataIndex]->HuffmanCodesInf[HuffmanCodesCount]->CodeLength=i;
				DHT[DataIndex]->HuffmanCodesInf[HuffmanCodesCount]->CodeQuantity=jpgdata[JpgDataIndex]->data[i];
				HuffmanCodesCount++;				
			}
		DHT[DataIndex]->HuffmanCodesCount=HuffmanCodesCount;
		temp=ReplaceHexBits(jpgdata[JpgDataIndex]->length)-2;
		HuffmanCodesCount=temp-i;
		DHT[DataIndex]->HuffmanCodes=(struct HuffmanCode**)malloc((HuffmanCodesCount)*sizeof(struct HuffmanCode*));
		HuffmanCodeNumber=0;
		for(j=0; j<DHT[DataIndex]->HuffmanCodesCount; j++)
			for(j2=0; j2<DHT[DataIndex]->HuffmanCodesInf[j]->CodeQuantity; j2++,i++,HuffmanCodeNumber++)
			{
				DHT[DataIndex]->HuffmanCodes[HuffmanCodeNumber]=(struct HuffmanCode*)malloc(sizeof(struct HuffmanCode)*DHT[DataIndex]->HuffmanCodesInf[j]->CodeQuantity);
				DHT[DataIndex]->HuffmanCodes[HuffmanCodeNumber]->HuffmanCodeLength=DHT[DataIndex]->HuffmanCodesInf[j]->CodeLength;
				DHT[DataIndex]->HuffmanCodes[HuffmanCodeNumber]->HuffmanCodeInFile=jpgdata[JpgDataIndex]->data[i];
			}
			DHT[DataIndex]->HuffmanCodesCount=HuffmanCodesCount;
			GetHuffmanCodes(DHT[DataIndex]);
			//for(i=0; i<DHT[DataIndex]->HuffmanCodesCount; i++)
			//	printf("Source: %s; HuffmanCode: %s\n",DecToHex(DHT[DataIndex]->HuffmanCodes[i]->HuffmanCodeInFile,1),DecToBin(DHT[DataIndex]->HuffmanCodes[i]->HuffmanCode));
		printf("==================================\n");
		JpgDataIndex++;
		DataIndex++;
	}
	JpgDataIndex=0;
	DataIndex=0;
	while(jpgdata[JpgDataIndex]->marker!=56063)
		JpgDataIndex++;	
	SOS=(struct FFDA*)malloc(sizeof(struct FFDA));	
	SOS->HeadlineLength=GetWORDSizeNumber(&jpgdata[JpgDataIndex]->data[0]);
	SOS->ScanComponentsCount=jpgdata[JpgDataIndex]->data[2];
	SOS->ScanComponents=(struct ScanComponent**)malloc(sizeof(struct ScanComponent*)*SOS->ScanComponentsCount);
	printf("HeadlineLength = %d; ScanComponentsCount = %d\n",SOS->HeadlineLength,SOS->ScanComponentsCount);
	for(i=0,DataIndex=3; i<SOS->ScanComponentsCount; i++,DataIndex+=2)
	{
		SOS->ScanComponents[i]=(struct ScanComponent*)malloc(sizeof(struct ScanComponent));
		SOS->ScanComponents[i]->ImageComponentNumber=jpgdata[JpgDataIndex]->data[DataIndex];
		SOS->ScanComponents[i]->HuffmanTableIdentifierForDCCoefficient=GetFirstHexBit(jpgdata[JpgDataIndex]->data[DataIndex+1]);
		SOS->ScanComponents[i]->HuffmanTableIdentifierForACCoefficient=GetLastHexBit(jpgdata[JpgDataIndex]->data[DataIndex+1]);
		printf("ImageComponentNumber=%d; HTIFDC = %d; HTIFAC = %d\n",SOS->ScanComponents[i]->ImageComponentNumber,SOS->ScanComponents[i]->HuffmanTableIdentifierForDCCoefficient,SOS->ScanComponents[i]->HuffmanTableIdentifierForACCoefficient);
	}
	SOS->UnknownBytes=(char*)malloc(sizeof(char)*3);
	for(i=0; i<3; i++,DataIndex++)
		SOS->UnknownBytes[i]=jpgdata[JpgDataIndex]->data[DataIndex];
	while(DataIndex<jpgdata[JpgDataIndex]->length)
	{
		printf("%s\n",DecToHex(jpgdata[JpgDataIndex]->data[DataIndex],1));
		DataIndex++;
	}*/
	//WriteJpgData(jpgdata,ResultFileName,&MarkersCount,&ImageDataSize);
	/*for(i=0; i<MarkersCount+1; i++)
	{
		free(jpgdata[i]->data);
		free(jpgdata[i]);
	}*/
	//=====================================================================	
    return 0;
}
