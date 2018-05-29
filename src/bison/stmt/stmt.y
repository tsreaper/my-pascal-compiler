ast_stmt_seq* stmt_seq_node;

#union

%type <stmt_seq_node> compound_stm stmt_seq
%type <node> stmt simple_stmt

%%

compound_stm:
    PAS_BEGIN stmt_seq PAS_END {
        $$ = $2;
    }
;

stmt_seq:
    {
        $$ = new ast_stmt_seq();
        YY_SET_LOCATION($$);
    }
    | stmt_seq stmt {
        $$ = $1;
        $$->add_stmt($2);
        YY_SET_LOCATION($$);
    }
;

stmt:
    simple_stmt SYM_SEMICOLON {
        $$ = $1;
    }
    | compound_stm {
        $$ = $1;
    }
    | if {
        $$ = $1;
    }
    | for {
        $$ = $1;
    }
    // TODO more statements
;

simple_stmt:
    {
        $$ = new ast_empty_stmt();
    }
    | assign {
        $$ = $1;
    }
    | proc_func_call {
        $$ = $1;
    }
    | sys_func {
        $$ = $1;
    }
    | continue {
        $$ = $1;
    }
    | break {
        $$ = $1;
    }
;
