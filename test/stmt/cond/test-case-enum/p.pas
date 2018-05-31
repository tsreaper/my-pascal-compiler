program test_case_enum;
type
    enum_t = (red, green, blue);
var
    a: enum_t;
begin
    for a := red to blue do
        case a of
        red: writeln(0);
        green: writeln(1);
        blue: writeln(2);
        end
end.
