#union

%type <node> compound_stm

%%

// TODO
compound_stm:
    {
        $$ = new ast_empty();
    }
;
