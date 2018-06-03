program test_record_ptr;
type
    r1 = record
        a, b: integer;
    end;
    r2 = record
        a, b: integer;
        c, d: r1;
    end;
var a: r2;

procedure p1(r: ^r1);
    begin
        read(r^.a, r^.b);
    end;

procedure p2(r: ^r2);
    begin
        read(r^.a, r^.b);
        p1(@(r^.c));
        p1(@(r^.d));
    end;

begin
    p2(@a);
    writeln(a.a);
    writeln(a.b);
    writeln(a.c.a);
    writeln(a.c.b);
    writeln(a.d.a);
    writeln(a.d.b);
end.
