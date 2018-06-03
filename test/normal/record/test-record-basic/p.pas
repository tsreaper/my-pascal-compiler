program test_record_basic;
type t = record
    a, b: integer;
    c, d: character;
end;
var a: t;

function f(x: integer): character;
    begin
        if x = 1 then
            f := '!';
        else
            f := '?';
    end;

begin
    read(a.a, a.b);
    a.c := f(a.a);
    a.d := f(a.b);
    writeln(a.a);
    writeln(a.b);
    writeln(a.c);
    writeln(a.d);
end.
