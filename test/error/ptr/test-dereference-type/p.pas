program test_dereference_type;
var a: integer;
begin
    a := (^integer)^;
end.
