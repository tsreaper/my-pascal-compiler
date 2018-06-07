#ifndef MPC_GEN_STR_TYPE_H
#define MPC_GEN_STR_TYPE_H

#include <llvm/IR/DerivedTypes.h>

#include "ast/ast_node.h"
#include "sem/type/sem_type.h"

namespace gen {
    llvm::ArrayType *get_llvm_str_type(const sem_type &type);

    llvm::Value *gen_str_add(ast_value_node *node_l, ast_value_node *node_r);

    llvm::Value *gen_str_eq(ast_value_node *node_l, ast_value_node *node_r);

    llvm::Value *gen_str_ne(ast_value_node *node_l, ast_value_node *node_r);

    llvm::Value *gen_str_lt(ast_value_node *node_l, ast_value_node *node_r);

    llvm::Value *gen_str_gt(ast_value_node *node_l, ast_value_node *node_r);

    llvm::Value *gen_str_le(ast_value_node *node_l, ast_value_node *node_r);

    llvm::Value *gen_str_ge(ast_value_node *node_l, ast_value_node *node_r);
}

#endif //MPC_GEN_STR_TYPE_H
