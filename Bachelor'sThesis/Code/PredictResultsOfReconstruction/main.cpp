#include "headers/model.h"
HANDLE console;
COORD ScreenCoordinates;
static bool SetConsoleSize(int cols, int rows) {
  HWND hWnd;
  HANDLE hConOut;
  CONSOLE_FONT_INFO fi;
  CONSOLE_SCREEN_BUFFER_INFO bi;
  int w, h, bw, bh;
  RECT rect = {0, 0, 0, 0};
  COORD coord = {0, 0};
  hWnd = GetConsoleWindow();
  if (hWnd) {
    hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConOut && hConOut != (HANDLE)-1) {
      //if (GetCurrentConsoleFont(hConOut, false, &fi)) {
        //if (GetClientRect(hWnd, &rect)) {
          w = rect.right-rect.left;
          h = rect.bottom-rect.top;
          //if (GetWindowRect(hWnd, &rect)) {
            bw = rect.right-rect.left-w;
            bh = rect.bottom-rect.top-h;
            if (GetConsoleScreenBufferInfo(hConOut, &bi)) {
              coord.X = bi.dwSize.X;
              coord.Y = bi.dwSize.Y;
              if (coord.X < cols || coord.Y < rows) {
                if (coord.X < cols) {
                  coord.X = cols;
                }
                if (coord.Y < rows) {
                  coord.Y = rows;
                }
                if (!SetConsoleScreenBufferSize(hConOut, coord)) {
					
                  return false;
                }
				
              }
             // return SetWindowPos(hWnd, NULL, rect.left, rect.top, cols*fi.dwFontSize.X+bw, rows*fi.dwFontSize.Y+bh, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
            }
          //}
        //}
      //}
    }
  }
	char* str=new char[50];
	string res="MODE CON: COLS="+to_string(cols)+" LINES="+to_string(rows);
	strcpy(str,res.c_str());
	//str="MODE CON: COLS=100 LINES=70";
	system (str);	
	SetWindowPos(GetConsoleWindow(),HWND_TOP,0,0,0,0,SWP_NOSIZE);	
	return false;
  
}
int main(void)
{
	typedef struct _CONSOLE_FONT_INFOEX
	{
		ULONG cbSize;
		DWORD nFont;
		COORD dwFontSize;
		UINT  FontFamily;
		UINT  FontWeight;
		WCHAR FaceName[LF_FACESIZE];
	}CONSOLE_FONT_INFOEX,*PCONSOLE_FONT_INFOEX;
	typedef BOOL (WINAPI *SETCONSOLEFONT)(HANDLE,DWORD);
	typedef BOOL (WINAPI*SETCURRENTCONSOLEFONTEX)(HANDLE,BOOL, PCONSOLE_FONT_INFOEX);
	SETCURRENTCONSOLEFONTEX SetCurrentConsoleFontEx;
	SETCONSOLEFONT SetConsoleFont;
	struct route
	{
		string departure,destination;
		double distance;
	};		
	string FileLine,NewTown,DistanceString;
	char DepartureFound,DestinationFound;	
	int i,j,DepartureIndex,DestinationIndex;
	int MaxCountOfIncompleteConstructions=70;
	double MaxCityArea=839.2,PercentageOfMaxCityArea,**matrix;
	double SimulationTime,CurrentTime;
	vector<StructCity> cities;
	vector<route> routes;
	StructCity NewCity;
	route NewRoute;	
	srand(time(0));
	cout.precision(2);
	cout.setf(ios::fixed);
	console=GetStdHandle(STD_OUTPUT_HANDLE);
	SimulationTime=5.0*365.0;	
	fstream MapFile("MapOfCities.csv");	
	getline(MapFile,FileLine);
	while(!MapFile.eof() && count(FileLine.begin(),FileLine.end(),';')<2)
	{
		for(i=0; FileLine[i]!=';'; i++)
			NewCity.name+=FileLine[i];
		for(i++; i<FileLine.length(); i++)
			DistanceString+=FileLine[i];
		PercentageOfMaxCityArea=100-((stod(DistanceString)*100.0)/MaxCityArea);
		NewCity.CountOfIncompleteConstructions=MaxCountOfIncompleteConstructions-(MaxCountOfIncompleteConstructions/100.0)*PercentageOfMaxCityArea;
		cities.push_back(NewCity);
		NewCity.name="";
		DistanceString="";
		getline(MapFile,FileLine);
	}	
	while(!MapFile.eof())
	{		
		for(i=0; FileLine[i]!=';'; i++)
			NewRoute.departure+=FileLine[i];
		for(i++; FileLine[i]!=';'; i++)
			NewRoute.destination+=FileLine[i];
		for(i++; i<FileLine.length(); i++)
			DistanceString+=FileLine[i];
		NewRoute.distance=stod(DistanceString);
		routes.push_back(NewRoute);
		NewRoute.departure="";
		NewRoute.destination="";
		DistanceString="";
		getline(MapFile,FileLine);
	}	
	MapFile.close();
	sort(cities.begin(),cities.end());
	matrix=new double*[cities.size()];	
	for(i=0,DepartureIndex=3; i<cities.size(); i++)
	{
		matrix[i]=new double[cities.size()];
		for(j=0; j<cities.size(); j++)
			matrix[i][j]=0.0;
		if(i%2==0)
			DepartureIndex++;
	}
	for(i=0; i<routes.size(); i++)
	{
		for(DepartureIndex=0; cities[DepartureIndex].name!=routes[i].departure; DepartureIndex++);
		for(DestinationIndex=0; cities[DestinationIndex].name!=routes[i].destination; DestinationIndex++);
		matrix[DepartureIndex][DestinationIndex]=routes[i].distance/10;
	}	
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0; // Width of each character in the font
	cfi.dwFontSize.Y = 17; // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	
	std::wcscpy(cfi.FaceName, L"Lucida Console"); // Choose your font
	SetCurrentConsoleFontEx=(SETCURRENTCONSOLEFONTEX) GetProcAddress(GetModuleHandleA("KERNEL32.DLL"), "SetCurrentConsoleFontEx");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);	
	SetConsoleSize(100,100);	
	/*auto console_window{ GetConsoleWindow() };
    if (!console_window) {
        std::cerr << "GetConsoleWindow() failed :(\n\n";
        return false;
    }*/
    //auto console_out{ GetStdHandle(STD_OUTPUT_HANDLE) };
    /*auto largest_size{ GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE)) };
    --largest_size.X;
    --largest_size.Y;*/
	/*auto largest_size=GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));	
	HWND console=GetConsoleWindow();
	ShowWindow(console, SW_MAXIMIZE);	
	--largest_size.X;
    --largest_size.Y;*/
	//HWND console1=GetConsoleWindow();
	//COORD coords=GetLargestConsoleWindowSize(console1);
	//cout<<coords.X<<"   "<<coords.Y<<"\n";
	//MoveWindow(console1, 0, 0, coords.X, coords.Y, TRUE);
    //MoveWindow(window_handle, x, y, width, height, redraw_window);
    //MoveWindow(console1,0, 0, 1030, 700, TRUE);
	
	
	model(3,0,0,1,50,vector<StructCity>(cities),matrix,10,0);
	for(i=0; i<cities.size(); i++)
		delete(matrix[i]);
	delete(matrix);
	getchar();
	return 0;
}