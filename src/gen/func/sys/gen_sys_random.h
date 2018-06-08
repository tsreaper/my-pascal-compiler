#ifndef MPC_GEN_SYS_RANDOM_H
#define MPC_GEN_SYS_RANDOM_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_random(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_randomize(const std::vector<ast_value_node *> &args);
}

#endif //MPC_GEN_SYS_RANDOM_H
