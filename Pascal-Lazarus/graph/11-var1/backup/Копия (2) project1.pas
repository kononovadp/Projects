program sin_x;
uses crt,graph;
var a,x, y, x0, y0, k, vga,vgahi,xc,yc,l,i,s,dx,dy:smallint; r,hl,hr,t:real; m:string;
begin
t:=0.2*3.14;
writeln('a= ');readln(a);
if a<=0 then begin writeln('Incorrect value'); readln;exit;
//writeln('b= ');readln(b);
end;
initgraph(vga,vgahi,'');

 Line(40,420,640,420);
 Line(40,420,40,20);
 SetTextStyle(DefaultFont,HorizDir,1);
 SetTextJustify(CenterText,TopText);
 OutTextXY(40,430,'0');
 FOR i:=1 TO 5 DO
  begin
   Line(40+i*100,420,40+i*100,410);//деления оси x
   Str(i/2:3:0,m);
   OutTextXY(40+i*100,430,m);
  end;

 SetTextJustify(RightText,CenterText);//деления оси y
 FOR i:=0 TO 10 DO
  begin
   Line(40,420-i*40,50,420-i*40);
   Str(i/2:3:0,m);
   OutTextXY(35,420-i*40,m);
  end;

{line(20,240,620,240);//ось x
Str(i/2:3:1,S);
OutTextXY(20,250,'*Pi');
line(320,20,320,400);}//ось y
X0:=320;
Y0:=240;
k:=50;
xc:=getmaxx div 3;
yc:=getmaxY div 2;
t:=0;
while t<=2*pi do
 begin
  r:=a*cos(t)+l;
  x:=round(xc+r*cos(t));
  y:=round(yc-r*sin(t));
  putpixel(x,y,14);
  t:=t+0.001;
 end;
//for X:=-320 to 320 do
//begin
//x:=round(a*sqr(cos(t))+b*cos(t));
//y:=round(a*cos(t)*sin(t)+b*sin(t));
//y:=trunc(k*sin(x/k));
PutPixel(x0+x,y0-y,4);

OutTextXY (50,440,'x=acos^2t+bcost, y=acostsint+bsint,a>0,tE0,2pi Vikonav Kononov M. A.');
readln;
closegraph;
end.
