ast_assign* assign_node;

#union

%type <assign_node> assign

%%

assign:
    deref_array_idx_field SYM_ASSIGN exp_or_array {
        $$ = new ast_assign($1, $3);
        YY_SET_LOCATION($$);
    }
;
