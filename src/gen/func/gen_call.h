#ifndef MPC_GEN_CALL_H
#define MPC_GEN_CALL_H

#include <llvm/IR/Value.h>

#include "ast/ast_node.h"
#include "sem/func/sem_func.h"

namespace gen {
    llvm::Value *get_func_call(const func_sign &call_sign, const std::vector<ast_value_node *> &args);

    std::vector<llvm::Value *> get_converted_llvm_args(
            const func_sign &sign, const std::vector<ast_value_node *> &node_vec
    );
}

#endif //MPC_GEN_CALL_H
