uses sysutils;
var n,i:integer; s1,s2,r,otv:string;  e:boolean;
  function f(n:integer):integer;
  begin
    if n<3 then f:=1 else f:=f(n-1)+f(n-2);
  end;

 begin
 readln(s1); readln(s2);  e:=true;
 n:=1;

 while (e) do
 for i:=1 to length(s1)-n+1 do
 begin  r:=copy(s1,i,n);   e:=false;
        if pos(r,s2)>0 then begin otv:=r; n:=n+1; e:=true; break; end  ;
      // writeln(n);
 end;



 writeln(otv);
 readln;
end.
