#ifndef MPC_GEN_SYS_MIN_H
#define MPC_GEN_SYS_MIN_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_min_int_impl(llvm::Value *a, llvm::Value *b);
}

#endif //MPC_GEN_SYS_MIN_H
