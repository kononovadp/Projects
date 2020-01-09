uses sysutils;
var o,v,s,n,po,pv,ps:integer;   r:string;
function zp(o,v,s,n:longword):string;
var r:string; zo,zv,zs,po,pv,ps:longword;
begin
if (v div 2=0) or (s div 2=0) or (v+s<>o)
then begin zp:='0'; exit; end;

zv:=n div 2; zs:=zv; zo:=zv+zs;
po:=zo-o; pv:=zv-v; ps:=zs-s;

if po+pv+ps>n then r:='0' else
r:='Olexiy Pr = '+inttostr(po)+', Zp = '+inttostr(zo)+'|'+
   'Viktor PP = '+inttostr(pv)+', Zp = '+inttostr(zv)+'|'+
   'Sergiy PP = '+inttostr(ps)+', Zp = '+inttostr(zs);
zp:=r; end;
begin
readln(o); readln(v); readln(s); readln(n);
//writeln(zp(o,v,s,n));
ps:=(n+o+v-3*s) div 4; writeln(ps);
pv:=ps+s-v;   writeln(pv);
po:=2*pv+2*v-o; writeln(po);
 r:='Olexiy Pr = '+inttostr(po)+', Zp = '+inttostr(o)+'|'+
   'Viktor PP = '+inttostr(pv)+', Zp = '+inttostr(v)+'|'+
   'Sergiy PP = '+inttostr(ps)+', Zp = '+inttostr(s);
 writeln(r);
readln;
end.
