program test_short_circuit_or;
var n: integer;

function f(x: integer): boolean;
    begin
        writeln('f');
        f := x = 1;
    end;

begin
    read(n);

    if true or true then writeln('T');
    if true or false then writeln('T');
    if true or f(n) then writeln('T');
    if true or f(n-1) then writeln('T');
    writeln('-');

    if false or true then writeln('T');
    if false or false then writeln('T');
    if false or f(n) then writeln('T');
    if false or f(n-1) then writeln('T');
    writeln('-');

    if f(n) or true then writeln('T');
    if f(n) or false then writeln('T');
    if f(n) or f(n) then writeln('T');
    if f(n) or f(n-1) then writeln('T');
    writeln('-');

    if f(n-1) or true then writeln('T');
    if f(n-1) or false then writeln('T');
    if f(n-1) or f(n) then writeln('T');
    if f(n-1) or f(n-1) then writeln('T');
    writeln('-');
end.
