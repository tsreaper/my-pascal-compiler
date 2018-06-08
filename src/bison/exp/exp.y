ast_exp_seq* exp_seq_node;

#union

%type <value_node> exp exp_or_array exp_base
%type <exp_seq_node> exp_seq exp_seq_not_empty
%type <exp_seq_node> exp_seq_with_array exp_seq_with_array_not_empty exp_seq_with_array_at_least_2

%%

exp_seq_with_array:
    {
        $$ = new ast_exp_seq();
        YY_SET_LOCATION($$);
    }
    | exp_seq_with_array_not_empty {
        $$ = $1;
    }
;

exp_seq_with_array_not_empty:
    exp_or_array {
        $$ = new ast_exp_seq();
        $$->add_exp($1);
        YY_SET_LOCATION($$);
    }
    | exp_seq_with_array_at_least_2 {
        $$ = $1;
    }
;

exp_seq_with_array_at_least_2:
    exp_or_array SYM_COMMA exp_or_array {
        $$ = new ast_exp_seq();
        $$->add_exp($1);
        $$->add_exp($3);
        YY_SET_LOCATION($$);
    }
    | exp_seq_with_array_at_least_2 SYM_COMMA exp_or_array {
        $$ = $1;
        $$->add_exp($3);
    }
;

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
    | exp_seq_not_empty SYM_COMMA exp {
        $$ = $1;
        $$->add_exp($3);
    }
;

exp_or_array:
    exp {
        $$ = $1;
    }
    | array {
        $$ = $1;
    }
;

exp:
    logic_or {
        $$ = $1;
    }
;

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
    | sizeof {
        $$ = $1;
    }
    | SYM_LPAREN exp SYM_RPAREN {
        $$ = $2;
    }
;
