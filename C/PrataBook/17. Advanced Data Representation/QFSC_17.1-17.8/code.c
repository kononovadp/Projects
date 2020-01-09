﻿/*1. Исходный тип данных и имя нового типа;
2. Список содержит только один указатель - на предыдущий элемент. Для обхода в обоих направлениях следует изменить определение следующим образом: struct film {char title [TSIZE]; int rating; struct film *next; struct film *prev;}
3. Abstract data type;
4. Преимущество передачи структуры как параметра в том, что исходная структура не меняется, а все изменения затрагивают только ее копию. Недостатки этого подхода: быстродействии, для изменения исходной структуры функция должна ее вернуть. Преимущества передачи адреса структуры: высокое быстродействие, для изменения данных структуры функция не обязательно должна возвращать тот же тип данных, что и данные структуры, изменения вносятся сразу в процессе работы функции. Недостаток передачи указателя: возможно случайное нежелательное изменение исходных данных.
5. D:\Projects\C\my_library\DataStructures\stack;
6. из 3 элементов - 2 шага; из 1023 - 512; из 65535 - 32768;
*/
#include <stdio.h>
#include <stdbool.h>
int main(void)
{
	
    return 0;
}
