ast_enum_type* enum_type_node;

#union

%type <enum_type_node> enum_type enum_type_body

%%

enum_type:
    SYM_LPAREN enum_type_body SYM_RPAREN {
        $$ = $2;
    }
;

enum_type_body:
    id {
        $$ = new ast_enum_type();
        $$->add_id($1);
        YY_SET_LOCATION($$);
    }
    | enum_type_body SYM_COMMA id {
        $$ = $1;
        $$->add_id($3);
        YY_SET_LOCATION($$);
    }
;
