{11 варіант.
2. Описати тип динамічний об'єкт, що містить:
поля: вектор, його розмір та його ідентифікатор у символьному вигляді;
методи: конструктор, деструктор, введення вектора, виведення вектора, сортування
за зростанням елементів вектора. Реалізувати екземпляр цього типу та виконати
над ним всі можливі дії.}
Uses crt;
Type
mas= array of integer;
vektor=object
v:mas; size:byte; name:string;
Constructor Init(n:string;s:byte);
Destructor DeleteObject; Virtual;
procedure input;
procedure output;
procedure sort;
end;

Constructor vektor.init(n:string;s:byte);
begin
name:=n; size:=s;
SetLength(v,size);
end;


procedure vektor.input;
var  i:integer;
begin
writeln('enter elements of array, ',size,' item');
   for i:=1 to size do begin
    readln(v[i]);
   end;
end;

Destructor vektor.DeleteObject;
var i:byte;
begin
SetLength(v,0); size:=0;
end;

procedure vektor.output;
var  i:integer;
begin
writeln(name);
for i:=1 to size do write(v[i],'   '); writeln;
end;

procedure vektor.sort;
var k,l,n,j,s:integer;
begin
n:=10;  s:=0;
 while n>1 do
  begin
   s:=s+1;
   n:=1;
   for l:=1 to 10-s do
   if v[l]>v[l+1] then
   begin
     j:=v[l];
     v[l]:= v[l+1];
     v[l+1]:=j;
     n:=l;
   end;
 end;
end;

var a:vektor;
begin
a.init('A',10);//конструктор
a.output;
a.input;   a.output;
a.sort;  writeln('sorted array:');   a.output;
a.DeleteObject;//деструктор
writeln('object deleted');  a.output;//проверка
readln;
end.
