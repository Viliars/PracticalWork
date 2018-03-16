program Vika;
type link=^list;
list=record
elem:integer;
next:link;
end;
var o,t,f,smin,smax:link;
x,n,i,min,max,j:integer;
sum:longint;

 {Для Вики, это процедура добавляет
 элемент в конец списка}
procedure insert(var l:link; k:integer);
var q,p:link;
begin
new(q);
 q^.elem:=x;
 q^.next:=nil;
  if l=nil then l:=q
  else p:=l;
   while p^.next<>nil do p:=p^.next;
  p^.next:=q;
 end;

begin

  readln(n);
  {отдельно читаю 1 элемент
  чтобы изначально значения макс и мин были заданы}
new(o);
read(x);
max:=x;
min:=x;
o^.elem:=x;
o^.next:=nil;
{потом продолжаю читать
и вставлять элементы процедурой}
 for i:=2 to n do begin
 read(x);
 insert(o,x);
 if i<n then
 end;
    {потом циклом прохожу, и ищу минимум и максимум
    запоминая при этом, ссылку на максимум
    и на минимум }
            f:=o;
 for i:=1 to n do begin
  if f^.elem<=min then begin
   min:=f^.elem;
   smin:=f;
  end;
  if f^.elem>=max then begin
   max:=f^.elem;
   smax:=f;

  end;
  f:=f^.next;
 end;

     sum:=0;

  {потом в зависимости от расположения мин и макс
  относительно друг друга, делаю 2 возможных варианта
  }
if nmin>nmax then begin
 f:=smax;
  while f<>smin^.next do begin
   sum:=sum+f^.elem;
   f:=f^.next;
  end;
end
  else begin
   f:=smin;
 while f<>smax^.next do begin
  sum:=sum+f^.elem;
  f:=f^.next;
 end;
 end;
  writeln(sum);

end.
