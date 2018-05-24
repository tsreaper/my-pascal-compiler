#union

%type <type_node> cmp_eq cmp_cmp

%%

cmp_eq:
    cmp_cmp {
        $$ = $1;
    }
    | cmp_eq SYM_EQ cmp_cmp {
        $$ = new ast_cmp_eq($1, $3);
        YY_SET_LOCATION($$);
    }
    | cmp_eq SYM_NE cmp_cmp {
        $$ = new ast_cmp_ne($1, $3);
        YY_SET_LOCATION($$);
    }
;

cmp_cmp:
    arith_add_sub {
        $$ = $1;
    }
    | cmp_cmp SYM_LT arith_add_sub {
        $$ = new ast_cmp_lt($1, $3);
        YY_SET_LOCATION($$);
    }
    | cmp_cmp SYM_GT arith_add_sub {
        $$ = new ast_cmp_gt($1, $3);
        YY_SET_LOCATION($$);
    }
    | cmp_cmp SYM_LE arith_add_sub {
        $$ = new ast_cmp_le($1, $3);
        YY_SET_LOCATION($$);
    }
    | cmp_cmp SYM_GE arith_add_sub {
        $$ = new ast_cmp_ge($1, $3);
        YY_SET_LOCATION($$);
    }
;
