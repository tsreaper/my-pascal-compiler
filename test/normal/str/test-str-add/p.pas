program test_str_add;
var
    a, b, c: string[3];
    d, e: string[6];
    f: string[9];
    g: string[12];

begin
    readln(a, b, c, d, e, f);
    writeln(a + b + c);
    writeln(a + b + c + d + e + f);
    writeln(concat(a, b) + concat(c, d) + concat(e, f));
    writeln(concat(a, b) + concat(c, d, e + f));
    g := a + ((b + c) + (d + e) + f);
    writeln(g);
end.
