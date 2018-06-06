program test_array_literal_as_param;
type e = (red, green, blue);

procedure p(a, b: array [1..2] of array ['a'..'c'] of integer; c: array [red..blue] of boolean);
    var
        i: integer;
        j: character;
        k: e;
    begin
        for i := 1 to 2 do for j := 'a' to 'c' do for k := red to blue do
        begin
            if c[k] then
                writeln(a[i, j], ' ', b[i, j]);
            else
                writeln(-a[i, j], ' ', -b[i, j]);
        end
    end;

begin
    p(((1, 2, 3), (4, 5, 6)), ((7, 8, 9), (10, 11, 12)), (true, false, true));
end.
