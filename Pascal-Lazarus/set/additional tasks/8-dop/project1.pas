{8. Дано натуральне число N. Описати функцію Digit від параметра N, яка
підраховує кількість різних цифр в десятковому записі натурального числа N.}
program z1;
var i,m:byte; n:longint; k:set of byte;
function digit(n:integer):byte;
begin
    m:=0;
    while n>0 do begin
    i:=n mod 10; n:= n div 10;  if not (i in k) then k:=k+[i]; end;
    for i:=0 to 9 do if i in k then m:=m+1;
    digit:=m;
end;
begin
   read(n);
   n:=digit(n); writeln(n);
   readln; readln;
end.

{program z1;
var i,n,m:byte;  k:set of byte;
function digit(n:byte):byte;
begin m:=0;
   while n>0 do begin
   i:=n mod 10; n:= n div 10; k:=k+[i]; end;
   for i:=0 to 9 do if i in k then m:=m+1;
   digit:=m;
end;
begin
   readln(n);
   n:=digit(n); write(n);
   readln;
end.}
