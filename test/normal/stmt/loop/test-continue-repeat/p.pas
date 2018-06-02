program test_continue_repeat;
var
    tcase, n, ans: integer;
    x: integer;
begin
    {calculate sum of input data}
    read(tcase);
    repeat
    begin
        tcase := tcase - 1;
        read(n);
        ans := 0;
        repeat
        begin
            n := n - 1;
            read(x);
            if x mod 2 = 1 then continue;
            ans := ans + x;
        end
        until n = 0
        writeln(ans);
    end
    until tcase = 0
end.
