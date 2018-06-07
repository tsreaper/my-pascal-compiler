#ifndef MPC_GEN_SYS_COPY_H
#define MPC_GEN_SYS_COPY_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_copy(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_copy_impl(
            llvm::Value *src_mem, llvm::Value *idx, llvm::Value *cnt, int dest_len, bool ret_mem = false
    );
}

#endif //MPC_GEN_SYS_COPY_H
