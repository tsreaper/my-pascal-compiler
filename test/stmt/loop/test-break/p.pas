program test_break;
var
    tcase, n, ans: integer;
    i, x: integer;
begin
    {calculate sum of integers until the first odd integer is met}
    read(tcase);
    while tcase > 0 do
    begin
        tcase := tcase - 1;
        read(n);
        ans := 0;

        for i := 1 to n do
        begin
            read(x);
            if x mod 2 = 1 then break;
            ans := ans + x;
        end

        {read remaining integers}
        for i := i + 1 to n do
            read(x);

        writeln(ans);
    end
end.
