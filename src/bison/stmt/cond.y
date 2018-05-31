ast_if* if_node;
ast_case* case_node;

#union

%type <if_node> if
%type <case_node> case case_body

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

case:
    PAS_CASE case_body PAS_END {
        $$ = $2;
    }
    | PAS_CASE case_body PAS_DEFAULT SYM_COLON stmt PAS_END {
        $$ = $2;
        $$->set_default($5);
    }
;

case_body:
    exp PAS_OF {
        $$ = new ast_case($1);
        YY_SET_LOCATION($$);
    }
    | case_body exp_seq SYM_COLON stmt {
        $$ = $1;
        $$->add_seq($2, $4);
        YY_SET_LOCATION($$);
    }
;
