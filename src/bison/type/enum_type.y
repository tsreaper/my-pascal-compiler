ast_enum_type* enum_type_node;

#union

%type <enum_type_node> enum_type

%%

enum_type:
    SYM_LPAREN id_seq SYM_RPAREN {
        $$ = new ast_enum_type($2);
        YY_SET_LOCATION($$);
    }
;
