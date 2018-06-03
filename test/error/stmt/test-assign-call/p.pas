program test_assign_call;
function f: integer;
    begin
        read(f);
    end;
begin
    f() := 1;
end.
