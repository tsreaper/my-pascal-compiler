ast_func_head* func_head_node;
ast_func_dec* func_dec_node;
ast_func_def* func_def_node;

#union

%type <func_dec_node> proc_func_dec
%type <func_def_node> proc_func_def
%type <func_head_node> proc_head func_head
%type <func_head_node> proc_func_head_has_param

%%

proc_func_dec:
    proc_head PAS_FORWARD SYM_SEMICOLON {
        $$ = new ast_func_dec($1);
        YY_SET_LOCATION($$);
    }
    | func_head PAS_FORWARD SYM_SEMICOLON {
        $$ = new ast_func_dec($1);
        YY_SET_LOCATION($$);
    }
;

proc_func_def:
    proc_head local_block SYM_SEMICOLON {
        $$ = new ast_func_def($1, $2);
        YY_SET_LOCATION($$);
    }
    | func_head local_block SYM_SEMICOLON {
        $$ = new ast_func_def($1, $2);
        YY_SET_LOCATION($$);
    }
;

proc_head:
    PAS_PROCEDURE id SYM_SEMICOLON {
        $$ = new ast_func_head($2);
        YY_SET_LOCATION($$);
    }
    | PAS_PROCEDURE id SYM_LPAREN SYM_RPAREN SYM_SEMICOLON {
        $$ = new ast_func_head($2);
        YY_SET_LOCATION($$);
    }
    | PAS_PROCEDURE proc_func_head_has_param SYM_RPAREN SYM_SEMICOLON {
        $$ = $2;
    }
;

func_head:
    PAS_FUNCTION id SYM_COLON type SYM_SEMICOLON {
        $$ = new ast_func_head($2);
        $$->set_ret_type_node($4);
        YY_SET_LOCATION($$);
    }
    | PAS_FUNCTION id SYM_LPAREN SYM_RPAREN SYM_COLON type SYM_SEMICOLON {
        $$ = new ast_func_head($2);
        $$->set_ret_type_node($6);
        YY_SET_LOCATION($$);
    }
    | PAS_FUNCTION proc_func_head_has_param SYM_RPAREN SYM_COLON type SYM_SEMICOLON {
        $$ = $2;
        $$->set_ret_type_node($5);
    }
;

proc_func_head_has_param:
    id SYM_LPAREN id SYM_COLON type {
        $$ = new ast_func_head($1);
        $$->add_param($3, $5);
        YY_SET_LOCATION($$);
    }
    | proc_func_head_has_param SYM_SEMICOLON id SYM_COLON type {
        $$ = $1;
        $$->add_param($3, $5);
        YY_SET_LOCATION($$);
    }
;
