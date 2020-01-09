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
   for j:=1 to 2*i-1 do//номера строк уменьшаются
   begin
     gotoXY(2*i-j,j); write('*'); delay(30)
   end;
 //  sverhu vniz
 for j:= 2*i downto 1 do
  begin
    gotoXY(2*i+1-j,j); write('*'); delay(30)
  end;

end;
    readln;
//Zapolnyaem osnovnuyu chast"
for i:=13 to 40 do
begin
 // sverhu vniz
   for j:=1 to 25 do
   begin
     gotoXY(2*i-j,j); write('*'); delay(10)
   end;

//snizu  vverh
 for j:= 25 downto 1 do
  begin
    gotoXY(2*i+1-j,j); write('*'); delay(10)
  end;

end;

{Zapolnyaem nijniy ugol}
for i:=1 to 12 do
begin
  {sverhu vniz}
   for j:=2*i to 25 do
   begin
     gotoXY(79-j+2*i,j); write('*'); delay(10)
   end;

{snizu  vverh}
 for j:= 25 downto 2*i+1 do
  begin
    gotoXY(80-j+2*i,j); write('*'); delay(10)
  end;

end;
gotoXY(1,25);
readln;
END.

