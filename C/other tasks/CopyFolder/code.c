#include <stdio.h>
#include <string.h>
#include <windows.h>
#define WIN32_DEFAULT_LIBS
typedef unsigned long int DWORD;
char *timetostr(int n)
{
	char *result=(char*)calloc(sizeof(char),100);
	char *temp=(char*)calloc(sizeof(char),100);
	if(n<60)
	{		
		_itoa(n,result,10);
		strcat(result," sec.");
	}
	else
		if(n<3600)
		{
			_itoa(n/60,result,10);
			strcat(result," min.");
			if(n%60>0)
			{
				strcat(result," ");
				_itoa(n%60,temp,10);
				strcat(result,temp);
				strcat(result," sec.");
			}
		}
		else
		{
			_itoa(n/3600,result,10);
			strcat(result," hr.");
			if(n%3600<60)
			{
				strcat(result," ");
				_itoa(n%3600,temp,10);
				strcat(result,temp);
				strcat(result," sec.");
				return result;
			}
			else
			{
				n=n%3600;
				strcat(result," ");
				_itoa(n/60,temp,10);
				strcat(result,temp);
				strcat(result," min.");
				if(n%60!=0)
				{
					strcat(result," ");
					_itoa(n%60,temp,10);
					strcat(result,temp);
					strcat(result," sec.");					
				}
			}
		}
	free(temp);
	return result;
}
char *ChooseDirectory(char *FileTypes)
{
	WIN32_FIND_DATA DirectoryData;
	HANDLE hf=FindFirstFile(FileTypes,&DirectoryData);
	int i,j,k,ch,DigitsCount,FileNumber=1;
	char *result=(char*)calloc(sizeof(char),500);
	char **directories=(char**)calloc(sizeof(char*),10000);
	directories[0]=(char*)calloc(5,sizeof(char));
	strcpy(directories[0],"back");
	if(hf!=INVALID_HANDLE_VALUE)
		do
		{
			if (strcmp(DirectoryData.cFileName,".") && strcmp(DirectoryData.cFileName,"..")&&(DirectoryData.dwFileAttributes != FILE_ATTRIBUTE_REPARSE_POINT))
			{
				if (DirectoryData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					directories[FileNumber]=(char*)calloc(strlen(DirectoryData.cFileName)+1,sizeof(char));
					if(strlen(DirectoryData.cFileName)>=20)
					{
						strncpy(directories[FileNumber],DirectoryData.cFileName,20);
						i=strlen(directories[FileNumber])-1;
						directories[FileNumber][i]='.';
						directories[FileNumber][i-1]='.';
						directories[FileNumber][i-2]='.';
					}
					else
						strcpy(directories[FileNumber],DirectoryData.cFileName);
					FileNumber++;
				}
			}
		}while(FindNextFile(hf,&DirectoryData)!=0);
	FindClose(hf);
	for(i=0,ch=10,DigitsCount=1; i<FileNumber;)
	{
		for(k=i+3; i<FileNumber && i<k; i++)
		{
			printf("%d. %s",i,directories[i]);
			if(i==ch)
			{
				DigitsCount++;
				ch*=10;
			}
			for(j=23-(strlen(directories[i])+DigitsCount+2); j>-1; j--)
				putchar(' ');
		}
		putchar('\n');
	}
	if(FileNumber<9)
	{
		printf("Press number of file or %d to stop: ",FileNumber);
		ch=_getche()-'0';
		while(ch>FileNumber+1)
		{
			printf("\nIncorrect file number, try again: ");
			ch=_getche()-'0';
		}
		putchar('\n');
	}
	else
	{
		printf("Type number of file or %d to stop and press ENTER: ",FileNumber);
		scanf("%d",&ch);
		while(ch>FileNumber+1)
		{
			printf("Incorrect file number, try again: ");
			scanf("%d",&ch);
		}
	}
	if(ch==0)
		result=-1;
	else
		if(ch==FileNumber)
			result=NULL;
		else
			strcpy(result,directories[ch]);
	for(ch=0; ch<FileNumber; ch++)
		free(directories[ch]);
	free(directories);
	return result;
}
char ChooseDrive()
{
	int DisksCount,i,number;
	char letter,*drives=(char*)calloc(sizeof(char),27);
	DWORD LogicalDrives=GetLogicalDrives();		
	for(i=0,DisksCount=0; i<26; i++)
	{
		number=(LogicalDrives>>i)&1;
		if(number)
		{
			drives[DisksCount]=65+i;			
			printf("%d. Disk %c; ",DisksCount+1,drives[DisksCount]);
			DisksCount++;
			if(DisksCount%6==0)
				putchar('\n');
		}
	}
	if(DisksCount%6!=0)
		putchar('\n');
	if(DisksCount<9)
	{
		printf("Press number of disk or %d to exit: ",DisksCount+1);
		letter=_getche()-'0';
		while(letter>DisksCount+1)
		{
			printf("\nIncorrect disk number, try again: ");
			letter=_getche()-'0';
		}
		putchar('\n');
	}
	else
	{
		printf("Type number of disk or %d to exit and press ENTER: ",DisksCount+1);
		scanf("%d",&letter);
		while(letter>DisksCount+1)
		{
			printf("Incorrect disk number, try again: ");
			scanf("%d",&letter);
		}
	}
	if(letter==DisksCount+1)
		exit(1);
	letter=drives[letter]-1;
	free(drives);
	return letter;
}
char *GetFolder()
{
	int i,j,k;
	char *ChoosenDirectory,*temp=(char*)calloc(sizeof(char),500);
	char *folder=(char*)calloc(sizeof(char),500);
	strcpy(folder,"C:\\*.*");
	folder[0]=ChooseDrive();
	ChoosenDirectory=ChooseDirectory(folder);
	while(ChoosenDirectory!=NULL)
	{
		strncpy(temp,folder,strlen(folder)-3);
		strcpy(folder,temp);
		if(ChoosenDirectory!=-1)
			strcat(folder,ChoosenDirectory);
		else
			if(ChoosenDirectory==-1 && strlen(folder)>3)
			{
				j=strlen(folder)-2;
				while(folder[j]!='\\')
					j--;
				for(k=strlen(temp); k>-1; k--)
					temp[k]=0;
				strncpy(temp,folder,j);
				strcpy(folder,temp);
			}
			else
				if(ChoosenDirectory==-1 && strlen(folder)==3)
					folder[0]=ChooseDrive();
		if(ChoosenDirectory!=-1)
			free(ChoosenDirectory);
		printf("PATH: %s\n",folder);
		strcat(folder,"\\*.*");		
		ChoosenDirectory=ChooseDirectory(folder);
	}
	free(temp);
	free(ChoosenDirectory);
	return folder;
}
void CopyFolder(char *SourceFolder,char *DestinationFolder)
{
	FILE *SourceFile,*ResultFile;
	WIN32_FIND_DATA DirectoryData;
	HANDLE hf;
	int i,j,k,ch,SourceFolderLength=strlen(SourceFolder)-1;
	int DestinationFolderLength=strlen(DestinationFolder)-1;
	hf=FindFirstFile(SourceFolder,&DirectoryData);
	if(hf!=INVALID_HANDLE_VALUE)
		do
		{
			if(strcmp(DirectoryData.cFileName,".") && strcmp(DirectoryData.cFileName,".."))
			{
				if(DirectoryData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					for(j=strlen(SourceFolder),k=j-3; j>=k; j--)
						SourceFolder[j]=0;
					strcat(SourceFolder,DirectoryData.cFileName);
					strcat(SourceFolder,"\\*.*");
					strcat(DestinationFolder,DirectoryData.cFileName);
					strcat(DestinationFolder,"\\");
					CreateDirectory(DestinationFolder,NULL);
					CopyFolder(SourceFolder,DestinationFolder);
					for(i=strlen(SourceFolder); i>SourceFolderLength-3; i--)
						SourceFolder[i]=0;
					strcat(SourceFolder,"*.*");
					for(i=strlen(DestinationFolder); i>DestinationFolderLength; i--)
						DestinationFolder[i]=0;
				}
				else
				{
					for(j=strlen(SourceFolder),k=j-3; j>=k; j--)
						SourceFolder[j]=0;
					strcat(SourceFolder,DirectoryData.cFileName);
					strcat(DestinationFolder,DirectoryData.cFileName);
					SourceFile=fopen(SourceFolder,"rb");
					ResultFile=fopen(DestinationFolder,"wb");
					while((ch=fgetc(SourceFile))!=EOF)
						fprintf(ResultFile,"%c",ch);
					fclose(SourceFile);
					fclose(ResultFile);
					for(i=strlen(SourceFolder); i>SourceFolderLength-3; i--)
						SourceFolder[i]=0;
					strcat(SourceFolder,"*.*");
					for(i=strlen(DestinationFolder); i>DestinationFolderLength; i--)
						DestinationFolder[i]=0;
				}
			}
		}while(FindNextFile(hf,&DirectoryData)!=0);
	FindClose(hf);
}
int main(void)
{
	time_t TimeEnd,TimeBegin;
	double DoubleTypeCount,percent,RealPercent;
	int count,i,progress,j,DestinationFolderLength,FolderNumber;
	char *SourceFolder,*DestinationFolder,*FolderNumberString,*TimeString;
	char *InitialName=(char*)calloc(sizeof(char),100);
	printf("Find folder, which you want to copy.\n");
	SourceFolder=GetFolder();
	printf("Find folder, where you want to save copies.\n");
	DestinationFolder=GetFolder();	
	printf("Initial string: ");
	scanf("%s",InitialName);
	printf("count of folders: ");
	scanf("%d",&count);
	TimeBegin=time(&TimeBegin);
	i=strlen(DestinationFolder)-1;
	DestinationFolder[i]=0; DestinationFolder[i-1]=0; DestinationFolder[i-2]=0;
	strcat(DestinationFolder,InitialName);
	DestinationFolder[strlen(DestinationFolder)]='.';
	DestinationFolderLength=strlen(DestinationFolder);
	FolderNumberString=(char*)calloc(sizeof(char),10);
	printf("Writing...\n");
	if(count<80)
	{		
		for(i=1,progress=80/count,count++; i<count; i++)
		{		
			FolderNumber=sprintf(FolderNumberString,"%d\\",i);
			strcat(DestinationFolder,FolderNumberString);
			for(j=0; j<FolderNumber; j++)
				FolderNumberString[j]=0;
			CreateDirectory(DestinationFolder,NULL);
			CopyFolder(SourceFolder,DestinationFolder);
			for(FolderNumber=strlen(DestinationFolder),j=FolderNumber; j>=DestinationFolderLength; j--)
				DestinationFolder[j]=0;
			for(j=0; j<progress; j++)
				putchar('X');
		}
		progress=progress*(count-1);
		if(progress<80)
			while(progress++<80)
				putchar('X');
	}
	else
		for(i=1,DoubleTypeCount=(double)count,percent=1.0,count++; i<count; i++)
		{
			FolderNumber=sprintf(FolderNumberString,"%d\\",i);
			strcat(DestinationFolder,FolderNumberString);
			for(j=0; j<FolderNumber; j++)
				FolderNumberString[j]=0;
			CreateDirectory(DestinationFolder,NULL);
			CopyFolder(SourceFolder,DestinationFolder);
			for(FolderNumber=strlen(DestinationFolder),j=FolderNumber; j>=DestinationFolderLength; j--)
				DestinationFolder[j]=0;
			RealPercent=(i/DoubleTypeCount)*80.0;
			if(RealPercent>=percent)
			{
				putchar('X');
				percent=percent+1.0;
			}
		}
	free(SourceFolder);
	free(DestinationFolder);
	free(FolderNumberString);
	free(InitialName);
	printf("\nDone!");
	TimeEnd=time(&TimeEnd);
	TimeString=timetostr(TimeEnd-TimeBegin);
	printf(" Time: %s",TimeString);
	free(TimeString);
	getche();
	return 0;
}
