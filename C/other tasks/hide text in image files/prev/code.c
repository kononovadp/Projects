#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TextMarker "message begin"
struct information_about_text
{
	char *array_of_chars;
	unsigned long long int symbols_count;
};
typedef unsigned short WORD;
typedef unsigned long int DWORD;
typedef signed long LONG;
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
int get_bits_count(unsigned int n)
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
char *generate_random_text(int n)
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
}
void tangle_text(char *output, char *input, unsigned long long int CharsCount)
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
void untangle_text(char *output, char *input, unsigned long long int CharsCount)
{
//	char *res=(char*)malloc(strlen(input)*sizeof(char)+1);	
	int i=0;
	int j=0;
	int beg=0;
	int end=0;
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
	/*strcpy(text,res);
	free(res);*/
}
unsigned char get_mask(int bits_count)
{
	unsigned char res=1;
	for(int i=0; i<bits_count-1; i++)
	{
		res<<=1;
		res|=1;
	}
	return res;
}
unsigned char copy_bits(unsigned char count, unsigned char receiver, unsigned char source)
{ 
	receiver&=get_mask(get_bits_count(receiver))<<count;
	source&=get_mask(count);
	return receiver|source;
}
unsigned long long int get_bitmap_size(char *file_name)
{
	FILE *f=fopen(file_name,"rb");
	char filechar;
	unsigned long long int FileSize=0;
	bitmapinfo inf;
	fseek(f,0,SEEK_SET);
	fread(&inf,sizeof(inf)-1,1,f);
	while(fread(&filechar,sizeof(filechar),1,f))
		FileSize++;
	return FileSize;
}
void read_image_info(FILE *f, bitmapinfo *image_inf)
{
	fread(&image_inf->FileType,sizeof(image_inf->FileType),1,f);
	fread(&image_inf->FileSize,sizeof(image_inf->FileSize),1,f);
	fread(&image_inf->Reserved1,sizeof(image_inf->Reserved1),1,f);
	fread(&image_inf->Reserved2,sizeof(image_inf->Reserved2),1,f);
	fread(&image_inf->BitmapBeginning,sizeof(image_inf->BitmapBeginning),1,f);	
	fread(&image_inf->SecondStructureSize,sizeof(image_inf->SecondStructureSize),1,f);
	fread(&image_inf->ImageWidth,sizeof(image_inf->ImageWidth),1,f);
	fread(&image_inf->ImageHeight,sizeof(image_inf->ImageHeight),1,f);
	fread(&image_inf->Planes,sizeof(image_inf->Planes),1,f);
	fread(&image_inf->BitCount,sizeof(image_inf->BitCount),1,f);
}
void write_message_to_bmp(char *text, short TextBitsCountPerFileByte, char *file_name)
{
	int j,MaxBitsCount,textchar,PreviousTextBitsCountPerFileByte;
	unsigned char filechar;
	unsigned long long  int BitmapSize,TextCharNumber,FileCharNumber=0;
	FILE *f=fopen(file_name,"rb");
	bitmapinfo inf;
	fseek(f,0,SEEK_SET);
	fread(&inf,sizeof(inf)-1,1,f);
	BitmapSize=get_bitmap_size(file_name);
	char *FileData=(char*)malloc(BitmapSize*sizeof(char));
	while(fread(&filechar,sizeof(filechar),1,f))
	{
		FileData[FileCharNumber]=filechar;
		FileCharNumber++;
	}
	fclose(f);
	FileCharNumber=0;
	PreviousTextBitsCountPerFileByte=TextBitsCountPerFileByte;	
	for(TextCharNumber=0; TextCharNumber<strlen(text); TextCharNumber++)
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
			filechar=copy_bits(TextBitsCountPerFileByte,filechar,textchar);
			FileData[FileCharNumber]=filechar;
			FileCharNumber++;
			MaxBitsCount-=TextBitsCountPerFileByte;
			textchar>>=TextBitsCountPerFileByte;
		}
	}
	f=fopen(file_name,"wb");
	fwrite(&inf,sizeof(inf)-1,1,f);
	for(FileCharNumber=0; FileCharNumber<BitmapSize; FileCharNumber++)
		fwrite(&FileData[FileCharNumber],sizeof(char),1,f);
	free(FileData);
	fclose(f);
}
short get_text_bits_count(unsigned long long int ImageSize,unsigned long long int TextSize)
{
	int BitsPerByte=0;
	short BytesCountForOneSymbol;
	unsigned long long int TextBytesCount=ImageSize;
	while(TextBytesCount>=ImageSize && ++BitsPerByte<8)
	{
		BytesCountForOneSymbol=8/BitsPerByte;
		if(BitsPerByte!=1 && BitsPerByte%2==1)
			BytesCountForOneSymbol++;
		TextBytesCount=BytesCountForOneSymbol*TextSize;
	}
	return BitsPerByte;
}
void show_text(char *text)
{
	unsigned long long int i=0;
	while(text[i])
	{
		putchar(text[i]);
		i++;
	}
}
void write_message(struct information_about_text *text_info,char encryption)
{	
	char ch;
	char *ready_message=NULL;	
	char *temp=NULL;
	char *file_name="source.bmp";
	short TextBitsCount,TextLengthCharsCount=0;
	unsigned long long int TextLength=text_info->symbols_count;
	unsigned long long int i,ImageBytesCount=TextLength;
	char *temp_str=(char*)malloc(strlen(TextMarker)*sizeof(char));
//	strcpy(temp_str,TextMarker);
	tangle_text(temp_str,TextMarker,strlen(TextMarker));
	
	while(TextLength>0)
	{
		TextLengthCharsCount++;
		TextLength/=10;
	}
	TextLength=ImageBytesCount;
	ImageBytesCount=get_bitmap_size(file_name);
	TextBitsCount=get_text_bits_count(ImageBytesCount,TextLength);
	ready_message=(char*)malloc(sizeof(char)*(strlen(TextMarker)+TextLengthCharsCount)+TextLength+1);	
	strcpy(ready_message,temp_str);
	strcat(ready_message,_itoa(TextLengthCharsCount,temp_str,10));
	strcat(ready_message,_itoa(TextLength,temp_str,10));
	strcat(ready_message,_itoa(encryption,temp_str,10));
	strcat(ready_message,text_info->array_of_chars);
	write_message_to_bmp(ready_message,TextBitsCount,file_name);
	printf("Written data:\n%s\n",ready_message);
	free(ready_message);
	free(temp_str);
}
char *read_message_from_bmp(int TextBitsCountPerFileByte, int TextLength, int offset, char *file_name)
{
	FILE *f=fopen(file_name,"rb");
	bitmapinfo inf;
	char *text=(char*)malloc(TextLength*sizeof(char)+1);
	int MaxBitsCount,TextChar,lastbits,shiftscount=0;
	int PreviousTextBitsCountPerFileByte;
	unsigned char filechar;
	fseek(f,sizeof(bitmapinfo)+offset-1,SEEK_SET);
	/*fseek(f,0,SEEK_SET);
	fread(&inf,sizeof(inf)-1,1,f);*/
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
			lastbits=copy_bits(TextBitsCountPerFileByte,lastbits,filechar);
			lastbits<<=shiftscount;
			lastbits=copy_bits(get_bits_count(TextChar)-1,lastbits,TextChar);
			TextChar=lastbits;
			shiftscount+=TextBitsCountPerFileByte;
			MaxBitsCount-=TextBitsCountPerFileByte;
		}
		TextChar&=get_mask(8);
		text[i]=TextChar;
		text[i+1]=0;
	}
	fclose(f);
	return text;
}
char *read_message(void)
{
	char *fn="source.bmp";
	char *message=(char*)calloc(strlen(TextMarker)+1,sizeof(char));
	char *temp_str=(char*)calloc(strlen(TextMarker),sizeof(char));
	char *untangle_result=(char*)calloc(strlen(TextMarker),sizeof(char));
	short i,j,encryption,TextLengthCharsCount,TextBitsCount=1;
	unsigned long long int TextLength,PreviousMessageLength;
	message=read_message_from_bmp(TextBitsCount,strlen(TextMarker)+1,0,fn);	
	strcpy(temp_str,"");
	strncpy(temp_str,message,strlen(message)-1);
	untangle_text(untangle_result,temp_str,strlen(TextMarker));
//	printf("mes: %s\n",temp_str);
	while(strcmp(untangle_result,TextMarker)!=0 && ++TextBitsCount<9)
	{		
		message=read_message_from_bmp(TextBitsCount,strlen(TextMarker)+1,0,fn);
		strncpy(temp_str,message,strlen(message)-1);
//		printf("mes: %s\n",temp_str);
		untangle_text(untangle_result,temp_str,strlen(TextMarker));
	}
	if(TextBitsCount==9)
	{
		printf("The file doesn't contain a message added by this program.");
		return NULL;
	}	
	TextLengthCharsCount=message[strlen(message)-1]-'0';
	/*message=(char*)*/realloc(message,strlen(TextMarker)+2+TextLengthCharsCount);
	message=read_message_from_bmp(TextBitsCount,strlen(TextMarker)+2+TextLengthCharsCount,0,fn);
	strcpy(temp_str,"");
	for(j=0,i=strlen(TextMarker)+1; i<strlen(message)-1; i++,j++)
	{
		temp_str[j]=message[i];
		temp_str[j+1]=0;
	}
	TextLength=atoi(temp_str);	
	encryption=message[strlen(message)-1]-'0';
	PreviousMessageLength=strlen(message);
	/*message=(char*)*/realloc(message,strlen(TextMarker)+2+TextLengthCharsCount+TextLength);
	message=read_message_from_bmp(TextBitsCount,TextLength,
	8/TextBitsCount*PreviousMessageLength,fn);
	if(encryption==1)
	{
		untangle_result=(char*)realloc(untangle_result,sizeof(char)*TextLength);
		untangle_text(untangle_result,message,TextLength);
		free(temp_str);
		free(message);
		return untangle_result;
	}
	free(temp_str);
	return message;
}
char *get_keyboard_data(unsigned long long int *CharsCount)
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
struct information_about_text *get_text_data(char keyboard_or_file, char encryption)
{	
	if(keyboard_or_file==1)
	{
		struct information_about_text *text_info=(struct information_about_text*)malloc(sizeof(struct information_about_text)*1);
		unsigned long long int CharsCount=0;
		printf("Text message: ");
		char *output,*input=get_keyboard_data(&CharsCount);
		text_info->symbols_count=CharsCount;
		if(encryption==1)
		{
			output=(char*)calloc(CharsCount+2,sizeof(char));
			tangle_text(output,input,CharsCount);
			free(input);
			text_info->array_of_chars=output;
			return text_info;
		}
		text_info->array_of_chars=input;
		return text_info;
	}
	else
	{
		FILE *f;
		struct information_about_text *text_info=(struct information_about_text*)malloc(sizeof(struct information_about_text)*1);
		unsigned long long int CharsCount=0;
		printf("Text file name: ");
		char *file_name=get_keyboard_data(&CharsCount);
		if((f=fopen(file_name,"rb"))==NULL)
		{
			file_name=(char*)realloc(file_name,sizeof(char)*
			(strlen(file_name)+4));
			strcat(file_name,".txt");
			if((f=fopen(file_name,"rb"))==NULL)
			{
				printf("The file %s does not exist\n",file_name);
				return NULL;
			}
		}
		char *output=NULL;
		char ch,*input=(char*)calloc(2,sizeof(char));
		CharsCount=0;
		while(fread(&ch,sizeof(char),1,f))
		{
			input[CharsCount]=ch;
			input[CharsCount+1]=0;
			CharsCount++;
			input=realloc(input,CharsCount+2);
		}
		text_info->symbols_count=CharsCount;
		if(encryption==1)
		{
			output=(char*)calloc(CharsCount+2,sizeof(char));
			tangle_text(output,input,CharsCount);
			free(input);
			fclose(f);
			text_info->array_of_chars=output;
			return text_info;
		}
		fclose(f);
		text_info->array_of_chars=input;
		return text_info;
	}
}
int main(void)
{
	char keyboard_or_file=2;
	char *message,encryption=1;	
	struct information_about_text *text_info=get_text_data(keyboard_or_file,encryption);
	if(text_info==NULL)
		return 0;
	write_message(text_info,encryption);
	printf("\n======================================================\n");
	free(text_info);
	message=read_message();
	printf("Text in file:\n");
	show_text(message);
	/*char *s="bNeIg MeEgSaS";//"bNeIg MeEgSaS";
	for(int bitscount=1; bitscount<9; bitscount++)
	{
		write_message_to_bmp(s,bitscount,"source.bmp");
		s=read_message_from_bmp(bitscount,strlen(s),"source.bmp");
		printf("bitscount = %d; res = %s|\n",bitscount,s);
	}*/
    return 0;
}
