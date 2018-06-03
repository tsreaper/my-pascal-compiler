program test_continue_for;
var
    tcase, n, ans: integer;
    cas, i, x: integer;
begin
    {calculate the sum of even integers in the input}
    read(tcase);
    for cas := tcase downto 1 do
    begin
        read(n);
        ans := 0;
        for i := 1 to n do
        begin
            n := n - 1;
            read(x);
            if x mod 2 = 1 then continue;
            ans := ans + x;
        end
        writeln(ans);
    end
end.
