Var k:integer;
 j:byte;
 A:array[1..12] of integer;{�������� ��������� ����������� ������� �� ���������
 � ������������ ����������, ����� ������ ���������}
 f:text;
Begin
k:=3; j:=1;
while j<=11 do begin
asm
{if j<>7 then}
CMP    j,07
JZ     @20
{k:=k+j;}
MOV    AL,j
XOR    AH,AH
ADD    AX,k
MOV    k,AX
{A[j]:=k;}
@20:
mov    dx,[k]
mov    al,[j]
xor    ah,ah
mov    di,ax
shl    di,1
mov    word ptr [di+A],dx
{j:=j+1;}
MOV    AL,j
XOR    AH,AH
INC    AX
MOV    j,AL
end;
end;
assign(f,'f.txt'); rewrite(f); {���������� ������� � ����, ��� ��� readln ������-�� �� ��������}
for j:=2 to 12 do begin
write(f,A[j]:4);writeln; end;
close(f);
End.