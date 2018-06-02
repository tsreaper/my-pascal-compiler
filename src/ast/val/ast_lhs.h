#ifndef MPC_AST_LHS_H
#define MPC_AST_LHS_H

#include "ast/ast_node.h"

class ast_lhs : public ast_value_node {
public:
    virtual llvm::Value *get_llvm_mem() const = 0;

    bool analyse() override;

    bool analyse(bool as_rhs);
};

#endif //MPC_AST_LHS_H
