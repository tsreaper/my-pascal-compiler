program test_array_ptr;
var
    a: array[1..3, 1..4, 1..5] of integer;
    i, j, k: integer;

procedure fill_1d(a: ^array[1..5] of integer; init: integer; col_inc: integer);
    var i: integer;
    begin
        for i := 1 to 5 do a^[i] := init + col_inc * (i - 1);
    end;

procedure fill_2d(a: ^array[1..4, 1..5] of integer; row_inc: integer; col_inc: integer);
    var i: integer;
    begin
        for i := 1 to 4 do fill_1d(@(a^[i]), row_inc * (i - 1), col_inc);
    end;

begin
    for i := 1 to 3 do fill_2d(@a[i], i, 1);
    for i := 1 to 3 do for j := 1 to 4 do for k := 1 to 5 do writeln(a[i, j, k]);
end.
