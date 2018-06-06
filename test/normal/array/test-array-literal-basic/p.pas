program test_array_literal_basic;
var
    a: array [1..2, 'a'..'c'] of integer;
    i: integer;
    j: character;

begin
    a := (
        (1, 2, 3),
        (4, 5, 6)
    );

    for i := 1 to 2 do for j := 'a' to 'c' do writeln(a[i, j]);
end.
