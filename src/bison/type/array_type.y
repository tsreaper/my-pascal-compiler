ast_array_type* array_type_node;

#union

%type <array_type_node> array_type array_index

%%

array_type:
    array_index SYM_RBRAC PAS_OF array_ele_type {
        $$ = $1;
        $$->set_ele_type($4);
    }
;

array_index:
    PAS_ARRAY SYM_LBRAC range_type {
        $$ = new ast_array_type();
        $$->append_range($3);
        YY_SET_LOCATION($$);
    }
    | array_index SYM_COMMA range_type {
        $$ = $1;
        $$->append_range($3);
    }
    | array_index SYM_RBRAC PAS_OF PAS_ARRAY SYM_LBRAC range_type {
        $$ = $1;
        $$->append_range($6);
    }
;
