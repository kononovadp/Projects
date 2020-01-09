program z1;
uses crt;
const
  cq=9; //кол-во комманд
  rq=33; //общее кол-во команд и регистров
var s:string; i:byte; f:text;
  coms: array[1..cq] of string;
  regs: array[1..rq] of string;
begin
assign(f,'InitialData.txt'); reset(f);
while i<cq do begin
inc(i); readln(f,s); coms[i]:=s; end;
while not (eof(f)) do begin
inc(i); readln(f,s); regs[i]:=s; end;
close(f);
for i:= 1 to cq do writeln(coms[i]);
readln;
end.
