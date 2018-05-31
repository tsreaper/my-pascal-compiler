#ifndef MPC_AST_H
#define MPC_AST_H

#include "ast/ast_node.h"
#include "ast/exp/ast_all_exps.h"
#include "ast/exp/ast_exp_seq.h"
#include "ast/func/ast_func_head.h"
#include "ast/func/ast_func_dec.h"
#include "ast/func/ast_func_def.h"
#include "ast/func/ast_call.h"
#include "ast/func/ast_exit.h"
#include "ast/func/sys/ast_all_sys_funcs.h"
#include "ast/label/ast_label.h"
#include "ast/program/ast_program.h"
#include "ast/program/ast_block.h"
#include "ast/stmt/ast_stmt.h"
#include "ast/stmt/ast_all_stmts.h"
#include "ast/type/ast_type.h"
#include "ast/type/ast_all_types.h"
#include "ast/val/ast_const.h"
#include "ast/val/ast_var.h"
#include "ast/val/ast_id.h"
#include "ast/val/literal/ast_all_literals.h"

extern ast_node *ast_root;

#endif //MPC_AST_H
