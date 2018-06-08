program test_fillchar;
var
    i: integer = 7;
    c: char = 'x';
    a: array [1..2, 'a'..'c'] of integer;
var
    li: integer;
    lc: char;

begin
    fillchar(i, sizeof(i), 0);
    fillchar(c, sizeof(c), 'a');
    fillchar(a, sizeof(a), -1);

    writeln(i);
    writeln(c);
    for li := 1 to 2 do for lc := 'a' to 'c' do writeln(a[li, lc]);
end.
