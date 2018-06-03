program test_record_with_ptr;
type t = record
    a, b: integer;
    c, d: ^integer;
end;
var a: t;

begin
    read(a.a, a.b);
    writeln(a.a);
    writeln(a.b);

    a.c := @a.a;
    a.d := @a.b;
    a.c^ := a.a * 2;
    a.d^ := a.b * 2;
    writeln(a.a);
    writeln(a.b);
end.
