ast_program_head* program_head_node;
ast_program* program_node;

#union

%type <program_head_node> program_head
%type <program_node> program

%start program

%%

program:
    program_head global_block SYM_PERIOD {
        ast_root = new ast_program($1, $2);
        YY_SET_LOCATION(ast_root);
    }
;

program_head:
    {
        $$ = nullptr;
    }
    | PAS_PROGRAM ID SYM_SEMICOLON {
        $$ = new ast_program_head($2);
        YY_SET_LOCATION($$);
    }
;
