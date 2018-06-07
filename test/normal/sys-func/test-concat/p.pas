program test_concat;
var
    a, b, c: string[3];
    d, e: string[6];
    f: string[9];
    g: string[12];

begin
    readln(a, b, c, d, e, f);
    writeln(concat(a, b, c));
    writeln(concat(a, b, c, d, e, f));
    writeln(concat(concat(a, b), concat(c, d), concat(e, f)));
    writeln(concat(concat(a, b), concat(c, d, concat(e, f))));
    g := concat(a, b, c, d, e, f);
    writeln(g);
end.
