ast_exit* exit_node;

#union

%type <exit_node> exit

%%

exit:
    PAS_EXIT {
        $$ = new ast_exit();
        YY_SET_LOCATION($$);
    }
;
