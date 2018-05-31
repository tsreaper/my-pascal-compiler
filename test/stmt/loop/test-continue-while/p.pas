program test_continue_while;
var
    tcase, n, ans: integer;
    x: integer;
begin
    {calculate the sum of even integers in the input}
    read(tcase);
    while tcase > 0 do
    begin
        tcase := tcase - 1;
        read(n);
        ans := 0;
        while n > 0 do
        begin
            n := n - 1;
            read(x);
            if x mod 2 = 1 then continue;
            ans := ans + x;
        end
        writeln(ans);
    end
end.
