{9. Дано натуральне число N. Описати функцію Print від параметра N, яка друкує
в порядку зростання всі цифри, які не входять в десятковий запис натурального числа N.}
program z1;
var i,n,m:word;  k:set of byte;
function Print(n:word):byte;
  begin m:=0;
  while n>0 do begin
  i:=n mod 10; n:= n div 10; k:=k+[i];   end;
  for i:=0 to 9 do if not (i in k) then write(i);
  Print:=m;
  end;
begin
  readln(n);
  n:=Print(n);
  readln;
end.
