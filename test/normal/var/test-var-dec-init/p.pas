program test_var_dec_init;
var
    i: integer = 1;
    r: real = 3.141592;
    c: char = 'a';
    b: boolean = true;
    a: array [1..2, 'a'..'c'] of integer = ((1, 2, 3), (4, 5, 6));
    s: string[15] = 'hello world';
    ii: integer = a[1, 'c'];
    cc: char = s[5];
var
    li: integer;
    lc: char;

begin
    writeln(i);
    writeln(r);
    writeln(c);
    if b then writeln('T');
    for li := 1 to 2 do for lc := 'a' to 'c' do writeln(a[li, lc]);
    writeln(s);
    writeln(ii);
    writeln(cc);
end.
