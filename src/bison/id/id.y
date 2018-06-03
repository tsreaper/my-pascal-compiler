ast_id* id_node;
ast_id_seq* id_seq_node;
ast_id_seq_with_type* id_seq_with_type_node;

#union

%type <id_node> id
%type <id_seq_node> id_seq
%type <id_seq_with_type_node> id_seq_with_type

%%

id_seq_with_type:
    id_seq SYM_COLON type {
        $$ = new ast_id_seq_with_type($1, $3);
        YY_SET_LOCATION($$);
    }
;

id_seq:
    id {
        $$ = new ast_id_seq();
        $$->add_id($1);
        YY_SET_LOCATION($$);
    }
    | id_seq SYM_COMMA id {
        $$ = $1;
        $$->add_id($3);
        YY_SET_LOCATION($$);
    }
;

id:
    ID {
        $$ = new ast_id($1);
        YY_SET_LOCATION($$);
    }
;
