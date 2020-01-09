program z1;
uses crt;
var i,j,n,k:byte;
BEGIN
TextBackGround (1);
clrscr;
Textcolor(yellow);

//for i:=1 to 12 do
i:=1;
begin

 for j:= 24 downto 1 do
   begin
    gotoXY(i,j); write('!'); delay(10)
  end;
   readln;
  for j:= 1 to 80 do
  begin
    gotoXY(j,i); write('*'); delay(10)
   end;
     readln;
  for j:= 1 to 24 do
   begin
    gotoXY(80,j); write('!'); delay(10)
  end;

  for j:= 80 downto 2 do // 2*i-1
  begin
    gotoXY(j,24); write('*'); delay(10)
   end;

end;gotoXY(80,24);
    readln;end.
