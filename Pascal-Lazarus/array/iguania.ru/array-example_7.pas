program z3;
var
	n:longint;
        z:byte;
       a:set of byte;

begin
         write('n = '); readln(n);
         a:=[];
     while n>0 do
        begin
         z:=n mod 10;  a:=a+[z];
         n:=n div 10;      end;
for z:= 0 to 9 do
  if not(z in a) then write(z:3);

   readln;
end.
