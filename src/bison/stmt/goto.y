ast_goto* goto_node;

#union

%type <goto_node> goto

%%

goto:
    PAS_GOTO INT {
        $$ = new ast_goto($2);
        YY_SET_LOCATION($$);
    }
;
