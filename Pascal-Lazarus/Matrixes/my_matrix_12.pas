program z1;
uses crt;
var i,j,n,k:byte;
BEGIN
TextBackGround (1);
clrscr;
Textcolor(yellow);
{Zapolnyaem praviy ugol}
for i:=1 to 24 do
begin
{sprava nalevo}
 for j:= 24 downto 1 do // 2*i-1
   begin
    gotoXY(56+i+j-1,i); write('*'); delay(10)
  end;
    {sleva napravo}
  { for j:= 24 downto 1 do // 2*i-1
   begin
   gotoXY(54+i+j,i); write('*'); delay(10)
   end;}
   end;
   readln;
{Zapolnyaem seredinu}
for i:=24 downto 1 do
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
 {Zapolnyaem leviy ugol}
for i:=1 to 24 do  //количество петель (каждая два ряда)
begin
//snizu  vverh
 for j:=1 to 2*i-1 do//номера строк уменьшаются
   begin
     gotoXY(i-j div 2,i); write('*'); delay(10)
   end;gotoXY(1,24);
 //  sverhu vniz
 {for j:=1 to 2*i-1 do//номера строк уменьшаются
   begin
     gotoXY(i-j div 2,i); write('*'); delay(10)
  end;}
end;
readln;
end.
