program z1;
uses crt;

var x,y,z:integer; f:text;

begin
assign(f,'s.txt');//��� � 䠩���
reset(f); ///�����⮢�� 䠩�� � �⥭��

 while not (eof(f)) do
  begin
    read(f,x,y); z:=y+x; writeln(z);
  end;
  close(f);//�����襭�� ࠡ��� � 䠩���
   writeln(y);
readln;



END.
