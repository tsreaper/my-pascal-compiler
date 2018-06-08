#ifndef MPC_GEN_SYS_INC_DEC_H
#define MPC_GEN_SYS_INC_DEC_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_inc(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_dec(const std::vector<ast_value_node *> &args);
}

#endif //MPC_GEN_SYS_INC_DEC_H
