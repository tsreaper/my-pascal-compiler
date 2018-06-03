program test_local_array;

procedure p;
    var
        a: array [1..2, 1..2] of integer;
        i, j: integer;
    begin
        for i := 1 to 2 do for j := 1 to 2 do read(a[i, j]);
        for i := 1 to 2 do for j := 1 to 2 do writeln(a[i, j]);
    end;

begin
    p();
end.
