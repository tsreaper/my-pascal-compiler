#union

%%

deref_array_idx_field:
    deref_array_idx_field SYM_PERIOD ID {
        $$ = new ast_field($1, $3);
        YY_SET_LOCATION($$);
    }
;
