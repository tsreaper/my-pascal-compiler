program test_func_basic;
var a, b, c: integer;
function sum2(a: integer; b: integer): integer;
    begin
        sum2 := a + b;
    end;
function sum3(a: integer; b: integer; c: integer): integer;
    begin
        sum3 := sum2(sum2(a, b), c);
    end;
begin
    read(a, b, c);
    writeln(sum2(a, b));
    writeln(sum3(a, b, c));
end.
