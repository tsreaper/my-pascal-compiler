program test_case_basic;
var
    tcase, n: integer;
begin
    read(tcase);
    while tcase > 0 do
    begin
        tcase := tcase - 1;
        read(n);
        case n of
        1: writeln(1);
        2: writeln(2);
        3: writeln(3);
        end
    end
end.
