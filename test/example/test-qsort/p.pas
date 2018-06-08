program qsort;
var
    n: integer;
    a: array [1..10000] of integer;

procedure qsort(l,r:longint);
    var i,j,mid:longint;
    begin
        if l>=r then exit;
        i:=l; j:=r; mid:=a[l+random(r-l+1)];
        repeat
        begin
            while a[i]<mid do inc(i);
            while a[j]>mid do dec(j);
            if i<=j then
            begin
                a[0]:=a[i];a[i]:=a[j];a[j]:=a[0];
                inc(i);dec(j);
            end
        end
        until i>j
        qsort(l,j); qsort(i,r);
    end;

var i: integer;

begin
    read(n);
    for i:=1 to n do read(a[i]);
    qsort(1,n);
    for i:=1 to n do
    begin
        write(a[i]);
        if i < n then write(' '); else write('#10');
    end
end.
