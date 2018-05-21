ast_const_def_seq* const_def_seq_node;
ast_const_def* const_def_node;

#union

%type <node> const_def_part
%type <const_def_seq_node> const_def_body
%type <const_def_node> const_def
%type <value_node> const

%%

const_def_part:
    PAS_CONST const_def_body {
        $$ = $2;
    }
    | {
        $$ = new ast_empty();
    }
;

const_def_body:
    const_def SYM_SEMICOLON {
        $$ = new ast_const_def_seq();
        $$->add_const_def($1);
        YY_SET_LOCATION($$);
    }
    | const_def_body const_def SYM_SEMICOLON {
        $$ = $1;
        $$->add_const_def($2);
        YY_SET_LOCATION($$);
    }
;

const_def:
    ID SYM_EQ const {
        $$ = new ast_const_def(new ast_id($1), $3);
        YY_SET_LOCATION($$);
    }
;

const:
    literal {
        $$ = $1;
    }
    | id {
        $$ = $1;
    }
    | SYM_ADD id {
        $$ = $2;
    }
    | SYM_SUB id {
        // TODO
        $$ = $2;
        // $$ = new ast_sub(new ast_int(0), $2);
    }
;
