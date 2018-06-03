#union

%type <value_node> arith_add_sub arith_mul_div arith_pos_neg

%%

arith_add_sub:
    arith_mul_div {
        $$ = $1;
    }
    | arith_add_sub SYM_ADD arith_mul_div {
        $$ = new ast_arith_add($1, $3);
        YY_SET_LOCATION($$);
    }
    | arith_add_sub SYM_SUB arith_mul_div {
        $$ = new ast_arith_sub($1, $3);
        YY_SET_LOCATION($$);
    }
;

arith_mul_div:
    arith_pos_neg {
        $$ = $1;
    }
    | arith_mul_div SYM_MUL arith_pos_neg {
        $$ = new ast_arith_mul($1, $3);
        YY_SET_LOCATION($$);
    }
    | arith_mul_div SYM_DIV arith_pos_neg {
        $$ = new ast_arith_div($1, $3);
        YY_SET_LOCATION($$);
    }
    | arith_mul_div PAS_DIV arith_pos_neg {
        $$ = new ast_arith_div_floor($1, $3);
        YY_SET_LOCATION($$);
    }
    | arith_mul_div PAS_MOD arith_pos_neg {
        $$ = new ast_arith_mod($1, $3);
        YY_SET_LOCATION($$);
    }
;

arith_pos_neg:
    at {
        $$ = $1;
    }
    | SYM_ADD at {
        $$ = $2;
    }
    | SYM_SUB at {
        $$ = new ast_arith_sub(new ast_int_val(0), $2);
        YY_SET_LOCATION($$);
    }
;
