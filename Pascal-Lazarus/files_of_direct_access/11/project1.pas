program z1;
var f:file of real; x,y:real; k,i,l,n:byte;
begin
assign(f,'text.dat');rewrite(f);
n:=10;
for i:=1 to n do
  begin
   x:=i;
   write(f,x); writeln(x:0:3);
  end;
close(f); readln;
    reset(f);
    k:=filesize(f);
for l:=1 to k div 2 do
  begin  //кількість кроків вставки
   seek(f,k-1); read(f,y);   //зчитування останнього елемента
   for i:= k-2 downto 2*l-1 do  //цикл від передостаннього елемента до місця вставки
     begin
      seek(f,i); read(f,x); write(f,x); //зсув елементів
     end;
   seek(f,2*l-1); write(f,y); //запис останнього елемента в місце вставки
  end;
close(f); writeln;
reset(f);
  while not (eof(f)) do
    begin
     read(f,x);
     writeln(x:0:3);
    end; close(f); readln;
end.
