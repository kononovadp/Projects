program z1;

uses crt;
var i,j,n:byte;

BEGIN

TextBackGround (1);
clrscr;
Textcolor(yellow);

 {Zapolnyaem praviy ugol}

 for i:=1 to 12 do  //количество петель (каждая два ряда)
begin

{snizu  vverh}
   for j:=24 downto 26-2*i do//номера строк уменьшаются
   begin
     gotoXY(2*i+j-24,j); write('*'); delay(50)
   end;
   {sverhu vniz}
 for j:= 25-2*i to 24 do
  begin
    gotoXY(2*i+1+j-24,j); write('*'); delay(100)
  end;
   readln;
end;
    readln;
{Zapolnyaem osnovnuyu chast"}
for i:=13 to 40 do
begin
  {sverhu vniz}
   for j:=1 to 25 do
   begin
     gotoXY(81-2*i+j,j); write('*'); delay(100)
   end;

{snizu  vverh}
 for j:= 25 downto 1 do
  begin
    gotoXY(80-2*i+j,j); write('*'); delay(100)
  end;

end;

{Zapolnyaem nijniy ugol}
for i:=1 to 12 do
begin
  {sverhu vniz}
   for j:=2*i to 25 do
   begin
     gotoXY(1-2*i+j,j); write('*'); delay(100)
   end;

{snizu  vverh}
 for j:= 25 downto 2*i+1 do
  begin
    gotoXY(j-2*i,j); write('*'); delay(100)
  end;

end;
gotoXY(1,25);
readln;
END.

