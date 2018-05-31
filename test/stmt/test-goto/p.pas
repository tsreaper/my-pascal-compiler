program test_label;
label 1, 2, 3, 4;
procedure p;
    label 1, 2, 3, 4, 5;
    begin
        goto 3;
        1:
        writeln(11);
        goto 5;
        2:
        writeln(22);
        goto 1;
        3:
        writeln(33);
        goto 4;
        4:
        writeln(44);
        goto 2;
        5:;
    end;
begin
    goto 2;
    1:
    writeln(1);
    goto 3;
    2:
    writeln(2);
    goto 1;
    3:
    writeln(3);
    goto 4;
    4:
    writeln(4);
    p();
end.
