var a:array[1..5,1..5] of byte;
  st,z:array[1..5] of byte;
  i,j,s,f,n,k:byte;
  begin
    randomize;
    for i:=1 to 5 do
        begin
        for j:=1 to 5 do    begin
    a[i,j]:=random(10);  write(a[i,j]:5); end;
        writeln;
        end;
 write('b= '); readln(s);   write('f= '); readln(f);

 for i :=1 to 5 do z[i]:=100;
  for i :=1 to 5 do st[i]:=100;
n:=1;  i:=s;  st[s]:=1; z[s]:=0;
while (n<5)and(st[f]=100) do
   begin
  for k:=1 to 5 do
      if st[k]=n then
            for j:=1 to 5 do
                if (a[i,j]>0 )and (z[j]>z[k]+ a[i,j])then
                      begin z[j]:=z[k]+ a[i,j]; st[j]:=n+1; end;


    for i :=1 to 5 do write(st[i],' (',z[i],')   - '); writeln;


   n:=n+1

   end;



  readln; end.

