﻿/*1. Автоматический, регистровый, статический без связывания;
2. Все статические классы;
3. В нескольких файлах - статический внешнее связывание, в одном файле - статический внутреннее связывание;
4. Без связывания;
5. Extern обозначает внешнее связывание для использования переменной в нескольких файлах...;
6. Calloc устанавливает все биты в 0, malloc заполняет блок случайными значениями;
7. daisy видна в обоих файлах и во всех функциях. lily видна только в main. Объявление lily как extern в функции petal ошибочно, так как она не глобальная. Файл 2 содержит другую переменную lily, видную только в его пределах. Rose является глобальной, но функция stem() имеет отдельную переменную rose с другим значением.
8. color в main() равно B
color в first() равно R
color в main равно B
color в second равно G
color в main равно G
9.а static int plink - внешняя переменная с областью видимости в пределах файла. Функция value_ct содержит свой набор переменных, известных только ей. plink может быть передана в эту функцию в качестве одного из аргументов value или n, но делать это необязательно.
9.б не увеличит, так как функция value_ct получает копию данных и изменения в любом случае не затронут исходные значения.
*/
