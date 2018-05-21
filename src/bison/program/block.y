#union

%type <node> block

%start block

%%

block:
    label_dec_part const_def_part type_def_part var_dec_part proc_func_dec_part compound_stm {
        ast_root = new ast_pascal($1, $2, $3, $4, $5, $6);
    }
;
