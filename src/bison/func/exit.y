ast_exit* exit_node;

#union

%type <exit_node> exit

%%

exit:
    PAS_EXIT {
        $$ = new ast_exit();
        YY_SET_LOCATION($$);
    }
    | PAS_EXIT SYM_LPAREN SYM_RPAREN {
        $$ = new ast_exit();
        YY_SET_LOCATION($$);
    }
    | PAS_EXIT SYM_LPAREN exp_or_array SYM_RPAREN {
        $$ = new ast_exit($3);
        YY_SET_LOCATION($$);
    }
;
