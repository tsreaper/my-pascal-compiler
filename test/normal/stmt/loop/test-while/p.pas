program test_while;
var
    tcase, n, ans: integer;
    x: integer;
begin
    {calculate sum of input data}
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
            ans := ans + x;
        end
        writeln(ans);
    end
end.
