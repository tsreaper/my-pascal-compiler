#ifndef MPC_GEN_CALL_H
#define MPC_GEN_CALL_H

#include <llvm/IR/Value.h>

#include "ast/ast_node.h"
#include "sem/func/sem_func.h"

namespace gen {
    llvm::Value *get_func_call(const func_sign &call_sign, const std::vector<ast_value_node *> &args);
}

#endif //MPC_GEN_CALL_H
