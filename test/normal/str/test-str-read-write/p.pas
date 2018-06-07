program test_str_read_write;
var s: string[10];

begin
    readln(s);
    writeln(s);
    read(s[3]);
    writeln(s);
    s[5] := 'z';
    writeln(s);
end.
