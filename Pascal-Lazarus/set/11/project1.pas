program set11;
type per=(f,g,h,k,l,m,n,o,p,q);
var a,b,c,d,e,x:set of per; i:per; j:byte;
  begin
    a:=[ f,g,h,k,l,m,n,o,p,q];
    write('Set A:  ');
    for i:=f to q do if i in a then write(i:2);  writeln;
    write('Set B:  ');
    b:=[f,l,m,p,q];
    for i:=f to q do if i in b then write(i:2);  writeln;
    write('Set C:  ');
    c:=[f,g,h,n,o,p,q];
    for i:=f to q do if i in c then write(i:2);  writeln;
    write('Set D:  ');
    d:=[f,g,h,n] ;
    for i:=f to q do if i in d then write(i:2);  writeln;
    write('Set E:  ');
    e:=[f,n,o,p,q];
    for i:=f to q do if i in e then write(i:2);  writeln;
    if a*c=e+d then begin x:=a+(b-c-d-e);
    writeln('Condition a*c=e+d of variant 11 is true and x=a+(b-c-d-e)');
    write('Set X:  ');
    for i:=f to q do if i in x then write(i:2);
    end
    else  begin x:=a-b-(c*d*e);
    writeln('Condition a*c=e+d of variant 11 is false and x=a-b-(c*d*e)');
    write('Set X:  ');
    for i:=f to q do if i in x then write(i:2); end; writeln;
    write('----------------------------------------------------------');
    writeln;
    a:=[ f,g,h,k,l,m,o,p,q];
    write('Set A:  ');
    for i:=f to q do if i in a then write(i:2);  writeln;
    write('Set B:  ');
    b:=[f,l,m,p,q];
    for i:=f to q do if i in b then write(i:2);  writeln;
    write('Set C:  ');
    c:=[f,g,h,o,p,q];
    for i:=f to q do if i in c then write(i:2);  writeln;
    write('Set D:  ');
    d:=[f,g,n] ;
    for i:=f to q do if i in d then write(i:2);  writeln;
    write('Set E:  ');
    e:=[f,n,p,q];
    for i:=f to q do if i in e then write(i:2);  writeln;

    if a*c=e+d then begin x:=a+(b-c-d-e);
    writeln('Condition a*c=e+d of variant 11 is true and x=a+(b-c-d-e)');
    write('Set X:  ');
    for i:=f to q do if i in x then write(i:2);
    end
    else  begin x:=a-b-(c*d*e);
    writeln('Condition a*c=e+d of variant 11 is false and x=a-b-(c*d*e)');
    write('Set X:  ');
    for i:=f to q do if i in x then write(i:2); end; writeln;
    readln;
    end.
