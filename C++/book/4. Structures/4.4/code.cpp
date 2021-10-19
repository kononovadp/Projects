/*4. Создайте структуру с именем employee, содержащую два поля: номер сотрудника типа int и величину его пособия в долларах типа float. Запросите с клавиатуры данные о трех сотрудниках, сохраните их в трех структурах переменных типа employee и выведите информацию о каждом из сотрудников на экран.*/
#include <iostream>
using namespace std;
struct employee
{
	int number;
	float allowance;
};
int main(void)
{
	struct employee *e=(struct employee*)malloc(sizeof(struct employee)*3);
	int i;
	for(i=0; i<3; i++)
	{
		cout<<"ID of employee "<<i+1<<": ";
		cin>>e[i].number;
		cout<<"Allowance: ";
		cin>>e[i].allowance;
	}
	cout<<"=================================="<<endl;
	for(i=0; i<3; i++)
		cout<<"Employee "<<i+1<<": ID "<<e[i].number<<"; Allowance "<<e[i].allowance<<endl;
	free(e);
	return 0;
}
