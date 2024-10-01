//9. Внесем некоторое разнообразие в пример HORSE из главы 10, создав класс для внесения в него лошадей экстракласса. Предположим, что любая лошадь, которая на скачках к середине дистанции находится впереди всех, становится практически непобедимой. Относительно класса лошадей создадим порожденный класс comhorse (для конкурентоспособной лошади). Перегрузим функцию horse_tick() в этом классе таким образом, чтобы каждая лошадь могла проверять, является ли она ведущей и нет ли поблизости соперников (скажем, ближе, чем на 0.1 форлонг (1/80 часть мили или 20.1 м.)). Если есть, то ей следует немного ускориться. Может быть, не настолько, чтобы побеждать на всех скачках, но в достаточной мере для того, чтобы оставаться конкурентоспособной. Как каждая лошадь узнает, где находятся остальные? Моделирующий ее объект должен иметь доступ к области памяти, в которой хранятся данные о соперниках. В программе HORSE это hArray. Будьте внимательны: вы создаете класс для передовой лошади, он должен быть наследником класса всех лошадей. Поэтому классу comhorse потребуется перегрузить hArray. Вам может потребоваться создать еще один производный класс, comtrack, для отслеживания позиции лошади. Можно непрерывно проверять, лидирует ли ваша лошадь, и если она впереди всех, но лишь ненамного, следует ее немного ускорить.
#include "msoftcon.h" //for console graphics
#include "../../accessories.h"
const int CPF=5;
class track;
class horse
{
	protected:
	const track* ptrTrack;
	const int horse_number;
	bool state;
	float finish_time;
	float distance_run;
	public:
	horse(const int n,const track* ptrT):horse_number(n),ptrTrack(ptrT),distance_run(0.0),state(true){}
	~horse(){}
	float GetState(){return state;}
	float GetRanDistance(){return distance_run;}
	void display_horse()
	{
		set_cursor_pos(1,3+horse_number);
		for(int i=0; i<2+int(distance_run*CPF); i++)
			cout<<" ";
		set_color(static_cast<color>(cGREEN+horse_number));
		char horse_char='0'+static_cast<char>(horse_number);
		putch(' '); putch('\xDB'); putch(horse_char); putch('\xDB');
		if(state==false)
		{
			int minutes=(int)finish_time/60;
			int seconds=(int)finish_time-minutes*60;
			cout<<" Time: " <<minutes<<":"<<seconds;		
		}
	}
	void horse_tick(const float elapsed_time);
};
class comhorse: public horse
{
	bool CompetitiveHorse;
	horse** horses;
	int CountOfHorses;
	public:
	comhorse(int number,track* ptrT,horse** AllHorses,int NewCountOfHorses):CompetitiveHorse(false),horses(AllHorses),CountOfHorses(NewCountOfHorses),horse(number,ptrT){}
	void horse_tick(float elapsed_time);
	void SetCompetitiveHorse(){CompetitiveHorse=true;}
	void display_horse()
	{		
		horse::display_horse();		
		if(CompetitiveHorse)		
			cout<<" COMPETITIVE HORSE";				
	}
};
class track
{
	comhorse** hArray;
	int total_horses;
	int horse_count;
	const float track_length;
	float elapsed_time;
	public:
	track(float lenT,int nH):track_length(lenT),total_horses(nH),horse_count(0),elapsed_time(0.0)
	{
		hArray=new comhorse*[total_horses];
		horse** horses=(horse**)hArray;
		for(int j=0; j<total_horses; j++)
			hArray[j]=new comhorse(horse_count++,this,horses,total_horses);
		time_t aTime;
		srand(static_cast<unsigned>(time(&aTime)));
		display_track();
	}	
	~track()
	{
		for(int j=0; j<total_horses; j++)
			delete hArray[j];
		delete[]hArray;
	}
	void display_track()
	{
		int i;
		for(int f=0; f<=track_length; f++)
			for(int r=3,i=0; i<total_horses; r++,i++)
			{
				set_cursor_pos(f*CPF+5,r);
				if(f==0 || f==track_length)
					cout<<'\xDE';
				else
					cout<<'\xB3';
			}
	}
	void run()
	{
		bool finish=false;
		float MaxRanDistance,RanDistance;
		int i,CompetitiveHorseNumber=total_horses;
		while(!finish && CompetitiveHorseNumber==total_horses)
		{
			elapsed_time+=1.75;
			finish=true;
			MaxRanDistance=track_length/2;
			for(i=0; i<total_horses; i++)
			{				
				hArray[i]->horse_tick(elapsed_time);
				hArray[i]->display_horse();
				if(hArray[i]->GetState())
					finish=false;
				RanDistance=hArray[i]->GetRanDistance();
				if(RanDistance>MaxRanDistance)
				{
					MaxRanDistance=RanDistance;
					CompetitiveHorseNumber=i;
				}					
			}				
			wait(10);
		}
		hArray[CompetitiveHorseNumber]->SetCompetitiveHorse();
		while(!finish)
		{
			elapsed_time+=1.75;
			finish=true;
			for(i=0; i<total_horses; i++)
			{				
				hArray[i]->horse_tick(elapsed_time);
				hArray[i]->display_horse();
				if(hArray[i]->GetState())
					finish=false;
			}
			wait(10);
		}
	}
	float get_track_len()const{return track_length;}
};
void horse::horse_tick(float elapsed_time)
{
	if(distance_run<ptrTrack->get_track_len()+1.0/CPF)
	{
		if(rand()%3)
			distance_run+=0.2F;
		finish_time=elapsed_time;
	}
	else
		state=false;
}
void comhorse::horse_tick(float elapsed_time)
{
	horse::horse_tick(elapsed_time);	
	if(CompetitiveHorse==true && distance_run<ptrTrack->get_track_len()+1.0/CPF)
	{		
		for(int i=0; i<CountOfHorses; i++)
			if(horse_number!=i && distance_run-horses[i]->GetRanDistance()<0.5)
			{				
				distance_run+=0.2F;				
				break;
			}
	}
}
int main()
{
	float TrackLength;
	int CountOfHorses;
	char ch=0;
	InitFloatingPointAndRandomNumbers();
	init_graphics();
	while(ch!='0')
	{
		TrackLength=GetRandomFloat(1,12);
		CountOfHorses=GetRandomInt(2,6);
		clear_screen();
		cout<<"Distance: "<<TrackLength<<"\nCount of horses: "<<CountOfHorses;
		track NewTrack(TrackLength,CountOfHorses);
		NewTrack.run();
		set_color(static_cast<color>(cWHITE));
		cout<<"\nPress 1 to start again or 0 to exit: ";
		ch=getch();
		while(ch!='0' && ch!='1')		
			ch=getch();		
		cout<<ch<<endl;
	}
	return 0;
}