Var k:integer;
 j:byte;
 A:array[1..11] of integer;
Begin
 k:=3; j:=1;
 while j<=11 do begin
 if j<>7 then
 k:=k+j;
 A[j]:=k;
 j:=j+1;
 end;
 for j:=1 to 11 do
 write(A[j]:4);writeln;
 readln;{добавил readln, чтобы увидеть результат}
End.