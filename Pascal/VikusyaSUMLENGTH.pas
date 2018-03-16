program Vyktorya;
var
p,v:integer;
i,x,y:integer;
 c:char;
begin
v:=0; p:=0;
   y:=0;
repeat
read(c);
p:=p+1;
if (c>='0') and (c<='9') then begin
x:=ord(c)-48;
v:=v+x;
end;
until c='.';
p:=p-1;
if p=v then writeln('YES');
if p<>v then writeln('NO');

end.
