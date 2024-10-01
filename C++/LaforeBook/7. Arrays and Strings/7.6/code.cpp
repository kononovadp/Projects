/*6. В игре бридж каждому из игроков раздают 13 карт, таким образом колода расходуется полностью. Модифицируйте программу CARDARAY этой главы так, чтобы после перемешивания колоды она делилась на четыре части по 13 карт каждая. Каждая из четырех групп карт затем должна быть выведена.*/
// cardaray.cpp
// класс игральных карт
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
enum Suit {clubs,diamonds,hearts,spades};
// от 2 до 10 обычные числа
const int jack = 11;
const int queen = 12;
const int king = 13;
const int ace = 14;
/////////////////////////////////////////////////////////////
class card
{
	private:
	int number;
	Suit suit;
	public:
	card() { }// конструктор
	void set(int n, Suit s) // установка значения
	{ suit = s; number = n; }
	void display(); // показ карты
};
/////////////////////////////////////////////////////////////
void card::display()
{
	if(number >= 2 && number <= 10)
		cout << number;
	else
	{
		switch(number)
		{
			case jack: cout << 'J'; break;
			case queen: cout << 'Q'; break;
			case king: cout << 'K'; break;
			case ace: cout << 'A'; break;
		}
	}
	switch(suit)
	{	//приведение к типу
		case clubs: cout << "♣"; break;
		case diamonds: cout << "♦"; break;
		case hearts: cout << "♥"; break;
		case spades: cout << "♠"; break;
	}
}
/////////////////////////////////////////////////////////////
int main()
{
	card deck[52];
	card BridgeDeck[4][13];
	int i,j,k;
	cout << endl;
	for(j = 0; j < 52; j++) // создаем упорядоченную колоду карт
	{
		int num = (j % 13) + 2;
		Suit su = Suit(j / 13);
		deck[j].set(num, su);
	}
	// показываем исходную колоду
	cout << "Исходная колода:\n";
	for(j = 0; j < 52; j++)
	{
		deck[j].display();
		cout << " ";
		if(!((j + 1) % 13)) // начинаем новую строку после каждой 13-й карты
		cout << endl;
	}
	srand(time(NULL)); // инициализируем генератор случайных чисел
	for(j = 0; j < 52; j++)
	{
		k = rand() % 52; // выбираем случайную карту
		card temp = deck[j]; // и меняем ее с текущей
		deck[j] = deck[k];
		deck[k] = temp;
	}
	// показываем перемешанную колоду
	cout << "\nПеремешанная колода:\n";
	for(j = 0; j < 52; j++)
	{
		deck[j].display();
		cout << " ";
		if(!((j + 1) % 13)) // начинаем новую строку после каждой 13-й карты
		cout << endl;
	}
	for(i=0,k=0; i<4; i++)
		for(j=0; j<13; j++,k++)
			BridgeDeck[i][j]=deck[k];
	cout<<endl<<"Колоды для игры в бридж:";
	for(i=0; i<4; i++)
	{
		cout<<endl<<"Колода "<<i+1<<": ";
		for(j=0; j<13; j++)
		{
			BridgeDeck[i][j].display();
			cout << " ";
		}
	}
	return 0;
}
