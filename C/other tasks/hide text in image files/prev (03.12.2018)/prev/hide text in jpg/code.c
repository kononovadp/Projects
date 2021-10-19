#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TextMarker "text begin"
struct information_about_text
{
	char *array_of_chars;
	unsigned long long int symbols_count;
	char encryption;
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
int invert_int(int n)
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
char get_digit_char(char ch)
{
	if(ch<10)
		return ch+'0';
	else
		return 'A'+(ch-10);
}
char *dec_to_hex(int n, size_t type_size)
{
	char ch,*res=(char*)malloc(sizeof(char)*(type_size*2));
	int i=0;
	for(int i=0; i<type_size*2; i++)
	{		
		res[i]='0';
		res[i+1]=0;
	}
	while(n>0)
	{
		ch=get_digit_char(n%16);
		res[2*type_size-i-1]=ch;
		n=n/16;
		i++;
	}
	res[type_size*2]=0;
	return res;
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
struct information_about_text *get_text_data(void)
{	
	char keyboard_or_file;
	printf("Press 0 to input text from keyboard or 1 from file or other key to exit: ");
	keyboard_or_file=_getche();
	if(keyboard_or_file=='0')
	{
		struct information_about_text *text_info=(struct information_about_text*)malloc(sizeof(struct information_about_text)*1);
		text_info->symbols_count=0;
		printf("\nText: ");
		char *output,*input=get_keyboard_data(&text_info->symbols_count);
		printf("Press 1 to enable encryption text, 0 to disable it or other key to exit: ");
		text_info->encryption=_getche();
		if(text_info->encryption=='1')
		{
			output=(char*)calloc(text_info->symbols_count+2,sizeof(char));
			tangle_text(output,input,text_info->symbols_count);
			free(input);
			text_info->array_of_chars=output;
			return text_info;
		}
		text_info->array_of_chars=input;
		return text_info;
	}
	else if(keyboard_or_file=='1')
	{
		FILE *f;
		struct information_about_text *text_info=(struct information_about_text*)malloc(sizeof(struct information_about_text)*1);
		text_info->symbols_count=0;
		printf("\nText file name (.txt will be added automatically): ");
		char *file_name=get_keyboard_data(&text_info->symbols_count);
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
		text_info->symbols_count=0;
		while(fread(&ch,sizeof(char),1,f))
		{
			input[text_info->symbols_count]=ch;
			input[text_info->symbols_count+1]=0;
			text_info->symbols_count++;
			input=realloc(input,text_info->symbols_count+2);
		}
		printf("Press 1 to enable encryption text, 0 to disable it or other key to exit: ");
		text_info->encryption=_getche();
		if(text_info->encryption=='1')
		{
			output=(char*)calloc(text_info->symbols_count+2,sizeof(char));
			tangle_text(output,input,text_info->symbols_count);
			free(input);
			fclose(f);
			text_info->array_of_chars=output;
			return text_info;
		}
		fclose(f);
		text_info->array_of_chars=input;
		return text_info;
	}
	else
		return NULL;
}
char get_file_type(char *filename)
{
	FILE *f=fopen(filename,"rb");
	WORD first_bytes;
	fread(&first_bytes,sizeof(first_bytes),1,f);
	if(first_bytes==55551)
		return 'j';
	else
		if(first_bytes==19778)
			return 'b';
		else
			printf("Unknown file format.\n");
		return '0';
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
char *read_text(void)
{
	char *fn="source.bmp";
	char *text=(char*)calloc(strlen(TextMarker)+1,sizeof(char));
	char *temp_str=(char*)calloc(strlen(TextMarker),sizeof(char));
	char *untangle_result=(char*)calloc(strlen(TextMarker),sizeof(char));
	short i,j,encryption,TextLengthCharsCount,TextBitsCount=1;
	unsigned long long int TextLength,PreviousMessageLength;
	text=read_message_from_bmp(TextBitsCount,strlen(TextMarker)+1,0,fn);	
	strcpy(temp_str,"");
	strncpy(temp_str,text,strlen(text)-1);
	untangle_text(untangle_result,temp_str,strlen(TextMarker));
	while(strcmp(untangle_result,TextMarker)!=0 && ++TextBitsCount<9)
	{		
		text=read_message_from_bmp(TextBitsCount,strlen(TextMarker)+1,0,fn);
		strncpy(temp_str,text,strlen(text)-1);
		untangle_text(untangle_result,temp_str,strlen(TextMarker));
	}
	if(TextBitsCount==9)
	{
		printf("The file doesn't contain a text added by this program.");
		return NULL;
	}	
	TextLengthCharsCount=text[strlen(text)-1]-'0';
	/*text=(char*)*/realloc(text,strlen(TextMarker)+2+TextLengthCharsCount);
	text=read_message_from_bmp(TextBitsCount,strlen(TextMarker)+2+TextLengthCharsCount,0,fn);
	strcpy(temp_str,"");
	for(j=0,i=strlen(TextMarker)+1; i<strlen(text)-1; i++,j++)
	{
		temp_str[j]=text[i];
		temp_str[j+1]=0;
	}
	TextLength=atoi(temp_str);	
	encryption=text[strlen(text)-1]-'0';
	PreviousMessageLength=strlen(text);
	/*text=(char*)*/realloc(text,strlen(TextMarker)+2+TextLengthCharsCount+TextLength);
	text=read_message_from_bmp(TextBitsCount,TextLength,
	8/TextBitsCount*PreviousMessageLength,fn);
	if(encryption==1)
	{
		untangle_result=(char*)realloc(untangle_result,sizeof(char)*TextLength);
		untangle_text(untangle_result,text,TextLength);
		free(temp_str);
		free(text);
		return untangle_result;
	}
	free(temp_str);
	return text;
}
void ChangeFileExtension(char *FileName, char *NewExtension)
{
	int i,j;
	for(i=strlen(FileName)-1, j=0; i>strlen(FileName)-4; i--,j++)
		FileName[i]=NewExtension[strlen(NewExtension)-j-1];	
}
WORD replace_hex_bits(WORD n)
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
void write_message_to_bmp(struct information_about_text *text_info,
short TextBitsCountPerFileByte, char *file_name)
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
	for(TextCharNumber=0; TextCharNumber<text_info->symbols_count; TextCharNumber++)
	{
		TextBitsCountPerFileByte=PreviousTextBitsCountPerFileByte;
		textchar=text_info->array_of_chars[TextCharNumber]|1<<8;
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
char *GetImageFileName(void)
{	
	unsigned long long int CharsCount=0;
	char ch,*filename=NULL;
	FILE *f;
	printf("File name: (extension will be added automatically): ");
	filename=get_keyboard_data(&CharsCount);
	if((f=fopen(filename,"rb"))!=NULL)
		return filename;
	if((f=fopen(filename,"rb"))==NULL)
	{
		filename=(char*)realloc(filename,sizeof(char)*
		(strlen(filename)+4));
		strcat(filename,".bmp");
		if((f=fopen(filename,"rb"))!=NULL)
		{	
			int i,j;
			ChangeFileExtension(filename,"jpg");
			if((f=fopen(filename,"rb"))==NULL)
			{
				printf("This file does not exist\n");
				return NULL;
			}
		}
	}
	return filename;
}
void write_text(void)
{	
	char ch;
	char *ready_message=NULL;	
	char *temp=NULL;	
	char *filename=GetImageFileName();
	short TextBitsCount,TextLengthCharsCount=0;
	struct information_about_text *text_info=get_text_data();
	unsigned long long int TextLength=text_info->symbols_count;
	unsigned long long int i,ImageBytesCount=TextLength;
	char *temp_str=(char*)malloc(strlen(TextMarker)*sizeof(char));
	tangle_text(temp_str,TextMarker,strlen(TextMarker));	
	while(TextLength>0)
	{
		TextLengthCharsCount++;
		TextLength/=10;
	}
	TextLength=ImageBytesCount;
	ImageBytesCount=get_bitmap_size(filename);
	TextBitsCount=get_text_bits_count(ImageBytesCount,TextLength);
	ready_message=(char*)malloc(sizeof(char)*(strlen(TextMarker)+TextLengthCharsCount)+TextLength+1);	
	strcpy(ready_message,temp_str);
	strcat(ready_message,_itoa(TextLengthCharsCount,temp_str,10));
	strcat(ready_message,_itoa(TextLength,temp_str,10));
	strcat(ready_message,_itoa(text_info->encryption,temp_str,10));
	strcat(ready_message,text_info->array_of_chars);
//	write_message_to_bmp(ready_message,TextBitsCount,filename);
	printf("Written data:\n%s\n",ready_message);
	free(ready_message);
	free(temp_str);
}
void write_text_to_jpg_comment(struct information_about_text *text_info,char *filename)
{
	FILE *f=fopen(filename,"rb");
	FILE *fw=fopen("res.jpg","wb");
	unsigned long long int i=0;
	unsigned long long int previous_part_length=0;
	unsigned int textchar;
	unsigned char filechar;
	char *text=text_info->array_of_chars;
	unsigned long long int TextCharsCount=text_info->symbols_count;
	WORD marker,block_length,CurrentTextCharsCount,comment_marker=65279;
	WORD MaximumTextLength=65533;
	fread(&marker,sizeof(marker),1,f);
	fwrite(&marker,sizeof(marker),1,fw);
	fread(&marker,sizeof(marker),1,f);
	while(marker!=65279 && marker!=56063)
	{
		fwrite(&marker,sizeof(marker),1,fw);
		fread(&block_length,sizeof(block_length),1,f);
		fwrite(&block_length,sizeof(block_length),1,fw);
		block_length=replace_hex_bits(block_length);
		for(i=0; i<block_length-2; i++)
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
			block_length=replace_hex_bits(block_length);
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
		block_length=replace_hex_bits(CurrentTextCharsCount+3);
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
			block_length=replace_hex_bits(CurrentTextCharsCount+2);
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
struct information_about_text *read_text_from_jpg(char *filename)
{
	struct information_about_text *text_info=(struct information_about_text*)malloc(sizeof(struct information_about_text)*1);
	char *text=(char*)malloc(sizeof(char));
	FILE *f=fopen(filename,"rb");
	unsigned int textchar;
	unsigned char filechar;
	unsigned long long int i;
	unsigned long long int previous_part_length=0;
	WORD marker,block_length;	
	fread(&marker,sizeof(marker),1,f);
	fread(&marker,sizeof(marker),1,f);
	while(marker!=65279 && marker!=56063)
	{
		fread(&block_length,sizeof(block_length),1,f);
		block_length=replace_hex_bits(block_length);
		for(i=0; i<block_length-2; i++)
			textchar=getc(f);
		fread(&marker,sizeof(marker),1,f);
	}
	if(marker!=65279)
	{
		printf("The comment field of this file doesn't contain a text.");
		return NULL;
	}
	i=0;
	fread(&block_length,sizeof(block_length),1,f);
	fread(&text_info->encryption,sizeof(char),1,f);
	block_length=replace_hex_bits(block_length);
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
		block_length=replace_hex_bits(block_length);
	}
	text_info->array_of_chars=text;
	text_info->symbols_count=i;
	fclose(f);
	return text_info;
}
int main(void)
{
	struct information_about_text *text_info=get_text_data();
	write_text_to_jpg_comment(text_info,"1.jpg");
	FILE *f=fopen("res.txt","wb");
	struct information_about_text *readres=read_text_from_jpg("res.jpg");
	printf("\n=====================================\n");
	if(readres==NULL)
		return 0;
	printf("text chars count = %lld; encryption = %c\n",
	readres->symbols_count,readres->encryption);
	for(unsigned long long int i=0; i<readres->symbols_count; i++)
		fprintf(f,"%c",readres->array_of_chars[i]);
	fclose(f);
    return 0;
}
