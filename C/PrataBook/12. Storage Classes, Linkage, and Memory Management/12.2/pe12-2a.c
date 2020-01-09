int mode_glob=0;
float distance;
float fuel_consumption;
void set_mode(int mode)
{
	if (mode!=0 && mode!=1)
	{
		printf("Указан недопустимый режим. Используется режим %d",mode_glob);
		if (mode_glob==0)
			printf(" (метрический)\n");
		else
			if (mode_glob==1)
				printf(" (американский)\n");
	}
	else
		mode_glob=mode;
}
void get_info()
{
	if(mode_glob==0)
		printf("Введите пройденное расстояние в километрах: ");
	else
		if(mode_glob==1)
			printf("Введите пройденное расстояние в милях: ");
	scanf("%f",&distance);
	if(mode_glob==0)
		printf("Введите объем израсходованного топлива в литрах: ");
	else
		if(mode_glob==1)
			printf("Введите объем израсходованного топлива в галлонах: ");
	scanf("%f",&fuel_consumption);
}
void show_info()
{
	if(mode_glob==0)
		printf("Расход топлива составляет %.2f литров на 100 км.\n",
				fuel_consumption/distance*100);
			else
				if(mode_glob==1)
					printf("Расход топлива составляет %.2f мили на галлон.\n",
							distance/fuel_consumption);
}
