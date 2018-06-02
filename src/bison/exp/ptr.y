ast_at* at_node;
ast_deref* deref_node;

#union

%type <at_node> at
%type <deref_node> deref

%%

at:
    SYM_AT id {
        $$ = new ast_at($2);
        YY_SET_LOCATION($$);
    }
;

deref:
    exp_base SYM_CARET {
        $$ = new ast_deref($1);
        YY_SET_LOCATION($$);
    }
;
