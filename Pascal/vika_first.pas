program Vika;
type link=^list;
list=record
elem:integer;
next:link;
end;
var o,p,q,t:link;
x,n,i,e,e1,j:integer;
sum:longint;


{ процедура вставляющая элемент
в конец списка}
procedure insert(var l:link; k:integer);
var q,p:link;
begin
new(q);
 q^.elem:=k;
 q^.next:=nil;
  if l=nil then l:=q
  else p:=l;
   while p^.next<>nil do p:=p^.next;
  p^.next:=q;
 end;
    {процедура удаляющая повторы в списке
    ОСНОВНОЙ АЛГОРИТМ ПРОГРАММЫ}
 procedure delete_povtor(r:link);
var p,q,t: link;
begin
while r^.next<>nil do
begin
 p:=r;
 while p^.next<>nil do begin
 if p^.next^.elem=r^.elem then begin
 q:=p^.next; p^.next:=p^.next^.next;
  dispose(q);
   end
   else p:=p^.next;
  end;
 if r^.next<>nil then r:=r^.next;
end;
end;





begin

  readln(n);  {начало считывания
  рекомендую заменить мое считывание своим}
 if n>0 then begin
  new(o);
  read(x);
  o^.elem:=x;
  o^.next:=nil;         {серьезно,он запалит}
 for i:=2 to n do begin
 read(x);
 insert(o,x);
 end;

delete_povtor(o); {вызов основного алгоритма}

             {вывод ответа}
while o<>nil do begin
  write(o^.elem,' ');
     o:=o^.next;
  end;
  end;
end.
