program my_array2;
uses crt;
var a: array[1..200] of integer; i: byte; b,s,s2,c,n: integer; k,l: longint;
ch: char;
label povtor;
begin
povtor: clrscr;
writeln('�뢮��� 15 楫�� ��砩��� �ᥫ');
randomize;
for i:= 1 to 15 do a[i]:=random(200);
for i:= 1 to 15 do write (' ',a[i]); readln;
s:=0;
for i:= 1 to 15 do s:= s+a[i]; write('�㬬� ��� ����⮢: ',s);readln;
write('���� �᫠: ');
for i:= 1 to 15 do
if a[i] mod 2=0 then write (a[i],(', ')); readln;
b:=0;
write('������⢮ ���� �ᥫ: ');
for i:= 1 to 15 do
if a[i] mod 2=0 then b:=b+1; write(b); readln;
write('�㬬� ���� �ᥫ: ');
s2:=0;
for i:=1 to 15 do if a[i] mod 2=0 then s2:=s2+a[i]; write(s2);readln;

write('����� �᫠: ');
for i:= 1 to 15 do
if a[i] mod 2=1 then write (a[i],(', ')); readln;
b:=0;
write('������⢮ ������ �ᥫ: ');
for i:= 1 to 15 do
if a[i] mod 2=1 then b:=b+1; write(b); readln;
write('�㬬� ������ �ᥫ: ');
s2:=0;
for i:=1 to 15 do if a[i] mod 2=1 then s2:=s2+a[i]; write(s2);readln;
write('��᫯� ����� 50: ');
for i:= 1 to 15 do
if a[i]<50 then write (a[i],(', ')); readln;
write('������⢮ ���祭�� ����� 50: ');
n:=0;
for i:=1 to 15 do if a[i]<50 then n:=n+1; write(n); readln;
k:=1;
write('�ந�������� ����⮢, ���祭�� ������ ����� 50: ');
for i:=1 to 15 do if a[i]<50 then k:=k*a[i]; write(k); readln;
write('�������� � �����ᠬ� �� 2 �� 7: ');
for i:=2 to 7 do write(a[i],', '); readln;
l:=1;
write('�ந�������� ����⮢ � �����ᠬ� 2 � 7: ');
l:=a[2]*a[7]; write(l); readln;
writeln('��� ����� 横�� ������ Enter, ��� ��室� - Esc');
ch:=readkey;
if ch=#13 then goto povtor;
if ch=#27 then exit;
end.
