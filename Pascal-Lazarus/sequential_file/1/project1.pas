{1. Знайти найменше зі значень компонета з парними  номерами.}
program z1;
var f:file of integer; x,min:integer; i,n:byte;
procedure createfile;
//var f:file of real; x:real;i,n:byte;
begin
  assign(f,'text.dat');rewrite(f);
  n:=10;
  for i:=1 to n do
  begin
    x:=i+round(exp(ln(2)*i));
    write(f,x);
    end;
end;
begin
   createfile; reset(f); min:=x;
   writeln('components of file:');
   while not (eof(f)) do begin
   read (f,x); min:=x;writeln(x);

   if (x<min) and (x mod 2 = 0) then min:=x;
   end;
   writeln('min= ',min); readln; close(f); end.
   {reset(f);
   //reset(f);
   // read(f,x); writeln(x);
   //read(f,x); min:=x;  writeln(x);
   while not (eof(f)) do
   begin
     read(f,x);//writeln(x);
     if (x<min) and (filepos(f) mod 2=0)then min:=x;
   end;
    writeln;
   write(min); readln;close(f);
end.        }
