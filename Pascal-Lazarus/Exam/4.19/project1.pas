{Составить процедуру, позволяющую определить позицию первого вхождения в
заданную строку какого-либо символа из второй заданной строки. Результатом
работы процедуры должна быть -1, если первая строка не содержит ни одного
символа, принадлежащего и второй заданной строке.}
program z1;
var a,b: string; i,j,c: integer;
  begin

    readln(a);
    readln(b); i:=1; j:=1;
    while i<length(a) do
    begin
    while j<length(b) do
    if a[i]=b[j] then begin write(i); i:=300; j:=300; end
                 else  j:=j+1;
    i:=i+1;
    end;
    if i<300 then writeln('-1');
    readln;
 end.
