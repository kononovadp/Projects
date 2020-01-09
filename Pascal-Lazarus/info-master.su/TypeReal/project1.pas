program ve;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

var  xr : real;
    xs : single;
    xd : double;
    xe : extended;
    xc : comp;
    xm : currency;

begin
  Writeln('Real     : ', xr);
  Writeln('Single   : ', xs);
  Writeln('Double   : ', xd);
  Writeln('Extended : ', xe);
  Writeln('Comp     : ', xc);
  Writeln('Currency : ', xm);

  Readln;
end.
