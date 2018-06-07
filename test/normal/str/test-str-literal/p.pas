program test_str_literal;
var
    s: string[10];

begin
    s := 'abcd';
    writeln(s);
    writeln('abcd');

    s := 'abcd' + 'efgh';
    writeln(s);
    writeln('abcd' + 'efgh');

    writeln(concat('ab', 'cd', concat('ef', 'gh', 'ij')));

    writeln('#97#98ab#99#100cd#10#101#102ef#103#104gh');
end.
