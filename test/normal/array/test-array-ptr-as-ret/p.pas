program test_array_ptr_as_ret;
type
    t_2d = array[1..2] of array [1..2] of integer;
    t_3d = array [1..3] of t_2d;
var
    a: t_3d;
    i, j, k: integer;

function get(a: ^t_3d; idx: integer): ^array [1..2, 1..2] of integer;
    begin
        get := @(a^[idx]);
    end;

begin
    for i := 1 to 3 do for j := 1 to 2 do for k := 1 to 2 do
        read(get(@a, i)^[j, k]);
    for i := 1 to 3 do for j := 1 to 2 do for k := 1 to 2 do
        writeln(a[i, j, k]);
end.
