program z1;
uses crt;
var i,j,n,k:byte;
BEGIN
TextBackGround (1);
clrscr;
Textcolor(yellow);
 {Zapolnyaem leviy ugol}
for i:=1 to 12 do  //количество петель (каждая два ряда)
begin
//snizu  vverh
   for j:=1 to 2*i-1 do//номера строк уменьшаются
   begin
     gotoXY(2*i-j,j); write('*'); delay(30)
   end;
 //  sverhu vniz
 for j:= 2*i downto 1 do
  begin
    gotoXY(2*i+1-j,j); write('*'); delay(30)
end;end;
readln;
{Zapolnyaem seredinu}
for i:=1 to 24 do
begin
  {sverhu vniz}
  for j:= 1 to 56 do // 2*i-1
  begin
    gotoXY(i+j,i); write('*'); delay(10)
  end;
{snizu  vverh}
   begin
   for j:= 1 to 55 do // 2*i-1
   gotoXY(i+j,i); write('*'); delay(10)
  end;
  end;
readln;
{Zapolnyaem praviy ugol}
for i:=24 downto 1 do
begin
{sprava nalevo}
 for j:= 1 to 24 do // 2*i-1
   begin
    gotoXY(56+i+j-1,i); write('*'); delay(10)
  end;gotoXY(80,1);
    {sleva napravo}
  { for j:= 24 downto 1 do // 2*i-1
   begin
   gotoXY(54+i+j,i); write('*'); delay(10)
   end;}
   end;
   readln;
end.
