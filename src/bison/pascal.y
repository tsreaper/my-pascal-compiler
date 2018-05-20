%locations
%define parse.error verbose

%code requires {
#include "ast/ast.h"

#define MAX_STR_LEN 128
}

%{
int yylex(void);
void yyerror(const char *s);
%}

%union {
    int tok;
    int num;
    double real;
    char str[MAX_STR_LEN];

    ast_node* node;
    ast_value_node* value_node;
    ast_const_def* const_def_node;
    ast_id* id_node;
}

%token PAS_AND PAS_ARRAY PAS_BEGIN PAS_CASE PAS_CONST PAS_DIV PAS_DO PAS_DOWNTO PAS_ELSE PAS_END
%token PAS_FILE PAS_FOR PAS_FUNCTION PAS_GOTO PAS_IF PAS_IN PAS_LABEL PAS_MOD PAS_NIL PAS_NOT PAS_OF PAS_OR
%token PAS_PACKED PAS_PROCEDURE PAS_PROGRAM PAS_RECORD PAS_REPEAT PAS_SET PAS_THEN PAS_TO PAS_TYPE
%token PAS_UNTIL PAS_VAR PAS_WHILE PAS_WITH

%token SYM_ADD SYM_SUB SYM_MUL SYM_DIV SYM_EQ SYM_LT SYM_GT SYM_LBRAC SYM_RBRAC SYM_PERIOD SYM_COMMA SYM_COLON
%token SYM_SEMICOLON SYM_CARET SYM_LPAREN SYM_RPAREN SYM_NE SYM_LE SYM_GE SYM_ASSIGN SYM_RANGE

%token ID INT REAL STR COMMENT_BEGIN COMMENT_END

%type <tok> PAS_AND PAS_ARRAY PAS_BEGIN PAS_CASE PAS_CONST PAS_DIV PAS_DO PAS_DOWNTO PAS_ELSE PAS_END
%type <tok> PAS_FILE PAS_FOR PAS_FUNCTION PAS_GOTO PAS_IF PAS_IN PAS_LABEL PAS_MOD PAS_NIL PAS_NOT PAS_OF PAS_OR
%type <tok> PAS_PACKED PAS_PROCEDURE PAS_PROGRAM PAS_RECORD PAS_REPEAT PAS_SET PAS_THEN PAS_TO PAS_TYPE
%type <tok> PAS_UNTIL PAS_VAR PAS_WHILE PAS_WITH

%type <tok> SYM_ADD SYM_SUB SYM_MUL SYM_DIV SYM_EQ SYM_LT SYM_GT SYM_LBRAC SYM_RBRAC SYM_PERIOD SYM_COMMA SYM_COLON
%type <tok> SYM_SEMICOLON SYM_CARET SYM_LPAREN SYM_RPAREN SYM_NE SYM_LE SYM_GE SYM_ASSIGN SYM_RANGE

%type <str> ID STR
%type <num> INT
%type <real> REAL
%type <tok> COMMENT_BEGIN COMMENT_END

%type <node> pascal

%type <node> label_dec_part label_dec_body

%type <node> const_def_part const_def_body
%type <const_def_node> const_def
%type <value_node> const

%type <node> type_def_part

%type <node> var_dec_part var_dec_body

%type <node> proc_func_dec_part

%type <node> compound_stm

// TODO Priority of each operator

%start pascal

%%

// ======= pascal =======

pascal:
    label_dec_part const_def_part type_def_part var_dec_part proc_func_dec_part compound_stm {
        ast_root = new ast_pascal($1, $2, $3, $4, $5, $6);
    }
;

// ======= label declaration =======

label_dec_part:
    PAS_LABEL label_dec_body {
        $$ = $2;
    }
    | {
        $$ = new ast_empty();
    }
;

label_dec_body:
    INT SYM_SEMICOLON {
        $$ = new ast_label_dec_part($1, new ast_empty());
    }
    | INT SYM_COMMA label_dec_body {
        $$ = new ast_label_dec_part($1, $3);
    }
;

// ======= constant definition =======

const_def_part:
    PAS_CONST const_def_body {
        $$ = $2;
    }
    | {
        $$ = new ast_empty();
    }
;

const_def_body:
    const_def SYM_SEMICOLON {
        $$ = new ast_const_def_part($1, new ast_empty());
    }
    | const_def SYM_SEMICOLON const_def_body {
        $$ = new ast_const_def_part($1, $3);
    }
;

const_def:
    ID SYM_EQ const {
        $$ = new ast_const_def(new ast_id($1), $3);
    }
;

const:
    INT {
        $$ = new ast_int($1);
    }
    | REAL {
        $$ = new ast_real($1);
    }
    | STR {
        $$ = new ast_str($1);
    }
    | ID {
        $$ = new ast_id($1);
    }
    | SYM_ADD ID {
        $$ = new ast_id($2);
    }
    | SYM_SUB ID {
        // TODO
        $$ = new ast_id($2);
        // $$ = new ast_sub(new ast_int(0), $2);
    }
;

// ======= type definition =======

// TODO add type definition part
type_def_part:
    {
        $$ = new ast_empty();
    }
;

// ======= variable definition =======

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

// ======= procedure and function declaration =======

// TODO

proc_func_dec_part:
    {
        $$ = new ast_empty();
    }
;

// ======= statement =======
// TODO

compound_stm:
    {
        $$ = new ast_empty();
    }
;

%%
