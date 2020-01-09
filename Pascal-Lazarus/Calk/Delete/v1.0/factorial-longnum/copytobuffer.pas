{$mode delphi}
uses windows, sysutils;
 
procedure ToBuffer(s: string);
var
  len: integer;
  Data: THandle;
  DataPtr: Pointer;
begin
  if OpenClipboard(0) then
    try
      len := Length(s) + 1;
      Data := GlobalAlloc(GMEM_DDESHARE or GMEM_MOVEABLE, len);
      try
        DataPtr := GlobalLock(Data);
        try
          Move(pchar(s)^, DataPtr^, len);
          EmptyClipboard;
          SetClipboardData(CF_TEXT, Data);
        finally
          GlobalUnlock(Data);
        end;
      except
        GlobalFree(Data);
      end;
    finally
      CloseClipboard;
    end;
end;
 
begin
  ToBuffer('another hello from fpc !!!');
end.