program test_if;
var
    tcase, a, b: integer;
begin
    read(tcase);
    while tcase > 0 do
    begin
        tcase := tcase - 1;
        read(a, b);
        if a < b then
            writeln(-1);
        else if a > b then
            writeln(1);
        else
            writeln(0);
    end
end.
