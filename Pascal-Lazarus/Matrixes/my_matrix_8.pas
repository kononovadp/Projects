program z1;
uses crt;
var i,j,n,k:byte;
BEGIN
TextBackGround (1);
clrscr;
Textcolor(yellow);

for i:=12 downto 1 do//����� ��אַ㣮��쭨�� (1 ��⮪ ᯨࠫ�)
//j - �������� �� ��१��

begin
 for j:= i+1 to 80-i do
   begin
    gotoXY(j,25-i); write('*'); delay(10)
  end;//᭨�� �����

  for j:= 25-i downto i do
  begin
    gotoXY(81-i,j); write('*'); delay(10)
   end;//᫥�� ���ࠢ�

  for j:= 81-i downto i do
   begin
    gotoXY(j,i); write('*'); delay(10)
  end;//ᢥ��� ����

  for j:= i to 25-i do // 2*i-1
  begin
    gotoXY(i,j); write('*'); delay(10)
   end;//�ࠢ� ������
end;

  {for j:= 13 to 81-13 do //��१��� ��᫥���� ��譨� 横� (⮫쪮 ���� ��१��)
  begin
    gotoXY(j,13); write('*'); delay(10)
   end;}
gotoXY(80,24) ;
    readln; end.
