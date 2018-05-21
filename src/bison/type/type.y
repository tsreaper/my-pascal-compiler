ast_type_def_seq* type_def_seq_node;
ast_type_def* type_def_node;

#union

%type <node> type_def_part
%type <type_def_seq_node> type_def_body
%type <type_def_node> type_def

%%

type_def_part:
    PAS_TYPE type_def_body {
        $$ = $2;
    }
    | {
        $$ = new ast_empty();
    }
;

type_def_body:
    type_def SYM_SEMICOLON {
        $$ = new ast_type_def_seq();
        $$->add_type_def($1);
        YY_SET_LOCATION($$);
    }
    | type_def_body type_def SYM_SEMICOLON {
        $$ = $1;
        $$->add_type_def($2);
        YY_SET_LOCATION($$);
    }
;

type_def:
    ID SYM_EQ ID {
        ast_id *child1 = new ast_id($1);
        YY_SET_LOCATION(child1);
        ast_id *child2 = new ast_id($3);
        YY_SET_LOCATION(child2);
        $$ = new ast_type_def(child1, child2);
        YY_SET_LOCATION($$);
    }
    | ID SYM_EQ builtin_type {
        ast_id *child = new ast_id($1);
        YY_SET_LOCATION(child);
        $$ = new ast_type_def(child, $3);
        YY_SET_LOCATION($$);
    }
    | ID SYM_EQ enum_type {
        ast_id *child = new ast_id($1);
        YY_SET_LOCATION(child);
        $$ = new ast_type_def(child, $3);
        YY_SET_LOCATION($$);
    }
    // TODO subrange type, structured type and pointer type
;
