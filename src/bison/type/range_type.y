ast_range_type* range_type_node;

#union

%type <range_type_node> range_type

%%

range_type:
    exp SYM_RANGE exp {
        $$ = new ast_range_type($1, $3);
        YY_SET_LOCATION($$);
    }
;
