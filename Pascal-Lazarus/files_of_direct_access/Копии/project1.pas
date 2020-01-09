program z1;
var f:file of real; x,y:real; k,i,l,n:byte;
  begin
     assign(f,'text.dat');rewrite(f);
    n:=10;
    for i:=1 to n do
    begin
      x:=i;
      write(f,x); writeln(x);
      end;   close(f);
      readln;
    assign(f,'text.dat');reset(f);

    k:=filesize(f);
    for l:=1 to k div 2 do begin  //кол-во шагов вставки
      seek(f,k-1); read(f,y);   //считываем последний элемент
      for i:= k-2 downto 2*l-1 do  //цикл от предпоследнего до места вставки
      begin
        seek(f,i); read(f,x); write(f,x); //здвигаем элементы
      end;
        seek(f,2*l-1); write(f,y); //в место вставки записываем последний элемент
    end;
    close(f); writeln;
      assign(f,'text.dat');reset(f);
      while not (eof(f)) do begin read(f,x); writeln(x:0:3); end;
      close(f); readln;


      end.

