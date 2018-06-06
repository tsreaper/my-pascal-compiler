ast_call* call_node;

#union

%type <call_node> proc_func_call

%%

proc_func_call:
    id SYM_LPAREN exp_seq_with_array SYM_RPAREN {
        $$ = new ast_call($1, $3);
        YY_SET_LOCATION($$);
    }
;
