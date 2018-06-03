program test_array_enum_idx;
var
    a: array[1..2, -7..-5] of integer;
    i, j: integer;
begin
    for i := 1 to 2 do for j := -7 to -5 do read(a[i, j]);
    writeln(a[1, -7]);
    writeln(a[2][-6]);
    for i := 1 to 2 do for j := -5 downto -7 do writeln(a[i][j]);
end.
