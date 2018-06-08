program test_builtin_type_abbr;
var
    i: longint;
    c: char;
    b: bool;
begin
    i := 1;
    c := 'a';
    b := true;
    if b then writeln(i, c);
end.
