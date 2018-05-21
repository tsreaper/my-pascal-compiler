ast_func_dec* func_dec_node;

#union

%type <func_dec_node> proc_dec func_dec
%type <func_dec_node> proc_func_dec_body

%%

proc_dec:
    PAS_PROCEDURE id SYM_SEMICOLON PAS_FORWARD SYM_SEMICOLON {
        $$ = new ast_func_dec($2);
        YY_SET_LOCATION($$);
    }
    | PAS_PROCEDURE id SYM_LPAREN SYM_RPAREN SYM_SEMICOLON PAS_FORWARD SYM_SEMICOLON {
        $$ = new ast_func_dec($2);
        YY_SET_LOCATION($$);
    }
    | PAS_PROCEDURE proc_func_dec_body SYM_RPAREN SYM_SEMICOLON PAS_FORWARD SYM_SEMICOLON {
        $$ = $2;
    }
;

func_dec:
    PAS_FUNCTION id SYM_COLON type SYM_SEMICOLON PAS_FORWARD SYM_SEMICOLON {
        $$ = new ast_func_dec($2);
        $$->set_ret_type($4);
        YY_SET_LOCATION($$);
    }
    | PAS_FUNCTION id SYM_LPAREN SYM_RPAREN SYM_COLON type SYM_SEMICOLON PAS_FORWARD SYM_SEMICOLON {
        $$ = new ast_func_dec($2);
        $$->set_ret_type($6);
        YY_SET_LOCATION($$);
    }
    | PAS_FUNCTION proc_func_dec_body SYM_RPAREN SYM_COLON type SYM_SEMICOLON PAS_FORWARD SYM_SEMICOLON {
        $$ = $2;
        $$->set_ret_type($5);
    }
;

proc_func_dec_body:
    id SYM_LPAREN id SYM_COLON type {
        $$ = new ast_func_dec($1);
        $$->add_param($3, $5);
        YY_SET_LOCATION($$);
    }
    | proc_func_dec_body SYM_SEMICOLON id SYM_COLON type {
        $$ = $1;
        $$->add_param($3, $5);
        YY_SET_LOCATION($$);
    }
;
