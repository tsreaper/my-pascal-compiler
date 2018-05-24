#union

%type <type_node> logic_or logic_xor logic_and logic_not

%%

logic_or:
    logic_xor {
        $$ = $1;
    }
    | logic_or PAS_OR logic_xor {
        $$ = new ast_logic_or($1, $3);
        YY_SET_LOCATION($$);
    }
;

logic_xor:
    logic_and {
        $$ = $1;
    }
    | logic_xor PAS_XOR logic_and {
        $$ = new ast_logic_xor($1, $3);
        YY_SET_LOCATION($$);
    }
;

logic_and:
    logic_not {
        $$ = $1;
    }
    | logic_and PAS_AND logic_not {
        $$ = new ast_logic_and($1, $3);
        YY_SET_LOCATION($$);
    }
;

logic_not:
    cmp_eq {
        $$ = $1;
    }
    | PAS_NOT logic_not {
        $$ = new ast_logic_not($2);
        YY_SET_LOCATION($$);
    }
;
