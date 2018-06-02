program test_array_assign;
var
    a: array [1..2, 1..2] of integer;
    b: array [1..2] of array [1..2] of integer;
    i, j: integer;
begin
    for i := 1 to 2 do for j := 1 to 2 do read(a[i, j]);
    for i := 1 to 2 do for j := 1 to 2 do read(b[i, j]);

    for i := 1 to 2 do for j := 1 to 2 do writeln(a[i, j]);
    for i := 1 to 2 do for j := 1 to 2 do writeln(b[i, j]);

    a[1] := b[1];
    for i := 1 to 2 do for j := 1 to 2 do writeln(a[i, j]);
    for i := 1 to 2 do for j := 1 to 2 do writeln(b[i, j]);

    a[1][1] := 100;
    a[1][2] := 200;
    for i := 1 to 2 do for j := 1 to 2 do writeln(a[i, j]);
    for i := 1 to 2 do for j := 1 to 2 do writeln(b[i, j]);
end.
