program test_case_enum;
type
    enum_t = (red, green, blue);
var
    a: enum_t;
begin
    for a := blue downto red do
    begin
        if a = red then writeln(0);
        if a = green then writeln(1);
        if a = blue then writeln(2);
    end
end.
