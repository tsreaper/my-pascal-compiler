ast_literal* literal_node;

#union

%type <literal_node> literal

%%

literal:
    INT {
        $$ = new ast_int_val($1);
        YY_SET_LOCATION($$);
    }
    | REAL {
        $$ = new ast_real_val($1);
        YY_SET_LOCATION($$);
    }
    | CHAR {
        $$ = new ast_char_val($1);
        YY_SET_LOCATION($$);
    }
    | BOOL_TRUE {
        $$ = new ast_bool_val(true);
        YY_SET_LOCATION($$);
    }
    | BOOL_FALSE {
        $$ = new ast_bool_val(false);
        YY_SET_LOCATION($$);
    }
    | STR {
        $$ = new ast_str_val($1);
        YY_SET_LOCATION($$);
    }
;
