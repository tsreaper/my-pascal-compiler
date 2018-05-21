ast_label_dec_seq* label_dec_seq_node;

#union

%type <node> label_dec_part
%type <label_dec_seq_node> label_dec_body;

%%

label_dec_part:
    PAS_LABEL label_dec_body SYM_SEMICOLON {
        $$ = $2;
    }
    | {
        $$ = new ast_empty();
    }
;

label_dec_body:
    INT {
        ast_label_dec* child = new ast_label_dec($1);
        YY_SET_LOCATION(child);
        $$ = new ast_label_dec_seq();
        $$->add_label_dec(child);
        YY_SET_LOCATION($$);
    }
    | label_dec_body SYM_COMMA INT {
        ast_label_dec* child = new ast_label_dec($3);
        YY_SET_LOCATION(child);
        $$ = $1;
        $$->add_label_dec(child);
        YY_SET_LOCATION($$);
    }
;
