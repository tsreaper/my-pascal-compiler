program test_deref_lhs;
var
    a, b: integer;
    c: ^integer;
procedure swap(a: ^integer; b: ^integer);
    var c: integer;
    begin
        c := a^;
        a^ := b^;
        b^ := c;
    end;
begin
    a := 1;
    b := 2;
    writeln(a, b);

    swap(@a, @b);
    writeln(a, b);

    swap(@a, @b);
    writeln(a, b);

    c := @a;
    for c^ := 1 to 3 do writeln(a);
end.
