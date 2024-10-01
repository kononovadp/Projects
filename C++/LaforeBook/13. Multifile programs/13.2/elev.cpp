#include "elev.h"
int GetIntFromKeyboard(int MinInt,int MaxInt)
{
	int i,result=MinInt-1;
	char ch=0;
	bool InputIsCorrect;
	string input,MaxNumber=to_string(MaxInt);	
	while(result<MinInt)
	{
		ch=getch();
		while(ch!=13)
		{
			InputIsCorrect=false;
			if(ch==27)
				exit(0);
			else
				if(ch==8 && input.length()>0)
				{
					cout<<"\b \b";
					input.pop_back();
				}
				else
					if(isdigit(ch))
					{
						if(input.length()+1<MaxNumber.length())
							InputIsCorrect=true;
						else
							if(input.length()+1==MaxNumber.length())
							{
								for(i=0; i<input.length(); i++)						
									if(input[i]<MaxNumber[i])
									{
										InputIsCorrect=true;
										break;
									}
									else
										if(input[i]>MaxNumber[i])
											break;
								if(i==input.length() && ch<=MaxNumber[MaxNumber.length()-1])
										InputIsCorrect=true;
							}
							if(input[0]=='0' && ch=='0')
								InputIsCorrect=false;
					}
					if(InputIsCorrect)
					{
						input+=ch;
						cout<<ch;
					}
					ch=getch();
		}
		if(input.length()==0)
		{
			result=0;
			cout<<result;
		}
		else
			result=stoi(input);
		if(result<MinInt)
			cout<<"\nInput number can't be less than "<<MinInt<<", try again: ";
	}
	return result;
}
building::building() //конструктор
{
	char ustring[BUF_LENGTH]; //строка для номеров этажей
	init_graphics(); //инициализация графики
	clear_screen(); //очистка экрана
	/*num_cars=0;
	for(int k=0; k<NUM_CARS; k++) //создать лифты
	{
		car_list[k]=new elevator(this,num_cars);
		num_cars++;
	}*/
	car_list=new elevator(this);
	for(int j=0; j<NUM_FLOORS; j++) //для каждого этажа
	{
		set_cursor_pos(3,NUM_FLOORS-j); //вывести номер этажа
		itoa(j+1,ustring,10); //на экран
		cout<<setw(3)<<ustring; 
		floor_request[UP][j]=false; //запросов еще не было
		floor_request[DN][j]=false;
	}
}
building::~building() //деструктор
{
	//for(int k=0; k<NUM_CARS; k++) //удалить лифты
	//	delete car_list[k];
	delete car_list;
}
void building::master_tick() //метроном
{
	//int j;
	show_floor_reqs(); //вывести запросы с этажей
	/*for(j=0; j<NUM_CARS; j++) //для каждого лифта
		car_list[j]->car_tick1(); //послать временную метку 1
	for(j=0; j<NUM_CARS; j++) //для каждого лифта
		car_list[j]->car_tick2(); //послать временную метку 2*/
	car_list->car_tick1();
	car_list->car_tick2();
}
void building::show_floor_reqs() const //вывод запросов
{
	for(int j=0; j<NUM_FLOORS; j++)
	{
		set_cursor_pos(SPACING,NUM_FLOORS-j);
		if(floor_request[UP][j]==true)
			cout<<'\x1E'; //стрелка вверх
		else
			cout<<' ';
		set_cursor_pos(SPACING+3,NUM_FLOORS-j);
		if(floor_request[DN][j]==true)
			cout<<'\x1F'; //стрелка вниз
		else
			cout<<' ';
	}
}
//record_floor_reqs()-получение запросов снаружи
void building::record_floor_reqs()
{
	if(car_list->TheElevatorIsMoving)
	{
		set_cursor_pos(1,NUM_FLOORS+1);
		clear_line();
		set_cursor_pos(1,NUM_FLOORS+1);
		cout<<"The elevator is moving...";
		return;
	}
	car_list->TheElevatorIsMoving=false;
	char ch='x'; //рабочий символ для ввода
	char ustring[BUF_LENGTH]; //рабочая строка ввода
	int iFloor; //этаж,с которого был запрос
	char chDirection; //'0' или '1' для выбора направления	
	set_cursor_pos(1,NUM_FLOORS+1);//(1,22); //низ экрана
	cout<<"Press ENTER call the elevator or ESC to exit: ";
	if(!kbhit()) //ожидание нажатия (должен быть CR, возврат каретки)
		return;
	/*cin.ignore(10,'\n');
	if(ch=='\x1B') //при нажатии escape выход из программы
		exit(0);*/	
	ch=getch();
	while(ch!=13 && ch!=27)
		ch=getch();
	if(ch==27)		
		exit(0);
	set_cursor_pos(1,NUM_FLOORS+1);//(1,22);
	clear_line(); //очистить от старого текста
	set_cursor_pos(1,NUM_FLOORS+1);//(1,22); //низ экрана
	cout<<"On what floor are you? ";
	//cin.get(ustring,BUF_LENGTH); //получить этаж
	//cin.ignore(10,'\n'); //съесть символы,включая разделитель
	//iFloor=atoi(ustring); //преобразовать в int
	iFloor=GetIntFromKeyboard(1,NUM_FLOORS);
	cout<<"\nDirection: press 1 to move up or 0 to move down or ESC to exit: ";
	//cin.get(chDirection); //(избежать повтора новых строк)
	//cin.ignore(10,'\n'); //съесть символы,включая разделитель
	chDirection=getch();
	while(chDirection!='0' && chDirection!='1' && chDirection!='\x1B')
		chDirection=getch();
	/*if(chDirection=='u' || chDirection=='U')
		floor_request[UP][iFloor-1]=true; //запрос «вверх»
	if(chDirection=='d' || chDirection=='D')
		floor_request[DN][iFloor-1]=true; //запрос «вниз»*/
	if(chDirection=='\x1B')
		exit(0);
	else
		if(chDirection=='1')
			floor_request[UP][iFloor-1]=true; //запрос «вверх»
		else
			if(chDirection=='0')
				floor_request[DN][iFloor-1]=true; //запрос «вниз»
	set_cursor_pos(1,NUM_FLOORS+1); clear_line();
	set_cursor_pos(1,NUM_FLOORS+2); clear_line();
	//set_cursor_pos(1,22); clear_line(); //стереть старый текст
	//set_cursor_pos(1,23); clear_line();
	//set_cursor_pos(1,24); clear_line();
	car_list->TheElevatorIsMoving=true;
}
//get_floor_req()-проверка наличия запросов
bool building::get_floor_req(const int dir,const int floor) const
{
	return floor_request[dir][floor];
}
//set_floor_req()-установить запрос
void building::set_floor_req(const int dir,const int floor,const bool updown) 
{
	floor_request[dir][floor]=updown;
}
//get_cars_floor()-найти кабинку
int building::get_cars_floor(/*const int carNo*/) const
{
	//return car_list[carNo]->get_floor();
	return car_list->get_floor();
}
//get_cars_dir()-определение направления
direction building::get_cars_dir(/*const int carNo*/) const
{
	//return car_list[carNo]->get_direction();
	return car_list->get_direction();
}
// определения функций класса elevator

