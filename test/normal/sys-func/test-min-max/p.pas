program test_min_max;
var
    i, j: integer;
    a, b: real;

begin
    read(i, j, a, b);
    writeln(min(i, j)); writeln(min(j, i));
    writeln(min(a, b)); writeln(min(b, a));
    writeln(min(i, b)); writeln(min(b, i));
    writeln(max(i, j)); writeln(max(j, i));
    writeln(max(a, b)); writeln(max(b, a));
    writeln(max(i, b)); writeln(max(b, i));
end.
