program test_builtin_type_abbr;
var
    i: int;
    j: longint;
    c: char;
    b: bool;
begin
    i := 1;
    j := 1;
    c := 'a';
    b := true;
    if b then writeln(i, j, c);
end.
