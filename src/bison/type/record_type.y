ast_record_type* record_type_node;

#union

%type <record_type_node> record_type record_type_body

%%

record_type:
    PAS_RECORD record_type_body PAS_END {
        $$ = $2;
    }
;

record_type_body:
    id_seq_with_type SYM_SEMICOLON {
        $$ = new ast_record_type();
        $$->add_seq($1);
        YY_SET_LOCATION($$);
    }
    | record_type_body id_seq_with_type SYM_SEMICOLON {
        $$ = $1;
        $$->add_seq($2);
    }
;