//конструктор
elevator::elevator(building* ptrB/*,int nc*/):ptrBuilding(ptrB)//,car_number(nc)
{
	TheElevatorIsMoving=false;
	current_floor=0; //начать с 0 (для пользователя-1)
	old_floor=0; //запомнить предыдущий этаж
	current_dir=STOP; //вначале стоит на месте
	for(int j=0; j<NUM_FLOORS; j++) //пассажиры еще не
		destination[j]=false; //нажимали кнопки
	loading_timer=0; //еще не началась посадка
	unloading_timer=0; //еще не началась высадка
}
int elevator::get_floor() const //получение текущего этажа
{
	return current_floor;
}
direction elevator::get_direction() const //получение текущего направления
{																				
	return current_dir;
}
void elevator::car_tick1() //метроном-1 для каждого лифта
{
	car_display(); //нарисовать кабинку
	dests_display(); //нарисовать конечные этажи
	if(loading_timer) //счет времени посадки
		--loading_timer;
	if(unloading_timer) //счет времени высадки
		--unloading_timer;
	decide(); //принятие решения
}
//все лифты должны знать,что делать,до начала движения
void elevator::car_tick2() //метроном-2 для каждого лифта
{
	 move(); //двигать лифт,если нужно
}
void elevator::car_display() //вывод образа лифта
{
	set_cursor_pos(SPACING+1/*(car_number+1)*/*SPACING,NUM_FLOORS-old_floor);
	cout<<"	"; //стереть со старой позиции
	set_cursor_pos(SPACING-1+1/*(car_number+1)*/*SPACING,NUM_FLOORS-current_floor);
	switch(loading_timer)
	{
		case 3:
			 cout<<"\x01\xDB \xDB "; //лифт с открытыми дверями
			 break; //слева-мордочка
		case 2:
			 cout<<" \xDB\x01\xDB "; //мордочка в дверях
			 get_destinations(); //получить конечный этаж
			 break;
		case 1:
			 cout<<" \xDB\xDB\xDB "; //нарисовать с закрытыми
			 break; //дверями без мордочки
		case 0:
			 cout<<" \xDB\xDB\xDB "; //двери закрыты,
			 break; //мордочки нет (по умолчанию)
	}
	set_cursor_pos(SPACING+1/*(car_number+1)*/*SPACING,NUM_FLOORS-current_floor);
	switch(unloading_timer)
	{
		 case 3:
			 cout<<"\xDB\x01\xDB ";	//двери открыты,
			 break; //мордочка слева
		 case 2:
			 cout<<"\xDB \xDB\x01";	//двери открыты,
			 break; //мордочка справа
		 case 1:
			 cout<<"\xDB\xDB\xDB ";	//двери закрыты
			 break; //мордочки нет
		 case 0:
			 cout<<"\xDB\xDB\xDB ";	//двери закрыты,
			 break; //мордочки нет (по умолчанию)
	}
	old_floor=current_floor; //запомнить старый этаж
} //конец car_display()

