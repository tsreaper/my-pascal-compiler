program test_cmp;
procedure print(x: boolean);
    begin
        if x then writeln(1); else writeln(0);
    end;
begin
    print(1 = 1);
    print(2 = 1);
    print(1 = 2);

    print(1 <> 1);
    print(2 <> 1);
    print(1 <> 2);

    print(1 < 1);
    print(2 < 1);
    print(1 < 2);

    print(1 > 1);
    print(2 > 1);
    print(1 > 2);

    print(1 <= 1);
    print(2 <= 1);
    print(1 <= 2);

    print(1 >= 1);
    print(2 >= 1);
    print(1 >= 2);
end.
