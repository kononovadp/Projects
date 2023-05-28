#include "headers/model.h"
HANDLE console;
COORD ScreenCoordinates;
int main(void)
{
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
	model(3,0,0,1,50,vector<StructCity>(cities),matrix,10,0);
	for(i=0; i<cities.size(); i++)
		delete(matrix[i]);
	delete(matrix);
	return 0;
}