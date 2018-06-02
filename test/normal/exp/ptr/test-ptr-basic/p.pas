program test_ptr_basic;
var
    a: integer;
    b: ^integer;
    c: ^^integer;
    d: ^^^integer;
begin
    d := @c;
    c := @b;
    b := @a;

    a := 1;
    writeln(a, b^, c^^, d^^^);
    writeln((c^)^, (d^)^^, (d^^)^);
    writeln((@a)^, (@b)^^, (@c)^^^, (@d)^^^^);

    a := 2;
    writeln(a, b^, c^^, d^^^);
    writeln((c^)^, (d^)^^, (d^^)^);
    writeln((@a)^, (@b)^^, (@c)^^^, (@d)^^^^);
end.
