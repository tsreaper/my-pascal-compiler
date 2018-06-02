ast_array_idx* array_idx_node;

#union

%type <array_idx_node> array_idx array_idx_body

%%

array_idx:
    array_idx_body SYM_RBRAC {
        $$ = $1;
    }
;

array_idx_body:
    id SYM_LBRAC exp {
        $$ = new ast_array_idx($1);
        $$->append_idx($3);
        YY_SET_LOCATION($$);
    }
    | array_idx_body SYM_COMMA exp {
        $$ = $1;
        $$->append_idx($3);
    }
    | array_idx_body SYM_RBRAC SYM_LBRAC exp {
        $$ = $1;
        $$->append_idx($4);
    }
;
