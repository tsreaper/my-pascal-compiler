ast_ptr_type* ptr_type_node;

#union

%type <ptr_type_node> ptr_type

%%

ptr_type:
    SYM_CARET type {
        $$ = new ast_ptr_type($2);
        YY_SET_LOCATION($$);
    }
;
