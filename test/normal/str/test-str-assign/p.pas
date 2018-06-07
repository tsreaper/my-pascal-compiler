program test_str_assign;
var
    s: string[10];
    t: string[5];

begin
    readln(t);
    s := t;
    writeln(s, ' ', t);
    readln(s);
    t := s;
    writeln(s, ' ', t);
end.
