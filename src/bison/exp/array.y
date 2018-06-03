#union

%%

deref_array_idx_field:
    deref_array_idx_field SYM_LBRAC exp_seq SYM_RBRAC {
        $$ = new ast_array_idx($1, $3);
        YY_SET_LOCATION($$);
    }
;
