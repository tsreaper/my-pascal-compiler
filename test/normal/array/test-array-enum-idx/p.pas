program test_array_enum_idx;
type e = (red, green, blue);
var
    a: array[1..2, red..blue] of integer;
    i: integer;
    j: e;
begin
    for i := 1 to 2 do for j := red to blue do read(a[i, j]);
    writeln(a[1, red]);
    writeln(a[2][green]);
    for i := 1 to 2 do for j := red to blue do writeln(a[i][j]);
end.
