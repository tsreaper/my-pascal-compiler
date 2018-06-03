program test_case_multi;
var
    tcase, n: integer;
begin
    read(tcase);
    while tcase > 0 do
    begin
        tcase := tcase - 1;
        read(n);
        case n of
        1: writeln('a');
        2, 3: writeln('b');
        4, 5, 6: writeln('c');
        default: writeln('x');
        end
    end
end.
