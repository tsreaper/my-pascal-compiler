#union

%type <value_node> sizeof

%%

sizeof:
    PAS_SIZEOF SYM_LPAREN exp_or_array SYM_RPAREN {
        $$ = new ast_size_of($3);
        YY_SET_LOCATION($$);
    }
    | PAS_SIZEOF SYM_LPAREN basic_type SYM_RPAREN {
        $$ = new ast_size_of($3);
        YY_SET_LOCATION($$);
    }
;
