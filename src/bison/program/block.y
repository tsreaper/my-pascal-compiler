ast_block_head* block_head_node;
ast_block* block_node;

#union

%type <node> global_block_head_component local_block_head_component
%type <block_head_node> global_block_head local_block_head
%type <block_node> global_block local_block

%%

global_block:
    global_block_head compound_stm {
        $$ = new ast_block($1, $2);
        YY_SET_LOCATION($$);
    }
;

global_block_head:
    {
        $$ = new ast_block_head();
        YY_SET_LOCATION($$);
    }
    | global_block_head global_block_head_component {
        $$ = $1;
        $$->add_node($2);
        YY_SET_LOCATION($$);
    }
;

global_block_head_component:
    local_block_head_component {
        $$ = $1;
    }
    | proc_func_dec {
        $$ = $1;
    }
    | proc_func_def {
        $$ = $1;
    }
;

local_block:
    local_block_head compound_stm {
        $$ = new ast_block($1, $2);
        YY_SET_LOCATION($$);
    }
;

local_block_head:
    {
        $$ = new ast_block_head();
        YY_SET_LOCATION($$);
    }
    | local_block_head local_block_head_component {
        $$ = $1;
        $$->add_node($2);
        YY_SET_LOCATION($$);
    }
;

local_block_head_component:
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
;
