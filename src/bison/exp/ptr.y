#union

%type <value_node> at deref_array_idx_field

%%

at:
    deref_array_idx_field {
        $$ = $1;
    }
    | SYM_AT deref_array_idx_field {
        $$ = new ast_at($2);
        YY_SET_LOCATION($$);
    }
;

deref_array_idx_field:
    exp_base {
        $$ = $1;
    }
    | deref_array_idx_field SYM_CARET {
        $$ = new ast_deref($1);
        YY_SET_LOCATION($$);
    }
;
