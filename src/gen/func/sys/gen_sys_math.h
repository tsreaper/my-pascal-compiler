#ifndef MPC_GEN_SYS_MATH_H
#define MPC_GEN_SYS_MATH_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_sqr(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_sqrt(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_exp(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_ln(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_sin(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_cos(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_tan(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_arcsin(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_arccos(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_arctan(const std::vector<ast_value_node *> &args);
}

#endif //MPC_GEN_SYS_MATH_H
