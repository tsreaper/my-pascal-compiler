program test_short_circuit_and;
var n: integer;

function f(x: integer): boolean;
    begin
        writeln('f');
        f := x = 1;
    end;

begin
    read(n);

    if true and true then writeln('T');
    if true and false then writeln('T');
    if true and f(n) then writeln('T');
    if true and f(n-1) then writeln('T');
    writeln('-');

    if false and true then writeln('T');
    if false and false then writeln('T');
    if false and f(n) then writeln('T');
    if false and f(n-1) then writeln('T');
    writeln('-');

    if f(n) and true then writeln('T');
    if f(n) and false then writeln('T');
    if f(n) and f(n) then writeln('T');
    if f(n) and f(n-1) then writeln('T');
    writeln('-');

    if f(n-1) and true then writeln('T');
    if f(n-1) and false then writeln('T');
    if f(n-1) and f(n) then writeln('T');
    if f(n-1) and f(n-1) then writeln('T');
    writeln('-');
end.
