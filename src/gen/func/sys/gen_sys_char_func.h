#ifndef MPC_GEN_SYS_CHAR_FUNC_H
#define MPC_GEN_SYS_CHAR_FUNC_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    llvm::Value *gen_sys_chr(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_ord(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_succ(const std::vector<ast_value_node *> &args);

    llvm::Value *gen_sys_pred(const std::vector<ast_value_node *> &args);
}

#endif //MPC_GEN_SYS_CHAR_FUNC_H
