ast_var_dec_seq* var_dec_seq_node;
ast_var_dec* var_dec_node;

#union

%type <node> var_dec_part
%type <var_dec_seq_node> var_dec_body
%type <var_dec_node> var_dec

%%

var_dec_part:
    PAS_VAR var_dec_body {
        $$ = $2;
    }
;

var_dec_body:
    var_dec SYM_SEMICOLON {
        $$ = new ast_var_dec_seq();
        $$->add_var_dec($1);
        YY_SET_LOCATION($$);
    }
    | var_dec_body var_dec SYM_SEMICOLON {
        $$ = $1;
        $$->add_var_dec($2);
        YY_SET_LOCATION($$);
    }
;

var_dec:
    id SYM_COLON type {
        $$ = new ast_var_dec($3);
        $$->add_id($1);
        YY_SET_LOCATION($$);
    }
    | id SYM_COMMA var_dec {
        $$ = $3;
        $$->add_id($1);
        YY_SET_LOCATION($$);
    }
;