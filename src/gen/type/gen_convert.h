#ifndef MPC_GEN_CONVERT_H
#define MPC_GEN_CONVERT_H

#include <vector>

#include <llvm/IR/Value.h>

#include "ast/ast_node.h"
#include "sem/type/sem_type.h"

namespace gen {
    llvm::Value *llvm_type_convert(const sem_type &dest_t, ast_value_node *node);

    std::vector<llvm::Value *> get_converted_llvm_args(
            const std::vector<sem_type> &dest_type_vec, const std::vector<ast_value_node *> &node_vec
    );
}

#endif //MPC_GEN_CONVERT_H
