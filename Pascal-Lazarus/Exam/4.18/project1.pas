{Составить процедуру, в результате обращения к которой из первойзаданной
строки удаляется каждый символ, принадлежащий и второй заданной строке.}
program z1;
var a,b,c: string; i,j: byte;
  begin
    c:='';
    readln(a);
    readln(b);
    {for i:=1 to length(a) do
    for j:=1 to length(b) do
    if a[i]=b[j] then delete(a,i,1);
    writeln(a);readln;}

    for i:=1 to length(a) do
    if pos(a[i],b)=0 then c:= c+a[i];
    writeln(c);readln;

  end.
