ast_str_type* str_type_node;

#union

%type <str_type_node> str_type

%%

str_type:
    TYPE_STRING {
        $$ = new ast_str_type();
        YY_SET_LOCATION($$);
    }
    | TYPE_STRING SYM_LBRAC exp SYM_RBRAC {
        $$ = new ast_str_type($3);
        YY_SET_LOCATION($$);
    }
;
