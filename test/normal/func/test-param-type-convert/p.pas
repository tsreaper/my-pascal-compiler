program test_param_type_convert;

procedure p(a: real; b: integer);
    begin
        writeln(1);
    end;

procedure p(a: integer; b: real);
    begin
        writeln(2);
    end;

procedure p(a, b: integer);
    begin
        writeln(3);
    end;

procedure p(a, b: real);
    begin
        writeln(4);
    end;

begin
    p(1, 1);
    p(1.0, 1);
    p(1, 1.0);
    p(1.0, 1.0);
end.
