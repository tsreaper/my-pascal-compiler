ast_for* for_node;
ast_cont* cont_node;
ast_break* break_node;

#union

%type <for_node> for

%type <cont_node> continue
%type <break_node> break

%%

for:
    PAS_FOR id SYM_ASSIGN exp PAS_TO exp PAS_DO stmt {
        $$ = new ast_for($2, $4, $6, $8, false);
        YY_SET_LOCATION($$);
    }
    | PAS_FOR id SYM_ASSIGN exp PAS_DOWNTO exp PAS_DO stmt {
        $$ = new ast_for($2, $4, $6, $8, true);
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
