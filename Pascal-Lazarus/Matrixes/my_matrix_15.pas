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

//snizu  vverh
   for j:=24 downto 26-2*i do//номера строк уменьшаются
   begin
     gotoXY(80+25-2*i-j,j); write('*'); delay(10)
   end;
 //  sverhu vniz
 for j:= 25-2*i to 24 do
  begin
    gotoXY(80+25-2*i-1-j,j); write('*'); delay(10)
  end;

end;
    readln;
//Zapolnyaem osnovnuyu chast"
for i:=13 to 39 do
begin
 // sverhu vniz
   for j:=1 to 25 do
   begin
     gotoXY(80+25-2*i-j,j); write('*'); delay(10)
   end;

//snizu  vverh
 for j:= 25 downto 1 do
  begin
    gotoXY(80+25-2*i-1-j,j); write('*'); delay(10)
  end;

end;

{Zapolnyaem nijniy ugol}
for i:=1 to 12 do
begin
  {sverhu vniz}
   for j:=1 to 26-2*i do
   begin
     gotoXY(-j+27-2*i,j); write('*'); delay(10)
   end;

{snizu  vverh}
 for j:= 25-2*i downto 1 do
  begin
    gotoXY(-j+26-2*i,j); write('*'); delay(10)
  end;

end;
gotoXY(1,25);
readln;
END.

