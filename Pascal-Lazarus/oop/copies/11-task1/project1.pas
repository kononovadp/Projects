{11 варіант.
1. Описати тип об'єкт, що містить:
поля: показівник на голову списку та його ідентифікатор у символьному вигляді;
методи: побудова однозв'язного списку, його виведення, вилучення i-го елементу.
Реалізувати екземпляр цього типу та виконати над ним всі можливі дії.
2. Описати тип динамічний об'єкт, що містить:
поля: вектор, його розмір та його ідентифікатор у символьному вигляді;
методи: конструктор, деструктор, введення вектора, виведення вектора, сортування за зростанням елементів вектора.
Реалізувати екземпляр цього типу та виконати над ним всі можливі дії.}
uses crt;
type
  pointer = ^list;
  list = record
    Info_head,Info_middle,Info_end: string;
    next: pointer;
  end;
var phead,pmiddle,pend:pointer; m,k:byte;
procedure AddHead(var t:pointer);
var y,p:pointer; i:string;
begin
write('Title of the list:  ');
new(y);
readln(i);
y^.Info_head:=i;
y^.next:=t;
t:=y;
end;

procedure AddMiddle(var t:pointer);
var x,p,q:pointer; i:string; k,n:byte;
begin
write('Number of fields:  ');
readln(n);
  for k:=1 to n do begin
    new(x);
    write('st ',k,': ');read(i); readln;
    x^.Info_middle:=i;
    x^.next:=t;
    t:=x;
  end;
m:=0;
end;

procedure AddEnd(var t:pointer);
var z,p:pointer; i:string;
begin
new(z);
i:='End of list';
z^.Info_end:=i;
z^.next:=t;
t:=z;
end;

procedure DeleteLastElement;
var x,dx:pointer;  i:string; k:byte;
begin
x:=pmiddle; pmiddle:=x^.next; dispose(x);
m:=1;
end;

{procedure DeleteFirstElement;
var x,dx:pointer;  i:string; k:byte;
begin
x := pmiddle; {Запомним адрес первого элемента списка}
pmiddle := x^.Next; {Теперь Head указывает на второй элемент списка}
Dispose(x); {Освободим память, занятую переменной x^}
{ f := pmiddle;
  dx :=pmiddle;
  while f^.Next<>Nil do
    Begin
      dx := f;
      f := f^.Next;
    End;
  {Удаляем элемент x^ из списка и освобождаем занимаемую им память}
  dx^.Next := Nil;
  Dispose(f); }
m:=2;
end; }

procedure ListOutput;
var q: pointer;
begin
k:=0;
case m of
0: writeln('----------Output of entered list----------');
1: writeln('----------Last element was deleted----------');
{2: writeln('----------First element was deleted----------');
3: writeln('----------Selected element was deleted----------');}
end;
q:=phead;
while q<>nil do begin
  writeln(q^.Info_head);
  q:=q^.next;
end;
q:=pmiddle;
while q<>nil do begin
  k:=k+1;
  writeln('st ',k,': ',q^.Info_middle);
  q:=q^.next;
end;
q:=pend;
while q<>nil do begin
  writeln(q^.Info_end);
  q:=q^.next;
end;
end;

begin
    AddHead(phead);
    AddMiddle(pmiddle);
    AddEnd(pend);
    ListOutput;
    DeleteLastElement;
    ListOutput;
    readln;
    end.
