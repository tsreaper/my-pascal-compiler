ast_builtin_type* builtin_type_node;

#union

%type <builtin_type_node> builtin_type

%%

builtin_type:
    TYPE_INT {
        $$ = new ast_int_type();
        YY_SET_LOCATION($$);
    }
    | TYPE_REAL {
        $$ = new ast_real_type();
        YY_SET_LOCATION($$);
    }
    | TYPE_CHAR {
        $$ = new ast_char_type();
        YY_SET_LOCATION($$);
    }
    | TYPE_BOOL {
        $$ = new ast_bool_type();
        YY_SET_LOCATION($$);
    }
;