void elevator::dests_display() const //вывести конечные
{ //этажи,выбранные кнопками
	for(int j=0; j<NUM_FLOORS; j++)//внутри лифта
	{
		set_cursor_pos(SPACING-2+1/*(car_number+1)*/*SPACING,NUM_FLOORS-j);
		if(destination[j]==true)
			cout<<'\xFE'; //маленький квадратик
		else
			cout<<' '; //пробел
	}
}
void elevator::decide() //принятие решения
{
	int j;
	//флаги показывают,сверху или снизу запросы или назначения
	bool destins_above,destins_below;	 //конечные пункты
	bool requests_above,requests_below; //запросы
	//ближайший запрос снизу и сверху
	int nearest_higher_req=0;
	int nearest_lower_req=0;
	//флаги указывают,есть ли другие лифты,движущиеся в том
	//же направлении между нами и ближайшим запросом с этажа (ЗЭ)
	bool car_between_up,car_between_dn;
	//флаги указывают,есть ли лифты противоположного
	//направления с другой стороны от ближайшего ЗЭ
	bool car_opposite_up,car_opposite_dn;
	//этаж и направление другого лифта
	int ofloor; //этаж
	direction odir; //направление
	//убедиться,что мы не слишком высоко или низко
	if((current_floor==NUM_FLOORS-1 && current_dir==UP) || (current_floor==0 && current_dir==DN))
		current_dir=STOP;
	//если этаж назначения-текущий,начать высадку
	if(destination[current_floor]==true)
	{
		destination[current_floor]=false; //удалить это назначение		
		if(!unloading_timer) //высадка
			unloading_timer=LOAD_TIME;
		TheElevatorIsMoving=false;	
		return;
	}
	//если есть запрос «вверх» с этого этажа и если
	//мы едем вверх или стоим,произвести посадку на борт
	if((ptrBuilding->get_floor_req(UP,current_floor) && current_dir!=DN))
	{
		current_dir=UP; //(если была остановка)
		//удалить ЗЭ в данном направлении движения
		ptrBuilding->set_floor_req(current_dir,current_floor,false);
		if(!loading_timer) //посадка
			loading_timer=LOAD_TIME;
		TheElevatorIsMoving=false;
		return;
	}
	//проверка других назначений или ЗЭ
	//расстояние считать до ближайшего запроса
	if((ptrBuilding->get_floor_req(DN,current_floor) && current_dir!=UP))
	{
		current_dir=DN;	//(в случае,если это была ОСТАНОВКА)
		//удалите запрос пола на направление,мы идем
		ptrBuilding->set_floor_req(current_dir,
			current_floor,false);
		if(!loading_timer) //загрузка пассажиров
			loading_timer=LOAD_TIME;
		TheElevatorIsMoving=false;
		return;
	}
	//проверьте,есть ли другие места назначения или запросы
	//расстояние записи до самого близкого запроса
	destins_above=destins_below=false;
	requests_above=requests_below=false;
	for(j=current_floor+1; j<NUM_FLOORS; j++)
	{ //проверять верхние этажи
		if(destination[j]) //если они-назначения
			destins_above=true; //установить флаг
		if(ptrBuilding->get_floor_req(UP,j) ||
			 ptrBuilding->get_floor_req(DN,j))
		{ //если ЗЭ
			requests_above=true; //установить флаг
			if(!nearest_higher_req) //если еще не установлен
				nearest_higher_req=j; //установить ближайший ЗЭ
		}
	}
	for(j=current_floor-1; j >= 0; j--) //проверка нижних этажей
	{
		if(destination[j]) //если назначения
			destins_below=true; //установить флаг
		if(ptrBuilding->get_floor_req(UP,j) || ptrBuilding->get_floor_req(DN,j))
		{ //если запросы
			requests_below=true; //установить флаг
			if(!nearest_lower_req) //если еще не установлен
				nearest_lower_req=j; //установить ближайший ЗЭ
		}
	}
	//если нет запросов сверху/снизу,остановиться
	if(!destins_above && !requests_above && !destins_below && !requests_below)
	 {
		 current_dir=STOP;
		 TheElevatorIsMoving=false;
		 return;
	 }
	//если есть назначение,а мы стоим или движемся к нему,
	//начать/продолжать движение
	if(destins_above && (current_dir==STOP || current_dir==UP))
	{
		current_dir=UP;
		return;
	}
	if(destins_below && (current_dir==STOP || current_dir==DN))
	{
		current_dir=DN;
		return;
	}
	//проверка,есть ли другие лифты,(a) того же направления
	//между нами и ближайшим ЗЭ,или
	//(b) встречного направления с другой стороны ЗЭ
	car_between_up=car_between_dn=false;
	car_opposite_up=car_opposite_dn=false;
	//for(j=0; j<NUM_CARS; j++) //проверить каждый лифт
	//{
		//if(j!=car_number) //если это не наш лифт
		//{ //получить его этаж			
			ofloor=ptrBuilding->get_cars_floor(); //и
			odir=ptrBuilding->get_cars_dir(); //направление
			if(/*(odir==UP || odir==STOP) && */requests_above)
				//если он при этом между нами и ЗЭ
				if((ofloor>current_floor
					 && ofloor<=nearest_higher_req)
				//или там же,но его номер ниже
					/*|| (ofloor==current_floor && j<car_number)*/)
					car_between_up=true;
			//если он едет вниз,и ЗЭ внизу
			if(/*(odir==DN || odir==STOP) && */requests_below)
				//если он снизу,но над ближайшим ЗЭ
				if((ofloor<current_floor
					 && ofloor>=nearest_lower_req)
					//или на том же этаже,но с меньшим номером
					/*|| (ofloor==current_floor && j<car_number)*/)
					car_between_dn=true;				
			//если идет вверх,а ЗЭ снизу
			if((odir==UP || odir==STOP) && requests_below)
				//и он ниже ЗЭ и ближе к нему,чем мы
				if(nearest_lower_req>=ofloor
					&& nearest_lower_req-ofloor
					 <current_floor-nearest_lower_req)
					car_opposite_up=true;
			//если идет вниз,а ЗЭ сверху
			if((odir==DN || odir==STOP) && requests_above)
				//и он над ЗЭ и ближе к нему,чем мы
				if(ofloor>=nearest_higher_req
					&& ofloor-nearest_higher_req
					 <nearest_higher_req-current_floor)
					car_opposite_dn=true;
		//}
	//}
	//если идем вверх или остановились,а ЗЭ над нами
	//и между нами и ЗЭ нет идущих вверх лифтов
	//или идущих вниз над ЗЭ и ближе к нему,чем мы,тогда
	//ехать вверх
	if((current_dir==UP || current_dir==STOP) && requests_above && !car_between_up && !car_opposite_dn)
	{
		current_dir=UP;
		return;
	}
	//если идем вниз или остановились,и снизу есть ЗЭ,
	//и нет лифтов,идущих вниз,между нами и ЗЭ
	//или под ЗЭ,идущих вверх и ближе нас к ЗЭ
	if((current_dir==DN || current_dir==STOP) && requests_below && !car_between_dn && !car_opposite_up)
	{
		current_dir=DN;
		return;
	}
	//если ничто иное случай,не остановиться
	current_dir=STOP;
}
void elevator::move()
{ //если посадка или высадка,
	if(loading_timer || unloading_timer) //не двигаться
		return;	
	if(current_dir==UP) //если идем вверх, идти вверх
		current_floor++;
	else
		if(current_dir==DN) //если идем вниз, идти вниз
			current_floor--;
}
void elevator::get_destinations() //остановка,получение пунктов назначения
{
	char ustring[BUF_LENGTH]; //входной рабочий буфер
	int dest_floor; //этаж назначения
	//set_cursor_pos(1,22); clear_line(); //удалить верхнюю строку
	set_cursor_pos(1,NUM_FLOORS+1); clear_line();
	set_cursor_pos(1,NUM_FLOORS+1);
	//set_cursor_pos(1,22);
	//cout<<"The elevator "<<(car_number+1)<<" is on the floor "<<(current_floor+1)<<"\nDestination floor (0 to stop input): ";
	cout<<"The elevator is on the floor "<<(current_floor+1)<<"\nDestination floor: ";
	//for(int j=1; j<NUM_FLOORS; j++)	 //получить запросы этажей максимум; обычно меньше
	//{																	 
		//set_cursor_pos(1,24);
		//cout<<"Destination floor "<<j<<": ";		
		/*cin.get(ustring,BUF_LENGTH); //(во избежание дублирования пустых строк)
		cin.ignore(10,'\n'); //съесть символы,включая ограничитель
		dest_floor=atoi(ustring);*/
		dest_floor=GetIntFromKeyboard(1,NUM_FLOORS);
		set_cursor_pos(1,NUM_FLOORS+1); clear_line();
		set_cursor_pos(1,NUM_FLOORS+2); clear_line();
		//set_cursor_pos(1,23);//(1,24);
		//clear_line(); //стереть старую строку
		//if(dest_floor==0) //если больше нет запросов, стереть нижние три строки
		//{ 	
			//set_cursor_pos(1,22); clear_line();		
			//set_cursor_pos(1,23); clear_line();
			//set_cursor_pos(1,24); clear_line();
			//return;
		//}
		--dest_floor; //начинать с 0,а не 1
		//if(dest_floor==current_floor) //выбрать текущий этаж
		//{
		//	--j;
		//	continue;
		//} //забыть его
		//если мы остановились,первый запрос выбирает направление движения
		//if(j==1 && current_dir==STOP)
		//	current_dir=(dest_floor<current_floor) ? DN : UP;
		destination[dest_floor]=true; //записать выбор
		TheElevatorIsMoving=true;
		dests_display(); //вывести этажи назначения
	//}
}