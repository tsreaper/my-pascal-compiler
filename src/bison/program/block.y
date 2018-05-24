ast_block_head* block_head_node;
ast_block* block_node;

#union

%type <node> block_head_component
%type <block_head_node> block_head
%type <block_node> block

%%

block:
    block_head compound_stm {
        $$ = new ast_block($1, $2);
        YY_SET_LOCATION($$);
    }
;

block_head:
    {
        $$ = new ast_block_head();
        YY_SET_LOCATION($$);
    }
    | block_head block_head_component {
        $$ = $1;
        $$->add_node($2);
        YY_SET_LOCATION($$);
    }
;

block_head_component:
    label_dec_part {
        $$ = $1;
    }
    | const_def_part {
        $$ = $1;
    }
    | type_def_part {
        $$ = $1;
    }
    | var_dec_part {
        $$ = $1;
    }
    | proc_func_dec {
        $$ = $1;
    }
    | proc_func_def {
        $$ = $1;
    }
;
