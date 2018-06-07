program teat_read_write;
var
    i: character;
    j: integer;
    k: real;
begin
    read(i, j, k);
    writeln(i);
    writeln(j);
    writeln(k);
    readln(i, j, k);
    write(i, j, ' ', k);
    read(i, j);
    writeln(' ', i, j);
end.
