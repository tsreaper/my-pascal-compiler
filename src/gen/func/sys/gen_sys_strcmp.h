#ifndef MPC_GEN_SYS_STRCMP_H
#define MPC_GEN_SYS_STRCMP_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_strcmp_impl(llvm::Value *mem_l, llvm::Value *mem_r);
}

#endif //MPC_GEN_SYS_STRCMP_H
