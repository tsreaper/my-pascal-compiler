program test_copy;
var
    s: string[10];
    t: string[5];
    i, j: integer;

begin
    readln(t);
    for i := 1 to 5 do for j := 1 to 7 do
    begin
        s := copy(t, i, j);
        writeln(s);
    end

    readln(s);
    for i := 1 to 10 do for j := 1 to 12 do
    begin
        t := copy(s, i, j);
        writeln(t);
    end

    writeln(copy(copy(copy(s, 2, 7), 2, 5), 2, 5));

    writeln(copy(s, 1, 1000000));
end.
