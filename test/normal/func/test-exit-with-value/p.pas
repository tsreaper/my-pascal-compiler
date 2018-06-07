program test_exit_with_value;
var
    tcase, a, b: integer;
function gcd(a: integer; b: integer): integer;
    begin
        if b = 0 then exit(a); else exit(gcd(b, a mod b));
    end;
begin
    read(tcase);
    while tcase > 0 do
    begin
        tcase := tcase - 1;
        read(a, b);
        writeln(gcd(a, b));
    end
    exit(0);
    writeln('x');
end.
