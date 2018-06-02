ast_lhs* lhs_node;

#union

%type <lhs_node> lhs

%%

lhs:
    id {
        $$ = $1;
    }
    | deref {
        $$ = $1;
    }
    | array_idx {
        $$ = $1;
    }
;
