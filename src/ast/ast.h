#ifndef MY_PASCAL_AST_H
#define MY_PASCAL_AST_H

#include "ast/ast_node.h"
#include "ast/exp/ast_arith.h"
#include "ast/exp/ast_cmp.h"
#include "ast/exp/ast_logic.h"
#include "ast/func/ast_func.h"
#include "ast/id/ast_id.h"
#include "ast/label/ast_label.h"
#include "ast/program/ast_program.h"
#include "ast/program/ast_block.h"
#include "ast/type/ast_type.h"
#include "ast/type/ast_builtin_type.h"
#include "ast/type/ast_enum_type.h"
#include "ast/value/ast_const.h"
#include "ast/value/ast_literal.h"
#include "ast/value/ast_var.h"

extern ast_node *ast_root;

#endif //MY_PASCAL_AST_H
