#union

%type <value_node> exp exp_base

%%

exp:
    logic_or {
        $$ = $1;
    }

exp_base:
    literal {
        $$ = $1;
    }
    | id {
        $$ = $1;
    }
    | proc_func_call {
        $$ = $1;
    }
    | SYM_LPAREN exp SYM_RPAREN {
        $$ = $2;
    }
;
