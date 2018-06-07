%option noyywrap yylineno caseless

%{
#include <cstring>

#include "pascal.y.hpp"

int yycolumn = 1;
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; \
yycolumn += yyleng;

void copy_str(char *str, int len) {
    int l = (len >= MAX_STR_LEN ? MAX_STR_LEN - 1 : len);
    strncpy(yylval.str, str, l);
    yylval.str[l] = 0;
}
%}

PAS_AND and
PAS_ARRAY array
PAS_BEGIN begin
PAS_BREAK break
PAS_CASE case
PAS_CONST const
PAS_CONTINUE continue
PAS_DEFAULT default
PAS_DIV div
PAS_DO do
PAS_DOWNTO downto
PAS_ELSE else
PAS_END end
PAS_EXIT exit
PAS_FILE file
PAS_FOR for
PAS_FORWARD forward
PAS_FUNCTION function
PAS_GOTO goto
PAS_IF if
PAS_IN in
PAS_LABEL label
PAS_MOD mod
PAS_NIL nil
PAS_NOT not
PAS_OF of
PAS_OR or
PAS_PACKED packed
PAS_PROCEDURE procedure
PAS_PROGRAM program
PAS_RECORD record
PAS_REPEAT repeat
PAS_SET set
PAS_THEN then
PAS_TO to
PAS_TYPE type
PAS_UNTIL until
PAS_VAR var
PAS_WHILE while
PAS_WITH with
PAS_XOR xor

SYM_ADD "+"
SYM_SUB "-"
SYM_MUL "*"
SYM_DIV "/"
SYM_EQ "="
SYM_LT "<"
SYM_GT ">"
SYM_LBRAC "["
SYM_RBRAC "]"
SYM_PERIOD "."
SYM_COMMA ","
SYM_COLON ":"
SYM_SEMICOLON ";"
SYM_AT "@"
SYM_CARET "^"
SYM_LPAREN "("
SYM_RPAREN ")"
SYM_NE "<>"
SYM_LE "<="
SYM_GE ">="
SYM_ASSIGN ":="
SYM_RANGE ".."

TYPE_INT integer|longint|int
TYPE_REAL real
TYPE_CHAR character|char
TYPE_BOOL boolean|bool
TYPE_STRING string

BOOL_TRUE true
BOOL_FALSE false

ID [a-zA-Z_][a-zA-Z0-9_]*

SIGN "+"|"-"
INT [0-9]+
REAL ([0-9]+\.[0-9]+|[0-9]+e{SIGN}?[0-9]+)

CHAR \'.\'
STR \'[^']*\'

COMMENT "{"[^\}]*"}"

%%

{PAS_AND} {
    return PAS_AND;
}
{PAS_ARRAY} {
    return PAS_ARRAY;
}
{PAS_BEGIN} {
    return PAS_BEGIN;
}
{PAS_BREAK} {
    return PAS_BREAK;
}
{PAS_CASE} {
    return PAS_CASE;
}
{PAS_CONST} {
    return PAS_CONST;
}
{PAS_CONTINUE} {
    return PAS_CONTINUE;
}
{PAS_DEFAULT} {
    return PAS_DEFAULT;
}
{PAS_DIV} {
    return PAS_DIV;
}
{PAS_DO} {
    return PAS_DO;
}
{PAS_DOWNTO} {
    return PAS_DOWNTO;
}
{PAS_ELSE} {
    return PAS_ELSE;
}
{PAS_END} {
    return PAS_END;
}
{PAS_EXIT} {
    return PAS_EXIT;
}
{PAS_FILE} {
    return PAS_FILE;
}
{PAS_FOR} {
    return PAS_FOR;
}
{PAS_FORWARD} {
    return PAS_FORWARD;
}
{PAS_FUNCTION} {
    return PAS_FUNCTION;
}
{PAS_GOTO} {
    return PAS_GOTO;
}
{PAS_IF} {
    return PAS_IF;
}
{PAS_IN} {
    return PAS_IN;
}
{PAS_LABEL} {
    return PAS_LABEL;
}
{PAS_MOD} {
    return PAS_MOD;
}
{PAS_NIL} {
    return PAS_NIL;
}
{PAS_NOT} {
    return PAS_NOT;
}
{PAS_OF} {
    return PAS_OF;
}
{PAS_OR} {
    return PAS_OR;
}
{PAS_PACKED} {
    return PAS_PACKED;
}
{PAS_PROCEDURE} {
    return PAS_PROCEDURE;
}
{PAS_PROGRAM} {
    return PAS_PROGRAM;
}
{PAS_RECORD} {
    return PAS_RECORD;
}
{PAS_REPEAT} {
    return PAS_REPEAT;
}
{PAS_SET} {
    return PAS_SET;
}
{PAS_THEN} {
    return PAS_THEN;
}
{PAS_TO} {
    return PAS_TO;
}
{PAS_TYPE} {
    return PAS_TYPE;
}
{PAS_UNTIL} {
    return PAS_UNTIL;
}
{PAS_VAR} {
    return PAS_VAR;
}
{PAS_WHILE} {
    return PAS_WHILE;
}
{PAS_WITH} {
    return PAS_WITH;
}
{PAS_XOR} {
    return PAS_XOR;
}

