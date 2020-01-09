program z1;
uses crt;
var i,j,n,k:byte;
BEGIN
TextBackGround (1);
clrscr;
Textcolor(yellow);

for i:=1 to 12 do//номер прямоуголльника (1 виток спирали)
//j - элементы на отрезке
begin
 for j:= 25-i downto i do
   begin
    gotoXY(i,j); write('*'); delay(10)
  end;//снизу вверх

  for j:= i to 81-i do
  begin
    gotoXY(j,i); write('*'); delay(10)
   end;//слева направо

  for j:= i to 25-i do
   begin
    gotoXY(81-i,j); write('*'); delay(10)
  end;//сверху вниз

  for j:= 81-i downto 1+i do // 2*i-1
  begin
    gotoXY(j,25-i); write('*'); delay(10)
   end; end;//справа налево



 {for j:= 13 to 81-13 do //вырезаем последний лишний цикл (только один отрезок)
  begin
    gotoXY(j,13); write('*'); delay(10)
   end;}
gotoXY(80,24) ;
   readln; end.
