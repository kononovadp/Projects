#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>
#include <shlobj.h>
#include <fstream>
#include <vector>
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "comdlg32.lib")
using namespace std;
char* GetPathToFolder(char* title)
{	
	TCHAR* path=(char*)calloc(sizeof(char),MAX_PATH);
	BROWSEINFO bi={0};
	bi.lpszTitle=(title);
	bi.ulFlags=BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	LPITEMIDLIST pidl=SHBrowseForFolder(&bi);
	if (pidl!=0)
	{
		SHGetPathFromIDList(pidl,path);
		IMalloc* imalloc=0;
		if(SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
		return path;
	}
	return (char*)"";
}
char* GetPathToFile()
{
	OPENFILENAME ofn;
	TCHAR szFile[260]={0};
	ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner=GetActiveWindow();
	ofn.lpstrFile=(char*)calloc(sizeof(char),MAX_PATH);
	ofn.nMaxFile=sizeof(szFile);
	ofn.lpstrFilter=(".txt\0*.txt\0");
	ofn.nFilterIndex=1;
	ofn.lpstrFileTitle=NULL;
	ofn.nMaxFileTitle=0;
	ofn.lpstrInitialDir=NULL;
	ofn.Flags=OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;	
	bool CorrectFileName=false;
	int i;
	while(!CorrectFileName)
	{
		GetOpenFileName(&ofn);
		CorrectFileName=true;
		if(strlen(ofn.lpstrFile)>0)
		{
			for(i=strlen(ofn.lpstrFile)-1; ofn.lpstrFile[i]!='.'; i--);
			for(i--; ofn.lpstrFile[i]!='\\' && CorrectFileName; i--)
				if(!isdigit(ofn.lpstrFile[i]))
				{
					CorrectFileName=false;
					strcpy(ofn.lpstrFile,(char*)"");
					if(MessageBox(FindWindowA("ConsoleWindowClass",NULL),"File name must be a number of the chapter and can contain digits only.", "MessageTitleOK", MB_OKCANCEL)==IDCANCEL)
						exit(1);
				}			
		}
	}
	return ofn.lpstrFile;
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
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	char* SourceFolder=GetPathToFolder((char*)"SELECT FOLDER TO COPY");	
	if(strlen(SourceFolder)==0)
		return 0;	
	char* PathToTasks=GetPathToFile();
	if(strlen(PathToTasks)==0)
		return 0;
	char* DestinationFolder=GetPathToFolder((char*)"SELECT DESTINATION FOLDER");
	if(strlen(DestinationFolder)==0)
		return 0;
	string line,CodeText;	 
	if(DestinationFolder=="")
		return 0;	
	int i,j,k;
	bool NewTask;
	char* PathToCodeFile=(char*)calloc(sizeof(char),MAX_PATH);
	strcpy(PathToCodeFile,SourceFolder);
	strcat(PathToCodeFile,"\\code.cpp");
	ifstream CodeFile(PathToCodeFile);
	while(getline(CodeFile,line))	
		CodeText+=line+"\n";
	CodeFile.close();
	free(PathToCodeFile);
	strcat(SourceFolder,"\\*.*");
	for(i=strlen(PathToTasks)-1; PathToTasks[i]!='\\'; i--);
	char* TasksFileName=(char*)calloc(sizeof(char),MAX_PATH);
	char* NewFolderName=(char*)calloc(sizeof(char),MAX_PATH);
	char* FolderNumber=(char*)calloc(sizeof(char),MAX_PATH);
	char* NewDestinationFolder=(char*)calloc(sizeof(char),MAX_PATH);
	char* ChangedSourceFolder=(char*)calloc(sizeof(char),MAX_PATH);
	for(i++,j=0; PathToTasks[i]!='.'; i++,j++)
		TasksFileName[j]=PathToTasks[i];
	TasksFileName[j]='.';
	DestinationFolder[strlen(DestinationFolder)]='\\';
	strcat(DestinationFolder,TasksFileName);	
	ifstream TasksFile(PathToTasks);
	vector<string> AllTasks;
    while(getline(TasksFile,line))
    {
		NewTask=false;
		if(line[0]=='*')
			i=1;
		else
			i=0;
		for(; i<line.length() && isdigit(line[i]); i++);
		if(line[i]=='.')
			NewTask=true;
		/*if(line[0]=='*')
			NewTask=true;
		else
			if(isdigit(line[0]))
			{
				NewTask=true;				
				for(i=1; i<line.length() && line[i]!='.'; i++)
					if(!isdigit(line[i]))
					{
						NewTask=false;
						break;
					}
				if(line[i]!='.')
					NewTask=false;
			}*/
		if(NewTask)
			AllTasks.push_back(line);
		else
			AllTasks[AllTasks.size()-1]+="\n"+line;
		
		line="";
    }
	TasksFile.close();	
	for(i=0; i<AllTasks.size(); i++)
	{		
		strcpy(NewDestinationFolder,DestinationFolder);
		strcpy(FolderNumber,itoa(i+1,NewFolderName,10));
		strcat(NewDestinationFolder,FolderNumber);
		strcat(NewDestinationFolder,"\\");
		strcpy(ChangedSourceFolder,SourceFolder);
		CreateDirectory(NewDestinationFolder,NULL);
		CopyFolder(ChangedSourceFolder,NewDestinationFolder);
		strcat(NewDestinationFolder,"\\code.cpp");
		ofstream NewCodeFile(NewDestinationFolder);
		for(j=0,k=0; j<AllTasks[i].length(); j++)
			if(AllTasks[i][j]=='\n')
				k++;
		if(k==0)		
			NewCodeFile<<"//"<<AllTasks[i]<<"\n";		
		else
		{
			AllTasks[i][AllTasks[i].length()-1]='*';
			NewCodeFile<<"/*"<<AllTasks[i]<<"/\n";
		}
		for(j=3; j<CodeText.length(); j++)
			NewCodeFile<<CodeText[j];
		NewCodeFile.close();
	}
	free(TasksFileName);
	free(NewFolderName);
	free(FolderNumber);
	free(NewDestinationFolder);
	free(ChangedSourceFolder);
	return 0;
}