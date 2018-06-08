program test_inc_dec;
var
    i: integer;
    c: char;

begin
    i := 7;
    writeln(i);
    inc(i);
    writeln(i);
    inc(i, 7);
    writeln(i);
    inc(i, i + 7);
    writeln(i);

    i := 3;
    c := 'a';
    writeln(c);
    inc(c);
    writeln(c);
    inc(c, 3);
    writeln(c);
    inc(c, i);
    writeln(c);

    i := 7;
    writeln(i);
    dec(i);
    writeln(i);
    dec(i, 7);
    writeln(i);
    dec(i, i + 7);
    writeln(i);

    i := 3;
    c := 'z';
    writeln(c);
    dec(c);
    writeln(c);
    dec(c, 3);
    writeln(c);
    dec(c, i);
    writeln(c);
end.
