/*Модифицируйте код в листинге 16.15 так, чтобы программа использовала массив элементов struct names (как определено после листинга) вместо массива элементов double. Задействуйте меньше элементов и явно инициализируйте массив подходящим набором имен.*/
//  generic.c -- определение обобщенных макросов

#include <stdio.h>
#include <math.h>
#define RAD_TO_DEG (180/(4 * atanl(1)))

// обобщенна¤ функци¤ извлечени¤ квадратного корн¤
#define SQRT(X) _Generic((X),\
    long double: sqrtl,\
    default: sqrt,\
    float: sqrtf)(X)

// обобщенна¤ функци¤ вычислени¤ синуса угла, заданного в градусах
#define SIN(X) _Generic((X),\
    long double: sinl((X)/RAD_TO_DEG),\
    default:     sin((X)/RAD_TO_DEG),\
    float:       sinf((X)/RAD_TO_DEG)\
)

int main(void)
{
    float x = 45.0f;
    double xx = 45.0;
    long double xxx =45.0L;

    long double y = SQRT(x);
    long double yy= SQRT(xx);
    long double yyy = SQRT(xxx);
    printf("%.17Lf\n", y);   // соответствует float
    printf("%.17Lf\n", yy);  // соответствует default
    printf("%.17Lf\n", yyy); // соответствует long double
    int i = 45;
    yy = SQRT(i);            // соответствует default
    printf("%.17Lf\n", yy);
    yyy= SIN(xxx);           // соответствует long double
    printf("%.17Lf\n", yyy);

    return 0;
}
