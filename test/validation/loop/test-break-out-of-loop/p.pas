program test_break_out_of_loop;
var i: integer;
begin
    for i := 1 to 5 do
        writeln(i);
    break;
end.
