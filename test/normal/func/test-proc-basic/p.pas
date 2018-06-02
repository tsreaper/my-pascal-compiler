program test_proc_basic;
var n, m: integer;
procedure p3(a: integer; b: integer);
    begin
        writeln(a);
        writeln(b);
    end;
procedure p2(a: integer);
    begin
        writeln(a);
        p3(a, 300);
    end;
procedure p1;
    begin
        p2(200);
    end;
begin
    read(n, m);
    p1();
    p2(n);
    p3(n, m);
end.
