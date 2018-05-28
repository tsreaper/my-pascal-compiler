ast_sys_write* sys_write_node;

#union

%type <sys_write_node> sys_write sys_write_has_param
%type <sys_write_node> sys_writeln sys_writeln_has_param

%%

sys_write:
    SYS_WRITE SYM_LPAREN SYM_RPAREN {
        $$ = new ast_sys_write(false);
        YY_SET_LOCATION($$);
    }
    | sys_write_has_param SYM_RPAREN {
        $$ = $1;
    }
;

sys_write_has_param:
    SYS_WRITE SYM_LPAREN exp {
        $$ = new ast_sys_write(false);
        $$->add_param($3);
        YY_SET_LOCATION($$);
    }
    | sys_write_has_param SYM_COMMA exp {
        $$ = $1;
        $$->add_param($3);
        YY_SET_LOCATION($$);
    }
;

sys_writeln:
    SYS_WRITELN SYM_LPAREN SYM_RPAREN {
        $$ = new ast_sys_write(true);
        YY_SET_LOCATION($$);
    }
    | sys_writeln_has_param SYM_RPAREN {
        $$ = $1;
    }
;

sys_writeln_has_param:
    SYS_WRITELN SYM_LPAREN exp {
        $$ = new ast_sys_write(true);
        $$->add_param($3);
        YY_SET_LOCATION($$);
    }
    | sys_writeln_has_param SYM_COMMA exp {
        $$ = $1;
        $$->add_param($3);
        YY_SET_LOCATION($$);
    }
;
