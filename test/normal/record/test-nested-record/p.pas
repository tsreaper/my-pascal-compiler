program test_nested_record;
type
    r1 = record
        a, b: integer;
    end;
    r2 = record
        a, b: integer;
        c, d: r1;
        e: record
            a, b: integer;
        end;
    end;
var a: r2;

begin
    read(a.a, a.b);
    a.c.a := a.a * 2;
    a.c.b := a.b * 3;
    a.d.a := a.a * 4;
    a.d.b := a.b * 5;
    a.e.a := a.a * 6;
    a.e.b := a.b * 7;

    writeln(a.a);
    writeln(a.b);
    writeln(a.c.a);
    writeln(a.c.b);
    writeln(a.d.a);
    writeln(a.d.b);
    writeln(a.e.a);
    writeln(a.e.b);
end.
