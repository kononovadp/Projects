{2. Перевірити чи існує файл}
program z1;
var f:file of integer;
  ch: char;
  st:string;
  begin
write('enter a file name');
readln(st);
assign(f,st);
{$i}
reset(f);
{$i+}
if ioresult=0 then begin write('file exists'); close(f); end
else write('file ',st,'does not exist');
readln;
  end.

