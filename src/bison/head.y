%locations
%define parse.error verbose

%code requires {
#include "ast/ast.h"

#define MAX_STR_LEN 1024
}

%{
#define YY_SET_LOCATION(dest) (dest)->set_location(yylloc.first_line, yylloc.first_column)

int yylex(void);
void yyerror(const char *s);
%}

// TODO Priority of each operator
