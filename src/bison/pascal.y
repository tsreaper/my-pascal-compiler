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

%union {
    int tok;
    int num;
    double real;
    char chr;
    char str[MAX_STR_LEN];

    ast_node* node;
    ast_type_node* type_node;
    ast_value_node* value_node;

    ast_label_dec_seq* label_dec_seq_node;

    ast_literal* literal_node;

    ast_const_def_seq* const_def_seq_node;
    ast_const_def* const_def_node;

    ast_builtin_type* builtin_type_node;

    ast_type_def_seq* type_def_seq_node;
    ast_type_def* type_def_node;
}

%token PAS_AND PAS_ARRAY PAS_BEGIN PAS_CASE PAS_CONST PAS_DIV PAS_DO PAS_DOWNTO PAS_ELSE PAS_END
%token PAS_FILE PAS_FOR PAS_FUNCTION PAS_GOTO PAS_IF PAS_IN PAS_LABEL PAS_MOD PAS_NIL PAS_NOT PAS_OF PAS_OR
%token PAS_PACKED PAS_PROCEDURE PAS_PROGRAM PAS_RECORD PAS_REPEAT PAS_SET PAS_THEN PAS_TO PAS_TYPE
%token PAS_UNTIL PAS_VAR PAS_WHILE PAS_WITH

%token SYM_ADD SYM_SUB SYM_MUL SYM_DIV SYM_EQ SYM_LT SYM_GT SYM_LBRAC SYM_RBRAC SYM_PERIOD SYM_COMMA SYM_COLON
%token SYM_SEMICOLON SYM_CARET SYM_LPAREN SYM_RPAREN SYM_NE SYM_LE SYM_GE SYM_ASSIGN SYM_RANGE

%token TYPE_INT TYPE_REAL TYPE_CHAR TYPE_BOOL

%token BOOL_TRUE BOOL_FALSE

%token ID INT REAL CHAR STR COMMENT_BEGIN COMMENT_END

%type <tok> PAS_AND PAS_ARRAY PAS_BEGIN PAS_CASE PAS_CONST PAS_DIV PAS_DO PAS_DOWNTO PAS_ELSE PAS_END
%type <tok> PAS_FILE PAS_FOR PAS_FUNCTION PAS_GOTO PAS_IF PAS_IN PAS_LABEL PAS_MOD PAS_NIL PAS_NOT PAS_OF PAS_OR
%type <tok> PAS_PACKED PAS_PROCEDURE PAS_PROGRAM PAS_RECORD PAS_REPEAT PAS_SET PAS_THEN PAS_TO PAS_TYPE
%type <tok> PAS_UNTIL PAS_VAR PAS_WHILE PAS_WITH

%type <tok> SYM_ADD SYM_SUB SYM_MUL SYM_DIV SYM_EQ SYM_LT SYM_GT SYM_LBRAC SYM_RBRAC SYM_PERIOD SYM_COMMA SYM_COLON
%type <tok> SYM_SEMICOLON SYM_CARET SYM_LPAREN SYM_RPAREN SYM_NE SYM_LE SYM_GE SYM_ASSIGN SYM_RANGE

%type <tok> TYPE_INT TYPE_REAL TYPE_CHAR TYPE_BOOL
%type <tok> BOOL_TRUE BOOL_FALSE

%type <str> ID STR
%type <num> INT
%type <real> REAL
%type <chr> CHAR
%type <tok> COMMENT_BEGIN COMMENT_END

%type <node> pascal

%type <node> label_dec_part
%type <label_dec_seq_node> label_dec_body;

%type <literal_node> literal

%type <node> const_def_part
%type <const_def_seq_node> const_def_body
%type <const_def_node> const_def
%type <value_node> const

%type <builtin_type_node> builtin_type

%type <node> type_def_part
%type <type_def_seq_node> type_def_body
%type <type_def_node> type_def

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
        ast_label_dec* child = new ast_label_dec($1);
        YY_SET_LOCATION(child);
        $$ = new ast_label_dec_seq();
        $$->add_label_dec(child);
        YY_SET_LOCATION($$);
    }
    | INT SYM_COMMA label_dec_body {
        ast_label_dec* child = new ast_label_dec($1);
        YY_SET_LOCATION(child);
        $$ = $3;
        $$->add_label_dec(child);
        YY_SET_LOCATION($$);
    }
;

// ======= literal =======
literal:
    INT {
        $$ = new ast_lit_int($1);
        YY_SET_LOCATION($$);
    }
    | REAL {
        $$ = new ast_lit_real($1);
        YY_SET_LOCATION($$);
    }
    | CHAR {
        $$ = new ast_lit_char($1);
        YY_SET_LOCATION($$);
    }
    | BOOL_TRUE {
        $$ = new ast_lit_bool(true);
        YY_SET_LOCATION($$);
    }
    | BOOL_FALSE {
        $$ = new ast_lit_bool(false);
        YY_SET_LOCATION($$);
    }
    | STR {
        $$ = new ast_lit_str($1);
        YY_SET_LOCATION($$);
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
        $$ = new ast_const_def_seq();
        $$->add_const_def($1);
        YY_SET_LOCATION($$);
    }
    | const_def SYM_SEMICOLON const_def_body {
        $$ = $3;
        $$->add_const_def($1);
        YY_SET_LOCATION($$);
    }
;

const_def:
    ID SYM_EQ const {
        $$ = new ast_const_def(new ast_id($1), $3);
        YY_SET_LOCATION($$);
    }
;

const:
    literal {
        $$ = $1;
    }
    | ID {
        $$ = new ast_id($1);
        YY_SET_LOCATION($$);
    }
    | SYM_ADD ID {
        $$ = new ast_id($2);
        YY_SET_LOCATION($$);
    }
    | SYM_SUB ID {
        // TODO
        $$ = new ast_id($2);
        YY_SET_LOCATION($$);
        // $$ = new ast_sub(new ast_int(0), $2);
    }
;

// ======= builtin type =======
builtin_type:
    TYPE_INT {
        $$ = new ast_bti_int();
        YY_SET_LOCATION($$);
    }
    | TYPE_REAL {
        $$ = new ast_bti_real();
        YY_SET_LOCATION($$);
    }
    | TYPE_CHAR {
        $$ = new ast_bti_char();
        YY_SET_LOCATION($$);
    }
    | TYPE_BOOL {
        $$ = new ast_bti_bool();
        YY_SET_LOCATION($$);
    }
;

// ======= type definition =======

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
    | type_def SYM_SEMICOLON type_def_body {
        $$ = $3;
        $$->add_type_def($1);
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
    // TODO ordinal type, structured type and pointer type
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
