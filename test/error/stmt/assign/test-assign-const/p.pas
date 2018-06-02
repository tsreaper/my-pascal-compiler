program test_assign_const;
var v: integer;
const c = 1;
begin
    v := c;
    c := v;
end.
