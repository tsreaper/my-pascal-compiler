ast_for* for_node;
ast_repeat* repeat_node;
ast_while* while_node;
ast_cont* cont_node;
ast_break* break_node;

#union

%type <for_node> for
%type <repeat_node> repeat
%type <while_node> while

%type <cont_node> continue
%type <break_node> break

%%

for:
    PAS_FOR deref_array_idx SYM_ASSIGN exp PAS_TO exp PAS_DO stmt {
        $$ = new ast_for($2, $4, $6, $8, false);
        YY_SET_LOCATION($$);
    }
    | PAS_FOR deref_array_idx SYM_ASSIGN exp PAS_DOWNTO exp PAS_DO stmt {
        $$ = new ast_for($2, $4, $6, $8, true);
        YY_SET_LOCATION($$);
    }
;

repeat:
    PAS_REPEAT stmt PAS_UNTIL exp {
        $$ = new ast_repeat($4, $2);
        YY_SET_LOCATION($$);
    }
;

while:
    PAS_WHILE exp PAS_DO stmt {
        $$ = new ast_while($2, $4);
        YY_SET_LOCATION($$);
    }
;

continue:
    PAS_CONTINUE {
        $$ = new ast_cont();
        YY_SET_LOCATION($$);
    }
;

break:
    PAS_BREAK {
        $$ = new ast_break;
        YY_SET_LOCATION($$);
    }
;
