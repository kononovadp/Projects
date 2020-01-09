{1. Описати тип об'єкт, що містить:
поля: показівник на голову списку та його ідентифікатор у символьному вигляді;
методи: побудова однозв'язного списку, його виведення, вилучення i-го елементу.
Реалізувати екземпляр цього типу та виконати над ним всі можливі дії.}
program oop1;
uses crt;
type
pointer = ^list;
list = record
    El: string;
    next: pointer;
end;
spisok=object
headpointer:pointer; name:string;
    procedure buildlist;
    procedure deleteelement;
    procedure listoutput;
end;
procedure spisok.BuildList;
var y,t:pointer; i:string;  j,k:byte;
begin
write('Title of the list:  '); readln(i);
write('Quantity of elements:  '); readln(k);
new(y);
y^.el:=i;
y^.next:=nil;
t:=y; headpointer:=y;
 for j:= 1 to k do
 begin    new(y);
   write('string ',j,': '); readln(i);
y^.el:=i;
t^.next:=y;
   y^.next:=nil;   t:=y;
 end;
end;
procedure spisok.DeleteElement;
var x,dx:pointer;  i:string; k,j:byte;
begin
write('enter a number of deleted element '); read(k);readln;
  x:=headpointer;
  for j:=1 to k-1 do x:= x^.next;
  dx:=x^.next;
x^.next:=dx^.next; dispose(dx);
end;
procedure spisok.ListOutput;
var q: pointer;
begin
q:=headpointer;
while q<>nil do begin
  writeln(q^.el);
  q:=q^.next;
end;
end;
var  sp:spisok;
begin
  sp.BuildList;
  sp.ListOutput;
  sp.DeleteElement;
  sp.ListOutput;
  readln;
end.
