#union

%type <value_node> at deref_array_idx

%%

at:
    deref_array_idx {
        $$ = $1;
    }
    | SYM_AT deref_array_idx {
        $$ = new ast_at($2);
        YY_SET_LOCATION($$);
    }
;

deref_array_idx:
    exp_base {
        $$ = $1;
    }
    | deref_array_idx SYM_CARET {
        $$ = new ast_deref($1);
        YY_SET_LOCATION($$);
    }
;
