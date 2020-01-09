/*В полярной системе координат вектор описывается модулем и углом с осью x в направлении против часовой стрелки. В прямоугольной системе координат тот же вектор описывается составляющими x и y. Напишите программу, которая считывает значения модуля и угла (в градусах) вектора, а затем отображает составляющие x и y. Воспользуйтесь следующими уравнениями: x = r cos A; y = r sin A. Для выполнения преобразования применяйте функцию, которая принимает структуру, содержащую полярные координаты, и возвращает структуру, содержащую прямоугольные координаты (или, если хотите, выберите вариант с указателями на эти структуры).*/
#include <stdio.h>
#include <math.h>
#define RAD_TO_DEG (180/(4 * atan(1)))
struct current_magnitude_and_angle
{
	double magnitude;
	double angle;
};
struct components_x_and_y
{
	double component_x;
	double component_y;
};
struct components_x_and_y get_components(struct current_magnitude_and_angle current_data)
{
	struct components_x_and_y result_struct;
	result_struct.component_x=cos(current_data.angle*RAD_TO_DEG)*current_data.magnitude;
	result_struct.component_y=sin(current_data.angle*RAD_TO_DEG)*
	current_data.magnitude;
	return result_struct;
}
int main(void)
{
    int data1,data2;
	struct current_magnitude_and_angle current_data;
	struct components_x_and_y result;
    printf("Введите модуль: ");
	data1=scanf("%lf",&current_data.magnitude);
	if (data1==1)
	{
		printf("Введите угол: ");
		data2=scanf("%lf",&current_data.angle);
	}
    while (data1==1 && data2==1)
    {
        result = get_components(current_data);
        printf("Составляющая x = %0.2f; составляющая y = %0.2f\n",
				result.component_x, result.component_y);
		printf("Введите модуль: ");
		data1=scanf("%lf",&current_data.magnitude);
		if (data1==1)
		{
			printf("Введите угол: ");
			data2=scanf("%lf",&current_data.angle);
		}
    }
    return 0;
}