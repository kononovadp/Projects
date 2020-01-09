program graph1;
uses SysUtils,graph,crt;
var b,a,vga,vgahi,xc,yc,i,xend,yend,xbeg,ybeg,xp,yp,c,cx,cy,k,kba:smallint;
    t,mx,my,xmin,xmax,ymin,ymax,x,y:real;
    m,sa,sb,scx,scy: string;
    cord:array[1..1000,1..2] of real;
label l1;
begin
l1:write('a= '); readln(a); write('b= '); readln(b); kba:= a+b;
if (kba<=28) or (kba>=-28) then k:=1; if (kba>=28) or (kba<=-28) then k:=5;
if (kba>=100) or (kba<=-100) then k:=50;
write('camber X= '); readln(cx); write('camber Y= '); readln(cy);
write('Press 0 to display the figure horizontally or 1 to display it vertically ');
readln(c);
if (c<0) or (c>1) then begin writeln('Incorrect parameter value!');goto l1; end;
sa:=sa+(IntToStr(a)); sb:=sb+(floatToStr(b));
scx:=scx+(floatToStr(cx)); scy:=scy+(floatToStr(cy));
initgraph(vga,vgahi,'C:\tp7\bgi');
t:=0; i:=1;   xmin:=-10;xmax:=10;ymin:=-10; ymax:=10;
xc:=getmaxx div 2; yc:=getmaxY div 2;
xbeg:=10; xend:=getmaxx-10;
ybeg:=10; yend:=getmaxy-10;
while t<2*pi do
 begin
  if c= 1 then begin
  x:=(-a*cos(t-cx/10)*sin(t-cx/10)+b*sin(t-cx/10));
  y:=(-a*sqr(cos(t-cy/10))+b*cos(t-cy/10)); end
  else begin
  x:=(a*sqr(cos(t-cx/10))+b*cos(t-cx/10));
  y:=(a*cos(t-cy/10)*sin(t-cy/10)+b*sin(t-cy/10)); end;
  if x>xmax then xmax:=x;   if x<xmin then xmin:=x;
  if y>ymax then ymax:=y;   if y<ymin then ymin:=y;
  cord[i,1]:=x;   cord[i,2]:=y; i:=i+1;
  t:=t+0.01; //крок зміни аргумента
 end;
mx:=(xend-xbeg)/(xmax-xmin)/2;//масштаб по осі X
my:=(yend-ybeg)/(ymax-ymin)/2;//масштаб по осі Y
for i:=1 to 1000 do
 begin
  xp:=round(cord[i,1]*mx)+xc;
  yp:=round(cord[i,2]*my)+yc;
  putpixel(xp,yp,14);
 end;
Line(0,yc,getmaxx,yc);
Line(xc,0,xc,getmaxy);
OutTextXY(xc-8,yc+8,'0');
//шкала по осі X
for i:=kba+100 downto -kba-100 do begin
Line(round(xc+(mx*i)*k),yc+10,round(xc+(mx*i)*k),yc-10);
Line(xc+10,round(yc+(my*i)*k),xc-10,round(yc+(my*i)*k));
end;
//нумерація шкали по осі Х до центра
for i:= -kba-100 to -1 do begin
 Str(i,m);
 OutTextXY(round(xc+(mx*i)*k)-10,yc+20,m);
end;
//нумерація шкали по осі Х від центра
for i:= 1 to kba+100 do begin
 Str(i,m);
OutTextXY(round(xc+(mx*i)*k)-2,yc-20,m);
end;
//нумерація шкали по осі Y до центра
for i:= -kba-100 to -1 do begin
 Str(i,m);
 OutTextXY(xc+20,round(yc+(my*i)*k)-3,m);
end;
//нумерація шкали по осі Y від центра
for i:= 1 to kba+100 do begin
 Str(i,m);
 OutTextXY(xc-32,round(yc+(my*i)*k)-3,m);
end;
setcolor(3);
SetTextStyle(8,0,2); OutTextXY(xbeg,yend-25,'Performed by Kononov M. A.');
SetTextStyle(DefaultFont, HorizDir,2);
OutTextXY(xbeg,ybeg,'A = '+SA+'  Camber X = '+scx);
OutTextXY(xbeg,ybeg+20,'B = '+SB+'  Camber Y = '+scy);
if c=0 then begin
OutTextXY(xbeg,ybeg+40,'x = a cos t + b cos t');
OutTextXY(xbeg,ybeg+60,'y = a cos t sin t + b sin t');
SetTextStyle(DefaultFont, HorizDir,1); OutTextXY(xbeg+143,ybeg+37,'2');
end else begin
OutTextXY(xbeg,ybeg+40,'x = a cos t sin t + b sin t');
OutTextXY(xbeg,ybeg+60,'y = a cos t + b cos t');
SetTextStyle(DefaultFont, HorizDir,1); OutTextXY(xbeg+143,ybeg+57,'2');
end;
readln;
closegraph;
end.
