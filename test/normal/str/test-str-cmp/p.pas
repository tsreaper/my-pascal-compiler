program test_str_cmp;
var
    a: array [1..6] of string[5];
    i, j: integer;

procedure print(x: boolean);
    begin
        if x then writeln('T'); else writeln('F');
    end;

begin
    for i := 1 to 6 do readln(a[i]);
    for i := 1 to 6 do for j := 1 to 6 do
    begin
        print(a[i] = a[j]);
        print(a[i] <> a[j]);
        print(a[i] < a[j]);
        print(a[i] > a[j]);
        print(a[i] <= a[j]);
        print(a[i] >= a[j]);
    end
end.
