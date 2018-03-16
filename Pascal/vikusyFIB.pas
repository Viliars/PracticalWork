program Viktorya;
var
p,x1,x2,v:longint;



begin
  x1:=1; x2:=1;

readln(p); v:=1;
while v<p do begin
v:=x1+x2;
x1:=x2;
x2:=v;
end;

if v=p then
writeln('YES');
if v<>p then writeln('NO');
end.
