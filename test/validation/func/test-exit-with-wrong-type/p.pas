program test_exit_with_wrong_type;

function f(): integer;
    begin
        exit('a');
    end;

begin
    writeln(f());
end.
