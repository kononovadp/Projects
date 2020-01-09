#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct information_about_text
{
	char *array_of_chars;
	unsigned long long int symbols_count;
};
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
		printf("Keyboard input: ");
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
	char keyboard_or_file=1;
	char encryption=0;
	struct information_about_text *text_info=get_text_data(keyboard_or_file,encryption);
	unsigned long long int i=0;
	if(text_info==NULL)
		return 0;
	printf("\n=========================output:=========================\n");
	printf("Symbols count: %lld\n",text_info->symbols_count);
	while(text_info->array_of_chars[i])
	{
		putchar(text_info->array_of_chars[i]);
		i++;
	}
    return 0;
}
