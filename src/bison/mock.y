#union

%type <node> proc_func_dec_part

%type <node> compound_stm

%%

// TODO
proc_func_dec_part:
    {
        $$ = new ast_empty();
    }
;

// TODO
compound_stm:
    {
        $$ = new ast_empty();
    }
;
