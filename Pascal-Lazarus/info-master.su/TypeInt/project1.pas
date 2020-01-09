program td;

{$mode objfpc}{$H+} //длинный тип integer
{{$mode tp}{$H+}}//"короткий" тип integer

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

begin
  Writeln('Byte : ', Low(Byte), '..', High(Byte));
  Writeln('Shortint : ',  Low(Shortint), '..', High(Shortint));
  Writeln('Smallint : ',  Low(Smallint), '..', High(Smallint));
  Writeln('Word : ',  Low(Word), '..', High(Word));
  Writeln('Integer : ',  Low(Integer), '..', High(Integer));
  Writeln('Cardinal : ',  Low(Cardinal), '..', High(Cardinal));
  Writeln('Longint : ',  Low(Longint), '..', High(Longint));
  Writeln('Longword : ',  Low(Longword), '..', High(Longword));
  Writeln('Int64 : ',  Low(Int64), '..', High(Int64));
  Writeln('QWord : ',  Low(QWord), '..', High(QWord));

  Readln;
end.
