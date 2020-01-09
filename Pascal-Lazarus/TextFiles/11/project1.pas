program TextFile;
var f,g:text; s,fam,im,ot,s2:string; k,i,l,n:byte; ch:char;
begin
{$I-} {змінюємо режим контролю помилок вводу-виводу}
assign(f,'file-f.txt');reset(f); assign(g,'file-g.txt');rewrite(g);
{$I+} {повертаємо режим контрою помилок вводу-виводу в попередній стан}
If IOResult <> 0 then begin
writeln('File file-f.txt does not exist. The program can not be executed!'); readln; exit; end;
if eof(f) then begin
writeln('File is empty. The program can not be executed!'); readln; exit; end
else begin
fam:='';
writeln('SOURCE FILE F:');
  while not (eof(f)) do begin
    readln(f,s); writeln(s); fam:=s; S2:='';
      for i:=1 to length(fam) do if s[i]=' ' then delete(fam,i+1,length(fam)-i);
      for i:=1 to length(s) do
    if (s[i] = ' ') then s2:=s2+s[i+1]+'. ';
    fam:=fam+s2;writeln(g,fam);
  end;
writeln; writeln('RESULTANT FILE G:');reset(g);
while not (eof(g)) do begin readln(g,fam); writeln(fam); end;
close(f); close(g); readln;
end; end.
