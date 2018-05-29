ast_if* if_node;

#union

%type <if_node> if

%%

if:
    PAS_IF exp PAS_THEN stmt {
        $$ = new ast_if($2, $4);
        YY_SET_LOCATION($$);
    }
    | PAS_IF exp PAS_THEN stmt PAS_ELSE stmt {
        $$ = new ast_if($2, $4, $6);
        YY_SET_LOCATION($$);
    }
;
