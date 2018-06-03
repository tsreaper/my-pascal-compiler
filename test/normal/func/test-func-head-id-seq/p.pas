program test_func_head_id_seq;
var a, b, c: integer;

function f(a, b, c: integer; d: boolean): integer;
    begin
        if d then
            f := a * b * c;
        else
            f := a + b + c;
    end;

begin
    read(a, b, c);
    writeln(f(a, b, c, true));
    writeln(f(a, b, c, false));
end.
