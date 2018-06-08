program test_random;
const lim = 10000;
var
    a: array [1..10] of integer;
    i, j: integer;
begin
    randomize();
    for i := 1 to 10 do a[i] := random(lim);

    {range check}
    for i := 1 to 10 do
        if a[i] >= lim or a[i] < 0 then
        begin
            writeln('Result out of range!');
            exit(0);
        end

    {value check}
    for i := 1 to 10 do for j := i + 1 to 10 do
        if a[i] <> a[j] then
        begin
            writeln('OK');
            exit(0);
        end
    writeln('FAIL...You should consider buying a lottery!');
end.
