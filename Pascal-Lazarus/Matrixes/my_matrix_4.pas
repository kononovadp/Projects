program z1;
uses crt;
var i,j,n,k:byte;
BEGIN
TextBackGround (1);
clrscr;
Textcolor(yellow);

for i:=1 to 12 do//����� ��אַ㣮��쭨�� (1 ��⮪ ᯨࠫ�)
//j - �������� �� ��१��

begin

  for j:= i to 25-i do
  begin
    gotoXY(81-i,j); write('*'); delay(10)
   end;//᫥�� ���ࠢ�

   for j:= 81-i downto i do
   begin
    gotoXY(j,25-i); write('*'); delay(10)
  end;//᭨�� �����

    for j:= 25-i downto i do // 2*i-1
  begin
    gotoXY(i,j); write('*'); delay(10)
   end;//�ࠢ� ������

  for j:= i to 81-i do
   begin
    gotoXY(j,i); write('*'); delay(10)
  end;end;//ᢥ��� ����



{ for j:= 12 to 81-12 do //��१��� ��᫥���� ��譨� 横� (⮫쪮 ���� ��१��)
  begin
    gotoXY(j,12); write('*'); delay(10)
   end;}
    gotoXY(80,24);
    readln; end.
