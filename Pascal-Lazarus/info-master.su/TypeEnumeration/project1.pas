program enum;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type TSeasons = (Winter, Spring, Summer, Autumn);

var Seasons : TSeasons;

begin
  Writeln('Seasons : ', Low(Seasons), '..', High(Seasons));
  ReadLn;
end.
