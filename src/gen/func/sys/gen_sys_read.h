#ifndef MPC_GEN_SYS_READ_H
#define MPC_GEN_SYS_READ_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_read(const std::vector<ast_value_node *> &args, bool new_line);
}

#endif //MPC_GEN_SYS_READ_H