{SYM_ADD} {
    return SYM_ADD;
}
{SYM_SUB} {
    return SYM_SUB;
}
{SYM_MUL} {
    return SYM_MUL;
}
{SYM_DIV} {
    return SYM_DIV;
}
{SYM_EQ} {
    return SYM_EQ;
}
{SYM_LT} {
    return SYM_LT;
}
{SYM_GT} {
    return SYM_GT;
}
{SYM_LBRAC} {
    return SYM_LBRAC;
}
{SYM_RBRAC} {
    return SYM_RBRAC;
}
{SYM_PERIOD} {
    return SYM_PERIOD;
}
{SYM_COMMA} {
    return SYM_COMMA;
}
{SYM_COLON} {
    return SYM_COLON;
}
{SYM_SEMICOLON} {
    return SYM_SEMICOLON;
}
{SYM_AT} {
    return SYM_AT;
}
{SYM_CARET} {
    return SYM_CARET;
}
{SYM_LPAREN} {
    return SYM_LPAREN;
}
{SYM_RPAREN} {
    return SYM_RPAREN;
}
{SYM_NE} {
    return SYM_NE;
}
{SYM_LE} {
    return SYM_LE;
}
{SYM_GE} {
    return SYM_GE;
}
{SYM_ASSIGN} {
    return SYM_ASSIGN;
}
{SYM_RANGE} {
    return SYM_RANGE;
}

{TYPE_INT} {
    return TYPE_INT;
}
{TYPE_REAL} {
    return TYPE_REAL;
}
{TYPE_CHAR} {
    return TYPE_CHAR;
}
{TYPE_BOOL} {
    return TYPE_BOOL;
}
{TYPE_STRING} {
    return TYPE_STRING;
}

{BOOL_TRUE} {
    return BOOL_TRUE;
}
{BOOL_FALSE} {
    return BOOL_FALSE;
}

{ID} {
    copy_str(yytext, yyleng);
    return ID;
}

{INT} {
    yylval.num = atoi(yytext);
    return INT;
}
{REAL} {
    yylval.real = atof(yytext);
    return REAL;
}

{CHAR} {
    yylval.chr = yytext[1];
    return CHAR;
}
{STR} {
    copy_str(yytext + 1, yyleng - 2);
    return STR;
}

{COMMENT} {}

\n|(\r\n) {
    yycolumn = 1;
}
" "|\t {}

. {
    printf("unknown character %d\n", (int) yytext[0]);
    return yytext[0];
}

%%

void yyerror(const char *s) {
    fprintf(stderr, "%s (at %d:%d)\n", s, yylloc.first_line, yylloc.first_column);
}
