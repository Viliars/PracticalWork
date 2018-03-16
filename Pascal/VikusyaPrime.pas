program Viktoria;
var j,v,p:longint;
begin
readln(p);
for v:=1 to p do
if p mod v=0 then
j:=j+1;
if (j=2) or (j=1) then
writeln('YES');
if (j<>2) and (j<>1) then writeln('NO');
end.
