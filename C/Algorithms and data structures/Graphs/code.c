#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <limits.h>
#include <omp.h>
//http://poisk-vagonov.ru/route.php#
//https://glogist.ru/site/calculateDist
struct town
{
	char* name;
	double latitude,longitude;
	int population;
};
struct route
{
	int departure,destination;
	double** distances;
};
void InsertionSort(double* arr,int size)
{
	double t;
	int i,j;
	for(i=1; i<size; i++)
		for(j=i; j>0 && arr[j-1]>arr[j]; j--)
		{
			t=arr[j];
			arr[j]=arr[j-1];
			arr[j-1]=t;
		}
}
void RadixSortLSD(int* array,int n)//https://habr.com/ru/post/533206/
{		
	char* b;
	int* TempArray=(int*)malloc(sizeof(int)*n);//Память под временный массив
	int* baskets=(int*)calloc(sizeof(int),1024);
	int i,value,digit,off,key,*temp;
	for(i=0; i<n; ++i)//Заполняем массив корзин для всех разрядов
	{
		key=array[i];
		for(digit=0; digit<4; digit++)		
			baskets[((key>>(digit*8))&0xFF)+256*digit]++;		
	}	
	for (digit=0; digit<4; digit++)//Пересчитываем смещения для корзин
	{
		off=0;
		for(i=0; i<256; i++)
		{
			value=baskets[i+256*digit];
			baskets[i+256*digit]=off;
			off+=value;
		}
	}	
	for(i=0,b=(char*)&array[n],temp=&baskets[0]; i<n; ++i)
	{
		key=array[i];
		off=(key>>(0))&0xFF;
		TempArray[temp[off]++]=key;
	}	
	for(i=0,b=(char*)&TempArray[n]+1,temp=&baskets[256]; i<n; ++i)
	{
		key=TempArray[i];
		off=(key>>(8))&0xFF;
		array[temp[off]++]=key;
	}
	free(baskets);
	free(TempArray);
}
void ShowTowns(struct town** towns,int TownsCount)
{
	int i;
	for(i=0; i<TownsCount; i++)
	{
		printf("%2d. %14s; ",i,towns[i]->name);
		if((i+1)%4==0)
			putchar('\n');
	}
}
char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');   // поиск новой строки
        if (find)                  // если адрес не равен NULL,
            *find = '\0';          // поместить туда нулевой символ
        else
            while (getchar() != '\n')
                continue;          // отбросить остаток строки
    }
    return ret_val;
}
int GetTownsNumber(char FirstString,struct town** towns,int TownsCount)
{
	int i,res=-1;
	char CorrectString=1,*input=(char*)calloc(sizeof(char),10);
	if(FirstString==0)
		printf("Number of a departure town:\n");
	else
		printf("Number of a destination town:\n");
	ShowTowns(towns,TownsCount);
	printf("%2d. %14s. ",TownsCount,"Exit");
	if(TownsCount+1%4==0)
		putchar('\n');
	printf("Your choice: ");
	input=s_gets(input,10);
	for(i=0; i<strlen(input) && CorrectString==1; i++)
		if(!isdigit(input[i]))
			CorrectString=0;
	if(CorrectString==1)
	{
		res=atoi(input);
		if(res>TownsCount)
			CorrectString=0;			
	}
	while(CorrectString==0)
	{
		printf("Enter a correct number of town or %d to exit: ",TownsCount+1);
		input=s_gets(input,10);
		for(i=0,CorrectString=1; i<strlen(input) && CorrectString==1; i++)
			if(!isdigit(input[i]))
				CorrectString=0;
		res=-1;
		if(CorrectString==1)
		{
			res=atoi(input);
			if(res>TownsCount)
				CorrectString=0;			
		}
	}
	return res;
}
void InsertionSortingOfTowns(struct town** towns,int TownsCount,char TypeOfData)
{
	struct town* t;
	int i,j;	
	switch(TypeOfData)
	{
		case 0:
		for(i=1; i<TownsCount; i++)
			for(j=i; j>0 && towns[j-1]->longitude>towns[j]->longitude; j--)
			{
				t=towns[j];
				towns[j]=towns[j-1];
				towns[j-1]=t;
			}		
		break;
		case 1:
		for(i=1; i<TownsCount; i++)
			for(j=i; j>0 && towns[j-1]->latitude>towns[j]->latitude; j--)
			{
				t=towns[j];
				towns[j]=towns[j-1];
				towns[j-1]=t;
			}
		break;		
		case 2:
		for(i=1; i<TownsCount; i++)
			for(j=i; j>0 && towns[j-1]->population<towns[j]->population; j--)
			{
				t=towns[j];
				towns[j]=towns[j-1];
				towns[j-1]=t;
			}
		break;
	}
	ShowTowns(towns,TownsCount);
}
void VisitAllTowns(int** graph,char* visited,struct town** towns,int TownsCount,int departure)
{
	int i;
	printf("%s",towns[departure]->name);
	visited[departure]=1;
	for(i=0; i<TownsCount; i++)
		if(visited[i]==0 && graph[departure][i]==1)
		{
			printf("->");
			VisitAllTowns(graph,visited,towns,TownsCount,i);
		}
}
int DepthFirstSearch(int** graph,char* visited,int* route,int* StepsCounts,int size,int departure,int destination,int StepsCount)
{
	int i,min=10000,minind,result;
	if(graph[departure][destination]>0)
	{
		route[departure]=destination;
		return StepsCount;
	}
	visited[departure]=1;
	for(i=0; i<size; i++)
		if(graph[departure][i]>0 && visited[i]==0)
		{
			result=DepthFirstSearch(graph,visited,route,StepsCounts,size,i,destination,StepsCount+1);
			if(result>-1 && result<min)
			{
				min=result;
				minind=i;
			}
		}
	visited[departure]=0;
	if(min==10000)
		return -1;
	if(StepsCounts[departure]==0||(StepsCounts[departure]>0 && min<StepsCounts[departure]))
	{
		StepsCounts[departure]=min;
		route[departure]=minind;
	}	
	return min;
}
void DepthFirstSearchShowRoute(int* route,struct town** towns,int departure,int destination)
{
	int i;
	for(i=departure; i!=destination; i=route[i])
		printf("%s->",towns[i]->name);
	printf("%s\n",towns[destination]->name);
}
void BreadthFirstSearch(int** matrix,struct town** towns,int TownsCount,int departure,int destination)
{
	char AllTownsVisited=0,*visited=(char*)calloc(sizeof(char),TownsCount);
	int i,j,StepsCount=1,*distances=(int*)calloc(sizeof(int),TownsCount);
	int QueueItem,QueueItemsCount=1,QueueStart=0,QueueEnd=1;
	int* queue=(int*)malloc(sizeof(int)*TownsCount);
	int* route=(int*)malloc(sizeof(int)*TownsCount);
	queue[0]=departure;
	visited[departure]=1;
	while(AllTownsVisited!=1 && distances[destination]==0)
	{
		AllTownsVisited=1;
		for(i=QueueStart; i<QueueItemsCount; i++)
		{
			QueueItem=queue[i];			
			for(j=0; j<TownsCount; j++)
				if(matrix[QueueItem][j]>0 && visited[j]==0)
				{
					visited[j]=1;
					route[j]=QueueItem;
					distances[j]=StepsCount;
					queue[QueueEnd]=j;
					QueueEnd++;
					AllTownsVisited=0;					
				}
		}		
		QueueStart=QueueItemsCount;
		QueueItemsCount=QueueEnd;
		StepsCount++;
	}		
	if(distances[destination]==0)
		printf("BREADTH FIRST SEARCH: there is no route");
	else
	{
		printf("BREADTH FIRST SEARCH: minimal count of steps is %d\nroute: ",distances[destination]);
		for(i=destination,j=0; i!=departure; i=route[i],j++)
			queue[j]=i;
		printf("%s->",towns[departure]->name);
		for(j--; j>0; j--)
			printf("%s->",towns[queue[j]]->name);
		printf("%s\n",towns[queue[j]]->name);
	}
	free(route);
	free(queue);
	free(visited);
	free(distances);
}
void BellmanFord(double** matrix,struct town** towns,int TownsCount,int departure,int destination)
{
	int i,j,k;
	double* MinimalDistances=(double*)malloc(sizeof(double)*TownsCount);
	int* route=(int*)calloc(sizeof(int),TownsCount);
	for(i=0; i<TownsCount; i++)
		MinimalDistances[i]=10000;
	MinimalDistances[departure]=0;
	for(i=0; i<TownsCount; i++)
		for(j=0; j<TownsCount; ++j)
			for(k=0; k<TownsCount; ++k)
				if(matrix[j][k]>0 && MinimalDistances[k]>MinimalDistances[j]+matrix[j][k])
				{
					MinimalDistances[k]=MinimalDistances[j]+matrix[j][k];
					route[k]=j;
				}
	printf("BELLMAN-FORD ALGORITHM:\n");
	if(MinimalDistances[destination]==10000)
		printf("there is no route from %s to %s.\n",towns[departure]->name,towns[destination]->name);
	else
	{
		printf("minimal distance from %s to %s is %.2lf km\nroute: ",towns[departure]->name,towns[destination]->name,MinimalDistances[destination]);
		for(i=destination,j=0; i!=departure; i=route[i],j++)
			MinimalDistances[j]=i;
		MinimalDistances[j]=i;
		for(; j>0; j--)
			printf("%s->",towns[(int)MinimalDistances[j]]->name);
		printf("%s",towns[(int)MinimalDistances[j]]->name);
		printf("\n---------------------------------------------------------------------------------\n");
	}
	free(route);
	free(MinimalDistances);
}
void FloydWarshall(double** matrix,struct town** towns,int TownsCount,int departure,int destination)
{
	int i,j,k,**route=(int**)malloc(sizeof(int*)*TownsCount);
	double** MinimalDistances=(double**)malloc(sizeof(double*)*TownsCount);
	for(i=0; i<TownsCount; i++)
	{
		MinimalDistances[i]=(double*)malloc(sizeof(double)*TownsCount);
		route[i]=(int*)malloc(sizeof(int)*TownsCount);
		for(j=0; j<TownsCount; j++)
		{
			route[i][j]=j;
			MinimalDistances[i][j]=10000;
		}
	}
	for(i=0; i<TownsCount; i++)
		MinimalDistances[i][i]=0;
	for(i=0; i<TownsCount; i++)
		for(j=0; j<TownsCount; j++)
			if(matrix[i][j]>0)
				MinimalDistances[i][j]=matrix[i][j];
	for(i=0; i<TownsCount; i++)
		for(j=0; j<TownsCount; j++)
			for(k=0; k<TownsCount; k++)
				if(MinimalDistances[j][i] && MinimalDistances[i][k] && j!=k)
					if(MinimalDistances[j][i]+MinimalDistances[i][k]<MinimalDistances[j][k] || MinimalDistances[j][k]==0)
					{
						MinimalDistances[j][k]=MinimalDistances[j][i]+MinimalDistances[i][k];
						route[j][k]=route[j][i];
					}
	printf("FLOYD-WARSHALL ALGORITHM:\n");
	if(MinimalDistances[departure][destination]==10000)
		printf("there is no route from %s to %s.\n",towns[departure]->name,towns[destination]->name);
	else
	{
		printf("minimal distance from %s to %s is %.2lf km\nroute: ",towns[departure]->name,towns[destination]->name,MinimalDistances[departure][destination]);
		for(; destination!=departure; departure=route[departure][destination])
			printf("%s->",towns[departure]->name);
		printf("%s",towns[departure]->name);
		printf("\n---------------------------------------------------------------------------------\n");
	}
	for(i=0; i<TownsCount; i++)
	{
		free(route[i]);
		free(MinimalDistances[i]);
	}
	free(MinimalDistances);
	free(route);
}
void Dijkstra(double** matrix,struct town** towns,int TownsCount,int departure,int destination)
{
	int* route=(int*)malloc(sizeof(int)*TownsCount);
	int i,j,k,minindex,end,prev,*visited=(int*)calloc(sizeof(int),TownsCount);
	double distance,MinimalDistance,*MinimalDistances=(double*)malloc(sizeof(double)*TownsCount);
	for(i=0; i<TownsCount; i++)
	{
		route[i]=-1;
		MinimalDistances[i]=10000;
	}
	MinimalDistances[departure]=0;
	do
	{
		MinimalDistance=10000;
		minindex=10000;		
		for(i=0; i<TownsCount; i++)
			if(visited[i]==0 && MinimalDistances[i]<MinimalDistance)
			{
				MinimalDistance=MinimalDistances[i];
				minindex=i;
			}
		if(MinimalDistance<10000)
		{
			for(i=0; i<TownsCount; i++)
				if(matrix[minindex][i]>0)
				{
					distance=MinimalDistance+matrix[minindex][i];
					if(distance<MinimalDistances[i])
					{
						MinimalDistances[i]=distance;
						route[i]=minindex;
					}
				}
			visited[minindex]=1;
		}
	}while(MinimalDistance<10000);
	printf("DIJKSTRA'S ALGORITHM:\n");
	if(MinimalDistances[destination]==10000)
		printf("there is no route from %s to %s.\n",towns[departure]->name,towns[destination]->name);
	else
	{
		printf("minimal distance from %s to %s is %.2lf km\nroute: ",towns[departure]->name,towns[destination]->name,MinimalDistances[destination]);
		for(i=0; i<TownsCount; i++)
			visited[i]=-1;
		for(i=destination,j=0; route[i]!=-1; i=route[i],j++)		
			visited[j]=route[i];
		for(j--; j>-1; j--)
			printf("%s->",towns[visited[j]]->name);
		printf("%s",towns[destination]->name);
		printf("\n---------------------------------------------------------------------------------\n");
	}
	free(route);
	free(visited);
	free(MinimalDistances);
}
//==========================================================================================
void DepthFirstSearchShowRoute_Matrix(int* route,int departure,int destination)
{
	int i;
	for(i=departure; i!=destination; i=route[i])
		printf("%d->",i);
	printf("%d\n",destination);
}
void BreadthFirstSearch_Matrix(int** matrix,int size,int departure,int destination)
{
	int AllTownsVisited=0,*visited=(int*)calloc(sizeof(int),size);
	int i,j,StepsCount=1,*distances=(int*)calloc(sizeof(int),size);
	int QueueItem,QueueItemsCount=1,QueueStart=0,QueueEnd=1;
	int* queue=(int*)malloc(sizeof(int)*size);
	int* route=(int*)malloc(sizeof(int)*size);
	queue[0]=departure;
	visited[departure]=1;
	while(AllTownsVisited!=1 && distances[destination]==0)
	{
		AllTownsVisited=1;
		for(i=QueueStart; i<QueueItemsCount; i++)
		{
			QueueItem=queue[i];			
			for(j=0; j<size; j++)
				if(matrix[QueueItem][j]>0 && visited[j]==0)
				{
					visited[j]=1;
					route[j]=QueueItem;
					distances[j]=StepsCount;
					queue[QueueEnd]=j;
					QueueEnd++;
					AllTownsVisited=0;					
				}
		}		
		QueueStart=QueueItemsCount;
		QueueItemsCount=QueueEnd;
		StepsCount++;
	}
	if(size<25)
	{
		if(distances[destination]==0)
			printf("there is no route\n");
		else
		{
			printf("%15s %2d; route: ","count of steps:",distances[destination]);
			for(i=destination,j=0; i!=departure; i=route[i],j++)
				queue[j]=i;
			printf("%d->",departure);
			for(j--; j>0; j--)
				printf("%d->",queue[j]);
			printf("%d\n",queue[j]);
		}
	}
	free(route);
	free(queue);
	free(visited);
	free(distances);	
}
void BellmanFord_Matrix(int** matrix,int size,int departure,int destination)
{
	int i,j,k;
	int* MinimalDistances=(int*)malloc(sizeof(int)*size);
	int* route=(int*)calloc(sizeof(int),size);
	for(i=0; i<size; i++)
		MinimalDistances[i]=10000;
	MinimalDistances[departure]=0;
	for(i=0; i<size; i++)
		for(j=0; j<size; ++j)
			for(k=0; k<size; ++k)
				if(matrix[j][k]>0 && MinimalDistances[k]>MinimalDistances[j]+matrix[j][k])
				{
					MinimalDistances[k]=MinimalDistances[j]+matrix[j][k];
					route[k]=j;
				}
	if(size<25)
	{
		if(MinimalDistances[destination]==10000)
			printf("there is no route\n");
		else
		{
			printf("%15s %2d; route: ","distance:",MinimalDistances[destination]);
			for(i=destination,j=0; i!=departure; i=route[i],j++)
				MinimalDistances[j]=i;
			MinimalDistances[j]=i;
			for(; j>0; j--)
				printf("%d->",MinimalDistances[j]);
			printf("%d\n",MinimalDistances[j]);		
		}
	}
	free(route);
	free(MinimalDistances);
}
void FloydWarshall_Matrix(int** matrix,int size,int departure,int destination)
{
	int i,j,k,**route=(int**)malloc(sizeof(int*)*size);
	int** MinimalDistances=(int**)malloc(sizeof(int*)*size);
	for(i=0; i<size; i++)
	{
		MinimalDistances[i]=(int*)malloc(sizeof(int)*size);
		route[i]=(int*)malloc(sizeof(int)*size);
		for(j=0; j<size; j++)
		{
			route[i][j]=j;
			MinimalDistances[i][j]=10000;
		}
	}
	for(i=0; i<size; i++)
		MinimalDistances[i][i]=0;
	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
			if(matrix[i][j]>0)
				MinimalDistances[i][j]=matrix[i][j];
	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
			for(k=0; k<size; k++)
				if(MinimalDistances[j][i] && MinimalDistances[i][k] && j!=k)
					if(MinimalDistances[j][i]+MinimalDistances[i][k]<MinimalDistances[j][k] || MinimalDistances[j][k]==0)
					{
						MinimalDistances[j][k]=MinimalDistances[j][i]+MinimalDistances[i][k];
						route[j][k]=route[j][i];
					}
	if(size<25)
	{
		if(MinimalDistances[departure][destination]==10000)
			printf("there is no route\n");
		else
		{
			printf("%15s %2d; route: ","distance:",MinimalDistances[departure][destination]);
			for(; destination!=departure; departure=route[departure][destination])
				printf("%d->",departure);
			printf("%d\n",departure);		
		}
	}
	for(i=0; i<size; i++)
	{
		free(route[i]);
		free(MinimalDistances[i]);
	}
	free(route);
	free(MinimalDistances);	
}
void Dijkstra_Matrix(int** matrix,int size,int departure,int destination)
{
	int* route=(int*)malloc(sizeof(int)*size);
	int i,j,k,minindex,end,prev,*visited=(int*)calloc(sizeof(int),size);
	int distance,MinimalDistance,*MinimalDistances=(int*)malloc(sizeof(int)*size);
	for(i=0; i<size; i++)
	{
		route[i]=-1;
		MinimalDistances[i]=10000;
	}
	MinimalDistances[departure]=0;
	do
	{
		MinimalDistance=10000;
		minindex=10000;		
		for(i=0; i<size; i++)
			if(visited[i]==0 && MinimalDistances[i]<MinimalDistance)
			{
				MinimalDistance=MinimalDistances[i];
				minindex=i;
			}
		if(MinimalDistance<10000)
		{
			for(i=0; i<size; i++)
				if(matrix[minindex][i]>0)
				{
					distance=MinimalDistance+matrix[minindex][i];
					if(distance<MinimalDistances[i])
					{
						MinimalDistances[i]=distance;
						route[i]=minindex;
					}
				}
			visited[minindex]=1;
		}
	}while(MinimalDistance<10000);
	if(size<25)
	{
		if(MinimalDistances[destination]==10000)
			printf("there is no route\n");
		else
		{
			printf("%15s %2d; route: ","distance:",MinimalDistances[destination]);
			for(i=0; i<size; i++)
				visited[i]=-1;
			for(i=destination,j=0; route[i]!=-1; i=route[i],j++)
				visited[j]=route[i];
			for(j--; j>-1; j--)
				printf("%d->",visited[j]);
			printf("%d\n",destination);
		}
	}
	free(route);
	free(visited);
	free(MinimalDistances);
}
void FisherYatesShuffle(int *array,int size)
{
	int i,j,k;
	for(i=size-1; i>=1; i--)
    {
		j=rand()%(i+1); 
        k=array[j];
        array[j]=array[i];
        array[i]=k;
    }
}
void CreateRandomGraph(int** graph,int size,int MinNumber,int MaxNumber,int NodesCount)
{
	int i,j,k,RandomDistance,column,row,StepSize,step=0,CountOfAddedNodes=0;
	int *indexes=(int*)malloc(sizeof(int)*size);
	printf("Count of required nodes: %6d;",NodesCount);
	i=(size*size-size)/2;
	if(i<NodesCount)
		NodesCount=i;
	StepSize=size/NodesCount;
	if(StepSize==0)
		StepSize=1;
	for(i=0; i<size; i++)
		indexes[i]=i;
	FisherYatesShuffle(indexes,size);
	for(i=0; i<size; i++)
		for(j=0; j<size; j++)
			graph[i][j]=0;	
	for(i=0,column=0,row=size-1; i<NodesCount;)
	{
		RandomDistance=MinNumber+rand()%(MaxNumber-MinNumber);
		if(row!=indexes[column] && graph[row][indexes[column]]==0 && graph[indexes[column]][row]==0)
		{
			graph[row][indexes[column]]=RandomDistance;
			graph[indexes[column]][row]=RandomDistance;
			CountOfAddedNodes++;
			i++;
		}
		else
			for(j=indexes[column],k=j+1; j>-1 || k<size; j--,k++)
				if(j>-1 && indexes[j]!=row && graph[row][indexes[j]]==0 && graph[indexes[j]][row]==0)
				{
					graph[row][indexes[j]]=RandomDistance;
					graph[indexes[j]][row]=RandomDistance;
					CountOfAddedNodes++;
					i++;
					break;
				}
				else
					if(k<size && indexes[k]!=row && graph[row][indexes[k]]==0 && graph[indexes[k]][row]==0)
					{
						graph[row][indexes[k]]=RandomDistance;
						graph[indexes[k]][row]=RandomDistance;
						CountOfAddedNodes++;
						i++;
						break;
					}
		row-=StepSize;
		column+=StepSize;
		if(row==-1)
		{
			row=size-1;
			column=0;
		}
	}	
	for(i=0,j=0,k=0,row=0; i<size; i++)
		for(j=0; j<size; j++)
			if(graph[i][j]>0 && graph[j][i]>0 && graph[i][j]==graph[j][i])
				k++;	
	printf(" count of added nodes: %6d = %6d\n",CountOfAddedNodes,k/2);
	free(indexes);
}
void CageOfGraph_Prim(int **graph,int size)
{//https://www.thecrazyprogrammer.com/2014/06/prims-algorithm-and-program-for-minimum-cost-spanning-tree.html
	int u,v,min_distance,no_of_edges,i,min_cost=0,j;
	int** EdgesOfSpanningTree=(int**)malloc(sizeof(int*)*size);
	int** cost=(int**)malloc(sizeof(int*)*size);
	int** spanning=(int**)malloc(sizeof(int*)*size);
	int* from=(int*)malloc(sizeof(int)*size);
	int* visited=(int*)malloc(sizeof(int)*size);
	int* distance=(int*)malloc(sizeof(int)*size);
	printf("Building of the spanning tree (Prim algorithm)...");
	for(i=0; i<size; i++)//create cost[][] matrix,spanning[][]
	{
		cost[i]=(int*)malloc(sizeof(int)*size);
		spanning[i]=(int*)malloc(sizeof(int)*size);	
		EdgesOfSpanningTree[i]=(int*)malloc(sizeof(int)*3);
		for(j=0;j<size;j++)
		{
			if(graph[i][j]==0)
				cost[i][j]=INT_MAX;
			else
				cost[i][j]=graph[i][j];
			spanning[i][j]=0;
		}
	}		
	distance[0]=0;//initialise visited[],distance[] and from[]
	visited[0]=1;
	for(i=1;i<size;i++)
	{
		distance[i]=cost[0][i];
		from[i]=0;
		visited[i]=0;
	}
	no_of_edges=size-1; //cost of spanning tree	
	for(j=0; no_of_edges>0; j++,no_of_edges--)
	{//find the vertex at minimum distance from the tree		
		min_distance=INT_MAX;
		for(i=1;i<size;i++)
			if(visited[i]==0&&distance[i]<min_distance)
			{
				v=i;
				min_distance=distance[i];
			}
		u=from[v];
		//insert the edge in spanning tree
		spanning[u][v]=distance[v];
		spanning[v][u]=distance[v];
		visited[v]=1;
		//updated the distance[] array
		for(i=1;i<size;i++)
			if(visited[i]==0&&cost[i][v]<distance[i])
			{
				distance[i]=cost[i][v];
				from[i]=v;
			}
		EdgesOfSpanningTree[j][0]=u;
		EdgesOfSpanningTree[j][1]=v;
		EdgesOfSpanningTree[j][2]=cost[u][v];
		min_cost=min_cost+cost[u][v];
	}	
	if(size<21)
	{
		for(i=0,putchar('\n'); i<j; i++)
			printf("%2d. %3d; %3d: %3d\n",i+1,EdgesOfSpanningTree[i][0],EdgesOfSpanningTree[i][1],EdgesOfSpanningTree[i][2]);
		printf("Cost of the spanning tree: %d\n",min_cost);
	}
	else
		printf(" Cost: %d\n",min_cost);
	for(i=0; i<size; i++)
	{
		free(cost[i]);
		free(spanning[i]);		
		free(EdgesOfSpanningTree[i]);
	}		
	free(from);
	free(cost);
	free(visited);
	free(distance);
	free(spanning);	
	free(EdgesOfSpanningTree);
}
void SortEdgesRadixSortLSD(int** array,int n)//https://habr.com/ru/post/533206/
{		
	char* b;
	int** TempArray=(int**)malloc(sizeof(int*)*n);//Память под временный массив
	int* baskets=(int*)calloc(sizeof(int*),1024);
	int i,value,digit,off,*key,*temp;
	for(i=0; i<n; ++i)//Заполняем массив корзин для всех разрядов
	{
		off=array[i][2];
		for(digit=0; digit<4; digit++)		
			baskets[((off>>(digit*8))&0xFF)+256*digit]++;		
	}	
	for(digit=0; digit<4; digit++)//Пересчитываем смещения для корзин
	{
		off=0;
		for(i=0; i<256; i++)
		{
			value=baskets[i+256*digit];
			baskets[i+256*digit]=off;
			off+=value;
		}
	}
	for(i=0,b=(char*)&array[n],temp=&baskets[0]; i<n; ++i)
	{
		key=array[i];
		off=(key[2]>>(0))&0xFF;
		TempArray[temp[off]++]=key;
	}	
	for(i=0,b=(char*)&TempArray[n]+1,temp=&baskets[256]; i<n; ++i)
	{
		key=TempArray[i];
		off=(key[2]>>(8))&0xFF;
		array[temp[off]++] =key;
	}
	free(baskets);
	free(TempArray);
}
void CageOfGraph_Kruskal(int **graph,int size)
{//https://www.thecrazyprogrammer.com/2014/03/kruskals-algorithm-for-finding-minimum-cost-spanning-tree.html
	int i,j,temp,EdgesCount=0,SpanningTreeEdgesCount=0;
	int* belongs=(int*)malloc(sizeof(int)*size);
	int** edges=(int**)malloc(sizeof(int*)*size*size);
	int** SpanningTree=(int**)malloc(sizeof(int*)*size*size);
	printf("Building of the spanning tree (Kruskal algorithm)...");
	for(i=1; i<size; i++)
	{
		for(j=0; j<i; j++)
			if(graph[i][j]!=0)
			{
				edges[EdgesCount]=(int*)malloc(sizeof(int)*3);
				edges[EdgesCount][0]=i;
				edges[EdgesCount][1]=j;
				edges[EdgesCount][2]=graph[i][j];
				EdgesCount++;
			}
		belongs[i-1]=i-1;
	}
	belongs[i-1]=i-1;
	SortEdgesRadixSortLSD(edges,EdgesCount);
	for(i=0; i<EdgesCount; i++)
	{
		temp=belongs[edges[i][1]];//find(belongs,edges[i][1]);
		if(belongs[edges[i][0]]!=belongs[edges[i][1]])
		{			
			SpanningTree[SpanningTreeEdgesCount]=edges[i];
			SpanningTreeEdgesCount++;
			for(j=0; j<size; j++)
				if(belongs[j]==temp)
					belongs[j]=belongs[edges[i][0]];//cno1;
		}
	}
	if(size<21)
	{
		for(i=0,j=0,putchar('\n'); i<SpanningTreeEdgesCount; i++)
		{
			printf("%2d. %3d; %3d: %3d\n",i+1,SpanningTree[i][0],SpanningTree[i][1],SpanningTree[i][2]);
			j=j+SpanningTree[i][2];
		}
		printf("Cost of the spanning tree: %d\n",j);
	}
	else
	{
		for(i=0,j=0; i<SpanningTreeEdgesCount; i++)			
			j=j+SpanningTree[i][2];
		printf("Cost: %d\n",j);
	}
	for(i=0; i<EdgesCount; i++)
		free(edges[i]);	
	free(edges);
	free(SpanningTree);
}	
void TestBigGraph(int **graph,int size,int NodesCount,FILE* f)
{
	int i,j,MinNumber=1,MaxNumber=size;
	int* DeparturePoints=(int*)malloc(sizeof(int)*size);
	int* DestinationPoints=(int*)malloc(sizeof(int)*size);
	int* route=(int*)malloc(sizeof(int)*size);
	int* StepsCounts=(int*)malloc(sizeof(int)*size);
	char* visited=(char*)malloc(sizeof(char)*size);
	DWORD StartTimeMsec,EndTimeMsec;
	DWORD Dijkstra=0,BellmanFord=0,FloydWarshall=0,DepthSearch=0,BreadthSearch=0;
	for(i=0; i<size; i++)
		DeparturePoints[i]=DestinationPoints[i]=i;
	FisherYatesShuffle(DeparturePoints,size);
	FisherYatesShuffle(DestinationPoints,size);	
	printf("Size of matrix: %6d; maximum count of nodes: %6d;\n",size,(size*size-size)/2);
	CreateRandomGraph(graph,size,MinNumber,MaxNumber,NodesCount);
	printf("================================================================================");
	for(i=0; i<10; i++)
	{
		if(DeparturePoints[i]==DestinationPoints[i])
			continue;		
		printf("Dijkstra...");
		StartTimeMsec=GetTickCount();
		Dijkstra_Matrix(graph,size,DeparturePoints[i],DestinationPoints[i]);
		EndTimeMsec=GetTickCount()-StartTimeMsec;
		Dijkstra+=EndTimeMsec;		
		printf(" Bellman-Ford...");
		StartTimeMsec=GetTickCount();
		BellmanFord_Matrix(graph,size,DeparturePoints[i],DestinationPoints[i]);
		EndTimeMsec=GetTickCount()-StartTimeMsec;
		BellmanFord+=EndTimeMsec;		
		printf(" Floyd-Warshall...");
		StartTimeMsec=GetTickCount();
		FloydWarshall_Matrix(graph,size,DeparturePoints[i],DestinationPoints[i]);
		EndTimeMsec=GetTickCount()-StartTimeMsec;
		FloydWarshall+=EndTimeMsec;
		if(NodesCount<=size)
		{
			printf(" Depth search...");
			for(j=0; j<size; j++)
			{
				visited[j]=0;
				route[j]=0;
				StepsCounts[j]=0;
			}
			StartTimeMsec=GetTickCount();
			MinNumber=DepthFirstSearch(graph,visited,route,StepsCounts,size,DeparturePoints[i],DestinationPoints[i],0)+1;
			EndTimeMsec=GetTickCount()-StartTimeMsec;
			DepthSearch+=EndTimeMsec;
		}
		else
			DepthSearch=SHRT_MAX;
		printf(" Breadth search...");
		StartTimeMsec=GetTickCount();
		BreadthFirstSearch_Matrix(graph,size,DeparturePoints[i],DestinationPoints[i]);
		EndTimeMsec=GetTickCount()-StartTimeMsec;
		BreadthSearch+=EndTimeMsec;
		putchar('\n');
	}
	fprintf(f,"%21d %20d %20d ",Dijkstra/10,BellmanFord/10,FloydWarshall/10);
	if(DepthSearch<SHRT_MAX)
		fprintf(f,"%20d ",DepthSearch/10);
	else
		fprintf(f,"%20c ",' ');	
	fprintf(f,"%20d ",BreadthSearch/10);
	if(NodesCount>size)
	{
		StartTimeMsec=GetTickCount();
		CageOfGraph_Prim(graph,size);
		EndTimeMsec=GetTickCount()-StartTimeMsec;
		fprintf(f,"%20d ",EndTimeMsec);
		StartTimeMsec=GetTickCount();
		CageOfGraph_Kruskal(graph,size);
		EndTimeMsec=GetTickCount()-StartTimeMsec;
		fprintf(f,"%20d\n",EndTimeMsec);
	}
	else
		fprintf(f,"\n");
	free(DestinationPoints);
	free(DeparturePoints);
	free(StepsCounts);
	free(visited);
	free(route);
}
void TestRandomGraphs()
{
	int i,j,size=20,EdgesCount=50,MinNumber=1,MaxNumber=size,StepsCount;	
	int* DeparturePoints=(int*)malloc(sizeof(int)*size);
	int* DestinationPoints=(int*)malloc(sizeof(int)*size);
	int* route=(int*)malloc(sizeof(int)*size);
	int* StepsCounts=(int*)malloc(sizeof(int)*size);
	char* visited=(char*)malloc(sizeof(char)*size);
	int** graph=(int**)malloc(sizeof(int*)*size);
	FILE* f=fopen("results.txt","w");
	srand(time(0));
	for(i=0; i<size; i++)
	{
		graph[i]=(int*)malloc(sizeof(int)*size);
		DeparturePoints[i]=DestinationPoints[i]=i;
	}
	FisherYatesShuffle(DeparturePoints,size);
	FisherYatesShuffle(DestinationPoints,size);	
	printf("Size of matrix: %6d; maximum count of nodes: %6d;\n",size,(size*size-size)/2);
	CreateRandomGraph(graph,size,MinNumber,MaxNumber,EdgesCount);
	printf("================================================================================");
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
			printf("%3d",graph[i][j]);
		putchar('\n');
	}
	printf("================================================================================");
	for(i=0; i<size; i++)
	{
		if(DeparturePoints[i]==DestinationPoints[i])
			continue;		
		printf("Departure point: %3d; destination point: %3d;\n",DeparturePoints[i],DestinationPoints[i]);
		printf("%25s","Dijkstra: ");
		Dijkstra_Matrix(graph,size,DeparturePoints[i],DestinationPoints[i]);
		printf("%25s","Bellman-Ford: ");
		BellmanFord_Matrix(graph,size,DeparturePoints[i],DestinationPoints[i]);
		printf("%25s","Floyd-Warshall: ");
		FloydWarshall_Matrix(graph,size,DeparturePoints[i],DestinationPoints[i]);
		printf("%25s","Depth first search: ");		
		for(j=0; j<size; j++)
		{
			visited[j]=0;				
			route[j]=0;
			StepsCounts[j]=0;
		}
		MinNumber=DepthFirstSearch(graph,visited,route,StepsCounts,size,DeparturePoints[i],DestinationPoints[i],0)+1;
		if(MinNumber==0)
			printf("there is no route\n");
		else
		{
			printf("%15s %2d; route: ","count of steps:",MinNumber);
			DepthFirstSearchShowRoute_Matrix(route,DeparturePoints[i],DestinationPoints[i]);
		}
		printf("%25s","Breadth-first search:");
		BreadthFirstSearch_Matrix(graph,size,DeparturePoints[i],DestinationPoints[i]);
		printf("--------------------------------------------------------------------------------");
	}
	CageOfGraph_Prim(graph,size);
	CageOfGraph_Kruskal(graph,size);
	for(i=0; i<size; i++)
		free(graph[i]);	
	free(DestinationPoints);
	free(DeparturePoints);	
	free(StepsCounts);
	free(visited);
	free(route);
	free(graph);
	size=1000;
	MaxNumber=(size*size-size)/2;
	graph=(int**)malloc(sizeof(int*)*size);
	for(i=0; i<size; i++)
		graph[i]=(int*)malloc(sizeof(int)*size);
	fprintf(f,"Size of matrix: %6d; maximum count of nodes: %6d\n",size,MaxNumber);
	fprintf(f,"%18s %20s %20s %20s %20s %20s %20s %20s\n","TYPE OF GRAPH","Dijkstra","Bellman-Ford","Floyd-Warshall","Depth first search","Breadth first search","Prim algorithm","Kruskal algorithm");	
	printf("==========================TEST OF THE DISCONNECTED GRAPH========================");
	fprintf(f,"%18s","DISCONNECTED GRAPH");
	TestBigGraph(graph,size,size-10,f);	
	printf("===========================TEST OF THE CONNECTED GRAPH==========================");
	fprintf(f,"%18s","CONNECTED GRAPH");
	TestBigGraph(graph,size,size,f);
	printf("===========================TEST OF THE HALF FULL GRAPH==========================");
	fprintf(f,"%18s","HALF FULL GRAPH");
	TestBigGraph(graph,size,MaxNumber/2,f);	
	printf("=============================TEST OF THE FULL GRAPH=============================");
	fprintf(f,"%18s","FULL GRAPH");
	TestBigGraph(graph,size,MaxNumber,f);
	fclose(f);
	for(i=0; i<size; i++)
		free(graph[i]);
	free(graph);
	printf("The file results.txt was created.\n");
}
int main(void)
{
	FILE* f=fopen("map.txt","r");
	int** graph;
	char* visited;
	double AverageDistance,**WeightedGraph;
	int i,j,k,*route,*StepsCounts,DistanceNumber,RoadTypeNumber,TownsCount=0,RoutesCount=0;
	char ch='a',*input=(char*)calloc(sizeof(char),20);
	struct town** towns=(struct town**)malloc(sizeof(struct town)),**SortedTowns;
	struct route** routes=(struct route**)malloc(sizeof(struct route));
	while(ch!='-')
	{
		towns=(struct town**)realloc(towns,(TownsCount+1)*sizeof(struct town*));
		towns[TownsCount]=(struct town*)malloc(sizeof(struct town));
		towns[TownsCount]->name=(char*)calloc(sizeof(char),30);
		i=-1;
		fscanf(f,"%c",&ch);
		while(!isdigit(ch) && ch!='-')
		{
			i++;
			towns[TownsCount]->name[i]=ch;
			fscanf(f,"%c",&ch);
		}
		towns[TownsCount]->name[i]=0;
		if(ch=='-')
		{
			routes[0]=(struct route*)malloc(sizeof(struct route));
			for(i=0; strcmp(towns[i]->name,towns[TownsCount]->name); i++);
			routes[0]->departure=i;
			free(towns[TownsCount]->name);
			free(towns[TownsCount]);
			break;
		}		
		i=1;
		input[0]=ch;		
		fscanf(f,"%c",&ch);
		while(ch!=' ')
		{			
			input[i]=ch;			
			fscanf(f,"%c",&ch);
			i++;
		}
		input[i]=0;
		towns[TownsCount]->latitude=atof(input);
		for(; i>-1; i--)
			input[i]=0;
		i=0;
		fscanf(f,"%c",&ch);
		while(ch!=' ')
		{			
			input[i]=ch;			
			fscanf(f,"%c",&ch);
			i++;
		}
		towns[TownsCount]->longitude=atof(input);
		for(; i>-1; i--)
			input[i]=0;
		i=0;
		fscanf(f,"%c",&ch);
		while(ch!=10)
		{			
			input[i]=ch;			
			fscanf(f,"%c",&ch);
			i++;
		}
		input[i]=0;
		towns[TownsCount]->population=atoi(input);
		//printf("Name: %s; latitude: %.2lf; longitude: %.2lf; population: %d;\n",towns[TownsCount]->name,towns[TownsCount]->latitude,towns[TownsCount]->longitude,towns[TownsCount]->population);
		TownsCount++;
	}	//printf("---------------------------------------------------------------------------\n");
	while(!feof(f))
	{
		fscanf(f,"%c",&ch);
		fscanf(f,"%c",&ch);
		i=-1;
		for(i=0; i<20; i++)
			input[i]=0;
		i=-1;
		while(!isdigit(ch))
		{
			i++;
			input[i]=ch;
			fscanf(f,"%c",&ch);			
		}
		input[i]=0;
		for(i=0; strcmp(input,towns[i]->name); i++);
		routes[RoutesCount]->destination=i;
		DistanceNumber=0;
		RoadTypeNumber=0;
		routes[RoutesCount]->distances=(double**)calloc(sizeof(double*),3);
		routes[RoutesCount]->distances[RoadTypeNumber]=(double*)calloc(sizeof(double),13);
		while(ch!=10 && !feof(f))
		{
			for(i=0; i<10; i++)
				input[i]=0;			
			i=-1;			
			while(ch!=' ' && ch!=';' && ch!=10 && !feof(f))
			{
				i++;
				input[i]=ch;
				fscanf(f,"%c",&ch);
			}
			routes[RoutesCount]->distances[RoadTypeNumber][DistanceNumber]=atof(input);
			if(ch==10 || feof(f))
				break;
			if(ch==';')
			{
				RoadTypeNumber++;
				routes[RoutesCount]->distances[RoadTypeNumber]=(double*)calloc(sizeof(double),13);
				DistanceNumber=-1;
				fscanf(f,"%c",&ch);
			}
			DistanceNumber++;
			fscanf(f,"%c",&ch);
		}
		for(i=1,AverageDistance=0; routes[RoutesCount]->distances[0][i]!=0; i++)
			AverageDistance+=routes[RoutesCount]->distances[0][i];
		InsertionSort(routes[RoutesCount]->distances[0],i-1);
		routes[RoutesCount]->distances[0][i]=AverageDistance/(i-1);
		for(i=0,AverageDistance=0; routes[RoutesCount]->distances[1][i]!=0; i++)
			AverageDistance+=routes[RoutesCount]->distances[1][i];
		InsertionSort(routes[RoutesCount]->distances[1],i);
		routes[RoutesCount]->distances[1][i]=AverageDistance/i;
		if(routes[RoutesCount]->distances[2]!=NULL)
		{
			for(i=0,AverageDistance=0; routes[RoutesCount]->distances[2][i]!=0; i++)
				AverageDistance+=routes[RoutesCount]->distances[2][i];
			InsertionSort(routes[RoutesCount]->distances[2],i);
			routes[RoutesCount]->distances[2][i]=AverageDistance/i;
		}
		/*printf("%d. Departure: %s; destination: %s; ",RoutesCount+1,towns[routes[RoutesCount]->departure]->name,towns[routes[RoutesCount]->destination]->name);
		printf("distances:\ndirect distance: %.2lf",routes[RoutesCount]->distances[0][0]);
		printf("\nhighway disances: ");
		for(i=1; routes[RoutesCount]->distances[0][i+1]!=0; i++)
			printf("%.2lf ",routes[RoutesCount]->distances[0][i]);
		printf("\naverage highway distance: %.2lf\nfoot path distances: ",routes[RoutesCount]->distances[0][i]);
		for(i=0; routes[RoutesCount]->distances[1][i+1]!=0; i++)
			printf("%.2lf ",routes[RoutesCount]->distances[1][i]);		
		printf("\naverage foot path distance: %.2lf",routes[RoutesCount]->distances[1][i]);
		if(routes[RoutesCount]->distances[2]!=NULL)
		{
			printf("\nrailway distances: ");
			for(i=0; routes[RoutesCount]->distances[2][i+1]!=0; i++)
				printf("%.2lf ",routes[RoutesCount]->distances[2][i]);
			printf("\naverage railway distance: %.2lf",routes[RoutesCount]->distances[2][i]);
		}		
		printf("\n---------------------------------------------------------------------------\n");*/
		if(feof(f))
			break;
		RoutesCount++;
		routes=(struct route**)realloc(routes,(RoutesCount+1)*sizeof(struct route*));
		routes[RoutesCount]=(struct route*)malloc(sizeof(struct route));
		for(i=0; i<20; i++)
			input[i]=0;
		fscanf(f,"%c",&ch);
		i=-1;
		while(ch!='-')
		{
			i++;
			input[i]=ch;
			fscanf(f,"%c",&ch);			
		}
		input[i]=0;
		for(i=0; strcmp(input,towns[i]->name); i++);
		routes[RoutesCount]->departure=i;
	}
	RoutesCount++;	
	graph=(int**)malloc(sizeof(int*)*TownsCount);	
	WeightedGraph=(double**)malloc(sizeof(double*)*TownsCount);
	route=(int*)malloc(sizeof(int*)*TownsCount);
	StepsCounts=(int*)malloc(sizeof(int*)*TownsCount);
	for(i=0; i<TownsCount; i++)
	{
		graph[i]=(int*)calloc(sizeof(int),TownsCount);
		WeightedGraph[i]=(double*)calloc(sizeof(double),TownsCount);
	}
	for(i=0; i<RoutesCount; i++)
		graph[routes[i]->departure][routes[i]->destination]=1;
	visited=(char*)calloc(sizeof(char),TownsCount);
	SortedTowns=(struct town**)malloc(sizeof(struct town*)*TownsCount);
	ch=0;
	while(ch!='8')
	{
		printf("1. Visit all towns starting the route from Mykolaiv;\n2. Find a route without taking a distance into account;\n3. Find the shortest route;\n4. Show towns from the west to the east;\n5. Show towns from the north to the south;\n6. Show towns according to the population;\n7. Test random graphs;\n8. Exit.\nYour choice: ");		
		ch=_getche();
		while(ch<'1' || ch>'8')
		{
			printf("\npress a correct digit: ");
			ch=_getche();
		}
		putchar('\n');
		switch(ch)
		{
			case '1':
			VisitAllTowns(graph,visited,towns,TownsCount,0);
			for(i=0; i<TownsCount; i++)
				visited[i]=0;
			putchar('\n');
			break;
			case '2':
			DistanceNumber=GetTownsNumber(0,towns,TownsCount);
			if(DistanceNumber==TownsCount)
				break;
			RoadTypeNumber=GetTownsNumber(1,towns,TownsCount);
			if(RoadTypeNumber==TownsCount)
				break;
			while(RoadTypeNumber==DistanceNumber)
			{
				printf("Departure and destination towns can not be equal,try again.\n");
				DistanceNumber=GetTownsNumber(0,towns,TownsCount);
				if(DistanceNumber==TownsCount)
					break;
				RoadTypeNumber=GetTownsNumber(1,towns,TownsCount);
				if(RoadTypeNumber==TownsCount)
					break;
			}
			if(DistanceNumber==TownsCount || RoadTypeNumber==TownsCount)				
				break;
			for(i=0; i<TownsCount; i++)
			{
				visited[i]=0;				
				route[i]=0;
				StepsCounts[i]=0;
			}
			i=DepthFirstSearch(graph,visited,route,StepsCounts,TownsCount,DistanceNumber,RoadTypeNumber,0)+1;
			printf("%s - %s;\nDEPTH-FIRST SEARCH: ",towns[DistanceNumber]->name,towns[RoadTypeNumber]->name);
			if(i==-1)
			{
				printf("there is no route\n");
				break;
			}
			else
			{
				printf("minimal count of steps is %d;\nroute: ",i);
				DepthFirstSearchShowRoute(route,towns,DistanceNumber,RoadTypeNumber);
			}
			printf("---------------------------------------------------------------------------------\n");
			BreadthFirstSearch(graph,towns,TownsCount,DistanceNumber,RoadTypeNumber);
			printf("---------------------------------------------------------------------------------\n");
			break;
			case '3':
			DistanceNumber=GetTownsNumber(0,towns,TownsCount);
			if(DistanceNumber==TownsCount)
				break;
			RoadTypeNumber=GetTownsNumber(1,towns,TownsCount);
			if(RoadTypeNumber==TownsCount)
				break;
			while(RoadTypeNumber==DistanceNumber)
			{
				printf("Departure and destination towns can not be equal,try again.\n");
				DistanceNumber=GetTownsNumber(0,towns,TownsCount);
				if(DistanceNumber==TownsCount)
					break;
				RoadTypeNumber=GetTownsNumber(1,towns,TownsCount);
				if(RoadTypeNumber==TownsCount)
					break;
			}
			if(DistanceNumber==TownsCount || RoadTypeNumber==TownsCount)				
				break;
			printf("Type of road:\n0. Direct route;\n1. The shortest highway;\n2. The longest highway;\n3. Average length of all highways;\n4. The shortest foot path;\n5. The longest foot path;\n6. Average length of all foot paths;\n7. The shortest railway;\n8. The longest railway;\n9. Average length of all railways;\nYour choice: ");
			ch=_getche();
			while(ch<'0' || ch>'9')
			{
				printf("\npress a correct digit: ");
				ch=_getche();
			}
			for(i=0; i<TownsCount; i++)
			{
				for(j=0; j<TownsCount; j++)
					WeightedGraph[i][j]=0;
			}
			for(i=0; i<RoutesCount; i++)
			{
				switch(ch)
				{
					case '0': AverageDistance=routes[i]->distances[0][0]; break;
					case '1': AverageDistance=routes[i]->distances[0][1]; break;
					case '2': for(j=0; AverageDistance=routes[i]->distances[0][j]!=0; j++);
					AverageDistance=routes[i]->distances[0][j-2]; break;
					case '3': for(j=0; AverageDistance=routes[i]->distances[0][j]!=0; j++);
					AverageDistance=routes[i]->distances[0][j-1]; break;
					case '4': AverageDistance=routes[i]->distances[1][0]; break;
					case '5': for(j=0; AverageDistance=routes[i]->distances[1][j]!=0; j++);
					AverageDistance=routes[i]->distances[1][j-2]; break;
					case '6': for(j=0; AverageDistance=routes[i]->distances[1][j]!=0; j++);
					AverageDistance=routes[i]->distances[1][j-1]; break;
					case '7':
					if(AverageDistance=routes[i]->distances[2]==NULL)
						AverageDistance=0;
					else
						AverageDistance=AverageDistance=routes[i]->distances[2][0];
					break;
					case '8':
					if(AverageDistance=routes[i]->distances[2]==NULL)
						AverageDistance=0;
					else
					{
						for(j=0; AverageDistance=routes[i]->distances[2][j]!=0; j++);
						AverageDistance=routes[i]->distances[2][j-2];
					}
					break;
					case '9':
					if(AverageDistance=routes[i]->distances[2]==NULL)
						AverageDistance=0;
					else
					{
						for(j=0; AverageDistance=routes[i]->distances[2][j]!=0; j++);
						AverageDistance=routes[i]->distances[2][j-1];
					}
					break;
				}
				WeightedGraph[routes[i]->departure][routes[i]->destination]=AverageDistance;
			}
			putchar('\n');
			BellmanFord(WeightedGraph,towns,TownsCount,DistanceNumber,RoadTypeNumber);
			FloydWarshall(WeightedGraph,towns,TownsCount,DistanceNumber,RoadTypeNumber);
			Dijkstra(WeightedGraph,towns,TownsCount,DistanceNumber,RoadTypeNumber);
			break;
			case '4':
			for(i=0; i<TownsCount; i++)
				SortedTowns[i]=towns[i];
			InsertionSortingOfTowns(towns,TownsCount,0);
			putchar('\n');
			break;
			case '5':
			for(i=0; i<TownsCount; i++)
				SortedTowns[i]=towns[i];
			InsertionSortingOfTowns(towns,TownsCount,1);
			putchar('\n');
			break;
			case '6':
			for(i=0; i<TownsCount; i++)
				SortedTowns[i]=towns[i];
			InsertionSortingOfTowns(towns,TownsCount,2);
			putchar('\n');
			break;
			case '7':
			TestRandomGraphs();
			break;
		}		
	}
	for(i=0; i<TownsCount; i++)
	{		
		free(towns[i]->name);
		free(towns[i]);
		free(WeightedGraph[i]);
		free(graph[i]);
	}
	for(i=0; i<RoutesCount; i++)
	{
		for(j=0; j<2; j++)
			free(routes[i]->distances[j]);
		if(routes[i]->distances[2])
			free(routes[i]->distances[2]);
		free(routes[i]->distances);
		free(routes[i]);
	}
	free(WeightedGraph);
	free(graph);
	free(input);
	free(routes);
	free(towns);
	free(visited);
	free(route);
	free(StepsCounts);
	fclose(f);
	return 0;
}
