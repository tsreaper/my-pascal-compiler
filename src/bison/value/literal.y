ast_literal* literal_node;

#union

%type <literal_node> literal

%%

literal:
    INT {
        $$ = new ast_lit_int($1);
        YY_SET_LOCATION($$);
    }
    | REAL {
        $$ = new ast_lit_real($1);
        YY_SET_LOCATION($$);
    }
    | CHAR {
        $$ = new ast_lit_char($1);
        YY_SET_LOCATION($$);
    }
    | BOOL_TRUE {
        $$ = new ast_lit_bool(true);
        YY_SET_LOCATION($$);
    }
    | BOOL_FALSE {
        $$ = new ast_lit_bool(false);
        YY_SET_LOCATION($$);
    }
    | STR {
        $$ = new ast_lit_str($1);
        YY_SET_LOCATION($$);
    }
;
