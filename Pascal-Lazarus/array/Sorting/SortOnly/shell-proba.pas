program shell;
uses crt;
var
mas1:array[1..10] of integer;
k,l,n,j,s,x,y,z:integer;
begin
clrscr;
randomize;
for n:=1 to 10 do mas1[n]:=random(100);
for n:=1 to 10 do write (mas1[n], '   ');
   writeln;
n:=10;  s:=0;
while n>1 do //kolichestwo shagov
begin
 z:=k div 2;//z - довжина підмасиву чисел (вона ж - висота "поверхів"), які будуть відсортовані окремо

while z>0 do
   begin
   for x:=0 to n do
   begin
   y:=n-x;//y - покажчик, який завжди знаходиться на 1 крок назад від x
   while  y>=0 do//поки y знаходиться в межах масиву
   if Sum1[y]>Sum1[y+z]//порівнюємо y та точку на крок спереду
   then begin//якщо вони стоять неправильно, міняємо місцями суми та інші елементи масиву
               el:=Sum1[y];      sl:=Mas[y];
               sum1[y]:=sum1[y+z];  Mas[y]:=Mas[y+z];
               sum1[y+z]:=el;       Mas[y+z]:=sl;
			   //покажчик y завжди переставляємо на крок назад
               y:=y-z
               end
   else y:=-1;//якщо елементи впорядковані правильно, то сортування вставками завершилось і можна переходити до наступного елементу x
   end;
   z:=z div 2;//зменшуємо кількість кроків удвічі
   end;
	z:=z div 2;
   end;
for l:=1 to 10 do write (mas1[l], '   ');
     writeln('step ',s, 'point of change ',n);
 end;//konec cicla while
//for n:=1 to 10 do write (mas1[n], '   ');
readln
end.