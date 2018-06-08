program test_real_int_func;
var
    i, j: integer;
    a, b, c, d: real;
begin
    i := 1;
    j := -1;
    a := 7.7;
    b := -7.7;
    c := 3.3;
    d := -3.3;
    writeln(int(a)); writeln(int(b)); writeln(int(c)); writeln(int(d));
    writeln(int(i)); writeln(int(j));
    writeln(frac(a)); writeln(frac(b)); writeln(frac(c)); writeln(frac(d));
    writeln(trunc(a)); writeln(trunc(b)); writeln(trunc(c)); writeln(trunc(d));
    writeln(trunc(i)); writeln(trunc(j));
    writeln(round(a)); writeln(round(b)); writeln(round(c)); writeln(round(d));
    writeln(round(i)); writeln(round(j));
end.
