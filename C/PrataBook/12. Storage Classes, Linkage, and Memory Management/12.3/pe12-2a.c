void show_info(int mode, float distance, float fuel_consumption);
int set_mode(int prew_mode, int mode)
{
	if (mode!=0 && mode!=1)
	{
		printf("Указан недопустимый режим. Используется режим %d",prew_mode);
		if (prew_mode==0)
			printf(" (метрический)\n");
		else
			if (prew_mode==1)
				printf(" (американский)\n");
		return prew_mode;
	}
	else
		return mode;
}
void get_info(int mode)
{
	float distance;
	float fuel_consumption;
	if(mode==0)
		printf("Введите пройденное расстояние в километрах: ");
	else
		if(mode==1)
			printf("Введите пройденное расстояние в милях: ");
	scanf("%f",&distance);
	if(mode==0)
		printf("Введите объем израсходованного топлива в литрах: ");
	else
		if(mode==1)
			printf("Введите объем израсходованного топлива в галлонах: ");
	scanf("%f",&fuel_consumption);
	show_info(mode,distance,fuel_consumption);
}
void show_info(int mode, float distance, float fuel_consumption)
{
	if(mode==0)
		printf("Расход топлива составляет %.2f литров на 100 км.\n",
				fuel_consumption / distance*100);
			else
				if(mode==1)
					printf("Расход топлива составляет %.2f мили на галлон.\n",
							distance / fuel_consumption);
}
