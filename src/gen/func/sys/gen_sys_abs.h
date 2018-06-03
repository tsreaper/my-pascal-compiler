#ifndef MPC_GEN_SYS_ABS_H
#define MPC_GEN_SYS_ABS_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_abs_int(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_abs_real(const std::vector<ast_value_node *> &args);
}

#endif //MPC_GEN_SYS_ABS_H
