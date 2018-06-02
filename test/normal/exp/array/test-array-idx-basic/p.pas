program test_array_idx_basic;
var
    n, m: integer;
    a: array [1..5] of integer;
    b: array [1..5, 1..5] of integer;
    i, j: integer;
begin
    {read/write 1d array}
    read(n);
    for i := 1 to n do read(a[i]);
    for i := 1 to n do writeln(a[i]);
    for i := 1 to n do a[i] := a[i] * 2;
    for i := 1 to n do writeln(a[i]);

    {read/write 2d array}
    read(n, m);
    for i := 1 to n do for j := 1 to m do read(b[i][j]);
    for i := 1 to n do for j := 1 to m do writeln(b[i, j]);
    for i := 1 to n do for j := 1 to m do b[i, j] := b[i][j] * 2;
    for i := 1 to n do for j := 1 to m do writeln(b[i][j]);
end.
