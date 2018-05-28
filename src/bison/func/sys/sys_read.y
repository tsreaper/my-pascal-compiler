ast_sys_read* sys_read_node;

#union

%type <sys_read_node> sys_read sys_read_has_param

%%

sys_read:
    SYS_READ SYM_LPAREN SYM_RPAREN {
        $$ = new ast_sys_read();
        YY_SET_LOCATION($$);
    }
    | sys_read_has_param SYM_RPAREN {
        $$ = $1;
    }
;

sys_read_has_param:
    SYS_READ SYM_LPAREN id {
        $$ = new ast_sys_read();
        $$->add_param($3);
        YY_SET_LOCATION($$);
    }
    | sys_read_has_param SYM_COMMA id {
        $$ = $1;
        $$->add_param($3);
        YY_SET_LOCATION($$);
    }
;
