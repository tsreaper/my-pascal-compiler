ast_call* call_node;

#union

%type <call_node> proc_func_call proc_func_call_has_param

%%

proc_func_call:
    id SYM_LPAREN SYM_RPAREN {
        $$ = new ast_call($1);
        YY_SET_LOCATION($$);
    }
    | proc_func_call_has_param SYM_RPAREN {
        $$ = $1;
    }
;

proc_func_call_has_param:
    id SYM_LPAREN exp {
        $$ = new ast_call($1);
        $$->add_param($3);
        YY_SET_LOCATION($$);
    }
    | proc_func_call_has_param SYM_COMMA exp {
        $$ = $1;
        $$->add_param($3);
        YY_SET_LOCATION($$);
    }
;
