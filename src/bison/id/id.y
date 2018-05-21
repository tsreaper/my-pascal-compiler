ast_id* id_node;

#union

%type <id_node> id

%%

id:
    ID {
        $$ = new ast_id($1);
        YY_SET_LOCATION($$);
    }
;
