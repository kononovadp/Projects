#define WIN32_DEFAULT_LIBS
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define ChangedFileMarker "_res"
char **GetFilesList_Windows(char *FileTypes,int *FilesCount)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	int i,FileNameLength,FileNumber=0;	 
	int FileTypeNumber=0;
	char **files=(char**)malloc(sizeof(char*));
	hf=FindFirstFile(FileTypes,&FindFileData);
	if(hf!=INVALID_HANDLE_VALUE)
		do
		{		
			files=(char**)realloc(files,(FileNumber+1)*sizeof(char*));
			FileNameLength=strlen(FindFileData.cFileName)+1;
			files[FileNumber]=(char*)calloc(FileNameLength,sizeof(char));
			for(i=0,FileNameLength-=1; i<FileNameLength; i++)
				files[FileNumber][i]=FindFileData.cFileName[i];
			files[FileNumber][i]=0;
			FileNumber++;
		}while(FindNextFile(hf,&FindFileData)!=0);
	FindClose(hf);
	if(FileNumber==0)
		return NULL;
	*FilesCount=FileNumber;
	return files;
}
char *ChooseFile(char **files, int FilesCount)
{
	int i,choice;
	char *FileName=NULL;
	if(files==NULL)
		return NULL;
	printf("\nText files list:\n");
	for(i=0; i<FilesCount; i++)
		printf("%d. %s\n",i+1,*(files+i));
	if(FilesCount<10)
	{
		printf("Press a number key to choose the file or 0 to exit: ");
		choice=_getche();
		while(choice)
		{
			if(choice=='0')
				return NULL;
			if(choice<'0' || choice>FilesCount+'0')
				printf("\nIncorrect choice.\n");
			else
				return files[choice-'0'-1];
			printf("Press a number key to choose the file or 0 to exit: ");
			choice=_getche();
		}
	}
	else
	{
		printf("Enter a number of file or 0 to exit and press ENTER: ");
		i=scanf("%d",&choice);
		while(1)
		{
			if(i==0)
				getchar();
			if(choice==0)
				return NULL;
			else
				if(choice>0 && choice<=FilesCount)
					return files[choice-1];				
			printf("Incorrect choice.\nEnter a number of file or 0 to exit and press ENTER: ");
			i=scanf("%d",&choice);			
		}
	}
}
char *AddMarkerToFileName(char *source)
{
	unsigned int i,k;
	int j=strlen(source)-1;
	int n=strlen(source)+strlen(ChangedFileMarker);
	char *NewName=(char*)malloc(n+1*sizeof(char));
	strcpy(NewName,source);	
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
	NewName[n]=0;
	return NewName;
}
int main(void)
{
	int i,j,r,b,ch,LinesCount=0,*RandomLines,*MixedLinesLengths,**MixedLines,*LinesLengths=NULL,FilesCount=0;
	char **files,*SourceFileName,*ResultFileName;
	char *FileTypes=(char*)malloc(8*sizeof(char));
	FILE *SourceFile,*ResultFile;
	strcpy(FileTypes,".\\*.txt");
	files=GetFilesList_Windows(FileTypes,&FilesCount);
	if(FilesCount==0)
	{
		printf("No txt files found!");
		free(FileTypes);
		for(i=0; i<FilesCount; i++)
			free(files[i]);
		return 0;
	}
	SourceFileName=ChooseFile(files,FilesCount);
	if(SourceFileName==NULL)
	{
		for(i=0; i<FilesCount; i++)
			free(files[i]);
		free(FileTypes);
		return 0;
	}
	ResultFileName=AddMarkerToFileName(SourceFileName);
	SourceFile=fopen(SourceFileName,"r");	
	ResultFile=fopen(ResultFileName,"w");
	for(i=0; i<FilesCount; i++)
		free(files[i]);
	free(FileTypes);
	while((ch=getc(SourceFile))!=EOF)
	{
		LinesCount++;
		LinesLengths=(int*)realloc(LinesLengths,LinesCount*sizeof(int));
		LinesLengths[LinesCount-1]=0;
		while(ch!='\n' && ch!=EOF)
		{
			ch=getc(SourceFile);
			LinesLengths[LinesCount-1]++;
		}	
	}
	fseek(SourceFile,0,SEEK_SET);
	MixedLines=(int**)calloc(LinesCount,sizeof(int*));
	RandomLines=(int*)calloc(LinesCount,sizeof(int));
	MixedLinesLengths=(int*)calloc(LinesCount,sizeof(int));
	srand((unsigned int)time(0));
	for(i=0; i<LinesCount; i++)
	{
		b=0;
		while(b==0)
		{
			b=1;
			r=rand()%LinesCount;
			for(j=0; j<i; j++)
				if(RandomLines[j]==r)
					b=0;
		}
		RandomLines[i]=r;
		MixedLinesLengths[r]=LinesLengths[i];
	}
	for(i=0; i<LinesCount; i++)
	{
		MixedLines[RandomLines[i]]=(int*)calloc(LinesLengths[i],sizeof(int));
		j=0;
		while((ch=getc(SourceFile))!='\n' && ch!=EOF)
		{
			MixedLines[RandomLines[i]][j]=ch;
			j++;
		}
	}
	for(i=0; i<LinesCount; i++)
	{
		for(j=0; j<MixedLinesLengths[i]; j++)
			fprintf(ResultFile,"%c",MixedLines[i][j]);
		fprintf(ResultFile,"\n");
	}
	fclose(SourceFile);
	fclose(ResultFile);
	for(i=0; i<LinesCount; i++)
		free(MixedLines[i]);
	free(MixedLines);
	free(RandomLines);
	free(LinesLengths);
	free(MixedLinesLengths);
	printf("\nFile \"%s\" created.\nPress ENTER to exit.",ResultFileName);
	free(ResultFileName);
	getchar();
	return 0;
}
