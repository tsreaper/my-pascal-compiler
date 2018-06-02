program test_exit;
var
    tcase, a, b: integer;
function gcd(a: integer; b: integer): integer;
    begin
        if b = 0 then
        begin
            gcd := a;
            exit;
        end
        gcd := gcd(b, a mod b);
    end;
begin
    read(tcase);
    while tcase > 0 do
    begin
        tcase := tcase - 1;
        read(a, b);
        writeln(gcd(a, b));
    end
    exit;
    writeln('x');
end.
