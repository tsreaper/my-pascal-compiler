ast_exp_seq* exp_seq_node;

#union

%type <value_node> exp exp_base
%type <exp_seq_node> exp_seq exp_seq_not_empty

%%

exp_seq:
    {
        $$ = new ast_exp_seq();
        YY_SET_LOCATION($$);
    }
    | exp_seq_not_empty {
        $$ = $1;
    }
;

exp_seq_not_empty:
    exp {
        $$ = new ast_exp_seq();
        $$->add_exp($1);
        YY_SET_LOCATION($$);
    }
    | exp_seq SYM_COMMA exp {
        $$ = $1;
        $$->add_exp($3);
        YY_SET_LOCATION($$);
    }
;

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
    | at {
        $$ = $1;
    }
    | deref {
        $$ = $1;
    }
    | SYM_LPAREN exp SYM_RPAREN {
        $$ = $2;
    }
;
