program test_chr_ord;
var
    i: integer;
    c: char;

begin
    i := ord('a');
    c := chr(i);
    writeln(i);
    writeln(c);
    c := chr(98);
    i := ord(c);
    writeln(i);
    writeln(c);
end.
