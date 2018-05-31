program test_for;
var
    tcase, n, ans: integer;
    cas, i, x: integer;
begin
    {calculate sum of input data}
    read(tcase);
    for cas := 1 to tcase do
    begin
        read(n);
        ans := 0;
        for i := n downto 1 do
        begin
            read(x);
            ans := ans + x;
        end
        writeln(ans);
    end
end.
