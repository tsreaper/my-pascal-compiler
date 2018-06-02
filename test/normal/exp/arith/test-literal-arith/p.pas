program test_arith;
begin
    {basic arithmetical operations}
    writeln(1 + 2 + 3);
    writeln(3 - 2 - 1);
    writeln(1 * 2 * 3);
    writeln(3 / 2 / 1);
    writeln(5 div 2);
    writeln(5 mod 2);

    {negative integers}
    writeln(-5);
    writeln(-5 - 5);
    writeln(-5 * -5 + -5 - -5);

    {priority test}
    writeln(1 + 2 * 3);
    writeln((1 + 2) * 3);
    writeln(1 + 2 * 3 - 6 mod (5 div 4) + (9 - 8) * 7);
end.
