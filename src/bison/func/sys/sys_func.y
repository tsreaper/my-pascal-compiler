#union

%type <node> sys_func

%%

sys_func:
    sys_write {
        $$ = $1;
    }
    | sys_writeln {
        $$ = $1;
    }
    | sys_read {
        $$ = $1;
    }
;
