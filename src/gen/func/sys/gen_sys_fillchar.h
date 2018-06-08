#ifndef MPC_GEN_SYS_FILLCHAR_H
#define MPC_GEN_SYS_FILLCHAR_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_fillchar(const std::vector<ast_value_node *> &args);
}

#endif //MPC_GEN_SYS_FILLCHAR_H
