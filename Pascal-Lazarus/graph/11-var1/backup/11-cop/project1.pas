uses crt, graph;
//const
     //grPath= 'C:\BP7\BGI';



var grDriver, grMode, Midx, Midy ,Errcode, g: Integer;
t,X,Y:Real;
a1:char;
procedure xx(A,B:integer);
begin
for g:=0 to 360 do begin
      t:=g*Pi/180;        {perevogimv radiani}
      X:=MidX+A*Sqr(cos(t))+B*cos(t);
      Y:=MidY+A*cos(t)*sin(t)+B*sin(t);
      if g=0 then
      MoveTo(Round(X), Round(Y)) else LineTo(Round(X),Round(y));
      end;
      end;
   begin
       Errcode:=graphresult;
      if Errcode<>grOk then
      begin
           Writeln(GraphErrorMSG(errcode));

      end;
begin
      //grDriver:=detect;
      //InitGraph(grDriver, grMode,grPath);
      MidX:=GetMaxX div 2;
      MidY:=GetMaxY div 2;



      repeat        {cikl}
      setfillstyle(1,BLACK);
      a1:=readkey;            {kak bi prisvaivaem funkciy perekluchenia}
      bar(0,0,640,480);          {risyet chernui priamougolnik}
      Line(0,GetMaxY div 2, GetMaxX, GetMaxY div 2);       {risyet osi}
      Line(GetMaxX div 2, 0, GetMaxX div 2, GetMaxY);

      if a1='q' then       xx(20,60);  {b>2a}
      if a1='w' then       xx(30,40);   {a<b<2a}
      if a1='e' then       xx(60,40) ;    {a>b}

      until a1='r'; {zakonchit cikl, poka ne nagmete klavishy r}
      CloseGraph;
end;end.
