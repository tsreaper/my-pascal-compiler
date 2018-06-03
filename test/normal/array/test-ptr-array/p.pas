program test_ptr_array;
var
    a: array [1..2, 1..2] of integer;
    p: array [1..2, 1..2] of ^integer;
    i, j: integer;
begin
    for i := 1 to 2 do for j := 1 to 2 do read(a[i, j]);
    for i := 1 to 2 do for j := 1 to 2 do p[i, j] := @a[i][j];
    for i := 1 to 2 do for j := 1 to 2 do p[i, j]^ := p[i, j]^ * 2;
    for i := 1 to 2 do for j := 1 to 2 do writeln(a[i, j]);
end.
