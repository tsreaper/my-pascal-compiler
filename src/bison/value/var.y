#union

%type <node> var_dec_part var_dec_body

%%

var_dec_part:
    PAS_VAR var_dec_body {
        $$ = $2;
    }
    | {
        $$ = new ast_empty();
    }
;

// TODO add variable declaration body
var_dec_body:
    {
        $$ = new ast_empty();
    }
;
