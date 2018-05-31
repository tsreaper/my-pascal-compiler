program text_mixed_loop;
var
    tcase, n, m, ans: integer;
    i, x: integer;
begin
    {calculate sum of a matrix}
    read(tcase);
    repeat
    begin
        tcase := tcase - 1;
        read(n, m);
        ans := 0;
        while n > 0 do
        begin
            n := n - 1;
            for i := m downto 1 do
            begin
                read(x);
                ans := ans + x;
            end
        end
        writeln(ans);
    end
    until tcase = 0
end.
