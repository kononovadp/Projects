program array4;
uses crt;
type mas=array[0..6,0..5] of integer;
var a:mas; i,j: byte; s:integer;
procedure print_mas(a:mas);
begin
writeln('�뢮��� �������� ���ᨢ� #26');
for i:=6 downto 0 do
begin  for j:= 0 to 5 do write (a[i,j]:5); writeln;  end;
end;
begin
 s:=1;
 for i:=0 to 2 do //7,9,11,13 ����� ��� ������
 if i mod 2=0//��ࢠ� ��ப� ��稭����� ᫥�� ��� �ࠢ�
 then
    for j:= 0 to 5 do
    begin
    a[i,j]:= s;  s:=s+1;
    a[6-i,5-j]:=s; s:=s+1;
    end
 else
   for j:= 5 downto 0 do
    begin
    a[i,j]:= s;  s:=s+1;
    a[6-i,5-j]:=s; s:=s+1;
    end;
    i:=3;
    for j:= 0 to 2 do //1.3.5 ᫥�� ��� �ࠢ�
    begin a[i,j]:= s;  s:=s+1;
    a[6-i,5-j]:=s; s:=s+1; end;
print_mas(a);readln;end.
