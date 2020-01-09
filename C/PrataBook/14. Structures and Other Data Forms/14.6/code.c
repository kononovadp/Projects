/*Текстовый файл содержит информацию о команде по софтболу (разновидность бейсбола). В каждой строке данные упорядочены следующим образом:
4 Джесси Джойбет 5 2 1 1
Первым членом является номер игрока (обычно это число из диапазона 0-18). Второй член - это имя игрока, а третий - его фамилия. Каждое имя состоит из одного слова. Следующий член показывает, сколько раз игрок принимал мяч, за которым следует количество нанесенных игроком ударом, проходов и засчитанных пробежек. Файл может содержать результаты более чем одной игры, следовательно, для одного и того же игрока может быть несколько строк. Напишите программу, которая сохраняет соответствующие данные в массиве структур. Структура должна состоять из членов, в которых представлена фамилия и имя, количество набранных очков, проходов и засчитанных пробежек, а также средний результат (эти значения вычисляются позже). В качестве индекса массива можете использовать номер игрока. Программа должна выполнять чтение до конца файла, и накапливать итоговые результаты по каждому игроку.
Мир статистики бейсбола довольно сложен. Например, проход или взятие базы в результате ошибки не расценивается так же высоко как тот же самый результат, полученный за счет меткого удара, однако он позволяет получить выигранную пробежку. Но эта программа должна только читать и обрабатывать файлы данных, как описано ниже, не заботясь о реалистичность данных.
Простейший способ предусматривает инициализацию содержимого структуры нулями, чтение данных из файла во временные переменные и затем их добавление к содержимому соответствующей структуры. После того как программа завершит чтение файла, она должна вычислить средний уровень достижений для каждого игрока и запомнить его в соответствующем члене структуры. Средний уровень достижений вычисляется путем деления накопленного числа ударов, выполненных игроком, на количество выходов на ударные позиции; результат должен быть с плавающей запятой. Затем программа должна отобразить накапливаемые данные по каждому игроку наряду со строкой, в которой содержатся суммарные статистические данные по всей команде.*/
#include <stdio.h>
#include <stdbool.h>
#define maximum_players_count 19
struct softball_player
{
	int player_number;
	char name[10];
	char last_name[10];
	int ball_reception_count;
	int attack_count;
	int passes_count;
	int travellings_count;
	float average_achievement_level;
};
int main(void)
{
    struct softball_player softball_players[maximum_players_count];	
	int player_number;
	char name[10];
	char last_name[10];
	int ball_reception_count;
	int attack_count;
	int passes_count;
	int travellings_count;
	int ch;
	int j,i=0;
	int players_count=0;
	bool player_exists;
	FILE *f=fopen("file.txt","r");
	for(i=0; i<maximum_players_count; i++)
	{
		softball_players[i].player_number=0;
		softball_players[i].ball_reception_count=0;
		softball_players[i].attack_count=0;
		softball_players[i].passes_count=0;
		softball_players[i].travellings_count=0;
		softball_players[i].average_achievement_level=0;
	}
	i=0;
	while(((ch=fgetc(f))!=EOF) && (players_count<maximum_players_count))
	{
		ungetc(ch,f);		
		fscanf(f,"%d",&player_number);
		fscanf(f,"%s",&name);
		fscanf(f,"%s",&last_name);
		fscanf(f,"%d",&ball_reception_count);
		fscanf(f,"%d",&attack_count);
		fscanf(f,"%d",&passes_count);
		fscanf(f,"%d",&travellings_count);
		i++;
		player_exists=false;
		for(j=0; j<i; j++)
			if(softball_players[j].player_number==player_number)
			{
				player_exists=true;				
				softball_players[j].ball_reception_count+=ball_reception_count;
				softball_players[j].attack_count+=attack_count;
				softball_players[j].passes_count+=passes_count;
				softball_players[j].travellings_count+=travellings_count;
				break;
			}
		if(player_exists==false)
		{
			
			softball_players[players_count].player_number=player_number;
			strcpy(softball_players[players_count].name,name);
			strcpy(softball_players[players_count].last_name,last_name);
			softball_players[players_count].ball_reception_count=ball_reception_count;
			softball_players[players_count].attack_count=attack_count;
			softball_players[players_count].passes_count=passes_count;
			softball_players[players_count].travellings_count=travellings_count;
			players_count++;
		}
	}
	fclose(f);
	for(i=0; i<players_count; i++)
		softball_players[i].average_achievement_level=(float)softball_players[i].attack_count/(float)softball_players[i].passes_count;
	for(int i=0; i<players_count; i++)
		printf("Номер игрока: %d; имя и фамилия: %s %s;\n"
	"количество приемов мяча: %d; количество нанесенных ударов: %d;\n"
	"количество проходов: %d; количество засчитанных пробежек: %d;\n"
	"средний уровень достижений: %f.\n"
	"--------------------------------------------------------------------\n",
	softball_players[i].player_number,softball_players[i].name,softball_players[i].last_name,softball_players[i].ball_reception_count,softball_players[i].attack_count,softball_players[i].passes_count,softball_players[i].travellings_count,softball_players[i].average_achievement_level);	
    return 0;
}