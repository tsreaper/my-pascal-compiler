program test_char_to_string;
var
    c: char;
    s: string[5];

procedure print(x: boolean);
    begin
        if x then writeln('T'); else writeln('F');
    end;

begin
    c := 'a';
    s := c;
    writeln(s);

    s[2] := c;
    print(c = s); print(s = c);
    print(c <> s); print(s <> c);
    print(c < s); print(s < c);
    print(c > s); print(s > c);
    print(c <= s); print(s <= c);
    print(c >= s); print(s >= c);

    s := s + c;
    writeln(s);

    writeln(concat(c, concat(c, c, c), s, concat(c, s), c));
end.
