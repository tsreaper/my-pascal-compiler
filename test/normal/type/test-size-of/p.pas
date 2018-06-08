program test_size_of;
var
    i, j: integer;
    a: array [1..10] of integer;

procedure print(x: boolean);
    begin
        if x then writeln('T'); else writeln('F');
    end;

begin
    print(sizeof(i) = sizeof(j));
    print(sizeof(i) = sizeof(integer));
    print(sizeof(i) = sizeof(1 + 2));
    print(sizeof(i) * 10 = sizeof(a));
    print(sizeof(1 + 2) * 10 = sizeof(a));
    print(sizeof(i) = sizeof(a));
end.
