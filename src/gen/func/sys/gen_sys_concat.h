#ifndef MPC_GEN_SYS_CONCAT_H
#define MPC_GEN_SYS_CONCAT_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_concat(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_concat_impl(const std::vector<llvm::Value *> &mem_vec, int dest_len);
}

#endif //MPC_GEN_SYS_CONCAT_H
