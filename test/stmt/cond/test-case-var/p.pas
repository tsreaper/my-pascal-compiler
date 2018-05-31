program test_case_var;
var
    tcase, a, b, c: integer;
begin
    read(tcase);
    while tcase > 0 do
    begin
        tcase := tcase - 1;
        read(a, b, c);
        case a + b - c + c - b of
        b: writeln('b');
        c: writeln('c');
        b + c: writeln('+');
        b - c: writeln('-');
        b * c: writeln('*');
        b div c: writeln('/');
        b mod c: writeln('%');
        default: writeln('?');
        end
    end
end.
