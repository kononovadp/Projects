Program test0011;
Var k:integer;
 j:byte;
 A:array[1..11] of integer;
Begin
 k:=3; j:=1;
asm
//while j<=11 do begin
9716:001A 803E54000B     CMP    [j],0B
9716:001F 772F           JA     0050
//if j<>7 then begin
9716:0021 803E540007     CMP    [j],07
9716:0026 740C           JZ     0034
//k:=k+j;
9716:0028 A05400         MOV    AL,[j]
9716:002B 30E4           XOR    AH,AH
9716:002D 03065200       ADD    AX,[k]
9716:0031 A35200         MOV    [k],AX
//A[j]:=k;
9716:0034 8B165200       MOV    DX,[k]
9716:0038 A05400         MOV    AL,[j]
9716:003B 30E4           XOR    AH,AH
9716:003D 8BF8           MOV    DI,AX
9716:003F D1E7           SHL    DI,1
9716:0041 89955400       MOV    [j+DI],DX
//j:=j+1;
9716:0045 A05400         MOV    AL,[j]
9716:0048 30E4           XOR    AH,AH
9716:004A 40             INC    AX
9716:004B A25400         MOV    [j],AL
//end;
9716:004E EBCA           JMP    001A
end;
end;
 { while j<=11 do
 begin
 if j<>7 then
 begin
 k:=k+j;
 end;
 A[j]:=k;
 j:=j+1;
 end; }
 for j:=1 to 11 do
 write(A[j]:4);writeln;
End.
