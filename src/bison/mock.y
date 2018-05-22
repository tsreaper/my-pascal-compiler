#union

%type <node> compound_stm

%%

// TODO
compound_stm:
    PAS_BEGIN PAS_END {
        $$ = new ast_empty();
    }
;
