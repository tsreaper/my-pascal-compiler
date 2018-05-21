ast_builtin_type* builtin_type_node;

#union

%type <builtin_type_node> builtin_type

%%

builtin_type:
    TYPE_INT {
        $$ = new ast_bti_int();
        YY_SET_LOCATION($$);
    }
    | TYPE_REAL {
        $$ = new ast_bti_real();
        YY_SET_LOCATION($$);
    }
    | TYPE_CHAR {
        $$ = new ast_bti_char();
        YY_SET_LOCATION($$);
    }
    | TYPE_BOOL {
        $$ = new ast_bti_bool();
        YY_SET_LOCATION($$);
    }
;
