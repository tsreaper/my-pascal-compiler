#ifndef MPC_GEN_SYS_MIN_H
#define MPC_GEN_SYS_MIN_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_min_int(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_min_int_impl(llvm::Value *a, llvm::Value *b);

    llvm::Value *gen_sys_max_int(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_max_int_impl(llvm::Value *a, llvm::Value *b);

    llvm::Value *gen_sys_min_real(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_min_real_impl(llvm::Value *a, llvm::Value *b);

    llvm::Value *gen_sys_max_real(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_max_real_impl(llvm::Value *a, llvm::Value *b);
}

#endif //MPC_GEN_SYS_MIN_H
